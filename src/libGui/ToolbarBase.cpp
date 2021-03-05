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
#include "ToolbarBase.h"
using namespace app;
using namespace std;
ToolbarBase::ToolbarBase(const AppToolbarTask t, QGroupBox *parentGrp )
	: m_taskId(t)
	, m_grpBoxParent(parentGrp)
	, m_rectStartQuit(0,0,0,0)
{
	appAssert(m_taskId >= 0 && m_taskId < APP_TOOLBAR_ITEM_CNT, "ToolbarBase::ToolbarBase(): invalid taskId");
}

ToolbarBase::~ToolbarBase()
{
}

void ToolbarBase::createWidgets()
{
	m_grpBoxStartQuit = new QGroupBox(m_grpBoxParent);
	m_startTaskButton = new QPushButton(m_grpBoxStartQuit);
	m_quitTaskButton = new QPushButton(m_grpBoxStartQuit);
}

void ToolbarBase::resizeUI(const bool isInit)
{
	const int h = APP_LINE_HEIGHT;
	const int b = APP_GUI_BORDER_SIZE;
	int w = m_rectStartQuit.width() - 2 * b;

	m_grpBoxStartQuit->setGeometry( m_rectStartQuit );
	m_startTaskButton->setGeometry(b, b, w, h);
	m_quitTaskButton->setGeometry(b, 2*b+h, w, h);
}

void ToolbarBase::retranslateUI()
{
	string s1 = "Start " + g_AppToolbarTaskName[m_taskId];
	string s2 = "Quit " + g_AppToolbarTaskName[m_taskId];
	m_startTaskButton->setText(QString::fromStdString(s1));
	m_quitTaskButton->setText(QString::fromStdString(s2));
}

void ToolbarBase::calToolbarRects(const bool isInit)
{
}

bool ToolbarBase::isActive()
{
	int w = m_grpBoxParent->width();
	int h = m_grpBoxParent->height();
	return ( w>0  && h>0 );
}
