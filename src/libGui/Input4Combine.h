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

#ifndef __INPUT_4_COMBINE_H__
#define __INPUT_4_COMBINE_H__
#include "libCfg/AppCfg.h"
#include "libUtil/libUtil.h"
#include "GuiUtil.h"
#include "AppSlider.h"
namespace app {
	enum CombineInPushButton {
		COMBINE_IN_PBUTTON_BROWSE_FOLDER = 0,
		COMBINE_IN_PBUTTON_BROWSE_MP3_FILE=1,
		//---do not change the order from 2 to 7 --
		COMBINE_IN_PBUTTON_LOAD_ALL=2,
		COMBINE_IN_PBUTTON_REMOVE_ALL=3,
		COMBINE_IN_PBUTTON_APPEND_ONE=4,
		COMBINE_IN_PBUTTON_REMOVE_ONE=5,
		COMBINE_IN_PBUTTON_UP=6,
		COMBINE_IN_PBUTTON_DOWN=7,
		//---------keep order -----------
		COMBINE_IN_PBUTTON_CNT,
	};

	enum CombineInLineEdit {
		COMBINE_IN_LEDIT_INPUT_FOLDER = 0,
		COMBINE_IN_LEDIT_MP3_PATH,
		COMBINE_IN_LEDIT_CNT
	};

	enum CombineInLabel {
		COMBINE_IN_LABEL_VIDEO_FOLDER = 0,
		COMBINE_IN_LABEL_ADD_VIDEOS,
		COMBINE_IN_LABEL_MP3_FILE,
		COMBINE_IN_LABEL_MP3_PCT,
		COMBINE_IN_LABEL_SLIDER_MIN,
		COMBINE_IN_LABEL_SLIDER_MAX,
		COMBINE_IN_LABEL_SLIDER_CUR,
		COMBINE_IN_LABEL_CNT
	};

	class Input4Combine
	{
	public:
		Input4Combine( QGroupBox *parentGrp );
		virtual ~Input4Combine();

		virtual void retranslateUI();
		virtual void createWidgets();
		virtual void resizeUI();

		void getCurrentInputVideoFileName(int &idx, std::string &fname);
		void getInputVideoFiles(std::vector<std::string> &vFileNames);
		void appendAllInputVideos(const std::vector<std::string> &vFileNames);
		std::string  appendOneInputVideo(const std::string  &fileName);
		void removeAllInputVideos();
		void removeOneInputVideo(const int idx);
		void moveUpOrDown( const int step );
		void enableDisableButtons();
	protected:
		void resetRectToZeros();
		void calRectsOut();
		void setTextOut(const int languageId);

		QList<QTableWidgetItem*> takeRow(int row);
		void setRow(int row, const QList<QTableWidgetItem*>& rowItems);

	public:
		QGroupBox	*m_grpBoxParent;

		QLabel      *m_vLabel[COMBINE_IN_LABEL_CNT];
		QLineEdit	*m_vLineEdit[COMBINE_IN_LEDIT_CNT];
		QPushButton *m_vPushBotton[COMBINE_IN_PBUTTON_CNT];
		QSlider		*m_sliderMp3;
		QTableWidget *m_inputFileTable;

	protected:
		QRect		m_rectGrpBox;
		QRect		m_vRectLabel[COMBINE_IN_LABEL_CNT];
		QRect		m_vRectLineEdit[COMBINE_IN_LEDIT_CNT];
		QRect		m_vRectPushButton[COMBINE_IN_PBUTTON_CNT];
		QRect		m_rectSliderMp3;
		QRect		m_rectInputFileTable;

		std::string m_vTextLabel[COMBINE_IN_LABEL_CNT];
		std::string m_vTextLineEdit[COMBINE_IN_LEDIT_CNT];
		std::string m_vTextButton[COMBINE_IN_PBUTTON_CNT];
		std::string	m_textGrpBoxTitle;
		AppSlider	m_sliderMp3Prm;

		QStringList m_tableHeader;
	};

	typedef std::shared_ptr<Input4Combine>		Input4CombinePtr;
}

#endif

