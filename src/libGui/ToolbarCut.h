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

#ifndef __TOOLBAR_CUT_H__
#define __TOOLBAR_CUT_H__

#include "ToolbarBase.h"

namespace app {
	enum ToolbarCutPushbutton {
		CUT_PBUTTON_OPEN_INPUT_FILE = 0,
		CUT_PBUTTON_OPEN_OUTP_FOLDER,
		CUT_PBUTTON_CNT
	};

	class ToolbarCut : public ToolbarBase
	{
	public:
		ToolbarCut( QGroupBox *parentGrp );
		virtual ~ToolbarCut();

		virtual void enableVisibility(const bool isVisiable);
		virtual void retranslateUI();
		virtual void createWidgets();
		virtual void resizeUI(const bool isInit);
		virtual void initSettings(AppCfgPtr &cfg);

	protected:
		virtual void calToolbarRects(const bool isInit);

	public:
		QPushButton	*m_vPushbuttonCut[CUT_PBUTTON_CNT];
		QLineEdit	*m_vLineEditCut[CUT_PBUTTON_CNT];

	protected:
		QGroupBox	*m_grpBoxCut;
		QLabel		*m_vLabelCut[CUT_PBUTTON_CNT];

		//---------------------------------
		// [grpBoxCut | grpBoxStartQuit]
		//---------------------------------
		QRect		m_rectGrpBoxCut;
		QRect		m_vRectPushButtonCut[CUT_PBUTTON_CNT];
		QRect		m_vRectLineEditCut[CUT_PBUTTON_CNT];
		QRect		m_vRectLabelCut[CUT_PBUTTON_CNT];
		//QLineEdit	*m_vLineEdit[APP_LEDITOR_CNT];
		//QComboBox	*m_vComboBox[APP_CBOX_CNT];
		//PlayerControls		*player;

		//QSlider     *m_vSliderOut[OUT_SLIDER_CNT];
		//AppSlider	m_vSliderParam[OUT_SLIDER_CNT];

		std::vector<std::string> m_vLineEditInitText;
	};
	typedef std::shared_ptr<ToolbarCut>		ToolbarCutPtr;

}

#endif

