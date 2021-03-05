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
#include "ToolbarCut.h"
using namespace app;
using namespace std;
ToolbarCut::ToolbarCut( QGroupBox *parentGrp )
	:ToolbarBase(APP_TOOLBAR_CUT, parentGrp)
	, m_rectGrpBoxCut(0,0,0,0)
{
	m_vLineEditInitText.clear();
	m_vLineEditInitText.push_back(".");
	m_vLineEditInitText.push_back(".");
}

ToolbarCut::~ToolbarCut(){
}

void ToolbarCut::enableVisibility(const bool isVisiable)
{
}

void ToolbarCut::retranslateUI()
{
	ToolbarBase::retranslateUI();

	std::vector<std::string> vLabelText = { "Video File",  "Output folder" };
	for (int i = 0; i < CUT_PBUTTON_CNT; ++i) {
		m_vLabelCut[i]->setText(QString::fromStdString(vLabelText[i]));
		m_vPushbuttonCut[i]->setText(QString::fromStdString("..."));
		m_vLineEditCut[i]->setText(QString::fromStdString(m_vLineEditInitText[i]));
	}
}

void ToolbarCut::resizeUI(const bool isInit)
{
	if (!isActive()) return;
	calToolbarRects(isInit);

	ToolbarBase::resizeUI(isInit);

	m_grpBoxCut->setGeometry( m_rectGrpBoxCut );
	for (int i = 0; i < CUT_PBUTTON_CNT; ++i) {
		m_vLabelCut[i]->setGeometry(m_vRectLabelCut[i] );
		m_vLineEditCut[i]->setGeometry(m_vRectLineEditCut[i]);
		m_vPushbuttonCut[i]->setGeometry(m_vRectPushButtonCut[i]);
	}
}

void ToolbarCut::calToolbarRects(const bool isInit)
{
	if (!isActive()) {
		m_rectStartQuit.setRect(0, 0, 0, 0);
		m_rectGrpBoxCut.setRect(0, 0, 0, 0);
		return;
	}

	//-------------------------------------------------------------------
	// [ grpBoxCut grpBoxStartQuit (define in Toobarbase)]  
	//-------------------------------------------------------------------

	//cal Rect of <m_rectGrpBoxCut> and <m_rectStartQuit>
	const int b = APP_GUI_BORDER_SIZE;
	const int w0 = m_grpBoxParent->width();
	const int h0 = m_grpBoxParent->height();

	int x=b, y = b;
	int w2 = 150;  //start/quit button grp width
	int w1 = w0 - w2 - 2*b;
	int h = h0 - 2 * b;

	m_rectGrpBoxCut.setRect(x, y, w1, h);
	
	x += w1 + b;
	m_rectStartQuit.setRect(x, y, w2, h);

	//cal rect of label, line edit and pushbutton
	int w3 = 30;
	x = b; y = b;
	w1 = 70;
	w2 = w0 - (w1 + w3 + 3 * b);   //lineEdit width
	h = APP_LINE_HEIGHT;
	for (int i = 0; i < CUT_PBUTTON_CNT; ++i) {
		x = b;
		m_vRectLabelCut[i].setRect(x, y, w1, h);

		x += (w1 + b);
		m_vRectLineEditCut[i].setRect(x, y, w2, h);

		x += (w2 + b);
		m_vRectPushButtonCut[i].setRect(x, y, w3, h);

		//for the sencond line
		y = h0 / 2 + b;
	}
}

void ToolbarCut::createWidgets()
{
	ToolbarBase::createWidgets();

	m_grpBoxCut = new QGroupBox(m_grpBoxParent);

	for (int i = 0; i < CUT_PBUTTON_CNT; ++i) {
		m_vPushbuttonCut[i] = new QPushButton(m_grpBoxCut);
		m_vLineEditCut[i] = new QLineEdit(m_grpBoxCut);
		m_vLabelCut[i] = new QLabel(m_grpBoxCut);
	}
}

void ToolbarCut::initSettings(AppCfgPtr &cfg)
{

	CfgCutInput prmIn;
	CfgCutOutput prmOut;

	cfg->getInput(prmIn);
	cfg->getOutput(prmOut);

	m_vLineEditInitText.clear();
	m_vLineEditInitText.push_back(prmIn.inputVideoFilepath);
	m_vLineEditInitText.push_back(prmOut.outputVideoFolder);
}
