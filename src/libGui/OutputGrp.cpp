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
#include "OutputGrp.h"
using namespace app;
using namespace std;
OutputGrp::OutputGrp(QGroupBox *parentGrp)
	: m_grpBoxParent(parentGrp)
	, m_smDefaultType(APP_SM_YOUTUBE)
	, m_smCurrType(APP_SM_YOUTUBE)
	, m_inputVideoImgDim(1920, 1080)
	, m_inputVideoImgRatio(1.7)
	, m_userDefOuputVideoImgDim(0,0)
{
	int languageId = 0;
	setTextOut( languageId );

	m_vOutputVideoFileType.push_back("mp4");
	m_vOutputVideoFileType.push_back("mov");
	m_vOutputVideoFileType.push_back("avi");

	m_vOutputVideoFps.push_back("25");
	m_vOutputVideoFps.push_back("10");
	m_vOutputVideoFps.push_back("30");

	setDefaultOutputVideoSizes(m_smDefaultType);
}

OutputGrp::~OutputGrp()
{
}

void OutputGrp::createWidgets()
{
	for (auto &e:m_vLabelOut) {
		e = new QLabel(m_grpBoxParent);
	}
	for (auto &e : m_vLineEditOut) {
		e = new QLineEdit(m_grpBoxParent);
	}
	for (auto &e : m_vPushBottonOut) {
		e = new QPushButton(m_grpBoxParent);
	}
	for (auto &e : m_vComboBoxOut) {
		e = new QComboBox(m_grpBoxParent);
	}
	for (auto &e : m_vCheckBoxVerticalSzOut) {
		e = new QCheckBox(m_grpBoxParent);
	}
	for (auto &e : m_vCheckBoxHorizontalSzOut) {
		e = new QCheckBox(m_grpBoxParent);
	}
	for (auto &e : m_vCheckBox1To1SzOut) {
		e = new QCheckBox(m_grpBoxParent);
	}
}

void OutputGrp::resizeUI()
{
	calRectsOut();

	for (int i = 0; i < OUT_LABEL_CNT; ++i) {
		m_vLabelOut[i]->setGeometry(m_vRectLabelOut[i]);
	}
	for (int i = 0; i < OUT_LINE_EDIT_CNT; ++i) {
		m_vLineEditOut[i]->setGeometry(m_vRectLineEditOut[i]);
	}
	for (int i = 0; i < OUT_PBUTTON_CNT; ++i) {
		m_vPushBottonOut[i]->setGeometry(m_vRectPushButtonOut[i]);
	}
	for (int i = 0; i < OUT_COMBOBOX_CNT; ++i) {
		m_vComboBoxOut[i]->setGeometry(m_vRectComboBoxOut[i]);
	}
	for (int i = 0; i < APP_MAX_VIDEO_SZ_ITEMS; ++i) {
		m_vCheckBoxHorizontalSzOut[i]->setGeometry(m_vRectCheckBoxHorizontalSzOut[i]);
		m_vCheckBoxVerticalSzOut[i]->setGeometry(m_vRectCheckBoxVerticalSzOut[i]);
		m_vCheckBox1To1SzOut[i]->setGeometry(m_vRectCheckBox1To1SzOut[i]);
	}
}

void OutputGrp::retranslateUI()
{
	for (int i = 0; i < OUT_LABEL_CNT; ++i) {
		m_vLabelOut[i]->setText(QString::fromStdString(m_vTextLabelOut[i]));
	}

	for (int i = 0; i < OUT_LINE_EDIT_CNT; ++i) {
		m_vLineEditOut[i]->setPlaceholderText(QString::fromStdString(m_vTextLineEditOut[i]));
	}
	m_vLineEditOut[OUT_LINE_EDIT_INPUT_VIDEO_DIM]->setEnabled(false);
	m_vLineEditOut[OUT_LINE_EDIT_INPUT_VIDEO_RATIO]->setEnabled(false);

	for (int i = 0; i < OUT_PBUTTON_CNT; ++i) {
		m_vPushBottonOut[i]->setText(QString::fromStdString(m_vTextButtonOut[i]));
	}
	retranslateUI2(m_smDefaultType);

	m_grpBoxParent->setTitle(QString::fromStdString(m_textGrpBoxTitle));

}

void OutputGrp::retranslateUI2(const AppSocialMedia_t  type )
{
	for (int i = 0; i < m_nCheckBoxH; ++i) {
		m_vCheckBoxHorizontalSzOut[i]->setText(QString::fromStdString(m_vTextCheckBoxH[i]) );
	}
	for (int i = 0; i < m_nCheckBox1To1; ++i) {
		m_vCheckBox1To1SzOut[i]->setText(QString::fromStdString(m_vTextCheckBox1To1[i]));
	}
	for (int i = 0; i < m_nCheckBoxV; ++i) {
		m_vCheckBoxVerticalSzOut[i]->setText(QString::fromStdString(m_vTextCheckBoxV[i]));
	}

	//social media 
	QComboBox *p = m_vComboBoxOut[OUT_COMBOBOX_SOCIAL_MEDIA];
	for (const string &s : m_vSocailMediaType) {
		p->addItem(QString::fromStdString(s));
	}
	p->setCurrentText(QString::fromStdString(m_vSocailMediaType[0]));
	p->setEnabled(true);

	//set video fmt comboboxes
	p = m_vComboBoxOut[OUT_COMBOBOX_FILE_TYPE];
	for (const string &s : m_vOutputVideoFileType) {
		p->addItem(QString::fromStdString(s));
	}
	p->setCurrentText(QString::fromStdString(m_vOutputVideoFileType[0]));
	p->setEnabled(true);

	//set video fps comboboxes
	p = m_vComboBoxOut[OUT_COMBOBOX_FPS];
	for (const string &s : m_vOutputVideoFps) {
		p->addItem(QString::fromStdString(s));
	}
	p->setCurrentText(QString::fromStdString(m_vOutputVideoFps[0]));
	p->setEnabled(true);
}

void OutputGrp::calRectsOut()
{
	const int h = APP_LINE_HEIGHT;
	const int b = APP_GUI_BORDER_SIZE;

	const int w0 = m_grpBoxParent->width();
	const int h0 = m_grpBoxParent->height();
	const int w1 = 80;
	const int w5 = w0 / 2;

	int x = b, y = 3*b, w3=50;
	int w2 = w0 - (w1 + w3 + 4 * b);

	appAssert(w2>200, "OutputGrp::calRectsOut(): w2 is too small!");

	resetRectToZeros();

	//line 1
	m_vRectLabelOut[OUT_LABEL_FOLDER].setRect(x,y,w1,h);
	x += (w1 + b);
	m_vRectLineEditOut[OUT_LINE_EDIT_FOLDER].setRect(x, y, w2, h);
	x += (w2 + b);
	m_vRectPushButtonOut[OUT_PBUTTON_BROWSE_FOLDER].setRect(x, y, w3, h);

	//line 2: social media comboBox
	x = b; y += (h + b);
	m_vRectLabelOut[OUT_LABEL_MEDIA_TYPE].setRect(x, y, w1, h);
	x += (w1 + b);
	m_vRectComboBoxOut[OUT_COMBOBOX_SOCIAL_MEDIA].setRect(x, y, w2+w3+b, h);

	//line 3: output file type and FPS comboBoxes
	x = b; y += (h + b);
	w2 = (w5 - w1 - 3 * b);
	m_vRectLabelOut[OUT_LABEL_FILE_TYPE].setRect(x, y, w1, h);
	x += (w1 + b);
	m_vRectComboBoxOut[OUT_COMBOBOX_FILE_TYPE].setRect(x, y, w2, h);

	x = w5 + b;
	m_vRectLabelOut[OUT_LABEL_FPS].setRect(x, y, w1, h);
	x += (w1 + b);
	m_vRectComboBoxOut[OUT_COMBOBOX_FPS].setRect(x, y, w2, h);

	//line 4: current input video size and ratio
	x = b; y += (h + b); 
	m_vRectLabelOut[OUT_LABEL_INPUT_VIDEO_DIM].setRect(x, y, w1, h);
	x += w1 + b; 
	w2 = w5 - (w1 + 3*b);
	m_vRectLineEditOut[OUT_LINE_EDIT_INPUT_VIDEO_DIM].setRect(x, y, w2, h);

	x = w5 + b;
	m_vRectLabelOut[OUT_LABEL_INPUT_VIDEO_RATIO].setRect(x, y, w1, h);
	x += (w1 + b); 
	w2 = w5 - (w1 + 3*b);
	m_vRectLineEditOut[OUT_LINE_EDIT_INPUT_VIDEO_RATIO].setRect(x, y, w2, h);

	//line 5: output size-ratio labels
	int w = w0 / 3 - 3 * b;
	x = b; y += (h + b);
	m_vRectLabelOut[OUT_LABEL_HORIZONTAL].setRect(x, y, w, h);
	x += (w + b); 
	const int x2 = x; //cloumn location remember it
	m_vRectLabelOut[OUT_LABEL_1_TO_1].setRect(x, y, w, h);
	x += (w + b); 
	const int x3 = x; //cloumn location remember it
	m_vRectLabelOut[OUT_LABEL_VERTICAL].setRect(x, y, w, h);

	//line [6, 6+APP_MAX_VIDEO_SZ_ITEMS): check box sizes
	int y0 = y;
	x = b;  y = y0 + (h + b);
	for (int i = 0; i < m_nCheckBoxH; ++i) {
		m_vRectCheckBoxHorizontalSzOut[i].setRect(x, y, w, h);
		y += (h + b);
	}

	x = x2;  y = y0 + (h + b);
	for (int i = 0; i < m_nCheckBox1To1; ++i) {
		m_vRectCheckBox1To1SzOut[i].setRect(x, y, w, h);
		y += (h + b);
	}

	x = x3;  y = y0 + (h + b);
	for (int i = 0; i < m_nCheckBoxV; ++i) {
		m_vRectCheckBoxVerticalSzOut[i].setRect(x, y, w1, h);
		y += (h + b);
	}

	//last line
	x = b;  w = 120;
	m_vRectLabelOut[OUT_LABEL_USER_DEF_OUTPUT_DIM].setRect(x, y, w, h);

	x = x2;
	m_vRectLineEditOut[OUT_LINE_EDIT_USER_DEF_DIM_W].setRect(x, y, w1, h);

	x += (w1 + b);
	m_vRectLineEditOut[OUT_LINE_EDIT_USER_DEF_DIM_H].setRect(x, y, w1, h);
}


void OutputGrp::setTextOut(const int languageId)
{
	m_vTextLabelOut[OUT_LABEL_FOLDER] = "Output Folder";
	m_vTextLabelOut[OUT_LABEL_MEDIA_TYPE] = "Social Media";
	m_vTextLabelOut[OUT_LABEL_FILE_TYPE] = "Video Format";
	m_vTextLabelOut[OUT_LABEL_FPS] = "Frame Rate";
	m_vTextLabelOut[OUT_LABEL_INPUT_VIDEO_DIM] = "Input Video Dim";
	m_vTextLabelOut[OUT_LABEL_INPUT_VIDEO_RATIO] = "W:H Ratio";
	m_vTextLabelOut[OUT_LABEL_HORIZONTAL]	= "Horizontal";
	m_vTextLabelOut[OUT_LABEL_1_TO_1]		= "1:1";
	m_vTextLabelOut[OUT_LABEL_VERTICAL]		= "Vertical";
	m_vTextLabelOut[OUT_LABEL_USER_DEF_OUTPUT_DIM] = "User Defined (W x H)";

	m_vTextButtonOut[OUT_PBUTTON_BROWSE_FOLDER] = "Browse";

	m_vTextLineEditOut[OUT_LINE_EDIT_FOLDER] = "please input or browse an output folder";
	m_vTextLineEditOut[OUT_LINE_EDIT_INPUT_VIDEO_DIM] = std::to_string(m_inputVideoImgDim.w) + " x " + std::to_string(m_inputVideoImgDim.h);
	m_vTextLineEditOut[OUT_LINE_EDIT_INPUT_VIDEO_RATIO] = std::to_string((float)m_inputVideoImgDim.w / (float)m_inputVideoImgDim.h);
	m_vTextLineEditOut[OUT_LINE_EDIT_USER_DEF_DIM_W] = std::to_string(m_userDefOuputVideoImgDim.w);
	m_vTextLineEditOut[OUT_LINE_EDIT_USER_DEF_DIM_H] = std::to_string(m_userDefOuputVideoImgDim.h);

	m_vSocailMediaType.push_back("WeChat");
	m_vSocailMediaType.push_back("YouTube");
	m_vSocailMediaType.push_back("TikTok");
	m_vSocailMediaType.push_back("Twitter");
	m_vSocailMediaType.push_back("Instagram");
	m_vSocailMediaType.push_back("Facebook");

	m_textGrpBoxTitle = "Output";
}

void OutputGrp::resetRectToZeros()
{
	for (QRect &r : m_vRectLabelOut) {
		r.setRect(0, 0, 0, 0);
	}

	for (QRect &r : m_vRectLineEditOut) {
		r.setRect(0, 0,0,0);
	}

	for (QRect &r : m_vRectPushButtonOut) {
		r.setRect(0, 0, 0, 0);
	}

	for (QRect &r : m_vRectComboBoxOut) {
		r.setRect(0, 0, 0, 0);
	}

	for (QRect &r : m_vRectCheckBoxVerticalSzOut) {
		r.setRect(0, 0, 0, 0);
	}

	for (QRect &r : m_vRectCheckBoxHorizontalSzOut) {
		r.setRect(0, 0, 0, 0);
	}

	for (QRect &r : m_vRectCheckBox1To1SzOut) {
		r.setRect(0, 0, 0, 0);
	}
}

void OutputGrp::setDefaultOutputVideoSizes(const AppSocialMedia_t  type)
{
	for (int i = 0; i < APP_MAX_VIDEO_SZ_ITEMS; ++i) {
		m_vTextCheckBoxV[i] = "";
		m_vTextCheckBoxH[i] = "";
		m_vTextCheckBox1To1[i] = "";
	}

	m_vTextCheckBoxH[0]		= "1920 x 1080";
	m_vTextCheckBoxH[1]		= "720x640";
	m_vTextCheckBoxH[2] 	= "640x480";

	m_vTextCheckBoxV[0] = "1080 x 1920";
	m_vTextCheckBoxV[1] = "640 x 720";
	m_vTextCheckBoxV[2] = "480 x 640";

	m_vTextCheckBox1To1[0] = "1080 x 1080";
	m_vTextCheckBox1To1[1] = "640 x 640";
	m_vTextCheckBox1To1[2] = "480 x 480";

	m_nCheckBoxH=3;
	m_nCheckBoxV=3;
	m_nCheckBox1To1=3;

}
