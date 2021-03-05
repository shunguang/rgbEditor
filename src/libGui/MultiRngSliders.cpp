/*
*-------------------------------------------------------------------
* MultiRngSliders.cpp
* Copyright(c) 2019, The RgbVideoEditor Author (Shunguang Wu).
* All Rights Reserved.
* You may not use this file except in compliance with the License:
*      GNU GENERAL PUBLIC LICENSE (Version 3), 29 June 2007
*
* You may obtain a copy of the License at
*
*     https://www.gnu.org/licenses/gpl-3.0.en.html
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*-------------------------------------------------------------------
*/
#include "MultiRngSliders.h"

#define MIN_BOUNDARY_SPACE  2    //mini space between two sliders 

using namespace std;
using namespace app;

MultiRngSliders::MultiRngSliders(QWidget* aParent, const std::string &name)
	: QLabel(aParent)
	, m_name(name)
	, m_currEdge('L')
	, m_needRepaint(true)
	, m_notCurrRectColor(QColor(0xff, 0x00, 0xff))
	, m_currRectColor(QColor(0xff, 0xff, 0x00))
	, m_nextId(0)
{
}

void MultiRngSliders::reset(const RngWorld &worldBoundary)
{
	int g = this->width();
	m_scale_w2g = (double)g / (double)worldBoundary.width();

	//graph bundary
	m_gMax = m_scale_w2g* worldBoundary.upper - 1;
	m_gMin = m_scale_w2g* worldBoundary.lower + 1;

	m_list.clear();
}

//<v> is in order
void MultiRngSliders::reset(const RngWorld &worldBoundary, const std::vector<RngWorld> &vRngs )
{
	reset(worldBoundary);

	//[minVal, maxVal] boundaried for each range
	int minVal = m_gMin;
	int maxVal;
	int n = vRngs.size();
	for (int i = 0; i < n; ++i) {
		if (i == n - 1) { maxVal = m_gMax; }
		else { maxVal = (m_scale_w2g*vRngs[i + 1].lower) - MIN_BOUNDARY_SPACE; }

		RngGraph r = rngW2G(vRngs[i], m_scale_w2g);
		RngSliderPtr sld(new RngSlider(i, minVal, r.lower, r.upper, maxVal));
		m_list.push_back(sld);

		minVal = r.upper + MIN_BOUNDARY_SPACE;

		//cout << sld->to_string("init slider") << endl;
	}
	m_nextId = n;
	m_curr  = m_list.begin();
	m_left  = prev(m_curr);
	m_right = next(m_curr);

	drawInitRect();
	resetLastRect(m_left);
}

void MultiRngSliders::resetLastRect(const std::list<RngSliderPtr>::iterator &it)
{
	if ( !isExist(it) ) {
		return;
	}
	m_lastRect.setLeft( (*it)->lowVal );
	m_lastRect.setRight( (*it)->upVal );
}

void MultiRngSliders::getRngs(std::vector<RngWorld> &v)
{
	v.clear();
	for(const RngSliderPtr &s : m_list) {
		RngWorld r = rngG2W(RngGraph(s->lowVal, s->upVal), m_scale_w2g);
		v.push_back(r);
	}
}

bool MultiRngSliders::findNewNeighbors(const int x, std::list<RngSliderPtr>::iterator &itL, std::list<RngSliderPtr>::iterator &itR)
{
	itL = m_list.end();
	itR = m_list.end();
	if ( m_list.empty() ) {
		return true;
	}

	//check if <x> in the left of the 1st range
	std::list<RngSliderPtr>::iterator it1 = m_list.begin();
	if (x < (*it1)->lowVal) {
		itR = it1;
		return true;
	}

	//check if in the right of the last range
	std::list<RngSliderPtr>::iterator it2 =  last();
	if (x > (*it2)->upVal) {
		itL = it2;
		return true;
	}

	//check other
	std::list<RngSliderPtr>::iterator it = m_list.begin();
	for (it = it1; it != it2; ++it) {
		itL = it;
		itR = next(it);
		if (x > (*itL)->upVal && x < (*itR)->lowVal) {
			return true;
		}
	}
	return false;
}

bool MultiRngSliders::insertByCenter(const float xWorld)
{
	const int xc = round(m_scale_w2g * xWorld);
	
	std::list<RngSliderPtr>::iterator it = locateExistRange(xc);
	if ( isExist(it) ) {
		emit sigWarningMsg(QStringLiteral("Already in range [%1,%2]!").arg( (*it)->lowVal).arg((*it)->upVal));
		return false;
	}


	std::list<RngSliderPtr>::iterator itL, itR;
	bool found = findNewNeighbors(xc, itL, itR);
	if (!found) {
		//this should never be reached
		return false;
	}

	RngSlider *sL = isExist(itL) ? (itL->get()) : NULL;
	RngSlider *sR = isExist(itR) ? (itR->get()) : NULL;
	int minV, lowV, upV, maxV;
	if (sL &&  sR ) {	//insert in middle
		minV = sL->upVal + MIN_BOUNDARY_SPACE; 	maxV = sR->lowVal - MIN_BOUNDARY_SPACE;
	}
	else if (sL) {		//no right, insert at end
		minV = sL->upVal + MIN_BOUNDARY_SPACE; 	maxV = sL->maxVal;
	}
	else if (sR) {		//no left, insert at beging
		minV = sR->minVal; 	maxV = sR->lowVal - MIN_BOUNDARY_SPACE;
	}
	else {				//insert to an empty sliders 
		int w = this->width(); minV = 0; maxV = w-1;
	}

	if (maxV - minV < MIN_BOUNDARY_SPACE) {
		emit sigWarningMsg(QString("do not have enough space to insert!"));
		return false;
	}

	//if previous <m_curr> exist, recover it to <m_notCurrRectColor> 
	if (isExist(m_curr)) {
		drawRect_xor(*m_curr, m_currRectColor);
		drawRect_xor(*m_curr, m_notCurrRectColor);
	}

	//create an new item and insert into list
	appAssert(xc >= minV && maxV >= xc, "MultiRngSliders::insertByCenter(): wrong [minV, maxV]");
	int d = std::min<int>(xc - minV, maxV - xc)/2;
	if (d == 0) { //for the case xc==minV or xc==vaxV
		d = MIN_BOUNDARY_SPACE;
	}
	lowV = xc - d;
	if (lowV < minV) lowV = minV;

	upV = xc + d;
	if (upV > maxV ) upV = maxV;

	RngSliderPtr newX(new RngSlider(m_nextId, minV, lowV, upV, maxV));
	m_curr = m_list.insert(itR, newX);   //insert <newX> before <itR>
	m_nextId++;

	//update neiborhood max or min
	if ( sL ) {
		sL->maxVal = lowV - MIN_BOUNDARY_SPACE;
	}
	if ( sR ) {
		sR->minVal = upV + MIN_BOUNDARY_SPACE;
	}
	
	//update <m_curr>, <m_left>, and <m_right>
	//if( m_list.size()<2 )
	//	m_curr = m_list.begin();
	//else
	//	m_curr  = prev(itR);

	m_left  = prev(m_curr);
	m_right = next(m_curr);

	//draw the new insered and set it as <current slider
	drawRect_xor( *m_curr, m_currRectColor);

	return true;
}

std::list<RngSliderPtr>::iterator MultiRngSliders::locateExistRange(const int x)
{
	std::list<RngSliderPtr>::iterator it = m_list.begin();
	for (; it != m_list.end(); ++it) {
		if (x >= (*it)->lowVal && x <= (*it)->upVal) {
			return it;
		}
	}
	return m_list.end();
}

void MultiRngSliders::removeCurrent()
{
	if ( m_list.empty() ) {
		emit sigWarningMsg(QString("Already empty, cannot delete!"));
		return;
	}

	if (isExist(m_left) && isExist(m_right) ) {
		(*m_left)->maxVal  = (*m_curr)->maxVal;
		(*m_right)->minVal = (*m_curr)->minVal;
	}
	else if (isExist(m_left)) {  //no right, the current(deleted) one is the last one
		(*m_left)->maxVal = (*m_curr)->maxVal;
	}
	else if (isExist(m_right)) { //no left, the deleted one is the beging
		(*m_right)->minVal = (*m_curr)->minVal;
	}

	//3. remove <m_curr> in graphics
	drawRect_xor( *m_curr, m_currRectColor);

	//erase it
	m_list.erase(m_curr);

	//find the new <m_curr> and draw it
	if( isExist(m_right) )
		m_curr = m_right;
	else if ( isExist(m_left) )
		m_curr = m_left;
	else
		m_curr = m_list.end();

	m_left  = prev(m_curr);
	m_right = next(m_curr);

	if (isExist(m_curr)) {
		drawRect_xor(*m_curr, m_notCurrRectColor);
		drawRect_xor(*m_curr, m_currRectColor);
	}
}


//update <m_currEdge>, <m_curr>, <m_left>, and <m_right>
void MultiRngSliders::updateCurrSlider(const int x)
{
	if (m_list.size() < 1) {
		m_curr  = m_list.end();
		m_left  = m_list.end();
		m_right = m_list.end();
	}

	int d, dMin = INT_MAX;
	for ( std::list<RngSliderPtr>::iterator it = m_list.begin(); it != m_list.end(); ++it ) {
		const RngSlider *rs = it->get();
		d = std::min<int>(abs(rs->lowVal - x), abs(rs->upVal - x));
		if (d < dMin) {
			dMin = d;
			m_curr = it;
		}
		//printf("updateCurrSlider(): x=%d, %s, d=%d\n", x, rs->to_string().c_str(), d);
	}

	m_left  = prev(m_curr);
	m_right = next(m_curr);
	m_currEdge = 'R';
	if (abs( (*m_curr)->lowVal - x) < abs( (*m_curr)->upVal - x)) {
		m_currEdge = 'L';
	}
}

void MultiRngSliders::setMouseMovingRng()
{
	m_mouseMoveRng.lower = (*m_curr)->minVal;
	m_mouseMoveRng.upper = (*m_curr)->maxVal;
	//cout << m_mouseMoveRng.to_string("m_mouseMoveRng=") << endl;
}

void MultiRngSliders::mousePressEvent(QMouseEvent *event)
{
	if (m_list.size()==0) {
		return;
	}

	//qDebug() << "mouse pressed:"<< event->pos().x() << "," << event->pos().y();
	if (event->button() == Qt::LeftButton) {
		m_begPoint = event->pos();
		m_isPressed = true;
		m_isMoved = false;

		std::list<RngSliderPtr>::iterator prevCurr = m_curr;

		//update <m_curr>, <m_left>, <m_right>, and <m_currEdge>
		updateCurrSlider(m_begPoint.x());  

		//printf("====mousePressEvent(): oldCurrId=%d, newCurrId=%d, flag=%c, m_begPoint:(x=%d,y=%d)=====\n", (*oldCurr)->id, (*m_curr)->id, m_currEdge, m_begPoint.x(), m_begPoint.y());
		if ( m_curr != m_list.end() ) {
			if ( !isSame(prevCurr, m_curr) ) {
				//update color of  <prevCurr>
				drawRect_xor(*prevCurr, m_currRectColor);       //recover it bkg color
				drawRect_xor(*prevCurr, m_notCurrRectColor);    //draw new color

				//draw current with <m_currRectColor>
				drawRect_xor(*m_curr, m_notCurrRectColor);  //recover it bkg color
				drawRect_xor(*m_curr, m_currRectColor);     //draw new color
			}
#if 0
			if (m_left  != m_list.end()) { cout << (*m_left)->to_string("m_left") << endl; }
			if (m_curr  != m_list.end()) { cout << (*m_curr)->to_string("m_curr") << endl; }
			if (m_right != m_list.end()) { cout << (*m_right)->to_string("m_right") << endl; }
#endif

			setMouseMovingRng();
			m_lastRect.setLeft(  (*m_curr)->lowVal);
			m_lastRect.setRight( (*m_curr)->upVal);
		}
	}
}

void MultiRngSliders::mouseMoveEvent(QMouseEvent *event)
{
	//qDebug() << event->pos().x() << "," << event->pos().y();
	if ( m_list.size()<1 ) {
		return;
	}

	if ((event->buttons() & Qt::LeftButton) && m_isPressed) {
		m_endPoint = event->pos();
		int dx = abs(m_endPoint.x() - m_begPoint.x());
		const int &xEnd = m_endPoint.x();
		//printf("mouseMoveEvent(): m_endPoint(x=%d, y=%d), %s\n", m_endPoint.x(), m_endPoint.y(), m_mouseMoveRng.to_string("m_mouseMoveRng=").c_str());
		if (dx > 0 && m_mouseMoveRng.inclusiveIn(xEnd)) {
			m_isMoved = true;
			drawRectDuringMouseMove(xEnd, false);
		}
		else {
			_beep(2000, 1000);
		}
	}
}

void MultiRngSliders::mouseReleaseEvent(QMouseEvent *event)
{
	//qDebug() << "mouse released:" << event->pos().x() << "," << event->pos().y();
	if (m_list.size()<1) {
		return;
	}

#if 0		
	if (m_left !=m_list.end() ) { cout << m_left->to_string("AAA-mouseReleaseEvent(): left") << endl; }
	if (m_curr != m_list.end() ) { cout << m_curr->to_string("AAA-mouseReleaseEvent(): curr") << endl; }
	if (m_right != m_list.end() ) { cout << m_rigit->to_string("AAA-mouseReleaseEvent(): right") << endl; }
#endif

	if (event->button() == Qt::LeftButton && m_isPressed) {
		m_endPoint = event->pos();
		int xEnd = m_endPoint.x();
		
		if ( xEnd < m_mouseMoveRng.lower) xEnd = m_mouseMoveRng.lower;
		if ( xEnd > m_mouseMoveRng.upper) xEnd = m_mouseMoveRng.upper;
		int dx = abs(xEnd - m_begPoint.x());
		//printf("mouseReleaseEvent(): m_begPoint(x=%d,y=%d), m_endPoint(x=%d,y=%d), dx=%d\n", m_begPoint.x(), m_begPoint.y(), m_endPoint.x(), m_endPoint.y(), dx);
		if (dx > 0 && m_mouseMoveRng.inclusiveIn(xEnd)) {
			drawRectDuringMouseMove(xEnd, true);
		}
		updateRelatedSliders();
		m_isPressed = false;
#if 0		
		if (m_left != m_list.end())  { cout << m_left->to_string("BBB-mouseReleaseEvent(): left") << endl; }
		if (m_curr != m_list.end())  { cout << m_curr->to_string("BBB-mouseReleaseEvent(): curr") << endl; }
		if (m_right != m_list.end()) { cout << m_right->to_string("BBB-mouseReleaseEvent(): right") << endl; }
#endif
	}
}

void MultiRngSliders::updateRelatedSliders()
{
	int xL = m_lastRect.left();
	int xR = m_lastRect.right();
#if _DEBUG
	assert(xL < xR);
#endif
	(*m_curr)->lowVal = xL;
	(*m_curr)->upVal = xR;

	if ( isExist(m_left) ) {
		(*m_left)->maxVal = xL - MIN_BOUNDARY_SPACE;
	}
	if (isExist(m_right) ) {
		(*m_right)->minVal = xR + MIN_BOUNDARY_SPACE;
	}
}

//todo: remove <painter> to class varaibale, and only initialed once
void MultiRngSliders::drawRect_xor(const RngSliderPtr &sld, const QColor &pen)
{
	QPixmap *p = (QPixmap *)this->pixmap();
	if (p == 0 || sld == 0) {
		return;
	}
	m_tmpRect.setLeft(sld->lowVal);
	m_tmpRect.setRight(sld->upVal);

	QPainter painter(p);
	painter.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(pen);
	painter.drawRect(m_tmpRect);
	update();
}

void MultiRngSliders::drawRectDuringMouseMove(const int xEnd, const bool isMouseRealsed)
{
	int xL, xR;
	if (m_currEdge == 'L') {
		xL = xEnd;
		xR = (*m_curr)->upVal;  //original right edge
	}
	else {
		xL = (*m_curr)->lowVal; ////original left edge
		xR = xEnd;
	}
	if (abs(xR - xL) < 1) {
		return;
	}
	//cout<<m_curr->to_string("drawRect(): -- m_curr=")<<endl;
	//printf(" m_lastRect1=(L=%d,R=%d), xL=%d,xR=%d\n", m_lastRect.left(),  m_lastRect.right(), xL,xR);

	QPixmap *p = (QPixmap *)this->pixmap();
	if (p) {
		QPainter painter(p);
		painter.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
		painter.setRenderHint(QPainter::Antialiasing);
		painter.setPen(m_currRectColor);
		//erase the old one
		if (m_lastRect.width() > 0) {
			painter.drawRect(m_lastRect);
		}

		//update <m_lastRect>
		if (xL < xR) {
			m_lastRect.setLeft(xL);
			m_lastRect.setRight(xR);
		}
		else {
			m_lastRect.setLeft(xR);
			m_lastRect.setRight(xL);
		}
		//draw it
		painter.drawRect(m_lastRect);
		update();
	}
	//printf("drawRect(): m_lastRect=(L=%d,R=%d)-----end!\n", m_lastRect.left(), m_lastRect.right());
}

void MultiRngSliders::drawInitRect()
{
	//printf("%d,%d\n", this->width(), this->height());
	QPixmap *p = (QPixmap *)this->pixmap();
	if (p) {
		QPainter painter(p);
		painter.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
		painter.setRenderHint(QPainter::Antialiasing);

		std::list<RngSliderPtr>::iterator it = m_list.begin();
		for (; it != m_list.end(); ++it) {
			if ( it == m_curr) {
				painter.setPen(m_currRectColor);
			}
			else {
				painter.setPen(m_notCurrRectColor);
			}
			m_tmpRect.setLeft( (*it)->lowVal);
			m_tmpRect.setRight( (*it)->upVal);

			//draw it
			//printf("m_lastRect=(L=%d,R=%d)\n", m_lastRect.left(), m_lastRect.right());
			painter.drawRect(m_tmpRect);
		}
		update();
	}
}

RngGraph app::rngW2G(const RngWorld &w, float scale_w2g) 
{
	int L = round(w.lower * scale_w2g);
	int U = round(w.upper * scale_w2g);
	return RngGraph(L, U);
}
RngWorld app::rngG2W(const RngGraph &w, float scale_w2g) 
{
	uint32 L = round(w.lower / scale_w2g);
	uint32 U = round(w.upper / scale_w2g);
	return RngWorld(L, U);
}
