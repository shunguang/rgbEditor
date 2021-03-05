/*
*-------------------------------------------------------------------
* RunGuiEdit.cpp
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
#include "RunGuiEdit.h"
using namespace std;
using namespace app;

RunGuiEdit::RunGuiEdit(RunGuiDcPtr &dc)
	: m_dc(dc)
	, m_appCfg(dc->m_cfg.get())
	, m_appUi(dc->m_ui.get())
{
	//Toolbar Edit
	ToolbarEdit	*pp = dynamic_cast<ToolbarEdit *> (m_appUi->m_vToolbarGui[APP_TOOLBAR_EDIT].get());

	//input widgets
	m_inWgt = pp->m_in;
	QObject::connect(m_inWgt->m_vPushButton[EDIT_IN_PBUTTON_BROWSE_VIDEO_FILE], SIGNAL(clicked()), this, SLOT(on_pushButton_inputFile_clicked()), MY_QT_CONN);
	QObject::connect(m_inWgt->m_vLineEdit[EDIT_IN_LEDIT_VIDEO_FILE],
		SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_inputFile_edited(const QString &)), MY_QT_CONN);

	QObject::connect(m_inWgt->m_vPushButton[EDIT_IN_PBUTTON_BROWSE_MP3_FILE], SIGNAL(clicked()), this, SLOT(on_pushButton_mp3File_clicked()), MY_QT_CONN);
	QObject::connect(m_inWgt->m_vLineEdit[EDIT_IN_LEDIT_MP3_FILE],
			SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_mp3File_edited(const QString &)), MY_QT_CONN);
	
	//output widgets
	m_outWgt = pp->m_out;
	QObject::connect(m_outWgt->m_vPushBottonOut[OUT_PBUTTON_BROWSE_FOLDER], SIGNAL(clicked()), this, SLOT(on_pushButton_outputFolder_clicked()), MY_QT_CONN);
	QObject::connect(m_outWgt->m_vLineEditOut[OUT_LINE_EDIT_FOLDER],
		SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_outputVideoFolder_edited(const QString &)), MY_QT_CONN);
	QObject::connect(m_outWgt->m_vLineEditOut[OUT_LINE_EDIT_USER_DEF_DIM_W],
		SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_outputUserDefineW_edited(const QString &)), MY_QT_CONN);
	QObject::connect(m_outWgt->m_vLineEditOut[OUT_LINE_EDIT_USER_DEF_DIM_H],
		SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_outputUserDefineH_edited(const QString &)), MY_QT_CONN);

	QObject::connect(m_outWgt->m_vComboBoxOut[OUT_COMBOBOX_SOCIAL_MEDIA],
		SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_outputSocialMedia_currentIndexChanged(int)), MY_QT_CONN);

	//ctrl 
	m_ctrlWgt = pp->m_ctrl;
	QObject::connect(m_ctrlWgt->m_sliderKeyFrm, SIGNAL(valueChanged(int)), this, SLOT(on_keyFrmSlider_valueChgd(int)), MY_QT_CONN);
	QObject::connect(m_ctrlWgt->m_sliderKeyFrm, SIGNAL(sliderPressed()), this, SLOT(on_keyFrmSlider_pressed()), MY_QT_CONN);
	//QObject::connect(m_ctrlWgt->m_sliderKeyFrm, SIGNAL(sliderMoved()), this, SLOT(on_keyFrmSlider_moved()), MY_QT_CONN);
	QObject::connect(m_ctrlWgt->m_sliderKeyFrm, SIGNAL(sliderReleased()), this, SLOT(on_keyFrmSlider_released()), MY_QT_CONN);

	QObject::connect(m_ctrlWgt->m_vPushButton[EDIT_CTRL_PBUTTON_ADD_V], SIGNAL(clicked()), this, SLOT(on_pushbuttonV_addSlider_clicked()), MY_QT_CONN);
	QObject::connect(m_ctrlWgt->m_vPushButton[EDIT_CTRL_PBUTTON_RMV_V], SIGNAL(clicked()), this, SLOT(on_pushbuttonV_delSlider_clicked()), MY_QT_CONN);
	QObject::connect(m_ctrlWgt->m_vPushButton[EDIT_CTRL_PBUTTON_ADD_A], SIGNAL(clicked()), this, SLOT(on_pushbuttonA_addSlider_clicked()), MY_QT_CONN);
	QObject::connect(m_ctrlWgt->m_vPushButton[EDIT_CTRL_PBUTTON_RMV_A], SIGNAL(clicked()), this, SLOT(on_pushbuttonA_delSlider_clicked()), MY_QT_CONN);

	QObject::connect(m_ctrlWgt->m_mrsV, SIGNAL(sigWarningMsg(const QString &)), this, SLOT(respns_warning_msg(const QString&)), MY_QT_CONN);
	QObject::connect(m_ctrlWgt->m_mrsA, SIGNAL(sigWarningMsg(const QString &)), this, SLOT(respns_warning_msg(const QString&)), MY_QT_CONN);


	QObject::connect(m_ctrlWgt->m_player, SIGNAL(play()),	this, SLOT(respns_play()), MY_QT_CONN);
	QObject::connect(m_ctrlWgt->m_player, SIGNAL(pause()),	this, SLOT(respns_pause()), MY_QT_CONN);
	QObject::connect(m_ctrlWgt->m_player, SIGNAL(stop()),	this, SLOT(respns_stop()), MY_QT_CONN);
	QObject::connect(m_ctrlWgt->m_player, SIGNAL(next()),	this, SLOT(respns_next()), MY_QT_CONN);
	QObject::connect(m_ctrlWgt->m_player, SIGNAL(previous()),			this, SLOT(respns_previous()), MY_QT_CONN);
	QObject::connect(m_ctrlWgt->m_player, SIGNAL(changeVolume(int)),	this, SLOT(respns_changeVolume(int)), MY_QT_CONN);
	QObject::connect(m_ctrlWgt->m_player, SIGNAL(changeMuting(bool)),	this, SLOT(respns_changeMuting(bool)), MY_QT_CONN);
	QObject::connect(m_ctrlWgt->m_player, SIGNAL(changeRate(qreal)),	this, SLOT(respns_changePlayFrmRate(qreal)), MY_QT_CONN);


	//start/quit buttons
	QObject::connect(pp->m_startTaskButton, SIGNAL(clicked()), this, SLOT(on_pushButton_start_clicked()), MY_QT_CONN);
	QObject::connect(pp->m_quitTaskButton, SIGNAL(clicked()), this, SLOT(on_pushButton_quit_clicked()), MY_QT_CONN);

	m_appCfg->getInput(m_inputCfg);
	m_appCfg->getOutput(m_outputCfg);

	//m_cutWgts->enableDisableButtons();
}


RunGuiEdit::~RunGuiEdit()
{
}

void RunGuiEdit::on_pushButton_inputFile_clicked()
{
	std::string dir = getDirFromFilepath(m_inputCfg.inputVideoFile);
	QString initFolder = QString::fromStdString(dir);
	QString ff = QFileDialog::getOpenFileName(this, tr("Open mp3 File"), initFolder, QString::fromStdString(m_inputCfg.inputVideoFileFilter) );

	if (!ff.isEmpty()) {
		m_inWgt->m_vLineEdit[EDIT_IN_LEDIT_VIDEO_FILE]->setText(ff);
		on_lineEdit_inputFile_edited(ff);
	}
}


void RunGuiEdit::on_lineEdit_inputFile_edited(const QString &s)
{
	if (s.isEmpty()) 
		return;

	m_inputCfg.inputVideoFile = s.toStdString();
}

//output widgets
void RunGuiEdit::on_pushButton_mp3File_clicked()
{
	std::string dir = getDirFromFilepath(m_inputCfg.inputMp3File);
	QString initFolder = QString::fromStdString(dir);
	QString ff = QFileDialog::getOpenFileName(this, tr("Open mp3 File"), initFolder, ".mp3");

	if (!ff.isEmpty()) {
		m_inWgt->m_vLineEdit[EDIT_IN_LEDIT_MP3_FILE]->setText(ff);
		on_lineEdit_mp3File_edited(ff);
	}
}

void RunGuiEdit::on_lineEdit_mp3File_edited(const QString &s)
{
	if (s.isEmpty())
		return;

	m_inputCfg.inputMp3File = s.toStdString();
}


//output widgets
void RunGuiEdit::on_pushButton_outputFolder_clicked()
{
	QString initFolder = QString::fromStdString(m_outputCfg.outputVideoFolder);
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Input Video Folder"), initFolder, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (!dir.isEmpty()) {
		m_outWgt->m_vLineEditOut[OUT_LINE_EDIT_FOLDER]->setText(dir);
		on_lineEdit_outputVideoFolder_edited(dir);
	}
}

void RunGuiEdit::on_lineEdit_outputVideoFolder_edited(const QString &s)
{
	if (!s.isEmpty())
		m_outputCfg.outputVideoFolder = s.toStdString();
}

void RunGuiEdit::on_lineEdit_outputUserDefineW_edited(const QString &s)
{
	std::string dir2 = s.toStdString();
	m_outputCfg.outputVideoUsrDefSz.width = (int)string_to_uint64(dir2);
}

void RunGuiEdit::on_lineEdit_outputUserDefineH_edited(const QString &s)
{
	std::string dir2 = s.toStdString();
	m_outputCfg.outputVideoUsrDefSz.height = (int)string_to_uint64(dir2);
}

void RunGuiEdit::on_comboBox_outputSocialMedia_currentIndexChanged(const int newIdx)
{
	const ImgSize inputVideoSz(1920, 1080);
	m_outWgt->updateOutVideoSzCandiates(newIdx, inputVideoSz);
	m_outWgt->uncheckVideoSizeBoxes();
}

void RunGuiEdit::on_pushButton_quit_clicked()
{
	m_appCfg->setTask(APP_TOOLBAR_UNKN);
	m_appUi->switchToolbarTaskTo(APP_TOOLBAR_UNKN);
}

void RunGuiEdit::on_pushButton_start_clicked()
{
	//set the current setting prms into shared Cfg
	m_appCfg->setInput(m_inputCfg);
	m_appCfg->setOutput(m_outputCfg);
}


void RunGuiEdit::on_keyFrmSlider_valueChgd(int keyFrmIdx)
{
#if 0
	//cout << "sldier_keyFrm:" << value << endl;
	uint64 keyFrmNum;
	m_currVideoKeyFrmIdx = keyFrmIdx;
	//RunMgr *p = dynamic_cast<RunMgr *>(m_mgrThread.get());
	float64 t = m_runMgr->getCurrVideoTimeSecFromKeyFrmIdx(keyFrmIdx, keyFrmNum);
	m_ui->label_browseTimeCurrent->setText(QString::fromStdString(timeSecToHHMMSSxx(t)));

	bool suc = m_runMgr->getThumbnailFrm(keyFrmIdx, m_thumbnailFrm);
	if (suc) {
		dispThumbnail();
	}
#endif
}

void RunGuiEdit::on_keyFrmSlider_released()
{
#if 0
	uint32 dt = 0, timeout_ms = 300 * 1000;

	m_progDlg->reset();
	m_progDlg->setProgress(10, "Find new access location ...");
	//start from the previous frm, and read only one frm to current frm will be reach current frm
	//uint32 searchToKeyFrmId = (m_currVideoKeyFrmIdx > 0) ? (m_currVideoKeyFrmIdx - 1) : 0;
	m_runMgr->startDecoding(m_currVideoKeyFrmIdx);

	m_runMgr->printBrief();
	cout << "on_keyFrmSlider_released(): m_currVideoKeyFrmIdx=" << m_currVideoKeyFrmIdx << endl;

	m_saveDispImg4FileIdSwitch = true;
	m_runBrowseVideo->setLastFrmReached(false);
	m_runBrowseVideo->startDisp(BROWSE_FIRST_FRM_ONLY);
	m_progDlg->setProgress(100, "Find new access location ...");

	if (dt > timeout_ms) {
		popupMsg(this, POPUP_MSG_WIN_TITLE, "timeout to seek video file!", QMessageBox::Critical);
		return;
	}
#endif
}

void RunGuiEdit::on_keyFrmSlider_pressed()
{
	//m_runMgr->stopDecoding();
}

void RunGuiEdit::on_keyFrmSlider_moved()
{
	//todo:
}


void RunGuiEdit::on_pushbuttonV_addSlider_clicked()
{
	float xInWorld = m_ctrlWgt->m_sliderKeyFrm->value();
	m_ctrlWgt->m_mrsV->insertByCenter( xInWorld );
}

void RunGuiEdit::on_pushbuttonV_delSlider_clicked()
{
	m_ctrlWgt->m_mrsV->removeCurrent();
	//cout << "on_pushbutton_delSlider_clicked()" << endl;
}

void RunGuiEdit::on_pushbuttonA_addSlider_clicked()
{
	float xInWorld = m_ctrlWgt->m_sliderKeyFrm->value();
	m_ctrlWgt->m_mrsA->insertByCenter(xInWorld);
}


void RunGuiEdit::on_pushbuttonA_delSlider_clicked()
{
	m_ctrlWgt->m_mrsA->removeCurrent();
	//cout << "on_pushbutton_delSlider_clicked()" << endl;
}

//--------------
void RunGuiEdit::respns_play()
{
#if 0
	m_saveDispImg4FileIdSwitch = false;
	m_runBrowseVideo->startDisp(BROWSE_UTIL_PAUSE);
	m_ui->set4PlaycontrolButtonPressed(QMediaPlayer::PlayingState);
# endif
}

void RunGuiEdit::respns_pause()
{
#if 0
	m_runMgr->stopDecoding();  //stop decoding if need       
	m_runBrowseVideo->pauseJob();
	m_ui->set4PlaycontrolButtonPressed(QMediaPlayer::PausedState);

	boost::mutex::scoped_lock(m_runGuiMutex);
	m_vUsrSelectedKeyDispFrms[m_currFileId] = *m_dispFrm.get();
#endif
}

void RunGuiEdit::respns_stop()
{
#if 0
	m_runMgr->stopDecoding();  //stop decoding if need       
	m_runBrowseVideo->pauseJob();
	m_vUsrSelectedKeyDispFrms[m_currFileId] = *m_dispFrm.get();
	m_ui->set4PlaycontrolButtonPressed(QMediaPlayer::StoppedState);
#endif
}


void RunGuiEdit::respns_next()
{
#if 0
	uint32 keyFrmIdx = getNextKeyFrmIdx();
	if (keyFrmIdx == m_currVideoKeyFrmIdx) {
		return;
	}
	on_keyFrmSlider_pressed();   //stop decoding if need       
	on_keyFrmSlider_valueChgd(keyFrmIdx);
	on_keyFrmSlider_released();
	m_ui->slider_browseKeyFrm->setValue(keyFrmIdx);
#endif
}

void RunGuiEdit::respns_previous()
{
#if 0
	uint32 keyFrmIdx = getPrevKeyFrmIdx();
	if (keyFrmIdx == m_currVideoKeyFrmIdx) {
		return;
	}
	on_keyFrmSlider_pressed(); //stop decoding if need
	on_keyFrmSlider_valueChgd(keyFrmIdx);
	on_keyFrmSlider_released();
	m_ui->slider_browseKeyFrm->setValue(keyFrmIdx);
#endif
}

void RunGuiEdit::respns_changeVolume(int v)
{
}

void RunGuiEdit::respns_changeMuting(bool flag)
{
}

void RunGuiEdit::respns_changePlayFrmRate(qreal r)
{
//	m_runBrowseVideo->setFrmRate(r * 30);
}

//todo
uint32_t RunGuiEdit::getPrevKeyFrmIdx()
{
	return 0;
}

void RunGuiEdit::respns_warning_msg(const QString &msg)
{
	popupInfoMsg(POPUP_MSG_WIN_TITLE, msg.toStdString(), 2000 /*, QRect *placeRect = NULL*/);
}

void RunGuiEdit::respns_mgrHasErr(const QString &errMsg)
{
	popupMsg(this, POPUP_MSG_WIN_TITLE, errMsg.toStdString());
}
