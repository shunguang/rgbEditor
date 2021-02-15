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
	std::vector<std::string> vLineEditInitText = { "please choose or input an input file",  "please choose or input an output folder" };
	for (int i = 0; i < CUT_PBUTTON_CNT; ++i) {
		m_vLabelCut[i]->setText(QString::fromStdString(vLabelText[i]));
		m_vPushbuttonCut[i]->setText(QString::fromStdString("..."));
		m_vLineEditCut[i]->setText(QString::fromStdString(vLineEditInitText[i]));
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
	ToolbarBase::calToolbarRects(isInit);

	//cal Rect of <m_rectGrpBoxCut>
	const int h = APP_LINE_HEIGHT;
	const int b = APP_GUI_BORDER_SIZE;
	const int w0 = m_grpBoxParent->width() - m_startQuitRect.width() - 2*b;
	const int h0 = m_grpBoxParent->height() - 2 * b;
	m_rectGrpBoxCut.setRect(b, b, w0, h0);

	//cal rect of label, line edit and pushbutton
	int x = b, y = b;
	int w1 = 70, w2=0, w3=30;

	w2 = w0 - (w1 + w3 + 3 * b);   //lineEdit width
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
