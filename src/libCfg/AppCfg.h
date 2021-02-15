/*
*-------------------------------------------------------------------
* AppCfg.h
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

//todo : extend to thread safe
#ifndef __APP_CFG_H__
#define __APP_CFG_H__

#include "libUtil/DataTypes.h"
#include "libUtil/AppLog.h"
#include "libUtil/UtilFuncs.h"
#include "CfgUtil.h"
#include "CfgLog.h"
#include "CfgInput.h"
#include "CfgOutput.h"
#include "CfgGui.h"
#include "CfgDemuxingDecoding.h"
namespace app {
	//--------------------------------------
	class AppCfg {
	public:
		AppCfg();
		~AppCfg();

		void readFromFile(const char *fname);
		void writeToFile(const char *fanme);
		std::string toStr();

		CfgInput getInput() {
			CfgInput ret;
			{
				boost::mutex::scoped_lock lock(m_mutexCfg);
				ret = *(m_input.get());
			}
			return ret;
		}

		void setInput( const CfgInput &x) {
			boost::mutex::scoped_lock lock(m_mutexCfg);
			*(m_input.get()) = x;
		}


		CfgOutput getOutput() {
			CfgOutput ret;
			{
				boost::mutex::scoped_lock lock(m_mutexCfg);
				ret = *(m_output.get());
			}
			return ret;
		}

		void setOutput(const CfgOutput &x) {
			boost::mutex::scoped_lock lock(m_mutexCfg);
			*(m_output.get()) = x;
		}

		CfgGui getGui() {
			CfgGui ret;
			{
				boost::mutex::scoped_lock lock(m_mutexCfg);
				ret = *(m_gui.get());
			}
			return ret;
		}

		void setGui(const CfgGui &x) {
			boost::mutex::scoped_lock lock(m_mutexCfg);
			*(m_gui.get()) = x;
		}

		CfgLog getLog() {
			CfgLog ret;
			{
				boost::mutex::scoped_lock lock(m_mutexCfg);
				ret = *(m_log.get());
			}
			return ret;
		}

		void setLog(const CfgLog &x) {
			boost::mutex::scoped_lock lock(m_mutexCfg);
			*(m_log.get()) = x;
		}

		int getTask() {
			int t;
			{
				boost::mutex::scoped_lock lock(m_mutexCfg);
				t = m_toolbarTaskId;
			}
			return t;
		}

		void setTask( const int t ) {
			boost::mutex::scoped_lock lock(m_mutexCfg);
			m_toolbarTaskId = t;
		}


	private:
		virtual boost::property_tree::ptree toPropertyTree();
		virtual void fromPropertyTree(const boost::property_tree::ptree &pt);

		virtual boost::property_tree::ptree toPropertyTreeTeamInfo();
		virtual void fromPropertyTreeTeamInfo(const boost::property_tree::ptree &pt);

	public:
		int						m_toolbarTaskId;

		CfgDemuxingDecodingPtr	m_demux;
		CfgInputPtr				m_input;
		CfgOutputPtr			m_output;
		CfgGuiPtr	            m_gui;

		CfgLogPtr				m_log;

		//CfgRenderImg        m_imgRender;
		//CfgDc				m_dc0;            //m_dc is already used, for less confusion in search
	private:
		boost::mutex	m_mutexCfg;
	};

	typedef std::shared_ptr<AppCfg>		AppCfgPtr;
}
#endif
