/*
*------------------------------------------------------------------------
*CfgInput.h
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
//config for combine toolbar
#ifndef __CFG_COMBINE_INPUT_H__
#define __CFG_COMBINE_INPUT_H__

#include "CfgInput.h"
namespace app {
	class  CFG_EXPORT CfgCombineInput : public CfgInput {
	public:
		CfgCombineInput();
		CfgCombineInput( const CfgCombineInput &x )=default;
		virtual ~CfgCombineInput();
		CfgCombineInput& operator = (const CfgCombineInput &x) = default;

		virtual boost::property_tree::ptree toPropertyTree();
		virtual void fromPropertyTree(const boost::property_tree::ptree &pt);

		void setPrms(const CfgCombineInput &x) {
			*this = x;
		}
	public:
		std::string					inputVideoFolder;
		std::string					inputVideoFileFilter;
		std::vector<std::string>	vInputVideoFileNames;
		std::string					mp3File;
		int							mp3Percentage;
	};
	typedef std::shared_ptr<CfgCombineInput>		CfgCombineInputPtr;
}

#endif
