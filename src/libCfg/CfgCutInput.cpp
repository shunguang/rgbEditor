/*
*------------------------------------------------------------------------
*CfgCutInput.cpp
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
#include "CfgCutInput.h"

using namespace std;
using namespace app;

CfgCutInput::CfgCutInput()
	: CfgInput(APP_TOOLBAR_CUT)
	, inputVideoFilepath(".")
	, inputVideoFileFilter(".")
//	, inputVideoFolder(".")
{
}

CfgCutInput::~CfgCutInput()
{
}


void CfgCutInput::fromPropertyTree(const boost::property_tree::ptree &pt)
{
	inputVideoFilepath		= pt.get<std::string>("inputVideoFilepath");
	inputVideoFileFilter	= pt.get<std::string>("inputVideoFileFilter");
//	inputVideoFolder		= pt.get<std::string>("inputVideoFolder");
}

boost::property_tree::ptree CfgCutInput::toPropertyTree()
{
	boost::property_tree::ptree pt;
	pt.put("inputVideoFilepath",	inputVideoFilepath);
	pt.put("inputVideoFileFilter",	inputVideoFileFilter);
//	pt.put("inputVideoFolder",		inputVideoFolder);
	return pt;
}

