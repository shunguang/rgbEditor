/*
*-------------------------------------------------------------------
* Roi.h
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

#include "VideoSpec.h"

using namespace app;
using namespace std;

VideoSpec::VideoSpec(const AppSocialMedia_t socialMediaType)
	: type(socialMediaType)
	, name(g_AppSocialMediaName[type])
	, minW(32)
	, maxW(4096)
	, maxLength_sec(15)
	, maxFileSz_MB(512)
	, codec("H264")
	, fileType("mp4")
	, maxFps(30)
	, fps(25)
{
	genSpec();
}

void VideoSpec::reset(const AppSocialMedia_t socialMediaType)
{
	type = socialMediaType;
	name = g_AppSocialMediaName[type];

	genSpec();
}

void VideoSpec::genSpec()
{
	genSpec4Default();
	if (type == APP_SM_WECHAT)
		genSpec4Wechat();
	else if (type == APP_SM_TIKTOK)
		genSpec4Tiktok();
	else if (type == APP_SM_TWEETER)
		genSpec4Tweeter();
	else if (type == APP_SM_INSTAGRAM)
		genSpec4Instagram();
	else if (type == APP_SM_FACEBOOK)
		genSpec4Faccebook();
	else if (type == APP_SM_YOUTUBE)
		genSpec4Youtube();
}

void VideoSpec::genSpec4Wechat()
{
	vRatios.clear();
	vRatios.push_back(AppRatio(16, 9));
	vRatios.push_back(AppRatio(1, 1));
	vRatios.push_back(AppRatio(4, 5));
	vRatios.push_back(AppRatio(2, 3));
	vRatios.push_back(AppRatio(9, 16));

	vImgSz4HorizontalVideos[0] = ImgSize(320, 180);
	vImgSz4HorizontalVideos[1] = ImgSize(640, 360);
	vImgSz4HorizontalVideos[2] = ImgSize(1280, 720);
	vImgSz4HorizontalVideos[3] = ImgSize(1280, 1024);
	vImgSz4HorizontalVideos[4] = ImgSize(1920, 1080);
	defaultHorizontalSzId = 3;

	vImgSz4VerticalVideos[0] = ImgSize(240, 240);    //1:1
	vImgSz4VerticalVideos[1] = ImgSize(480, 720);    //2:3
	vImgSz4VerticalVideos[2] = ImgSize(640, 800);    //4:5
	vImgSz4VerticalVideos[3] = ImgSize(1080, 1920);  //9:16
	defaultVerticalSzId = 3;

	maxFileSz_MB = 4000;
	maxLength_sec = 15;
}

void VideoSpec::genSpec4Tiktok()
{
	vRatios.clear();
	vRatios.push_back(AppRatio(16, 9));
	vRatios.push_back(AppRatio(9, 16));

	vImgSz4HorizontalVideos[0] = ImgSize(1920, 1080);
	defaultHorizontalSzId = 0;

	vImgSz4VerticalVideos[0] = ImgSize(1080, 1920);
	defaultVerticalSzId = 0;

	maxFileSz_MB = 287.6;
	maxLength_sec = 15;
}

void VideoSpec::genSpec4Tweeter()
{
	vRatios.clear();
	vRatios.push_back(AppRatio(16, 9));
	vRatios.push_back(AppRatio(4, 3));

	vImgSz4HorizontalVideos[0] = ImgSize(320,180);
	vImgSz4HorizontalVideos[1] = ImgSize(640, 360);
	vImgSz4HorizontalVideos[2] = ImgSize(1280, 720);
	vImgSz4HorizontalVideos[3] = ImgSize(1280, 1024);
	vImgSz4HorizontalVideos[4] = ImgSize(1920, 1200);
	defaultHorizontalSzId = 3;

	vImgSz4VerticalVideos[0] = ImgSize(240, 240);
	vImgSz4VerticalVideos[1] = ImgSize(480, 480);
	vImgSz4VerticalVideos[2] = ImgSize(640, 640);
	vImgSz4VerticalVideos[3] = ImgSize(1200, 1900);
	defaultVerticalSzId = 3;

	maxFileSz_MB = 512;
	maxLength_sec = 140;
}

void VideoSpec::genSpec4Instagram()
{
}

void VideoSpec::genSpec4Faccebook()
{
}

void VideoSpec::genSpec4Youtube()
{
	vRatios.clear();
	vRatios.push_back(AppRatio(16, 9));
	vRatios.push_back(AppRatio(4, 3));

	vImgSz4HorizontalVideos[0] = ImgSize(640,360);
	vImgSz4HorizontalVideos[1] = ImgSize(854, 480);
	vImgSz4HorizontalVideos[2] = ImgSize(1280,720);
	vImgSz4HorizontalVideos[3] = ImgSize(1920,1080);
	vImgSz4HorizontalVideos[4] = ImgSize(2560, 1440);
	vImgSz4HorizontalVideos[5] = ImgSize(3840, 2160);
	defaultHorizontalSzId = 3;
}

void VideoSpec::genSpec4Default()
{
	vRatios.clear();
	vRatios.push_back(AppRatio(16, 9));
	vRatios.push_back(AppRatio(1, 1));	//square
	vRatios.push_back(AppRatio(4, 5));  //vertical
	vRatios.push_back(AppRatio(2, 3));  //vertical
	vRatios.push_back(AppRatio(9, 16)); //portrait
	minW = 32;
	maxW = 4096;

	defaultVerticalSzId = -1;
	defaultVerticalSzId = -1;
	for (int i = 0; i < APP_MAX_VIDEO_SZ_ITEMS; ++i) {
		vImgSz4HorizontalVideos[i] = ImgSize(-1, -1);
		vImgSz4VerticalVideos[i] = ImgSize(-1, -1);
	}

	maxLength_sec = 140;
	maxFileSz_MB = 512;
	codec = "H264";
	fileType = "mp4";
	maxFps = 30;
	fps = 25;
}

