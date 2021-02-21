/*
*-------------------------------------------------------------------
* CfgDc.h
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

#ifndef __CFG_DC_H__
#define __CFG_DC_H__

#include "libUtil/libUtil.h"
#include "CfgBase.h"
namespace app {
	class  CfgDc : public CfgBase {
	public:	
		CfgDc() : qSize(10) {};
		CfgDc(const CfgDc &x) = default;
		CfgDc& operator = (const CfgDc &x) = default;
		virtual ~CfgDc() { CfgBase::~CfgBase(); };

		virtual boost::property_tree::ptree toPropertyTree()
		{
			boost::property_tree::ptree pt;
			pt.put("qSize", qSize);
			return pt;
		}

		virtual void fromPropertyTree(const boost::property_tree::ptree &pt)
		{
			qSize = 10;
		}

	public:
		int		qSize;
	};
	typedef std::shared_ptr<CfgDc>		CfgDcPtr;
}
#endif
