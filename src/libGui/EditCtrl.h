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

#ifndef __EDIT_CTRL_H__
#define __EDIT_CTRL_H__
#include "libCfg/AppCfg.h"
#include "libUtil/libUtil.h"
#include "GuiUtil.h"
#include "AppSlider.h"
#include "PlayerControls.h"
#include "MultiRngSliders.h"
namespace app {
	enum EditCtrlPushButton {
		EDIT_CTRL_PBUTTON_ADD_V = 0,    //add region to cut images
		EDIT_CTRL_PBUTTON_RMV_V,		//remove region to cut images
		EDIT_CTRL_PBUTTON_ADD_A,		//add region to slient audio
		EDIT_CTRL_PBUTTON_RMV_A,		//remove region to slient audio
		EDIT_CTRL_PBUTTON_CNT,
	};

	enum EditCtrlLabel {
		EDIT_CTRL_LABEL_V = 0,       //video
		EDIT_CTRL_LABEL_K,			 //key frm	
		EDIT_CTRL_LABEL_A,			 //audio
		EDIT_CTRL_LABEL_CURR_TIME,   //current time
		EDIT_CTRL_LABEL_TOTAL_TIME,	 //total time or duration
		EDIT_CTRL_LABEL_CNT
	};

	class EditCtrl
	{
	public:
		EditCtrl( QGroupBox *parentGrp );
		virtual ~EditCtrl();

		virtual void retranslateUI();
		virtual void createWidgets();
		virtual void resizeUI();
		void enabledAll( const bool f );

		void updateMRS_V(const RngWorld &boundary = RngWorld(0, 100), const std::vector<RngWorld> &v = std::vector<RngWorld>() );
		void updateMRS_A(const RngWorld &boundary = RngWorld(0, 100), const std::vector<RngWorld> &v = std::vector<RngWorld>() );

	protected:
		void resetRectToZeros();
		void calRectsOut();
		void setTextOut(const int languageId);
	public:
		QGroupBox		*m_grpBoxParent;
		QGroupBox		*m_playerCotrolgroup;

		MultiRngSliders *m_mrsV;		//for video
		QSlider			*m_sliderKeyFrm;
		MultiRngSliders *m_mrsA;		//for audio
		PlayerControls	*m_player;
		QPushButton		*m_vPushButton[EDIT_CTRL_PBUTTON_CNT];
		QLabel			*m_vLabel[EDIT_CTRL_LABEL_CNT];


	protected:

		//QRect		m_rectGrpBox;
		QRect		m_rectMrsV;
		QRect		m_rectMrsA;
		QRect		m_rectSliderKeyFrm;
		QRect		m_rectPlayer;
		QRect		m_vRectLabel[EDIT_CTRL_LABEL_CNT];
		QRect		m_vRectPushButton[EDIT_CTRL_PBUTTON_CNT];

		std::string m_vTextLabel[EDIT_CTRL_LABEL_CNT];
		std::string m_vTextButton[EDIT_CTRL_PBUTTON_CNT];
		AppSlider	m_sliderKeyFrmPrm;

	};

	typedef std::shared_ptr<EditCtrl>		EditCtrlPtr;
}

#endif

