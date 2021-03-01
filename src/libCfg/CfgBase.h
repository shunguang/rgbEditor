/*
*------------------------------------------------------------------------
*CfgBase.h
*
* This code was developed by Shunguang Wu in his spare time. No government
* or any client funds were used.
*
*
* THE SOFTWARE IS PROVIDED AS-IS AND WITHOUT WARRANTY OF ANY KIND,
* EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
* WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
*
* IN NO EVENT SHALL THE AUTHOR OR DISTRIBUTOR BE LIABLE FOR
* ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
* OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
* WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
* LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
* OF THIS SOFTWARE.
*
* Permission to use, copy, modify, distribute, and sell this software and
* its documentation for any purpose is prohibited unless it is granted under
* the author's written notice.
*
* Copyright(c) 2020 by Shunguang Wu, All Right Reserved
*-------------------------------------------------------------------------
*/
#ifndef __CFG_BASE_H__
#define __CFG_BASE_H__

#include "libUtil/libUtil.h"
#include "CfgDefs.h"
namespace app {
	enum AppToolbarTask {
		APP_TOOLBAR_UNKN = -1,
		APP_TOOLBAR_CUT = 0,
		APP_TOOLBAR_EDIT,
		APP_TOOLBAR_COMBINE,
		APP_TOOLBAR_ITEM_CNT
	};
	static std::vector<std::string> g_AppToolbarTaskName = { "&Cut Video",  "&Edit Video",  "C&ombine Videos", "task unkn" };
	static std::vector<std::string>	g_AppToolbarStatusTip = {
		"cut long videos into short ones",
		"edit short videos",
		"combine iamges and short videos into long one",
		"please choose an task"
	};

	class CFG_EXPORT CfgBase {
	public:
		CfgBase();
		CfgBase(const CfgBase &x) = default;
		CfgBase& operator = (const CfgBase &x) = default;
		virtual ~CfgBase() = default;

		virtual boost::property_tree::ptree toPropertyTree() = 0;
		virtual void fromPropertyTree(const boost::property_tree::ptree &pt) = 0;
		virtual std::string toString();

		static std::string toString(const boost::property_tree::ptree &pt);
	};
	typedef std::shared_ptr<CfgBase>		CfgBasePtr;
}

#endif




