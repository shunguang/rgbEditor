/*
*-------------------------------------------------------------------
* RunGuiCombine.cpp
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
#include "RunGuiCombine.h"
using namespace std;
using namespace app;

RunGuiCombine::RunGuiCombine(RunGuiDcPtr &dc)
	: m_dc(dc)
	, m_appCfg(dc->m_cfg.get())
	, m_appUi(dc->m_ui.get())
{
	//Toolbar combine
	ToolbarCombine	*pp = dynamic_cast<ToolbarCombine *> (m_appUi->m_vToolbarGui[APP_TOOLBAR_COMBINE].get());

	//input widgets
	m_inWgts = pp->m_in;
	QObject::connect(m_inWgts->m_vPushBotton[COMBINE_IN_PBUTTON_BROWSE_FOLDER], SIGNAL(clicked()), this, SLOT(on_pushBotton_combineBrowseFolder_clicked()), MY_QT_CONN);
	QObject::connect(m_inWgts->m_vPushBotton[COMBINE_IN_PBUTTON_LOAD_ALL], SIGNAL(clicked()), this, SLOT(on_pushBotton_combineLoadAll_clicked()), MY_QT_CONN);
	QObject::connect(m_inWgts->m_vPushBotton[COMBINE_IN_PBUTTON_REMOVE_ALL], SIGNAL(clicked()), this, SLOT(on_pushBotton_combineRemoveAll_clicked()), MY_QT_CONN);
	QObject::connect(m_inWgts->m_vPushBotton[COMBINE_IN_PBUTTON_APPEND_ONE], SIGNAL(clicked()), this, SLOT(on_pushBotton_combineBrowseAppendOne_clicked()), MY_QT_CONN);
	QObject::connect(m_inWgts->m_vPushBotton[COMBINE_IN_PBUTTON_REMOVE_ONE], SIGNAL(clicked()), this, SLOT(on_pushBotton_combineBrowseRemoveOne_clicked()), MY_QT_CONN);
	QObject::connect(m_inWgts->m_vPushBotton[COMBINE_IN_PBUTTON_UP], SIGNAL(clicked()), this, SLOT(on_pushBotton_combineUp_clicked()), MY_QT_CONN);
	QObject::connect(m_inWgts->m_vPushBotton[COMBINE_IN_PBUTTON_DOWN], SIGNAL(clicked()), this, SLOT(on_pushBotton_combineDown_clicked()), MY_QT_CONN);
	QObject::connect(m_inWgts->m_vPushBotton[COMBINE_IN_PBUTTON_BROWSE_MP3_FILE], SIGNAL(clicked()), this, SLOT(on_pushBotton_combineBrowseMp3_clicked()), MY_QT_CONN);
	QObject::connect(m_inWgts->m_sliderMp3, SIGNAL(valueChanged(int)), this, SLOT(on_sliderMp3_valueChgd(int)), MY_QT_CONN);
	QObject::connect(m_inWgts->m_vLineEdit[COMBINE_IN_LEDIT_CNT], 
			SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_inputVideoFolder_edited(const QString &)), MY_QT_CONN);
	QObject::connect(m_inWgts->m_vLineEdit[COMBINE_IN_LEDIT_MP3_PATH],
			SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_inputMp3Path_edited(const QString &)), MY_QT_CONN);
	
	//output widgets
	m_outWgts = pp->m_out;
	QObject::connect(m_outWgts->m_vPushBottonOut[OUT_PBUTTON_BROWSE_FOLDER], SIGNAL(clicked()), this, SLOT(on_pushBotton_outputFolder_clicked()), MY_QT_CONN);
	QObject::connect(m_outWgts->m_vLineEditOut[OUT_LINE_EDIT_FOLDER],
		SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_outputVideoFolder_edited(const QString &)), MY_QT_CONN);
	QObject::connect(m_outWgts->m_vLineEditOut[OUT_LINE_EDIT_USER_DEF_DIM_W],
		SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_outputUserDefineW_edited(const QString &)), MY_QT_CONN);
	QObject::connect(m_outWgts->m_vLineEditOut[OUT_LINE_EDIT_USER_DEF_DIM_H],
		SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_outputUserDefineH_edited(const QString &)), MY_QT_CONN);

	QObject::connect(m_outWgts->m_vComboBoxOut[OUT_COMBOBOX_SOCIAL_MEDIA],
		SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_outputSocialMedia_currentIndexChanged(int)), MY_QT_CONN);

	//start/quit buttons
	QObject::connect( pp->m_startTaskButton, SIGNAL(clicked()), this, SLOT(on_pushButton_combineStart_clicked()), MY_QT_CONN);
	QObject::connect( pp->m_quitTaskButton, SIGNAL(clicked()), this, SLOT(on_pushButton_combineQuit_clicked()), MY_QT_CONN);

	m_appCfg->getInput(m_inputCfg);
	m_appCfg->getOutput(m_outputCfg);

	m_inWgts->enableDisableButtons();
}


RunGuiCombine::~RunGuiCombine()
{
}


void RunGuiCombine::on_pushBotton_combineBrowseFolder_clicked()
{
	QString initFolder = QString::fromStdString(m_inputCfg.inputVideoFolder);
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Input Video Folder"), initFolder, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	m_inWgts->m_vLineEdit[COMBINE_IN_LEDIT_INPUT_FOLDER]->setText(dir);
	on_lineEdit_inputVideoFolder_edited(dir);
}

void RunGuiCombine::on_pushBotton_combineBrowseMp3_clicked()
{
	string f0 = m_inputCfg.mp3File;
	std::string head, tail;
	app::splitFolder(f0, head, tail);

	boost::filesystem::path p(head);
	if (!boost::filesystem::exists(p)) {
		head = "c:/temp";
	}
	QString initFolder = QString::fromStdString(head);
	QString initFilter = QString::fromStdString("*.mp3");

	QString ff = QFileDialog::getOpenFileName(this, tr("Open mp3 File"), initFolder, initFilter);

	m_inWgts->m_vLineEdit[COMBINE_IN_LEDIT_MP3_PATH]->setText(ff);
	on_lineEdit_inputMp3Path_edited(ff);
}

void RunGuiCombine::on_pushBotton_combineLoadAll_clicked()
{
	const string &folder = m_inputCfg.inputVideoFolder;
	boost::filesystem::path p(folder);
	if (!boost::filesystem::exists(p)) {
		std::string msg = "The input video folder: " + folder + "does not exist!";
		popupMsg(this, POPUP_MSG_WIN_TITLE, msg);
		return;
	}

	vector<std::string> vFileNames;
	uint32_t n = getFileNameList(folder, "*", vFileNames);
	m_inWgts->appendAllInputVideos(vFileNames);
}

void RunGuiCombine::on_pushBotton_combineRemoveAll_clicked()
{
	m_inWgts->removeAllInputVideos();
}

void RunGuiCombine::on_pushBotton_combineBrowseAppendOne_clicked()
{
	const string &folder = m_inputCfg.inputVideoFolder;
	boost::filesystem::path p(folder);
	if (!boost::filesystem::exists(p)) {
		std::string msg = "The input video folder: " + folder + "does not exist!";
		popupMsg(this, POPUP_MSG_WIN_TITLE, msg);
		return;
	}
	QString initFolder = QString::fromStdString(folder);
	QString initFilter = QString::fromStdString("*.*");

	QString ff = QFileDialog::getOpenFileName(this, tr("Open mp3 File"), initFolder, initFilter);
	string head, fname;
	app::splitFolder(ff.toStdString(), head, fname);
	string errMsg = m_inWgts->appendOneInputVideo(fname);
	if (!errMsg.empty()) {
		popupMsg(this, POPUP_MSG_WIN_TITLE, errMsg);
	}
}

void RunGuiCombine::on_pushBotton_combineBrowseRemoveOne_clicked()
{
	int idx;
	string fname;
	m_inWgts->getCurrentInputVideoFileName(idx, fname);
	if (idx >= 0) {
		m_inWgts->removeOneInputVideo(idx);
	}
}

void RunGuiCombine::on_pushBotton_combineUp_clicked()
{
	m_inWgts->moveUpOrDown(-1);
}

void RunGuiCombine::on_pushBotton_combineDown_clicked()
{
	m_inWgts->moveUpOrDown(1);
}

void RunGuiCombine::on_lineEdit_inputVideoFolder_edited(const QString &s)
{
	//crashed on  dir.toStdString(), need to build QT5.5 w / VS2015
	std::string dir2 = s.toStdString();
	m_inputCfg.inputVideoFolder = dir2;

	//m_appUi->updateEnabilityGameInfoButtons();
}

void RunGuiCombine::on_lineEdit_inputMp3Path_edited(const QString &s)
{
	std::string dir2 = s.toStdString();
	m_inputCfg.mp3File = dir2;
}

void RunGuiCombine::on_sliderMp3_valueChgd(int value)
{
	m_inWgts->m_vLabel[COMBINE_IN_LABEL_SLIDER_CUR]->setText(QString::number(value));
	m_inputCfg.mp3Percentage = value;
}


//output widgets
void RunGuiCombine::on_pushBotton_outputFolder_clicked()
{
	QString initFolder = QString::fromStdString(m_outputCfg.outputVideoFolder);
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Input Video Folder"), initFolder, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	m_inWgts->m_vLineEdit[OUT_LINE_EDIT_FOLDER]->setText(dir);
	on_lineEdit_outputVideoFolder_edited(dir);
}

void RunGuiCombine::on_lineEdit_outputVideoFolder_edited(const QString &s)
{
	std::string dir2 = s.toStdString();
	m_outputCfg.outputVideoFolder = dir2;
}

void RunGuiCombine::on_lineEdit_outputUserDefineW_edited(const QString &s)
{
	std::string dir2 = s.toStdString();
	m_outputCfg.outputVideoUsrDefSz.width = (int)string_to_uint64( dir2 );
}
void RunGuiCombine::on_lineEdit_outputUserDefineH_edited(const QString &s)
{
	std::string dir2 = s.toStdString();
	m_outputCfg.outputVideoUsrDefSz.height = (int)string_to_uint64(dir2);
}

void RunGuiCombine::on_comboBox_outputSocialMedia_currentIndexChanged(const int newIdx)
{
	const ImgSize inputVideoSz(1920, 1080);
	m_outWgts->updateOutVideoSzCandiates( newIdx, inputVideoSz);
	m_outWgts->uncheckVideoSizeBoxes();
}


void RunGuiCombine::on_pushButton_combineQuit_clicked()
{
	m_appCfg->setTask(APP_TOOLBAR_UNKN);
	m_appUi->switchToolbarTaskTo(APP_TOOLBAR_UNKN);
}

void RunGuiCombine::on_pushButton_combineStart_clicked()
{
	//set the current setting prms into shared Cfg
	m_appCfg->setInput(m_inputCfg);
	m_appCfg->setOutput(m_outputCfg);
}
