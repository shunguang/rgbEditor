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
#include "Input4Combine.h"
#include "AppSlider.h"

using namespace app;
using namespace std;
Input4Combine::Input4Combine(QGroupBox *parentGrp)
	: m_grpBoxParent(parentGrp)
{
	int languageId = 0;
	m_sliderMp3Prm.name="mp3 %";
	m_sliderMp3Prm.minVal=0;
	m_sliderMp3Prm.maxVal=100;
	m_sliderMp3Prm.step=1;
	m_sliderMp3Prm.curVal=100;

	setTextOut(languageId);
}

Input4Combine::~Input4Combine()
{
}

void Input4Combine::createWidgets()
{
	for (auto &e:m_vLabel) {
		e = new QLabel(m_grpBoxParent);
	}
	for (auto &e : m_vLineEdit) {
		e = new QLineEdit(m_grpBoxParent);
	}
	for (auto &e : m_vPushBotton) {
		e = new QPushButton(m_grpBoxParent);
	}

	m_sliderMp3 = new QSlider(Qt::Horizontal, m_grpBoxParent);
	m_sliderMp3->setRange(0, 100);
	m_sliderMp3->setTickInterval(10);

	m_inputFileTable = new QTableWidget(0, 1, m_grpBoxParent);
	m_inputFileTable->setObjectName(QStringLiteral("tableFiles"));
	m_inputFileTable->setHorizontalHeaderLabels(m_tableHeader);
	m_inputFileTable->verticalHeader()->setVisible(false);
	m_inputFileTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_inputFileTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_inputFileTable->setSelectionMode(QAbstractItemView::SingleSelection);
	m_inputFileTable->setShowGrid(false);
	m_inputFileTable->setStyleSheet("QTableView {selection-background-color: blue;}");
	m_inputFileTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	m_inputFileTable->verticalHeader()->setDefaultSectionSize(18);

}

void Input4Combine::resizeUI()
{
	calRectsOut();

	for (int i = 0; i < COMBINE_IN_LABEL_CNT; ++i) {
		m_vLabel[i]->setGeometry(m_vRectLabel[i]);
	}
	for (int i = 0; i < COMBINE_IN_LEDIT_CNT; ++i) {
		m_vLineEdit[i]->setGeometry(m_vRectLineEdit[i]);
	}
	for (int i = 0; i < COMBINE_IN_PBUTTON_CNT; ++i) {
		m_vPushBotton[i]->setGeometry(m_vRectPushButton[i]);
	}
	m_sliderMp3->setGeometry(m_rectSliderMp3);
	m_inputFileTable->setGeometry(m_rectInputFileTable);
	m_inputFileTable->setColumnWidth(0, m_rectInputFileTable.width());
}

void Input4Combine::retranslateUI()
{
	for (int i = 0; i < COMBINE_IN_LABEL_CNT; ++i) {
		m_vLabel[i]->setText(QString::fromStdString(m_vTextLabel[i]));
	}

	for (int i = 0; i < COMBINE_IN_LEDIT_CNT; ++i) {
		m_vLineEdit[i]->setPlaceholderText(QString::fromStdString(m_vTextLineEdit[i]));
	}

	for (int i = 0; i < COMBINE_IN_PBUTTON_CNT; ++i) {
		m_vPushBotton[i]->setText(QString::fromStdString(m_vTextButton[i]));
	}
	m_grpBoxParent->setTitle(QString::fromStdString(m_textGrpBoxTitle));
}


void Input4Combine::calRectsOut()
{
	const int h = APP_LINE_HEIGHT;
	const int b = APP_GUI_BORDER_SIZE;

	const int w0 = m_grpBoxParent->width();
	const int h0 = m_grpBoxParent->height();
	const int w1 = 100;  //left side button width
	const int w3 = 50;   //browse button
	const int w2 = w0 - (w1 + w3 + 4 * b);     //input file folder width

	resetRectToZeros();

	//line 1
	int x = b, y = 3*b;
	m_vRectLabel[COMBINE_IN_LABEL_VIDEO_FOLDER].setRect(x,y,w1,h);
	x += (w1 + b);
	m_vRectLineEdit[COMBINE_IN_LEDIT_INPUT_FOLDER].setRect(x, y, w2, h);
	x += (w2 + b);
	m_vRectPushButton[COMBINE_IN_PBUTTON_BROWSE_FOLDER].setRect(x, y, w3, h);

	//line 2
	x = b;
	y += (h + b);
	m_vRectLabel[COMBINE_IN_LABEL_ADD_VIDEOS].setRect(x, y, w0-2*b, h);
	const int yTab = y;
	//line 3
	x = b;
	y += (h + b);
	for (int i = COMBINE_IN_PBUTTON_LOAD_ALL; i <= COMBINE_IN_PBUTTON_DOWN; ++i) {
		m_vRectPushButton[i].setRect(x, y, w1, h);
		y += (h + b);
	}

	//input file table
	x += (w1+b); 
	int wTab = w0 - (w1 + 3 * b);
	int hTab = y - yTab-b;
	m_rectInputFileTable.setRect(x, yTab, wTab, hTab);

	//mp3
	x = b;
	m_vRectLabel[COMBINE_IN_LABEL_MP3_FILE].setRect(x, y, w1, h);
	x += (w1 + b);
	m_vRectLineEdit[COMBINE_IN_LEDIT_MP3_PATH].setRect(x, y, w2, h);
	x += (w2 + b);
	m_vRectPushButton[COMBINE_IN_PBUTTON_BROWSE_MP3_FILE].setRect(x, y, w3, h);

	//mp3 slider
	y += (h + b);
	int u1 = w1, u2=40, u3, u4 = 40, u5 = 40;
	u3 = w0 - (u1 + u2 + u4 + u5 + 6*b);
	x = b;
	m_vRectLabel[COMBINE_IN_LABEL_MP3_PCT].setRect(x, y, u1, h);
	
	x += u1 + b;
	m_vRectLabel[COMBINE_IN_LABEL_SLIDER_MIN].setRect(x, y, u2, h);
	
	x += u2 + b;
	m_rectSliderMp3.setRect(x, y, u3, h);
	
	x += u3 + b;
	m_vRectLabel[COMBINE_IN_LABEL_SLIDER_MAX].setRect(x, y, u4, h);

	x += u4 + b;
	m_vRectLabel[COMBINE_IN_LABEL_SLIDER_CUR].setRect(x, y, u5, h);
}

void Input4Combine::setTextOut(const int languageId)
{
	m_vTextLabel[COMBINE_IN_LABEL_VIDEO_FOLDER] = "Media Folder";
	m_vTextLabel[COMBINE_IN_LABEL_ADD_VIDEOS] = "Add Videos or Images";
	m_vTextLabel[COMBINE_IN_LABEL_MP3_FILE] = "Add Mp3 File";
	m_vTextLabel[COMBINE_IN_LABEL_MP3_PCT] = "Mp3 percentage";
	m_vTextLabel[COMBINE_IN_LABEL_SLIDER_MIN] = std::to_string(m_sliderMp3Prm.minVal);
	m_vTextLabel[COMBINE_IN_LABEL_SLIDER_MAX] = std::to_string(m_sliderMp3Prm.maxVal);
	m_vTextLabel[COMBINE_IN_LABEL_SLIDER_CUR] = std::to_string(m_sliderMp3Prm.curVal);


	m_vTextButton[COMBINE_IN_PBUTTON_BROWSE_FOLDER] = "Browse";
	m_vTextButton[COMBINE_IN_PBUTTON_BROWSE_MP3_FILE] = "Browse";
	m_vTextButton[COMBINE_IN_PBUTTON_LOAD_ALL] = "Load All";
	m_vTextButton[COMBINE_IN_PBUTTON_REMOVE_ALL] = "Remove All";
	m_vTextButton[COMBINE_IN_PBUTTON_APPEND_ONE] = "Append One";
	m_vTextButton[COMBINE_IN_PBUTTON_REMOVE_ONE] = "Remove One";
	m_vTextButton[COMBINE_IN_PBUTTON_UP] = "Move Up";
	m_vTextButton[COMBINE_IN_PBUTTON_DOWN] = "Move Down";

	m_vTextLineEdit[COMBINE_IN_LEDIT_INPUT_FOLDER] = "please input or browse media folder";
	m_vTextLineEdit[COMBINE_IN_LEDIT_MP3_PATH] = "select an mp3 file if you want to change the sound";
	m_textGrpBoxTitle = "Input";
	m_tableHeader << "video/Image file list";

}

void Input4Combine::resetRectToZeros()
{
	for (QRect &r : m_vRectLabel) {
		r.setRect(0, 0, 0, 0);
	}

	for (QRect &r : m_vRectLineEdit) {
		r.setRect(0, 0,0,0);
	}

	for (QRect &r : m_vRectPushButton) {
		r.setRect(0, 0, 0, 0);
	}
}


void Input4Combine::getInputVideoFiles(std::vector<std::string> &vFileNames)
{
	vFileNames.clear();
	int n = m_inputFileTable->rowCount();
	for (int i = 0; i < n; ++i) {
		const QTableWidgetItem *it = m_inputFileTable->item(i, 0);
		vFileNames.push_back(it->text().toStdString());
	}
}

void Input4Combine::appendAllInputVideos(const std::vector<std::string> &vFileNames)
{
	BOOST_FOREACH(const string &f, vFileNames) {
		appendOneInputVideo(f);
	}
	enableDisableButtons();
}

std::string  Input4Combine::appendOneInputVideo(const std::string  &fileName)
{
	QList<QTableWidgetItem *> v = m_inputFileTable->findItems(QString::fromStdString(fileName), Qt::MatchExactly);
	if (v.size() > 0) {
		string msg = "file: <" + fileName + "> is already in list!";
		return msg;
	}

	int row = m_inputFileTable->rowCount();
	QTableWidgetItem *fileNameItem = new QTableWidgetItem(QString::fromStdString(fileName));
	m_inputFileTable->insertRow(row);
	m_inputFileTable->setItem(row, 0, fileNameItem);

	enableDisableButtons();
	return "";
}

void Input4Combine::removeAllInputVideos()
{
	while (m_inputFileTable->rowCount() > 0) {
		removeOneInputVideo(0);
	}
	enableDisableButtons();
}

void Input4Combine::removeOneInputVideo(const int idx)
{
	if (idx >= 0 && idx < m_inputFileTable->rowCount()) {
		m_inputFileTable->removeRow(idx);
	}
	enableDisableButtons();
}

void Input4Combine::getCurrentInputVideoFileName(int &idx, string &fname)
{
	idx = -1;
	fname = "";
	if (m_inputFileTable->rowCount() == 0) {
		return;
	}

	idx = m_inputFileTable->currentRow();
	QTableWidgetItem* item = m_inputFileTable->currentItem();
	fname = item->text().toStdString();
	cout << idx << ", fname=" << fname << endl;
}


//step=-1/1  <----------> move up/down
void Input4Combine::moveUpOrDown(const int step)
{
	const int n = m_inputFileTable->rowCount();
	if (n < 2) {
		return;
	}

	int curIdx;
	string curFname;
	getCurrentInputVideoFileName(curIdx, curFname);
	
	int newIdx = curIdx + step;
	if (newIdx < 0) newIdx = n-1;
	else if (newIdx >= n) newIdx = 0;

	QList<QTableWidgetItem*> curRow = takeRow(curIdx);
	QList<QTableWidgetItem*> newRow = takeRow(newIdx);

	setRow(curIdx, newRow);
	setRow(newIdx, curRow);
	m_inputFileTable->selectRow(newIdx);
}



// takes and returns the whole row
QList<QTableWidgetItem*> Input4Combine::takeRow(int row)
{
	QList<QTableWidgetItem*> rowItems;
	for (int col = 0; col < m_inputFileTable->columnCount(); ++col)
	{
		rowItems << m_inputFileTable->takeItem(row, col);
	}
	return rowItems;
}

// sets the whole row
void Input4Combine::setRow(int row, const QList<QTableWidgetItem*>& rowItems)
{
	for (int col = 0; col < m_inputFileTable->columnCount(); ++col)
	{
		m_inputFileTable->setItem(row, col, rowItems.at(col));
	}
}

void Input4Combine::enableDisableButtons()
{
	//enable all
	for (int i = COMBINE_IN_PBUTTON_LOAD_ALL; i <= COMBINE_IN_PBUTTON_DOWN; ++i) {
		m_vPushBotton[i]->setEnabled(true);
	}

	const int n = m_inputFileTable->rowCount();
	if (n == 0) {
		m_vPushBotton[COMBINE_IN_PBUTTON_REMOVE_ALL]->setEnabled(false);
		m_vPushBotton[COMBINE_IN_PBUTTON_REMOVE_ONE]->setEnabled(false);
		m_vPushBotton[COMBINE_IN_PBUTTON_UP]->setEnabled(false);
		m_vPushBotton[COMBINE_IN_PBUTTON_DOWN]->setEnabled(false);
	}
	else if (n == 1) {
		m_vPushBotton[COMBINE_IN_PBUTTON_UP]->setEnabled(false);
		m_vPushBotton[COMBINE_IN_PBUTTON_DOWN]->setEnabled(false);
	}
}
