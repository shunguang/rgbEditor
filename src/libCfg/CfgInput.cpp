/*
*------------------------------------------------------------------------
*CfgInput.cpp
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
#include "CfgInput.h"

using namespace std;
using namespace app;

CfgInput::CfgInput()
	: CfgBase()
	, inputVideoFolder("")
	, inputVideoFileFilter("")
	, vInputVideoFileNames()
	, mp3File("")
	, mp3Percentage(0)
{
}

void CfgInput::fromPropertyTree(const boost::property_tree::ptree &pt)
{
	inputVideoFileFilter = pt.get<std::string>("inputVideoFileFilter");
	inputVideoFolder = pt.get<std::string>("inputVideoFolder");

	const boost::property_tree::ptree pt1 = pt.get_child("videoFiles");
	//cout << game.name << ", " << pt1.size() << endl;
	vInputVideoFileNames.clear();
	BOOST_FOREACH(const boost::property_tree::ptree::value_type &vk, pt1) {
		const string fpath = vk.second.data();
		//if (!boost::filesystem::exists(fpath)) {
		//	dumpLog( "AppCfg::fromPropertyTree(): file %s does not exist!", fpath.c_str() );
		//}
		vInputVideoFileNames.push_back(fpath);
	}
	mp3File = pt.get<std::string>("mp3File");
	mp3Percentage = pt.get<int>("mp3Percentage");

}

boost::property_tree::ptree CfgInput::toPropertyTree()
{
	boost::property_tree::ptree pt;

	pt.put("inputVideoFileFilter", inputVideoFileFilter);
	pt.put("inputVideoFolder", inputVideoFolder);
	BOOST_FOREACH(const string &fp, vInputVideoFileNames) {
		pt.add("videoFiles.video", fp);
	}
	pt.put("mp3File", mp3File);
	pt.put("mp3Percentage", mp3Percentage);

	return pt;
}

