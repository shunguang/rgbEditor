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

#ifndef __APP_GUI_H__
#define __APP_GUI_H__


#include "libDc/AppCfg.h"
#include "libUtil/UtilFuncs.h"
#include "GuiUtil.h"
#include "MsgBox.h"
#include "ImgLabel.h"
#include "PlayerControls.h"
#include "GuiDefs.h"
#include "MultiRngSliders.h"

#include "ToolbarBase.h"
#include "ToolbarCut.h"
#include "ToolbarEdit.h"
#include "ToolbarCombine.h"


namespace app {

	class AppGui : public  QWidget
	{
	public:
		AppGui();
		void setupUi(QMainWindow *MainWindow, AppCfgPtr &cfg_ /*its value may be changed through gui settings*/);
		void showImg(const QPixmap &x);
		void showDebugMsgs(const QString &msg);
		void switchToolbarTaskTo(const AppToolbarTask newTask );

	private:
		void setupMenu(QMainWindow *mainWin);
		void createAppWidgets(QMainWindow *MainWindow);

		void retranslateUI(QMainWindow *MainWindow);
		void initSettings();
		void calRects( const bool isInit );
		void resizeUI(const bool isInit );
		void enableToolBarItems( bool isEnable );

	public:
		ImgLabel	*m_mainImg;
		QLabel		*m_vLabel[APP_LABEL_CNT];
		ToolbarBasePtr	m_vToolbarGui[APP_TOOLBAR_ITEM_CNT];
	public:
		QAction		*m_actionExit;
		QAction		*m_actionHelp;
		QAction		*m_actionAbout;
		QAction		*m_vToolbarAction[APP_TOOLBAR_ITEM_CNT];          //cut large videos to small files to edit

	protected:
		QMainWindow *m_mainWin;
		QWidget		*m_centralWidget;
		QRect	 	m_mainWinRect;
		QGroupBox	*m_vGroupBox[APP_GBOX_CNT];
		QRect	 	 m_vGrpBoxRect[APP_GBOX_CNT];	// the location of group boxes w.r.t. <m_centralWidget>
		QPixmap		 m_vPixmap[APP_PIXMAP_CNT];

		//--- menu bar and items ---
		QMenuBar	*m_menuBar;
		QMenu		*m_menuFile;
		QMenu		*m_menuHelp;
		QToolBar	*m_toolBar;

		//QStatusBar *statusbar;
		QIcon		 m_vToolbarIcon[APP_TOOLBAR_ITEM_CNT];

	protected:
		AppCfgPtr	m_cfg;
		bool		m_isShowDebugMsg;
		int			m_dispImgW, m_dispImgH;
		int			m_dispImgWInit, m_dispImgHInit;

	};
}

#endif // UI_SATGUI_H
