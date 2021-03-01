/*
*------------------------------------------------------------------------
*CfgOutput.h
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
//config for single camera related stuff
#ifndef __CFG_OUTPUT_H__
#define __CFG_OUTPUT_H__

#include "CfgBase.h"
namespace app {
	struct OutputVideoInfo {
		std::string  fielname;
		float		 frmRate;
		cv::Size	 frmSize;
		int			 fmt;
	};

	class CfgOutput : public CfgBase {
	public:
		CfgOutput(const int toolbarId_);
		CfgOutput(const CfgOutput &x) = default;
		virtual ~CfgOutput();

		CfgOutput& operator = (const CfgOutput &x) = default;

		virtual boost::property_tree::ptree toPropertyTree()=0;
		virtual void fromPropertyTree(const boost::property_tree::ptree &pt)=0;
		virtual void genOutputVideoInfo() = 0;

	public:
		int	 toolbarId;
		std::string  outputVideoFolder;
		std::vector	 <OutputVideoInfo> vOutputVideoInfo;
	};

	typedef std::shared_ptr<CfgOutput>		CfgOutputPtr;
}
#endif

