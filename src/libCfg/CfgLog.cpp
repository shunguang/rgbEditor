/*
*------------------------------------------------------------------------
*CfgLog.cpp
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

#include "CfgLog.h"
using namespace app;
using namespace std;
CfgLog::CfgLog()
	: CfgBase()
	, logFolder("c:/temp")
	, projProfileFolder("c:/temp/projectProfile")
	, isDumpLog(1)
	, isShowLogInConsole(0)
	, isDumpSelectedRawAudio(0)
{}


boost::property_tree::ptree CfgLog::toPropertyTree()
{
	boost::property_tree::ptree pt;
	//log
	pt.put("isDumpLog",					(uint8)isDumpLog);
	pt.put("isShowLogInConsole",		(uint8)isShowLogInConsole);
	pt.put("isDumpSelectedRawAudio",	(uint8)isDumpSelectedRawAudio);
	pt.put("logFolder",					logFolder);
	pt.put("projProfileFolder",			projProfileFolder);
	return pt;
}

void CfgLog::fromPropertyTree(const boost::property_tree::ptree &pt)
{
	isDumpLog = (bool)pt.get<uint8>("isDumpLog");
	isShowLogInConsole = (bool)pt.get<uint8>("isShowLogInConsole");
	isDumpSelectedRawAudio = (bool)pt.get<uint8>("isDumpSelectedRawAudio");
	logFolder = pt.get<std::string>("logFolder");
	projProfileFolder = pt.get<std::string>("projProfileFolder");
}
