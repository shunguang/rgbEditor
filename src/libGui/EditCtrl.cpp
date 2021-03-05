/*
*-------------------------------------------------------------------
* AppGui.h
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
#include "EditCtrl.h"
#include "AppSlider.h"

using namespace app;
using namespace std;
EditCtrl::EditCtrl(QGroupBox *parentGrp)
	: m_grpBoxParent(parentGrp)
{
	int languageId = 0;

	m_sliderKeyFrmPrm.name="";
	m_sliderKeyFrmPrm.minVal=0;
	m_sliderKeyFrmPrm.maxVal=100;
	m_sliderKeyFrmPrm.step=1;
	m_sliderKeyFrmPrm.curVal=100;

	setTextOut(languageId);
}

EditCtrl::~EditCtrl()
{
}

void EditCtrl::createWidgets()
{
	for (auto &e:m_vLabel) {
		e = new QLabel(m_grpBoxParent);
	}
	for (auto &e : m_vPushButton) {
		e = new QPushButton(m_grpBoxParent);
	}

	m_sliderKeyFrm = new QSlider(Qt::Horizontal, m_grpBoxParent);
	m_sliderKeyFrm->setRange(0, 100);
	m_sliderKeyFrm->setTickInterval(1);
	m_sliderKeyFrm->setFocusPolicy(Qt::StrongFocus);
	m_sliderKeyFrm->setTickPosition(QSlider::TicksBothSides); //QSlider::TicksAbove

	m_mrsV = new MultiRngSliders(m_grpBoxParent, "mrsV");
	m_mrsV->setObjectName(QStringLiteral("mrsV"));
	m_mrsV->setEnabled(true);

	m_mrsA = new MultiRngSliders(m_grpBoxParent, "mrsA");
	m_mrsA->setObjectName(QStringLiteral("mrsA"));
	m_mrsA->setEnabled(true);


	m_playerCotrolgroup = new QGroupBox(m_grpBoxParent);
	m_playerCotrolgroup->setFlat(true);
	m_playerCotrolgroup->setStyleSheet("border:0;");
	m_player = new PlayerControls(m_playerCotrolgroup);
}

void EditCtrl::resizeUI()
{
	calRectsOut();

	for (int i = 0; i < EDIT_CTRL_LABEL_CNT; ++i) {
		m_vLabel[i]->setGeometry(m_vRectLabel[i]);
	}
	for (int i = 0; i < EDIT_CTRL_PBUTTON_CNT; ++i) {
		m_vPushButton[i]->setGeometry(m_vRectPushButton[i]);
	}
	m_sliderKeyFrm->setGeometry(m_rectSliderKeyFrm);

	m_mrsV->setGeometry(m_rectMrsV);
	m_mrsA->setGeometry(m_rectMrsA);
	m_playerCotrolgroup->setGeometry(m_rectPlayer);

	updateMRS_V();
	updateMRS_A();
}

void EditCtrl::retranslateUI()
{
	for (int i = 0; i < EDIT_CTRL_LABEL_CNT; ++i) {
		m_vLabel[i]->setText(QString::fromStdString(m_vTextLabel[i]));
	}

	for (int i = 0; i < EDIT_CTRL_PBUTTON_CNT; ++i) {
		m_vPushButton[i]->setText(QString::fromStdString(m_vTextButton[i]));
	}
}

void EditCtrl::calRectsOut()
{
	const int h = 15; // APP_LINE_HEIGHT;
	const int b = APP_GUI_BORDER_SIZE;

	const int w0 = m_grpBoxParent->width();
	const int h0 = m_grpBoxParent->height();
	const int wPlayer = 260;

	int w1 = 10;  //left side button width
	int w2 = w0 - (w1 + 3*b );     //input file folder width

	resetRectToZeros();
	//line 1: video Multi-range sliders
	int x = b, y = b;
	m_vRectLabel[EDIT_CTRL_LABEL_V].setRect(x,y,w1,h);
	x += (w1 + b);
	m_rectMrsV.setRect(x, y, w2, h);

	//line 2: key frame slider
	x = b;
	y += h + b;
	m_vRectLabel[EDIT_CTRL_LABEL_K].setRect(x, y, w1, h);
	x += (w1 + b);
	m_rectSliderKeyFrm.setRect(x, y, w2, h);

	//line 3: audio Multi-range sliders
	x = b; 
	y += h + b;
	m_vRectLabel[EDIT_CTRL_LABEL_A].setRect(x, y, w1, h);
	x += (w1 + b);
	m_rectMrsA.setRect(x, y, w2, h);

	//line 4: time stamp and player, buttons etc
	y += h + b;
	w1 = 100;   //time label
	x = b; 
	m_vRectLabel[EDIT_CTRL_LABEL_CURR_TIME].setRect(x, y, w1, h);

	x += (w1 + b);
	m_vRectLabel[EDIT_CTRL_LABEL_TOTAL_TIME].setRect(x, y, w1, h);

	x += (w1 + b);
	m_rectPlayer.setRect(x, y, wPlayer, h);

	w1 = 40;
	x += (wPlayer + b);
	for (int i = 0; i < EDIT_CTRL_PBUTTON_CNT; ++i) {
		m_vRectPushButton[i].setRect(x, y, w1, h);
		x += (w1 + b);
	}
}


void EditCtrl::setTextOut(const int languageId)
{
	m_vTextLabel[EDIT_CTRL_LABEL_V] = "V";
	m_vTextLabel[EDIT_CTRL_LABEL_K] = "K";
	m_vTextLabel[EDIT_CTRL_LABEL_A] = "A";
	m_vTextLabel[EDIT_CTRL_LABEL_CURR_TIME] =  "00:00:00.00";
	m_vTextLabel[EDIT_CTRL_LABEL_TOTAL_TIME] = "00:00:00.00";

	m_vTextButton[EDIT_CTRL_PBUTTON_ADD_V] = "V+";
	m_vTextButton[EDIT_CTRL_PBUTTON_RMV_V] = "V-";
	m_vTextButton[EDIT_CTRL_PBUTTON_ADD_A] = "A+";
	m_vTextButton[EDIT_CTRL_PBUTTON_RMV_A] = "A-";

}

void EditCtrl::resetRectToZeros()
{
	for (QRect &r : m_vRectLabel) {
		r.setRect(0, 0, 0, 0);
	}

	for (QRect &r : m_vRectPushButton) {
		r.setRect(0, 0, 0, 0);
	}

	m_rectMrsV.setRect(0, 0, 0, 0);
	m_rectMrsA.setRect(0, 0, 0, 0);
	m_rectSliderKeyFrm.setRect(0, 0, 0, 0);
	m_rectPlayer.setRect(0, 0, 0, 0);
}

void EditCtrl::enabledAll(const bool f)
{
	for (int i = 0; i <= EDIT_CTRL_PBUTTON_CNT; ++i) {
		m_vPushButton[i]->setEnabled(f);
	}
}

void EditCtrl::updateMRS_V(const RngWorld &boundary, const std::vector<RngWorld> &v)
{
	QImage img(m_mrsV->width(), m_mrsV->height(), QImage::Format_RGB888);
	img.fill(QColor(156,181,58));

	m_mrsV->setPixmap(QPixmap::fromImage(img));

	//for test <rngSliderMgr>purpose
	m_mrsV->reset(boundary, v);
}

void EditCtrl::updateMRS_A(const RngWorld &boundary, const std::vector<RngWorld> &v)
{
	QImage img(m_mrsA->width(), m_mrsA->height(), QImage::Format_RGB888);
	img.fill(QColor(156, 181, 58));

	m_mrsA->setPixmap(QPixmap::fromImage(img));
	//for test <rngSliderMgr>purpose
	m_mrsA->reset(boundary, v);
}
