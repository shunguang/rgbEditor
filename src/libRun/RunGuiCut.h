/*
*-------------------------------------------------------------------
* RunGuiCut.h
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

#ifndef __RUN_GUI_CUT_H__
#define __RUN_GUI_CUT_H__

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
	class LIBRUN_EXPORT RunGuiCut : public QMainWindow
	{
		Q_OBJECT

	public:
		//all the threads share the same cfg located at only one physical address
		RunGuiCut( RunGuiDcPtr &dc );
		~RunGuiCut();

	public slots:
		//input file path
		void on_pushButton_inputFile_clicked();
		void on_lineEdit_inputFile_edited(const QString &s);

		//output folder
		void on_pushButton_outputFolder_clicked();
		void on_lineEdit_outputFolder_edited(const QString &s);

		//start/quit buttons	
		void on_pushButton_cutQuit_clicked();
		void on_pushButton_cutStart_clicked();

	private:
		RunGuiDcPtr		m_dc;

		ToolbarCut*		m_cutWgts;

		//not neccessary but just for convince coding
		AppCfg		*m_appCfg;
		AppGui		*m_appUi;

		CfgCutInput		m_inputCfg;
		CfgCutOutput	m_outputCfg;
	};
	typedef std::shared_ptr<RunGuiCut>	RunGuiCutPtr;
}
#endif // CLIENTGUI_H

