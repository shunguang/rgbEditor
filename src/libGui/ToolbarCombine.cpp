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
#include "ToolbarCombine.h"
using namespace app;
using namespace std;
ToolbarCombine::ToolbarCombine( QGroupBox *parentGrp )
	:ToolbarBase(APP_TOOLBAR_COMBINE, parentGrp)
	, m_out(0)
	, m_in(0)
{
}


void ToolbarCombine::enableVisibility(const bool isVisiable)
{
}

void ToolbarCombine::retranslateUI()
{
	ToolbarBase::retranslateUI();
	m_in->retranslateUI();
	m_out->retranslateUI();
}

void ToolbarCombine::resizeUI(const bool isInit)
{
	if (!isActive()) return;
	
	//cal rect boxes
	calToolbarRects(isInit);
	ToolbarBase::resizeUI( isInit );

	m_grpBoxIn->setGeometry(m_rectGrpBoxIn);
	m_grpBoxOut->setGeometry(m_rectGrpBoxOut);

	m_in->resizeUI();
	m_out->resizeUI();
}

void ToolbarCombine::calToolbarRects(const bool isInit)
{
	if (!isActive()) {
		m_rectGrpBoxIn.setRect(0, 0, 0, 0);
		m_rectGrpBoxOut.setRect(0, 0, 0, 0);
		m_rectStartQuit.setRect(0, 0, 0, 0);
		return;
	}

	const int b = APP_GUI_BORDER_SIZE;
	const int w0 = m_grpBoxParent->width();
	const int h0 = m_grpBoxParent->height();

	//-------------------------------------------------------------------
	// [ grpBoxIn | GrpBoxOut | grpBoxStartQuit (define in Toobarbase)]  
	//-------------------------------------------------------------------

	const int w3 = 150;  //start/quit button grp width
	const int y = b;
	const int h = h0 - 2 * b;

	const int w12 = w0 - w3 - 2 * b;
	int w1 = w12 / 2;
	int w2 = w12 - w1 - 2*b;
	int x=b;
	m_rectGrpBoxIn.setRect(x, y, w1, h);
	
	x += w1 + b;
	m_rectGrpBoxOut.setRect(x, y, w2, h);

	x += w2 + b;
	m_rectStartQuit.setRect(x, y, w3, h);
}

void ToolbarCombine::createWidgets()
{
	ToolbarBase::createWidgets();
	m_grpBoxIn = new QGroupBox(m_grpBoxParent);
	m_grpBoxOut = new QGroupBox(m_grpBoxParent);

	m_in.reset(new CombineInput(m_grpBoxIn));
	m_in->createWidgets();

	m_out.reset(new OutputWgt(m_grpBoxOut) );
	m_out->createWidgets();
}

void ToolbarCombine::initSettings(AppCfgPtr &cfg)
{
	CfgCombineInput x;
	cfg->getInput(x);

	//QLabel      *m_vLabel[COMBINE_IN_LABEL_CNT];
	//QLineEdit	*m_vLineEdit[COMBINE_IN_LEDIT_CNT];
	//QPushButton *m_vPushButton[COMBINE_IN_PBUTTON_CNT];
	if (x.inputVideoFolder.length() > 0)
		m_in->m_vLineEdit[COMBINE_IN_LEDIT_INPUT_FOLDER]->setText(QString::fromStdString(x.inputVideoFolder));

	if (x.mp3File.length() > 0)
		m_in->m_vLineEdit[COMBINE_IN_LEDIT_MP3_PATH]->setText(QString::fromStdString(x.mp3File));

	m_in->m_sliderMp3->setValue( x.mp3Percentage );
	m_in->m_vLabel[COMBINE_IN_LABEL_SLIDER_CUR]->setText(QString::number(x.mp3Percentage));

	//QTableWidget *m_inputFileTable;

}
