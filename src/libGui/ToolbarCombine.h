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

#ifndef __TOOLBAR_COMBINE_H__
#define __TOOLBAR_COMBINE_H__

#include "ToolbarBase.h"
#include "OutputWgt.h"
#include "CombineInput.h"
namespace app {
	enum OutSlider {
		OUT_SLIDER_MP3_PCT = 0,
		OUT_SLIDER_CNT
	};

	class ToolbarCombine : public ToolbarBase
	{
	public:
		ToolbarCombine( QGroupBox *parentGrp );

		virtual void enableVisibility(const bool isVisiable);
		virtual void retranslateUI();
		virtual void createWidgets();
		virtual void resizeUI(const bool isInit);
		virtual void initSettings(AppCfgPtr &cfg);

	protected:
		virtual void calToolbarRects(const bool isInit);

	public:
		OutputWgtPtr		m_out;
		CombineInputPtr		m_in;

	protected:
		QGroupBox	*m_grpBoxOut;		//output grp
		QGroupBox	*m_grpBoxIn;		//input grp

		//-------------------------------------------------------------------
		// [ grpBoxIn | GrpBoxOut | grpBoxStartQuit (define in Toobarbase)]  
		//-------------------------------------------------------------------
		QRect			m_rectGrpBoxIn; 
		QRect			m_rectGrpBoxOut;
	};

	typedef std::shared_ptr<ToolbarCombine>		ToolbarCombinePtr;

}

#endif

