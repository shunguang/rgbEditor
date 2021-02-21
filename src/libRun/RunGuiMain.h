/*
*-------------------------------------------------------------------
* RunGuiMain.h
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
#ifndef __RUN_GUI_MAIN_H__
#define __RUN_GUI_MAIN_H__

#include "libUtil/libUtil.h"
#include "libCfg/AppCfg.h"
#include "libDc/libDc.h"

#include "libGui/QtHeaders.h"
#include "libGui/GuiUtil.h"
#include "libGui/AppGui.h"
#include "libGui/MsgBox.h"
#include "libGui/ProgDialog.h"

//#include "RunThread.h"
//#include "RunBrowseVideo.h"
//#include "RunMgr.h"
#include "RunGuiDc.h"
#include "RunGuiCombine.h"

namespace app {
	class LIBRUN_EXPORT RunGuiMain : public QMainWindow
	{
		Q_OBJECT
	public:
		//all the threads share the same cfg located at only one physical address
		RunGuiMain(AppCfgPtr &cfg, QWidget *parent = 0);
		~RunGuiMain();

	public slots:
		void on_actionExit_triggered();
		void on_actionHelp_triggered();
		void on_actionAbout_triggered();

		void on_actionCut_triggered()		{ respns_toolbarSwitchTask(APP_TOOLBAR_CUT); }
		void on_actionEdit_triggered()		{ respns_toolbarSwitchTask(APP_TOOLBAR_EDIT); }
		void on_actionCombine_triggered()	{ respns_toolbarSwitchTask(APP_TOOLBAR_COMBINE); }
		
		void on_pushButton_toolbarCutStart_clicked()	{ respns_toolbarStartTask(APP_TOOLBAR_CUT); }
		void on_pushButton_toolbarEditStart_clicked()	{ respns_toolbarStartTask(APP_TOOLBAR_EDIT); }
		void on_pushButton_toolbarCombineStart_clicked(){ respns_toolbarStartTask(APP_TOOLBAR_COMBINE); }

		void on_pushButton_toolbarCutQuit_clicked()		{ respns_toolbarQuitTask(APP_TOOLBAR_CUT);  }
		void on_pushButton_toolbarEditQuit_clicked()	{ respns_toolbarQuitTask(APP_TOOLBAR_EDIT); }
		void on_pushButton_toolbarCombineQuit_clicked() { respns_toolbarQuitTask(APP_TOOLBAR_COMBINE); }

		void respns_toolbarSwitchTask(const AppToolbarTask newTask);
		void respns_toolbarStartTask(const AppToolbarTask newTask);
		void respns_toolbarQuitTask(const AppToolbarTask newTask);

	private:
		virtual void closeEvent(QCloseEvent *event);

	private:
		AppCfgPtr			m_cfg;      //accessed by multi-threads, not nessary but for convinence purpose
		AppGuiPtr			m_ui;
		RunGuiDcPtr			m_dc;

		RunGuiCombinePtr	m_combineTask;
	};
}
#endif // CLIENTGUI_H

