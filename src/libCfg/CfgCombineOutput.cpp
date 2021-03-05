/*
*------------------------------------------------------------------------
*CfgCombineOutput.cpp
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

#include "CfgCombineOutput.h"
using namespace app;
using namespace std;
CfgCombineOutput::CfgCombineOutput()
	: CfgOutput(APP_TOOLBAR_COMBINE)
{}

CfgCombineOutput::~CfgCombineOutput()
{
}


boost::property_tree::ptree CfgCombineOutput::toPropertyTree()
{
	boost::property_tree::ptree pt;
	return pt;
}

void CfgCombineOutput::fromPropertyTree(const boost::property_tree::ptree &pt)
{
#if 0
	 headerVidoeFilePath = pt.get<std::string>("headerVidoeFilePath");
	 highlightSegmentLengthInSec = pt.get<float>("highlightSegmentLengthInSec");
	 minSegmentTimeSec = pt.get<float>("minSegmentTimeSec");
	 insertingVidoeFilePath = pt.get<std::string>("insertingVidoeFilePath");
	 originalAudioIntensity = pt.get<float>("originalAudioIntensity");
	 outputVideoFolder = pt.get<std::string>("outputVideoFolder");
	 isRenderTeamInfo = (bool)pt.get<uint8>("isRenderTeamInfo");

	//todo:
	 showDebugMsg = false;
	 vOutputVideoFileFmts.clear();
	 vOutputVideoFileFmts.push_back("mp4");
	 vOutputVideoFileFmts.push_back("avi");
	 outputVideoFmtIdx = 0;


	 vOutputVideoFrmSizes.clear();
	 vOutputVideoFrmSizes.push_back("Original");
	 vOutputVideoFrmSizes.push_back("1280x720");
	 vOutputVideoFrmSizes.push_back("640x480");
	 vOutputVideoFrmSizes_value.clear();
	 vOutputVideoFrmSizes_value.push_back(cv::Size(0, 0));
	 vOutputVideoFrmSizes_value.push_back(cv::Size(1280, 720));
	 vOutputVideoFrmSizes_value.push_back(cv::Size(640, 480));
	 outputVideoSizeIdx = 0;

	 vOutputVideoFrmRates.clear();
	 vOutputVideoFrmRates.push_back("Original");
	 vOutputVideoFrmRates.push_back("30");
	 vOutputVideoFrmRates.push_back("60");
	 outputVideoFpsIdx = 0;

	 vOutputVideoFrmRates_value.clear();
	 vOutputVideoFrmRates_value.push_back(0);   //
	 vOutputVideoFrmRates_value.push_back(30);
	 vOutputVideoFrmRates_value.push_back(60);

	 uploadPlatformIdx = 0;
	 vUploadPlatforms.push_back("YouTube");
	 vUploadPlatforms.push_back("Facebook");
	 vUploadPlatforms.push_back("Twitter");
	 vUploadPlatforms.push_back("Instagram");
	 vUploadPlatforms.push_back("Youku");
#endif
}

void CfgCombineOutput::genOutputVideoInfo()
{
}
