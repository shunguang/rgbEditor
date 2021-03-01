/*
*-------------------------------------------------------------------
* RunAppGui.h
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
//RunGuiDc an data container shared by all RunGui related object

#ifndef __RUN_GUI_DC_H__
#define __RUN_GUI_DC_H__

#include "libUtil/libUtil.h"
#include "libCfg/AppCfg.h"
#include "libDc/libDc.h"

#include "libGui/AppGui.h"
#include "libGui/GuiUtil.h"

#include "RunDefs.h"

#define TMP_BUF_SIZE			1024
#define NUM_SUB_PROGRESS		3
#define MY_QT_CONN				Qt::UniqueConnection

namespace app {
	class LIBRUN_EXPORT RunGuiDc
	{
	public:
		//all the threads share the same cfg located at only one physical address
		RunGuiDc(AppCfgPtr &cfg, AppGuiPtr &ui);
		RunGuiDc(const RunGuiDc &x) = delete;
		~RunGuiDc();
		RunGuiDc& operator = (const RunGuiDc &x) = delete;

		void showDebugMsg(const char *fmt, ...);
		void showDebugMsg(const std::string &msg);
	public:
		AppCfgPtr	m_cfg;      //accessed by multi-threads
		AppGuiPtr	m_ui;


		DcUIPtr		m_sharedDC;	//data container shared with other threads/filters

		uint32		m_frmNum;
		bool		m_guiReady;
		bool		m_showDebugMsg;

		uint64				m_currVideoKeyFrmIdx;    //current browsing key frames idx for current video
		uint64				m_currVideoTotalKeyFrms;      //total # of key frames for current video
		float64				m_currVideoDurationSec;

		boost::mutex m_debugMsgMutex;
		std::deque<std::string> m_debugMsgQ;
		RawFrmPtr				m_thumbnailFrm;
		DispFrmPtr				m_dispFrm;

		int						m_nTotInputFiles;
		int                     m_progressPercentage[NUM_SUB_PROGRESS]; //0-PRO_MSG_DEMUX_AUDIO, 1-PRO_MSG_ANA_AUDIO,2-PRO_MSG_WRT_VIDEO
		int                     m_timeUsedSec[NUM_SUB_PROGRESS];

		int								    m_currFileId;
		std::vector<DispFrm>				m_vUsrSelectedKeyDispFrms;    //the latest user selected dispFrms for each video file   
		//std::vector<std::vector<RngWorld>>	m_vUsrSelectedKeyFrmRngs;     //key frm Rngs

		int m_startProcess_button_task;     //0-the task flag of startProcess_button: decoding/analyzing,  1-write output video
		bool m_saveDispImg4FileIdSwitch;
		bool m_isShowKeyFrm;
		boost::mutex m_runGuiMutex;
	};
	typedef std::shared_ptr<RunGuiDc>		RunGuiDcPtr;

}
#endif


