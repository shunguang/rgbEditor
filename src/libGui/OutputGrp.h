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

#ifndef __OUTPUT_GRP_H__
#define __OUTPUT_GRP_H__
#include "libCfg/AppCfg.h"
#include "libUtil/libUtil.h"
#include "GuiUtil.h"
#include "videoSpec.h"

namespace app {
	enum OutPushButton {
		OUT_PBUTTON_BROWSE_FOLDER = 0,
		OUT_PBUTTON_CNT
	};

	enum OutComboBox {
		OUT_COMBOBOX_SOCIAL_MEDIA=0,
		OUT_COMBOBOX_FILE_TYPE,
		OUT_COMBOBOX_FPS,
		OUT_COMBOBOX_CNT
	};

	enum OutLineEdit {
		OUT_LINE_EDIT_FOLDER = 0,
		OUT_LINE_EDIT_INPUT_VIDEO_DIM,
		OUT_LINE_EDIT_INPUT_VIDEO_RATIO,
		OUT_LINE_EDIT_USER_DEF_DIM_W,
		OUT_LINE_EDIT_USER_DEF_DIM_H,
		OUT_LINE_EDIT_CNT
	};

	enum OutLabel {
		OUT_LABEL_FOLDER = 0,
		OUT_LABEL_MEDIA_TYPE,
		OUT_LABEL_FILE_TYPE,
		OUT_LABEL_FPS,
		OUT_LABEL_INPUT_VIDEO_DIM,
		OUT_LABEL_INPUT_VIDEO_RATIO,
		OUT_LABEL_HORIZONTAL,
		OUT_LABEL_1_TO_1,
		OUT_LABEL_VERTICAL,
		OUT_LABEL_USER_DEF_OUTPUT_DIM,
		OUT_LABEL_CNT
	};

	class OutputGrp
	{
	public:
		OutputGrp( QGroupBox *parentGrp );
		virtual ~OutputGrp();

		virtual void retranslateUI();
		virtual void createWidgets();
		virtual void resizeUI();

		//set the texts of horizontal, vertical and 1:1 output video size check boxes 
		//void setOutputVideoSizes(std::vector<ImgSize>vH, std::vector<ImgSize>vV, std::vector<ImgSize>v1To1);
		//void setInputVideoSzRation( const ImgSize &sz );

		void updateOutVideoSzCandiates( const int socialMediaIdx, const ImgSize &inputVideoSz  );
		void uncheckVideoSizeBoxes();
	protected:
		void resetRectToZeros();
		void calRectsOut();
		void setTextOut(const int languageId);
		void retranslateUI2();
		void setOutputVideoSizes();

	public:
		QGroupBox	*m_grpBoxParent;

		QLabel      *m_vLabelOut[OUT_LABEL_CNT];
		QLineEdit	*m_vLineEditOut[OUT_LINE_EDIT_CNT];
		QPushButton *m_vPushBottonOut[OUT_PBUTTON_CNT];
		QComboBox	*m_vComboBoxOut[OUT_COMBOBOX_CNT];
		
		QCheckBox	*m_vCheckBoxHorizontalSzOut[APP_MAX_VIDEO_SZ_ITEMS];
		QCheckBox	*m_vCheckBox1To1SzOut[APP_MAX_VIDEO_SZ_ITEMS];
		QCheckBox	*m_vCheckBoxVerticalSzOut[APP_MAX_VIDEO_SZ_ITEMS];


	protected:
		QRect		m_rectGrpBoxOut;
		QRect		m_vRectLabelOut[OUT_LABEL_CNT];
		QRect		m_vRectLineEditOut[OUT_LINE_EDIT_CNT];
		QRect		m_vRectPushButtonOut[OUT_PBUTTON_CNT];
		QRect		m_vRectComboBoxOut[OUT_COMBOBOX_CNT];
		QRect		m_vRectCheckBoxHorizontalSzOut[APP_MAX_VIDEO_SZ_ITEMS];
		QRect		m_vRectCheckBox1To1SzOut[APP_MAX_VIDEO_SZ_ITEMS];
		QRect		m_vRectCheckBoxVerticalSzOut[APP_MAX_VIDEO_SZ_ITEMS];

		std::string m_vTextLabelOut[OUT_LABEL_CNT];
		std::string m_vTextLineEditOut[OUT_LINE_EDIT_CNT];
		std::string m_vTextButtonOut[OUT_PBUTTON_CNT];
		std::string m_vTextComboBoxtOut[OUT_COMBOBOX_CNT];
		std::string m_vTextCheckBoxH[APP_MAX_VIDEO_SZ_ITEMS];
		std::string m_vTextCheckBox1To1[APP_MAX_VIDEO_SZ_ITEMS];
		std::string m_vTextCheckBoxV[APP_MAX_VIDEO_SZ_ITEMS];
		std::string	m_textGrpBoxTitle;

		std::vector<std::string> m_vSocailMediaType;
		std::vector<std::string> m_vOutputVideoFileType;
		std::vector<std::string> m_vOutputVideoFps;


		VideoSpecPtr			 m_videoSpec;	//hold all the video sizes for all kind of social medias
		AppSocialMedia_t		 m_smCurrType;				//current SocialMedia type

		int						 m_nCheckBoxH;
		int						 m_nCheckBoxV;
		int						 m_nCheckBox1To1;
		ImgSize					 m_inputVideoImgDim;
		float					 m_inputVideoImgRatio;
		ImgSize					 m_userDefOuputVideoImgDim;
	};

	typedef std::shared_ptr<OutputGrp>		OutputGrpPtr;
}

#endif

