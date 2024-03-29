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

#ifndef __TOOLBAR_EDIT_H__
#define __TOOLBAR_EDIT_H__

#include "ToolbarBase.h"
#include "OutputWgt.h"
#include "EditInput.h"
#include "EditCtrl.h"

namespace app {
	class ToolbarEdit : public ToolbarBase
	{
	public:
		ToolbarEdit( QGroupBox *parentGrp );
		virtual void enableVisibility(const bool isVisiable);
		virtual void retranslateUI();
		virtual void createWidgets();
		virtual void resizeUI(const bool isInit);
		virtual void initSettings(AppCfgPtr &cfg);

	protected:
		virtual void calToolbarRects(const bool isInit);

	public:
		OutputWgtPtr			m_out;
		EditInputPtr			m_in;
		EditCtrlPtr				m_ctrl;


	protected:
		QGroupBox	*m_grpBoxOut;		//output grp
		QGroupBox	*m_grpBoxIn;		//input grp
		QGroupBox	*m_grpBoxCtrl;		//input grp

		//-------------------------------------------------------------------
		// [ grpBoxIn | GrpBoxOut | grpBoxStartQuit (define in Toobarbase)]  
		//-------------------------------------------------------------------
		QRect			m_rectGrpBoxIn;
		QRect			m_rectGrpBoxOut;
		QRect			m_rectGrpBoxCtrl;

	};
	typedef std::shared_ptr<ToolbarEdit>		ToolbarEditPtr;

}

#endif

