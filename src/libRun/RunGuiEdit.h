/*
*-------------------------------------------------------------------
* RunGuiEdit.h
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

//response to the GUI activites for toolbarCombine

#ifndef __RUN_GUI_EDIT_H__
#define __RUN_GUI_EDIT_H__

#include "libUtil/libUtil.h"
#include "libCfg/AppCfg.h"
#include "libDc/libDc.h"

#include "libGui/QtHeaders.h"
#include "libGui/GuiUtil.h"
#include "libGui/AppGui.h"
#include "libGui/MsgBox.h"
#include "libGui/ProgDialog.h"

#include "RunGuiDc.h"

namespace app {
	class LIBRUN_EXPORT RunGuiEdit : public QMainWindow
	{
		Q_OBJECT

	public:
		//all the threads share the same cfg located at only one physical address
		RunGuiEdit( RunGuiDcPtr &dc );
		~RunGuiEdit();

	public slots:
		//input group
		void on_pushButton_inputFile_clicked();
		void on_lineEdit_inputFile_edited(const QString &s);
		void on_pushButton_mp3File_clicked();
		void on_lineEdit_mp3File_edited(const QString &s);

		//output group
		void on_pushButton_outputFolder_clicked();
		void on_lineEdit_outputVideoFolder_edited(const QString &s);
		void on_lineEdit_outputUserDefineW_edited(const QString &s);
		void on_lineEdit_outputUserDefineH_edited(const QString &s);
		void on_comboBox_outputSocialMedia_currentIndexChanged(const int newIdx);

		//ctrl group
		void on_keyFrmSlider_valueChgd(int value);
		void on_keyFrmSlider_released();
		void on_keyFrmSlider_pressed();
		void on_keyFrmSlider_moved();

		void on_pushbuttonV_addSlider_clicked();
		void on_pushbuttonV_delSlider_clicked();
		void on_pushbuttonA_addSlider_clicked();
		void on_pushbuttonA_delSlider_clicked();

		void respns_play();
		void respns_pause();
		void respns_stop();
		void respns_next();
		void respns_previous();
		void respns_changeVolume(int v);
		void respns_changeMuting(bool flag);
		void respns_changePlayFrmRate(qreal r);

		//start/quit buttons	
		void on_pushButton_quit_clicked();
		void on_pushButton_start_clicked();

		uint32_t getPrevKeyFrmIdx();
		void respns_mgrHasErr(const QString &errMsg);
		void respns_warning_msg(const QString &msg);

	private:
		RunGuiDcPtr		m_dc;
		EditInputPtr	m_inWgt;
		OutputWgtPtr	m_outWgt;
		EditCtrlPtr		m_ctrlWgt;


		//not neccessary but just for convince coding
		AppCfg		*m_appCfg;
		AppGui		*m_appUi;

		CfgEditInput		m_inputCfg;
		CfgEditOutput		m_outputCfg;
		CfgEditCtrl			m_ctrlCfg;
	};
	typedef std::shared_ptr<RunGuiEdit>	RunGuiEditPtr;
}
#endif // CLIENTGUI_H

