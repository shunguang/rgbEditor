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
#include "EditInput.h"
#include "AppSlider.h"

using namespace app;
using namespace std;
EditInput::EditInput(QGroupBox *parentGrp)
	: m_grpBoxParent(parentGrp)
{
	int languageId = 0;
	m_sliderMp3Prm.name="mp3 %";
	m_sliderMp3Prm.minVal=0;
	m_sliderMp3Prm.maxVal=100;
	m_sliderMp3Prm.step=1;
	m_sliderMp3Prm.curVal=100;

	setTextOut(languageId);
}

EditInput::~EditInput()
{
}

void EditInput::createWidgets()
{
	for (auto &e:m_vLabel) {
		e = new QLabel(m_grpBoxParent);
	}
	for (auto &e : m_vLineEdit) {
		e = new QLineEdit(m_grpBoxParent);
	}
	for (auto &e : m_vPushButton) {
		e = new QPushButton(m_grpBoxParent);
	}

	m_sliderMp3 = new QSlider(Qt::Horizontal, m_grpBoxParent);
	m_sliderMp3->setRange(0, 100);
	m_sliderMp3->setTickInterval(10);
}

void EditInput::resizeUI()
{
	calRectsOut();

	for (int i = 0; i < EDIT_IN_LABEL_CNT; ++i) {
		m_vLabel[i]->setGeometry(m_vRectLabel[i]);
	}
	for (int i = 0; i < EDIT_IN_LEDIT_CNT; ++i) {
		m_vLineEdit[i]->setGeometry(m_vRectLineEdit[i]);
	}
	for (int i = 0; i < EDIT_IN_PBUTTON_CNT; ++i) {
		m_vPushButton[i]->setGeometry(m_vRectPushButton[i]);
	}
	m_sliderMp3->setGeometry(m_rectSliderMp3);
}

void EditInput::retranslateUI()
{
	for (int i = 0; i < EDIT_IN_LABEL_CNT; ++i) {
		m_vLabel[i]->setText(QString::fromStdString(m_vTextLabel[i]));
	}

	for (int i = 0; i < EDIT_IN_LEDIT_CNT; ++i) {
		m_vLineEdit[i]->setPlaceholderText(QString::fromStdString(m_vTextLineEdit[i]));
	}

	for (int i = 0; i < EDIT_IN_PBUTTON_CNT; ++i) {
		m_vPushButton[i]->setText(QString::fromStdString(m_vTextButton[i]));
	}
	m_grpBoxParent->setTitle(QString::fromStdString(m_textGrpBoxTitle));
}


void EditInput::calRectsOut()
{
	const int h = APP_LINE_HEIGHT;
	const int b = APP_GUI_BORDER_SIZE;

	const int w0 = m_grpBoxParent->width();
	const int h0 = m_grpBoxParent->height();
	const int w1 = 100;  //left side button width
	const int w3 = 50;   //browse button
	const int w2 = w0 - (w1 + w3 + 4 * b);     //input file folder width

	resetRectToZeros();

	//line 1
	int x = b, y = 3*b;
	m_vRectLabel[EDIT_IN_LABEL_VIDEO_FILE].setRect(x,y,w1,h);
	x += (w1 + b);
	m_vRectLineEdit[EDIT_IN_LEDIT_VIDEO_FILE].setRect(x, y, w2, h);
	x += (w2 + b);
	m_vRectPushButton[EDIT_IN_PBUTTON_BROWSE_VIDEO_FILE].setRect(x, y, w3, h);

	//mp3
	y += (h + b);
	x = b;
	m_vRectLabel[EDIT_IN_LABEL_MP3_FILE].setRect(x, y, w1, h);
	x += (w1 + b);
	m_vRectLineEdit[EDIT_IN_LEDIT_MP3_FILE].setRect(x, y, w2, h);
	x += (w2 + b);
	m_vRectPushButton[EDIT_IN_PBUTTON_BROWSE_MP3_FILE].setRect(x, y, w3, h);

	//mp3 slider
	y += (h + b);
	int u1 = w1, u2=40, u3, u4 = 40, u5 = 40;
	u3 = w0 - (u1 + u2 + u4 + u5 + 6*b);
	x = b;
	m_vRectLabel[EDIT_IN_LABEL_MP3_PCT].setRect(x, y, u1, h);
	
	x += u1 + b;
	m_vRectLabel[EDIT_IN_LABEL_SLIDER_MIN].setRect(x, y, u2, h);
	
	x += u2 + b;
	m_rectSliderMp3.setRect(x, y, u3, h);
	
	x += u3 + b;
	m_vRectLabel[EDIT_IN_LABEL_SLIDER_MAX].setRect(x, y, u4, h);

	x += u4 + b;
	m_vRectLabel[EDIT_IN_LABEL_SLIDER_CUR].setRect(x, y, u5, h);
}

void EditInput::setTextOut(const int languageId)
{
	m_vTextLabel[EDIT_IN_LABEL_VIDEO_FILE] = "Video File";
	m_vTextLabel[EDIT_IN_LABEL_MP3_FILE] = "Add Mp3 File";
	m_vTextLabel[EDIT_IN_LABEL_MP3_PCT] = "Mp3 percentage";
	m_vTextLabel[EDIT_IN_LABEL_SLIDER_MIN] = std::to_string(m_sliderMp3Prm.minVal);
	m_vTextLabel[EDIT_IN_LABEL_SLIDER_MAX] = std::to_string(m_sliderMp3Prm.maxVal);
	m_vTextLabel[EDIT_IN_LABEL_SLIDER_CUR] = std::to_string(m_sliderMp3Prm.curVal);


	m_vTextButton[EDIT_IN_PBUTTON_BROWSE_VIDEO_FILE] = "Browse";
	m_vTextButton[EDIT_IN_PBUTTON_BROWSE_MP3_FILE] = "Browse";

	m_vTextLineEdit[EDIT_IN_LEDIT_VIDEO_FILE] = "please input or browse video file";
	m_vTextLineEdit[EDIT_IN_LEDIT_MP3_FILE] = "select an mp3 file if you want to change the sound";
	m_textGrpBoxTitle = "Input";
}

void EditInput::resetRectToZeros()
{
	for (QRect &r : m_vRectLabel) {
		r.setRect(0, 0, 0, 0);
	}

	for (QRect &r : m_vRectLineEdit) {
		r.setRect(0, 0,0,0);
	}

	for (QRect &r : m_vRectPushButton) {
		r.setRect(0, 0, 0, 0);
	}
}

void EditInput::enabledAll(const bool f)
{
	for (int i = 0; i <= EDIT_IN_PBUTTON_CNT; ++i) {
		m_vPushButton[i]->setEnabled(f);
	}
}
