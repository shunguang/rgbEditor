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

#ifndef __TOOLBAR_BASE_H__
#define __TOOLBAR_BASE_H__
#include "libCfg/AppCfg.h"
#include "libUtil/UtilFuncs.h"
#include "GuiUtil.h"

namespace app {
	class ToolbarBase
	{
	public:
		ToolbarBase( const AppToolbarTask t, QGroupBox *parentGrp );
		virtual ~ToolbarBase();

		virtual void enableVisibility(const bool isVisiable) = 0;
		virtual void retranslateUI();
		virtual void createWidgets();
		virtual void resizeUI(const bool isInit);
		virtual void initSettings(AppCfgPtr &cfg)=0;
	protected:
		virtual void calToolbarRects(const bool isInit);
		bool		 isActive();
	public:
		const AppToolbarTask	m_taskId;

		QGroupBox	*m_grpBoxParent;

		//all derived classes need the folloowing three
		QGroupBox	*m_grpBoxStartQuit;
		QPushButton	*m_startTaskButton;
		QPushButton	*m_quitTaskButton;

	protected:
		QRect		m_startQuitRect;

	};
	typedef std::shared_ptr<ToolbarBase>		ToolbarBasePtr;
}

#endif

