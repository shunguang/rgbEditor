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

#ifndef __EDIT_INPUT_H__
#define __EDIT_INPUT_H__
#include "libCfg/AppCfg.h"
#include "libUtil/libUtil.h"
#include "GuiUtil.h"
#include "AppSlider.h"
namespace app {
	enum EditInPushButton {
		EDIT_IN_PBUTTON_BROWSE_VIDEO_FILE = 0,
		EDIT_IN_PBUTTON_BROWSE_MP3_FILE=1,
		EDIT_IN_PBUTTON_CNT,
	};

	enum EditInLineEdit {
		EDIT_IN_LEDIT_VIDEO_FILE = 0,
		EDIT_IN_LEDIT_MP3_FILE,
		EDIT_IN_LEDIT_CNT
	};

	enum EditInLabel {
		EDIT_IN_LABEL_VIDEO_FILE = 0,
		EDIT_IN_LABEL_MP3_FILE,
		EDIT_IN_LABEL_MP3_PCT,
		EDIT_IN_LABEL_SLIDER_MIN,
		EDIT_IN_LABEL_SLIDER_MAX,
		EDIT_IN_LABEL_SLIDER_CUR,
		EDIT_IN_LABEL_CNT
	};

	class EditInput
	{
	public:
		EditInput( QGroupBox *parentGrp );
		virtual ~EditInput();

		virtual void retranslateUI();
		virtual void createWidgets();
		virtual void resizeUI();
		void enabledAll( const bool f );
	protected:
		void resetRectToZeros();
		void calRectsOut();
		void setTextOut(const int languageId);
	public:
		QGroupBox	*m_grpBoxParent;

		QLabel      *m_vLabel[EDIT_IN_LABEL_CNT];
		QLineEdit	*m_vLineEdit[EDIT_IN_LEDIT_CNT];
		QPushButton *m_vPushButton[EDIT_IN_PBUTTON_CNT];
		QSlider		*m_sliderMp3;

	protected:
		QRect		m_rectGrpBox;
		QRect		m_vRectLabel[EDIT_IN_LABEL_CNT];
		QRect		m_vRectLineEdit[EDIT_IN_LEDIT_CNT];
		QRect		m_vRectPushButton[EDIT_IN_PBUTTON_CNT];
		QRect		m_rectSliderMp3;

		std::string m_vTextLabel[EDIT_IN_LABEL_CNT];
		std::string m_vTextLineEdit[EDIT_IN_LEDIT_CNT];
		std::string m_vTextButton[EDIT_IN_PBUTTON_CNT];
		std::string	m_textGrpBoxTitle;
		AppSlider	m_sliderMp3Prm;
	};

	typedef std::shared_ptr<EditInput>		EditInputPtr;
}

#endif

