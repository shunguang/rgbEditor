/*
*-------------------------------------------------------------------
* RunGuiCut.cpp
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
#include "RunGuiCut.h"
using namespace std;
using namespace app;

RunGuiCut::RunGuiCut(RunGuiDcPtr &dc)
	: m_dc(dc)
	, m_appCfg(dc->m_cfg.get())
	, m_appUi(dc->m_ui.get())
{
	//Toolbar combine
	m_cutWgts = dynamic_cast<ToolbarCut *> (m_appUi->m_vToolbarGui[APP_TOOLBAR_CUT].get());

	QObject::connect(m_cutWgts->m_vPushbuttonCut[CUT_PBUTTON_OPEN_INPUT_FILE], SIGNAL(clicked()), this, SLOT(on_pushButton_inputFile_clicked()), MY_QT_CONN);
	QObject::connect(m_cutWgts->m_vLineEditCut[CUT_PBUTTON_OPEN_INPUT_FILE],
		SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_inputFile_edited(const QString &)), MY_QT_CONN);

	QObject::connect(m_cutWgts->m_vPushbuttonCut[CUT_PBUTTON_OPEN_OUTP_FOLDER], SIGNAL(clicked()), this, SLOT(on_pushButton_outputFolder_clicked()), MY_QT_CONN);
	QObject::connect(m_cutWgts->m_vLineEditCut[CUT_PBUTTON_OPEN_OUTP_FOLDER],
			SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_outputFolder_edited(const QString &)), MY_QT_CONN);
	
	//start/quit buttons
	QObject::connect(m_cutWgts->m_startTaskButton, SIGNAL(clicked()), this, SLOT(on_pushButton_cutStart_clicked()), MY_QT_CONN);
	QObject::connect(m_cutWgts->m_quitTaskButton, SIGNAL(clicked()), this, SLOT(on_pushButton_cutQuit_clicked()), MY_QT_CONN);

	m_appCfg->getInput(m_inputCfg);
	m_appCfg->getOutput(m_outputCfg);

	//m_cutWgts->enableDisableButtons();
}


RunGuiCut::~RunGuiCut()
{
}


void RunGuiCut::on_pushButton_inputFile_clicked()
{

	std::string dir = getDirFromFilepath(m_inputCfg.inputVideoFilepath);
	QString initFolder = QString::fromStdString(dir);
	QString initFilter = QString::fromStdString(m_inputCfg.inputVideoFileFilter);

	QString ff = QFileDialog::getOpenFileName(this, tr("Open a video File"), initFolder, initFilter);
	if (!ff.isEmpty() && fileExists(ff.toStdString()) ) {
		m_cutWgts->m_vLineEditCut[CUT_PBUTTON_OPEN_INPUT_FILE]->setText(ff);
		on_lineEdit_inputFile_edited(ff);
	}
}


void RunGuiCut::on_lineEdit_inputFile_edited(const QString &s)
{
	std::string f = s.toStdString();
	if (fileExists( f ))
		m_inputCfg.inputVideoFilepath = f;
}

//output widgets
void RunGuiCut::on_pushButton_outputFolder_clicked()
{
	QString initFolder = QString::fromStdString(m_outputCfg.outputVideoFolder);
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Input Video Folder"), initFolder, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	if ( !dir.isEmpty() && folderExists(dir.toStdString())) {
		m_cutWgts->m_vLineEditCut[CUT_PBUTTON_OPEN_OUTP_FOLDER]->setText(dir);
		on_lineEdit_outputFolder_edited(dir);
	}
}

void RunGuiCut::on_lineEdit_outputFolder_edited(const QString &s)
{
	std::string dir2 = s.toStdString();
	if (folderExists(dir2) )
		m_outputCfg.outputVideoFolder = dir2;
}

void RunGuiCut::on_pushButton_cutQuit_clicked()
{
	m_appCfg->setTask(APP_TOOLBAR_UNKN);
	m_appUi->switchToolbarTaskTo(APP_TOOLBAR_UNKN);
}

void RunGuiCut::on_pushButton_cutStart_clicked()
{
	//set the current setting prms into shared Cfg
	m_appCfg->setInput(m_inputCfg);
	m_appCfg->setOutput(m_outputCfg);
}
