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
#include "ToolbarEdit.h"
using namespace app;
using namespace std;
ToolbarEdit::ToolbarEdit( QGroupBox *parentGrp )
	:ToolbarBase(APP_TOOLBAR_EDIT, parentGrp)
	, m_out(0)
	, m_in(0)
	, m_ctrl(0)
{
}


void ToolbarEdit::enableVisibility(const bool isVisiable)
{
}

void ToolbarEdit::retranslateUI()
{
	ToolbarBase::retranslateUI();
	m_in->retranslateUI();
	m_out->retranslateUI();
	m_ctrl->retranslateUI();
}

void ToolbarEdit::resizeUI(const bool isInit)
{
	if (!isActive()) return;

	calToolbarRects(isInit);
	ToolbarBase::resizeUI(isInit);

	m_grpBoxIn->setGeometry(m_rectGrpBoxIn);
	m_grpBoxOut->setGeometry(m_rectGrpBoxOut);
	m_grpBoxCtrl->setGeometry(m_rectGrpBoxCtrl);

	m_in->resizeUI();
	m_out->resizeUI();
	m_ctrl->resizeUI();
}

void ToolbarEdit::calToolbarRects(const bool isInit)
{
	if (!isActive()) {
		m_rectGrpBoxCtrl.setRect(0, 0, 0, 0);
		m_rectGrpBoxIn.setRect(0, 0, 0, 0);
		m_rectGrpBoxOut.setRect(0, 0, 0, 0);
		m_rectStartQuit.setRect(0, 0, 0, 0);
		return;
	}

	const int b = APP_GUI_BORDER_SIZE;
	const int w0 = m_grpBoxParent->width();
	const int h0 = m_grpBoxParent->height();

	//ctrl group height, make sure consistant with its value set in AppGui::calRects(const bool isInit)
	const int hCtrl = 80;
	const int w3 = 150;		//start quit grup width
	int x = b, y = b;

	//-------------------------------------------------------------------
	// [                  grpBoxCtrl                                  ]
	// [ grpBoxIn | GrpBoxOut | grpBoxStartQuit (define in Toobarbase)]  
	//-------------------------------------------------------------------
	const int w = w0 - w3 - 2 * b;
	const int h = h0 - hCtrl - 4 * b;
	int w1 = w / 2;
	int w2 = w - w1 - 2 * b;

	m_rectGrpBoxCtrl.setRect(x,y,w0-2*b, hCtrl);
	y += hCtrl+b;
	m_rectGrpBoxIn.setRect(x, y, w1, h);
	x += w1 + b;
	m_rectGrpBoxOut.setRect(x, y, w2, h);
	x += w2 + b;
	m_rectStartQuit.setRect(x, y, w3, h);
}

void ToolbarEdit::createWidgets()
{
	ToolbarBase::createWidgets();

	m_grpBoxIn = new QGroupBox(m_grpBoxParent);
	m_grpBoxOut = new QGroupBox(m_grpBoxParent);
	m_grpBoxCtrl = new QGroupBox(m_grpBoxParent);

	m_in.reset(new EditInput(m_grpBoxIn));
	m_in->createWidgets();

	m_out.reset(new OutputWgt(m_grpBoxOut));
	m_out->createWidgets();

	m_ctrl.reset(new EditCtrl(m_grpBoxCtrl));
	m_ctrl->createWidgets();
}

void ToolbarEdit::initSettings(AppCfgPtr &cfg)
{
#if 0
	CfgCombineInput x;
	cfg->getInput(x);

	if (x.inputVideoFolder.length() > 0)
		m_in->m_vLineEdit[COMBINE_IN_LEDIT_INPUT_FOLDER]->setText(QString::fromStdString(x.inputVideoFolder));

	if (x.mp3File.length() > 0)
		m_in->m_vLineEdit[COMBINE_IN_LEDIT_MP3_PATH]->setText(QString::fromStdString(x.mp3File));

	m_in->m_sliderMp3->setValue(x.mp3Percentage);
	m_in->m_vLabel[COMBINE_IN_LABEL_SLIDER_CUR]->setText(QString::number(x.mp3Percentage));
#endif
}
