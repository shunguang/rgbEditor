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
	const int h = APP_LINE_HEIGHT;
	const int b = APP_GUI_BORDER_SIZE;

	ToolbarBase::calToolbarRects( isInit );

	//-------------------------------------------------------------------
	// [ grpBoxIn | GrpBoxOut | grpBoxStartQuit (define in Toobarbase)]  
	//-------------------------------------------------------------------
	const int w0 = m_grpBoxParent->width() - m_startQuitRect.width() - 2 * b;
	const int h0 = m_grpBoxParent->height() - 2*b;
	int w1 = w0 / 2;
	int w2 = w0 - w1 - 2*b;

	m_rectGrpBoxIn.setRect(b, b, w1, h0);
	m_rectGrpBoxOut.setRect(b+w1+b, b, w2, h0);
}

void ToolbarCombine::createWidgets()
{
	ToolbarBase::createWidgets();
	m_grpBoxIn = new QGroupBox(m_grpBoxParent);
	m_grpBoxOut = new QGroupBox(m_grpBoxParent);

	m_in.reset(new Input4Combine(m_grpBoxIn));
	m_in->createWidgets();

	m_out.reset(new OutputGrp(m_grpBoxOut) );
	m_out->createWidgets();
}
