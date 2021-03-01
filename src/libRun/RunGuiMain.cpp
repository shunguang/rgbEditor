/*
*-------------------------------------------------------------------
* RunGuiMain.cpp
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
#include "RunGuiMain.h"
using namespace std;
using namespace app;

RunGuiMain::RunGuiMain(AppCfgPtr &cfg, QWidget *parent)
	: m_cfg(cfg)
	, m_ui(new AppGui())
	, m_dc(NULL)
	, m_combineTask(NULL)
	, m_cutTask(NULL)
{
	m_dc.reset(new RunGuiDc(m_cfg, m_ui));

	//--------------------------------------------------------------------
	//1. start GUI 
	//--------------------------------------------------------------------
	m_ui->setupUi(this, m_cfg);


	//1.1 Menu item actions
	QObject::connect(m_ui->m_vToolbarAction[APP_TOOLBAR_CUT],	SIGNAL(triggered()), this, SLOT(on_actionCut_triggered()), MY_QT_CONN);
	QObject::connect(m_ui->m_vToolbarAction[APP_TOOLBAR_EDIT],	SIGNAL(triggered()), this, SLOT(on_actionEdit_triggered()), MY_QT_CONN);
	QObject::connect(m_ui->m_vToolbarAction[APP_TOOLBAR_COMBINE], SIGNAL(triggered()), this, SLOT(on_actionCombine_triggered()), MY_QT_CONN);
	QObject::connect(m_ui->m_actionExit, SIGNAL(triggered()), this, SLOT(on_actionExit_triggered()), MY_QT_CONN);

	QObject::connect(m_ui->m_actionAbout, SIGNAL(triggered()), this, SLOT(on_actionAbout_triggered()), MY_QT_CONN);
	QObject::connect(m_ui->m_actionHelp, SIGNAL(triggered()), this, SLOT(on_actionHelp_triggered()), MY_QT_CONN);

	//1.2 the start and quit buttons for all toolbar task items 
	QObject::connect(m_ui->m_vToolbarGui[APP_TOOLBAR_CUT]->m_startTaskButton, SIGNAL(clicked()), this, SLOT(on_pushButton_toolbarCutStart_clicked()), MY_QT_CONN);
	QObject::connect(m_ui->m_vToolbarGui[APP_TOOLBAR_EDIT]->m_startTaskButton, SIGNAL(clicked()), this, SLOT(on_pushButton_toolbarEditStart_clicked()), MY_QT_CONN);

	QObject::connect(m_ui->m_vToolbarGui[APP_TOOLBAR_CUT]->m_quitTaskButton, SIGNAL(clicked()), this, SLOT(on_pushButton_toolbarCutQuit_clicked()), MY_QT_CONN);
	QObject::connect(m_ui->m_vToolbarGui[APP_TOOLBAR_EDIT]->m_quitTaskButton, SIGNAL(clicked()), this, SLOT(on_pushButton_toolbarEditQuit_clicked()), MY_QT_CONN);

	//1.3 create Toolbar Combine task
	m_combineTask.reset(new RunGuiCombine(m_dc));

	//1.3 create Toolbar Cut task
	m_cutTask.reset(new RunGuiCut(m_dc));

	//2. other threads
	boost::this_thread::sleep(boost::posix_time::milliseconds(500));
	m_dc->m_guiReady = true;
}


RunGuiMain::~RunGuiMain()
{
}

void RunGuiMain::respns_toolbarSwitchTask( const AppToolbarTask newTask )
{
	m_cfg->setTask(newTask);
	m_ui->switchToolbarTaskTo(newTask );
}

void RunGuiMain::respns_toolbarStartTask(const AppToolbarTask newTask)
{
}
void RunGuiMain::respns_toolbarQuitTask(const AppToolbarTask newTask)
{
	m_cfg->setTask(APP_TOOLBAR_UNKN);
	m_ui->switchToolbarTaskTo(APP_TOOLBAR_UNKN);
}


void RunGuiMain::on_actionHelp_triggered()
{
	std::vector<std::string> v;

	v.push_back("=== Auto Clip Cut ===");
	v.push_back("line1");
	v.push_back("L2 ...");
	v.push_back("L3 ...");
	v.push_back("L4 ...");
	v.push_back("L5 ...");

	std::string s = "\n";
	for (int i = 0; i < v.size(); ++i) {
		s += v[i] + "\n";
	}

	QMessageBox::information(this, POPUP_MSG_WIN_TITLE, QString::fromStdString(s));

}
void RunGuiMain::on_actionAbout_triggered()
{
	QMessageBox::information(this, POPUP_MSG_WIN_TITLE, "          Auto Clip Cut\n          Shunguang Wu 2018.         ");
}

void RunGuiMain::on_actionExit_triggered()
{

	std::shared_ptr<ProgDialog> progDlg(new ProgDialog(this, "Starting ...", 0, 0, 300, 100));
	progDlg->setProgress(50, "Reading configuration file!");

	progDlg->setProgress(100, "Reading configuration file!");

	progDlg->reset();
	progDlg->resize(200, 100);
	progDlg->resetWinTitle("Preparing Quit");

	dumpLog("RunGuiMain::on_actionExit_triggered()--B");

	progDlg->setProgress(50, "Trerminal internal threads ...");

#if 0
	//clear up 
	m_runMgr->forceAllWorkersQuit();
	m_mgrThread->forceThreadQuit();
	m_browseThread->forceThreadQuit();
#endif

	progDlg->setProgress(100, "Successfully clean up!");
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	QApplication::quit();
}


void RunGuiMain::closeEvent(QCloseEvent *event)
{
	QMessageBox::StandardButton resBtn = QMessageBox::question(this, tr(POPUP_MSG_WIN_TITLE),
		tr("Do you really want to close?\n"),
		QMessageBox::No | QMessageBox::Yes,
		QMessageBox::Yes);

	if (resBtn != QMessageBox::Yes) {
		event->ignore();
	}
	else {
		on_actionExit_triggered();
		//event->accept();
	}
}

