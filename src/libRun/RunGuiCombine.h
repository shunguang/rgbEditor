/*
*-------------------------------------------------------------------
* RunGuiCombine.h
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
#ifndef __RUN_GUI_COMBINE_H__
#define __RUN_GUI_COMBINE_H__

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
	class LIBRUN_EXPORT RunGuiCombine : public QMainWindow
	{
		Q_OBJECT

	public:
		//all the threads share the same cfg located at only one physical address
		RunGuiCombine( RunGuiDcPtr &dc );
		~RunGuiCombine();

	public slots:
		void on_pushBotton_combineBrowseFolder_clicked();
		void on_pushBotton_combineBrowseMp3_clicked();
		void on_pushBotton_combineLoadAll_clicked();
		void on_pushBotton_combineRemoveAll_clicked();
		void on_pushBotton_combineBrowseAppendOne_clicked();
		void on_pushBotton_combineBrowseRemoveOne_clicked();
		void on_pushBotton_combineUp_clicked();
		void on_pushBotton_combineDown_clicked();

		void on_lineEdit_inputVideoFolder_edited(const QString &s);
		void on_lineEdit_inputMp3Path_edited(const QString &s);
		void on_sliderMp3_valueChgd(int value);

		//output group
		void on_pushBotton_outputFolder_clicked();
		void on_lineEdit_outputVideoFolder_edited(const QString &s);
		void on_lineEdit_outputUserDefineW_edited(const QString &s);
		void on_lineEdit_outputUserDefineH_edited(const QString &s);
		void on_comboBox_outputSocialMedia_currentIndexChanged(const int newIdx);
	private:
		RunGuiDcPtr			m_dc;
		Input4CombinePtr	m_inWgts;
		OutputGrpPtr		m_outWgts;

		//not neccessary but just for convince coding
		AppCfg		*cfg;
		AppGui		*ui;

		CfgInput	m_inputCfg;
		CfgOutput	m_outputCfg;
	};
	typedef std::shared_ptr<RunGuiCombine>	RunGuiCombinePtr;
}
#endif // CLIENTGUI_H

