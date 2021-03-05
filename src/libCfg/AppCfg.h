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

#include "libUtil/libUtil.h"
#include "CfgLog.h"
#include "CfgCutInput.h"
#include "CfgCutOutput.h"

#include "CfgEditInput.h"
#include "CfgEditCtrl.h"
#include "CfgEditOutput.h"

#include "CfgCombineInput.h"
#include "CfgCombineOutput.h"

#include "CfgGui.h"
#include "CfgDc.h"
#include "CfgRenderImg.h"
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

		void getInput(CfgCutInput &x);
		void getInput(CfgEditInput &x);
		void getInput(CfgCombineInput &x);

		void setInput(const CfgCombineInput &x) {
			setInputT<CfgCombineInput>(x);
		}
		void setInput(const CfgCutInput &x) {
			setInputT<CfgCutInput>(x);
		}
		void setInput(const CfgEditInput &x) {
			setInputT<CfgEditInput>(x);
		}


		void getOutput(CfgCutOutput &x);
		void getOutput(CfgEditOutput &x);
		void getOutput(CfgCombineOutput &x);

		void setOutput(const CfgCutOutput &x) {
			setOutputT<CfgCutOutput>(x);
		}
		void setOutput(const CfgEditOutput &x) {
			setOutputT<CfgEditOutput>(x);
		}
		void setOutput(const CfgCombineOutput &x) { 
			setOutputT<CfgCombineOutput>(x); 
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

		CfgDc getDc() {
			CfgDc ret;
			{
				boost::mutex::scoped_lock lock(m_mutexCfg);
				ret = *(m_dc.get());
			}
			return ret;
		}

		void setDc(const CfgDc &x) {
			boost::mutex::scoped_lock lock(m_mutexCfg);
			*(m_dc.get()) = x;
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
		template <class T>
		void setOutputT(const T &x)
		{
			boost::mutex::scoped_lock lock(m_mutexCfg);
			T *p = dynamic_cast<T *>(m_vOutput[x.toolbarId].get());
			p->setPrms(x);
		}

		template <class T>
		void setInputT(const T &x)
		{
			boost::mutex::scoped_lock lock(m_mutexCfg);
			T *p = dynamic_cast<T *>(m_vInput[x.toolbarId].get());
			p->setPrms(x);
		}

		virtual boost::property_tree::ptree toPropertyTree();
		virtual void fromPropertyTree(const boost::property_tree::ptree &pt);

	public:
		int						m_toolbarTaskId;

		CfgDemuxingDecodingPtr	m_demux;
		CfgGuiPtr	            m_gui;
		CfgLogPtr				m_log;
		//CfgRenderImg        m_imgRender;
		CfgDcPtr				m_dc;            //m_dc is already used, for less confusion in search

		CfgInputPtr				m_vInput[APP_TOOLBAR_ITEM_CNT];
		CfgOutputPtr			m_vOutput[APP_TOOLBAR_ITEM_CNT];
	private:
		boost::mutex	m_mutexCfg;

		//do not change, the order is defibned by enum AppToolbarTask{}, which will be used to make xml file filed names
		//such as <inputCut> ... </inputCut>, <outputCut> ... </outputCut>, <inputEdit> ... </inputEdit> etc
		const std::vector<std::string>	m_vToobarNames = { "Cut","Edit","Combine" };
	};

	typedef std::shared_ptr<AppCfg>		AppCfgPtr;
}
#endif
