/*
*-------------------------------------------------------------------
* MultiRngSliders.h
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
#ifndef __MULTI_RNG_SLIDERS__
#define __MULTI_RNG_SLIDERS__

#include "libUtil/libUtil.h"
#include <QtWidgets/QLabel>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>

namespace app {
	//assumption: any  range in physical world (with certain unit) can map to a uint32 model
	//for exampele
	// a: [0.25, 1.0] ---> s*([25,100]+b),		with s=0.01, b=0
	// b: [-0.25, 1.0] --->s*([0,125] + b)		with s=0.01, b=-25
	struct RngWorld {
		RngWorld(const uint32 l = 0, const uint32 u = 0) : lower(l), upper(u) {}

		uint32 width() const {
			return (upper - lower + 1);
		}
		uint32 lower;
		uint32 upper;
	};

	struct RngGraph {
		RngGraph(const int l = 0, const int u = 0) : lower(l), upper(u) {}

		bool  inclusiveIn(int x) {
			return (lower <= x) && (x <= upper);
		}

		bool  exclusiveIn(int x) {
			return (lower < x) && (x < upper);
		}

		float width() const {
			return (upper - lower);
		}

		std::string to_string(const std::string &msg = "") const {
			char buf[32];
			snprintf(buf, 32, "[%d,%d]", lower, upper);
			return msg + std::string(buf);
		}

		int lower;
		int upper;
	};


	struct RngSlider {
		//all the units are in graphic drawing panel
		RngSlider(int id_=0, int minVal_=0, int lowVal_=0, int upVal_=0, int maxVal_=0)
			: id(id_), minVal(minVal_), lowVal(lowVal_), upVal(upVal_), maxVal(maxVal_) {
			assert(check());
		}

		void setRange(const int minVal_, const int lowVal_, const int upVal_, const int maxVal_)
		{
			minVal = minVal_;
			lowVal = lowVal_;
			upVal = upVal_;
			maxVal = maxVal_;
		}

		int range() {
			return upVal - lowVal + 1;
		}
		bool valid() {
			return (upVal - lowVal + 1) > 0;
		}
		bool check() {
			return (minVal <= lowVal && lowVal <= upVal && upVal <= maxVal);
		}

		std::string to_string(const std::string &msg = "") const {
			char buf[128];
			snprintf(buf, 128, "id=%d, [%d,%d,%d,%d]", id, minVal, lowVal, upVal, maxVal);
			return msg + std::string(buf);
		}

		int id;				//debug purpose
		int lowVal, upVal;  //actual range values
		int minVal, maxVal; //potential boundary
	};
	typedef std::shared_ptr<RngSlider> RngSliderPtr;

	RngGraph rngW2G(const RngWorld &w, float scale_w2g);
	RngWorld rngG2W(const RngGraph &w, float scale_w2g);

	struct MultiRngSliders : public QLabel {
		Q_OBJECT
	public:
		MultiRngSliders(QWidget* aParent = 0, const std::string &name = "");

		//initial by ranges in world unit
		void reset(const RngWorld &worldBoundary = RngWorld(0,100) );
		void reset(const RngWorld &worldBoundary, const std::vector<RngWorld> &vRngs);

		//the following accesses the <m_currGroup>
		void getRngs(std::vector<RngWorld> &v); //get back the ranges in world unit
		bool insertByCenter(const float xWorld);   //add one if it is not in
		void removeCurrent();

		int setGeometry(QRect &r) {
			return setGeometry(r.x(), r.y(), r.width(), r.height());
		}

		virtual int setGeometry(int x, int y, int w, int h) {
			QLabel::setGeometry(x, y, w, h);
			m_lastRect.setTop(1);
			m_lastRect.setBottom(h - 2);
			m_tmpRect.setTop(1);
			m_tmpRect.setBottom(h - 2);
			return 0;
		}

	signals:
		void sigWarningMsg(const QString &msg);

	protected:
		void mousePressEvent(QMouseEvent *event) override;
		void mouseMoveEvent(QMouseEvent *event) override;
		void mouseReleaseEvent(QMouseEvent *event) override;
		void drawRectDuringMouseMove(const int xEnd, const bool isMouseRealsed = false);
		void drawRect_xor(const RngSliderPtr &sld, const QColor &pen);

		//void paintEvent(QPaintEvent *event);
		bool findNewNeighbors(const int x, std::list<RngSliderPtr>::iterator &itL, std::list<RngSliderPtr>::iterator &itR);
		std::list<RngSliderPtr>::iterator locateExistRange(const int x);

		//given pixel location <x>, find its nearest rangeSlider and set it as m_currSlider
		void updateCurrSlider(const int x);
		void setMouseMovingRng();
		void drawInitRect();
		void updateRelatedSliders();
		//void fillRects(const QColor &fillingColor, const QColor &borderColor);
		void resetLastRect(const std::list<RngSliderPtr>::iterator &it);

		inline bool isLast(const std::list<RngSliderPtr>::iterator &it) { return  std::distance(it, m_list.end()) == 1; }
		inline bool isFirst(const std::list<RngSliderPtr>::iterator &it) { return it != m_list.end() && it == m_list.begin(); }
		inline bool isSame(const std::list<RngSliderPtr>::iterator &it1, const std::list<RngSliderPtr>::iterator &it2) { return  it1 == it2; }
		inline bool isExist(const std::list<RngSliderPtr>::iterator &it) { return  it != m_list.end(); }
		inline bool isEnd(const std::list<RngSliderPtr>::iterator &it) { return  it == m_list.end(); }

		inline std::list<RngSliderPtr>::iterator next(const std::list<RngSliderPtr>::iterator &it) {
			if ( isEnd(it) || isLast(it) )
				return m_list.end();
		
			std::list<RngSliderPtr>::iterator itRet = it;
			return ++itRet;
		}

		inline std::list<RngSliderPtr>::iterator prev( const std::list<RngSliderPtr>::iterator &it) {
			if ( m_list.empty() || isFirst(it)  )
				return m_list.end();

			std::list<RngSliderPtr>::iterator itRet = it;
			return --itRet;
		}

		inline std::list<RngSliderPtr>::iterator first() {
			return m_list.begin();
		}

		inline std::list<RngSliderPtr>::iterator last() {
			if (m_list.empty()) return m_list.end();
			return --(m_list.end());
		}

	public:
		std::string				    m_name;		//group id
		std::list<RngSliderPtr>		m_list;     //list of rang sliders
		int		m_gMax, m_gMin;     //boundary of all sliders, mous can only move in [m_gMin, m_gMax]  

	protected:
		RngGraph		m_mouseMoveRng;

		std::list<RngSliderPtr>::iterator m_left;        //left of <current>
		std::list<RngSliderPtr>::iterator m_curr;        //curren
		std::list<RngSliderPtr>::iterator m_right;       //right of <current>

		char		m_currEdge;			//'L' or 'R' edge of current slider
		float       m_scale_w2g;		//world to graphic scale


		bool	m_isPressed;
		bool	m_isMoved;
		int		m_myPenWidth;
		QColor	m_myPenColor;
		QPoint	m_begPoint;
		QPoint  m_endPoint;
		QRect   m_lastRect;        //the last rect just drawed when pressing and moving mouse

		bool   m_needRepaint;


		QRect   m_tmpRect;

		const QColor            m_notCurrRectColor;
		const QColor            m_currRectColor;
		int						m_nextId;			//for debug purpose
	};
	typedef std::shared_ptr<MultiRngSliders> MultiRngSlidersPtr;
}
#endif
