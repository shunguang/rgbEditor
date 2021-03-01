/*
*-------------------------------------------------------------------
* AppGui.cpp
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
#include "AppGui.h"

using namespace std;
using namespace app;

AppGui::AppGui()
	: m_cfg(0)
	, m_isShowDebugMsg(true)
	, m_mainWinRect(50,50,720,640)
{
	Q_INIT_RESOURCE(appRes);

	//defined in appRes.qrc
	//and pre gnerated by coustom-buid tools

	//m_addIcon = QPixmap(QString::fromUtf8(":/resource/add_icon.png"));
	//m_delIcon = QPixmap(QString::fromUtf8(":/resource/del_icon.png"));
	m_vPixmap[APP_PIXMAP_INIT_BKG] = QPixmap(QString::fromUtf8(":/resource/InitBackgroundImg.png"));

	m_vToolbarIcon[APP_TOOLBAR_CUT]		= QIcon::fromTheme("document-new", QIcon(":resource/cut_long_video_icon.png"));
	m_vToolbarIcon[APP_TOOLBAR_EDIT]	= QIcon::fromTheme("document-new", QIcon(":resource/edit_short_video_icon.png"));
	m_vToolbarIcon[APP_TOOLBAR_COMBINE]  = QIcon::fromTheme("document-new", QIcon(":resource/combin_short_videos_icon.png"));

	//QFile file("c:/temp/test.png");
	//file.open(QIODevice::WriteOnly);
	//m_addIcon.save(&file, "PNG");
	for (int i = 0; i < APP_TOOLBAR_ITEM_CNT; ++i) {
		m_vToolbarGui[i] = NULL;
	}

}


void AppGui::setupUi(QMainWindow *mainWin, AppCfgPtr &cfg_)
{
	m_cfg = cfg_;
	//m_isShowDebugMsg = m_cfg->getShowDebugMsg();

	m_mainWin = mainWin;

	//define main window 
	if (m_mainWin->objectName().isEmpty()) {
		m_mainWin->setObjectName(QStringLiteral("mainWin"));
	}
	m_mainWin->setAnimated(false);

	//set central Widget
	m_centralWidget = new QWidget(mainWin);
	m_centralWidget->setObjectName(QStringLiteral("m_centralWidget"));

	m_mainWin->setCentralWidget(m_centralWidget);

	setupMenu(mainWin);
	createAppWidgets(mainWin);

	initSettingsFromCfg();

	//set text of menus, buttons, labes etc.
	retranslateUI(mainWin);

	resizeUI( true );

	showBkgImg();
}


void AppGui::switchToolbarTaskTo(const AppToolbarTask newTaskId )
{
	resizeUI( true );

	if (newTaskId == APP_TOOLBAR_UNKN) {
		enableToolBarItems(true);
		for ( auto &e : m_vToolbarAction ) {
			e->setChecked(false);
		}
	}
	else {
		enableToolBarItems(false);
		m_vToolbarAction[newTaskId]->setChecked(true);
		m_vToolbarGui[newTaskId]->m_startTaskButton->setEnabled(true);
		m_vToolbarGui[newTaskId]->m_quitTaskButton->setEnabled(true);
	}
	initSettingsFromCfg();
	showBkgImg();
}

void AppGui::createAppWidgets(QMainWindow *MainWindow)
{
	//create group box w.r.t. <m_centralWidget>
	for (int i = 0; i < APP_GBOX_CNT; ++i) {
		m_vGroupBox[i] = new QGroupBox(m_centralWidget);
		m_vGroupBox[i]->setObjectName( QString::fromStdString ( g_AppGrpBoxName[i] ) );
	}

	m_mainImg = new ImgLabel(m_vGroupBox[APP_GBOX_IMG]);
	m_mainImg->setObjectName(QStringLiteral("mainImg"));
	m_mainImg->setEnabled(true);

	//create Toolbar controled GUI
	m_vToolbarGui[APP_TOOLBAR_CUT].reset(new ToolbarCut(m_vGroupBox[APP_GBOX_TOOL_BAR_CUT]) );
	m_vToolbarGui[APP_TOOLBAR_EDIT].reset(new ToolbarEdit(m_vGroupBox[APP_GBOX_TOOL_BAR_EDIT]) );
	m_vToolbarGui[APP_TOOLBAR_COMBINE].reset(new ToolbarCombine(m_vGroupBox[APP_GBOX_TOOL_BAR_COMBINE]) );

	for (ToolbarBasePtr &e : m_vToolbarGui) {
		e->createWidgets();
	}

	//all group box are w.r.t. <m_centralWidget>
	if (m_isShowDebugMsg) {
		m_vLabel[APP_LABEL_LOG_MSG] = new QLabel(m_vGroupBox[APP_GBOX_LOG_MSG]);
		m_vLabel[APP_LABEL_LOG_MSG]->setObjectName(QString::fromStdString(g_AppLabelName[APP_LABEL_LOG_MSG]));
	}

} // setupUi

//todo: support multi-language
void AppGui::retranslateUI(QMainWindow *MainWindow)
{
	MainWindow->setWindowTitle(QApplication::translate("MainWindow", POPUP_MSG_WIN_TITLE, 0));
	m_menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
	m_menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));

	//tool bar icons
	for (int i = 0; i < APP_TOOLBAR_ITEM_CNT; ++i) {
		QAction *p = m_vToolbarAction[i];
		p->setText(QApplication::translate("MainWindow", g_AppToolbarTaskName[i].c_str(), 0));
		p->setIcon(m_vToolbarIcon[i]);
		p->setStatusTip(QString::fromStdString(g_AppToolbarStatusTip[i]));
	}

	m_actionExit->setText(QApplication::translate("MainWindow", "E&xit", 0));
	//m_actionExit->setIcon(const QIcon &icon);

	m_actionHelp->setText(QApplication::translate("MainWindow", "&Help", 0));
	//m_actionHelp->setIcon(const QIcon &icon);

	m_actionAbout->setText(QApplication::translate("MainWindow", "&About", 0));
	//m_actionAbout->setIcon(const QIcon &icon);

	if (m_isShowDebugMsg) {
		m_vGroupBox[APP_GBOX_LOG_MSG]->setTitle(QApplication::translate("MainWindow", "Log Messages", 0));
		m_vLabel[APP_LABEL_LOG_MSG]->setText(QString());
	}

	for (ToolbarBasePtr &e : m_vToolbarGui) {
		e->retranslateUI();
	}


} // retranslateUi


void AppGui::initSettingsFromCfg()
{
	for (int i = 0; i < APP_TOOLBAR_ITEM_CNT; ++i) {
		m_vToolbarGui[i]->initSettings( m_cfg );
	}
}

void AppGui::showBkgImg()
{
	showImg(m_vPixmap[APP_PIXMAP_INIT_BKG]);
}

void AppGui::setupMenu(QMainWindow *mainWin)
{
	//menu bar
	m_menuBar = new QMenuBar(mainWin);
	m_menuBar->setObjectName(QStringLiteral("menuBar"));
	m_menuBar->setNativeMenuBar(false);

	//File
	m_menuFile = new QMenu(m_menuBar);
	m_menuFile->setObjectName(QStringLiteral("menuFile"));

	//Help
	m_menuHelp = new QMenu(m_menuBar);
	m_menuHelp->setObjectName(QStringLiteral("menuHelp"));


	//QIcon icon;
	//icon.addFile(QStringLiteral(":/ClientGui/Resources/exit_icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
	//m_actionExit->setIcon(icon);


	m_actionAbout = new QAction(mainWin);
	m_actionAbout->setObjectName(QStringLiteral("actionAbout"));
	m_actionAbout->setCheckable(true);

	m_actionHelp = new QAction(mainWin);
	m_actionHelp->setObjectName(QStringLiteral("actionHelp"));
	m_actionHelp->setCheckable(true);

	//toolBar actions
	m_toolBar = new QToolBar(mainWin);
	m_toolBar->setObjectName(QStringLiteral("toolBar"));

	for (int i = 0; i < APP_TOOLBAR_ITEM_CNT; ++i) {
		m_vToolbarAction[i] = new QAction(mainWin);
		m_vToolbarAction[i]->setObjectName(QString::fromStdString(g_AppToolbarTaskName[i]));
		m_vToolbarAction[i]->setCheckable(false);
	}

	m_actionExit = new QAction(mainWin);
	m_actionExit->setObjectName(QStringLiteral("actionExit"));
	m_actionExit->setCheckable(false);

	//statusBar = new QStatusBar(mainWin);
	//statusBar->setObjectName(QStringLiteral("statusBar"));

	//add actions to menu bar
	m_menuBar->addAction(m_menuFile->menuAction());
	m_menuBar->addAction(m_menuHelp->menuAction());

	for (int i = 0; i < APP_TOOLBAR_ITEM_CNT; ++i) {
		m_menuFile->addAction(m_vToolbarAction[i]);
	}
	m_menuFile->addSeparator();
	m_menuFile->addAction(m_actionExit);

	m_menuHelp->addAction(m_actionHelp);
	m_menuHelp->addSeparator();
	m_menuHelp->addAction(m_actionAbout);


	for (int i = 0; i < APP_TOOLBAR_ITEM_CNT; ++i) {
		m_toolBar->addAction(m_vToolbarAction[i]);
	}

	//hook up with mainWin
	mainWin->setMenuBar(m_menuBar);
	mainWin->addToolBar(Qt::TopToolBarArea, m_toolBar);
	//mainWin->setStatusBar(statusBar);
}

void AppGui::enableToolBarItems(const bool isEnable )
{
	for (int i = 0; i < APP_TOOLBAR_ITEM_CNT; ++i) {
		m_vToolbarAction[i]->setEnabled(isEnable);
		m_vToolbarAction[i]->setChecked(false);
	}
}

void AppGui::resizeUI(const bool isInit)
{
	int b = APP_GUI_BORDER_SIZE;
	int b2 = 2*b;

	calRects( isInit );
	
	//main window and central widget
	int w = m_mainWinRect.width();
	int h = m_mainWinRect.height();
	m_mainWin->setGeometry(m_mainWinRect );
	m_mainWin->setMaximumSize(w + 30, h + 30);
	m_mainWin->setMinimumSize(w,h);
	m_mainWin->resize(w,h);

	m_centralWidget->setGeometry(0, 0, w, h);
	m_menuBar->setGeometry(QRect(0, 0, w, 21));
	m_toolBar->setGeometry(QRect(0, 0, w, 21));


	//set all groupBox Geometries
	for (int i = 0; i < APP_GBOX_CNT; ++i) {
		m_vGroupBox[i]->setGeometry(m_vGrpBoxRect[i]);
		//dumpLog("i=%d, x1=%d,y1=%d,w=%d,h=%d", i, m_vGrpBoxRect[i].left(), m_vGrpBoxRect[i].top(), m_vGrpBoxRect[i].width(), m_vGrpBoxRect[i].height());
	}

	//set main window to disp <m_mainImg>
	const QRect *pRect = &(m_vGrpBoxRect[APP_GBOX_IMG]);
	m_mainImg->setGeometry(b, b, pRect->width()-b2, pRect->height()-b2);

	//set log message win
	if (m_isShowDebugMsg) {
		pRect = &(m_vGrpBoxRect[APP_GBOX_LOG_MSG]);
		m_vLabel[APP_LABEL_LOG_MSG]->setGeometry(b, b, pRect->width()-b2, pRect->height()-b2);
	}

	//toolbar controled GUI
	for (ToolbarBasePtr &e : m_vToolbarGui) {
		e->resizeUI(isInit);
	}
}

void AppGui::showDebugMsgs(const QString &msg)
{
	if (m_isShowDebugMsg) {
		m_vLabel[APP_LABEL_LOG_MSG]->setText(msg);
	}
}

void AppGui::showImg(const QPixmap &x)
{
	m_mainImg->setPixmap(x);
	m_mainImg->resetNewFram();
}


void AppGui::calRects(const bool isInit)
{
	CfgGui gui =  m_cfg->getGui();

	//acquire image size
	const int b = APP_GUI_BORDER_SIZE;		//border size inside box
	const int b2 = 2 * b;
	const int logWinH = 50;
	const int toolbarCutWinH = 2*APP_LINE_HEIGHT + 3*b;
	const int toolbarEditWinH = 200;
	const int toolbarCombineWinH = 280;

	int imgWinW, imgWinH;
	//acquire main img window size
	const AppToolbarTask t = (AppToolbarTask)m_cfg->getTask();
	if (isInit) {
		imgWinW = gui.dispImgWidthInit;
		imgWinH = gui.dispImgHeightInit;
	}
	else{
		if ( t == APP_TOOLBAR_CUT) {
			imgWinW = gui.dispImgWidthInit;
			imgWinH = gui.dispImgHeightInit;
		}
		else {
			imgWinW = gui.dispImgWidth;
			imgWinH = gui.dispImgHeight;
		}
	}
	for (QRect &r : m_vGrpBoxRect) {
		r.setRect(0, 0, 0, 0);
	}

	int w = imgWinW +b2;
	int x=0, y=0;

	QRect *p = &(m_vGrpBoxRect[APP_GBOX_IMG]);
	p->setRect(x,y, w, imgWinH+b2);

	y = p->bottom() + b;
	if (t == APP_TOOLBAR_UNKN) {
		//do nothing.
	}
	else if (t == APP_TOOLBAR_CUT) {
		p = &(m_vGrpBoxRect[APP_GBOX_TOOL_BAR_CUT]);
		p->setRect(x, y, w, toolbarCutWinH + b2);
	}
	else if (t == APP_TOOLBAR_EDIT) {
		p = &(m_vGrpBoxRect[APP_GBOX_TOOL_BAR_EDIT]);
		p->setRect(x, y, w, toolbarEditWinH + b2);
	}
	else if (t == APP_TOOLBAR_COMBINE) {
		p = &(m_vGrpBoxRect[APP_GBOX_TOOL_BAR_COMBINE]);
		p->setRect(x, y, w, toolbarCombineWinH + b2);
	}
	else {
		appExit("AppGui::calRects(): wrong task flag!");
	}

	//log grp box
	y = p->bottom() + b;
	p = &(m_vGrpBoxRect[APP_GBOX_LOG_MSG]);
	p->setRect(x, y, w, logWinH + b2);

 	QRect *pTopGrpBox = &(m_vGrpBoxRect[APP_GBOX_IMG]);
	m_mainWinRect.setWidth(imgWinW + b2+20);
	m_mainWinRect.setHeight( p->bottom() - pTopGrpBox->top() + 60);
	//dumpLog("m_mainWinRect: x=%d,y=%d,w=%d,h=%d", m_mainWinRect.left(), m_mainWinRect.top(), m_mainWinRect.width(), m_mainWinRect.height());
}
