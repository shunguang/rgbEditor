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
	genSpec(1920,1080);
}

void VideoSpec::reset(const AppSocialMedia_t socialMediaType, const int inputW, const int inputH)
{
	type = socialMediaType;
	name = g_AppSocialMediaName[type];
	genSpec(inputW, inputH);
}

void VideoSpec::genSpec( const int inputW, const int inputH)
{
	genSpec4Default(inputW, inputH);
	if (type == APP_SM_WECHAT)
		genSpec4Wechat(inputW, inputH);
	else if (type == APP_SM_TIKTOK)
		genSpec4Tiktok(inputW, inputH);
	else if (type == APP_SM_TWEETER)
		genSpec4Tweeter(inputW, inputH);
	else if (type == APP_SM_INSTAGRAM)
		genSpec4Instagram(inputW, inputH);
	else if (type == APP_SM_FACEBOOK)
		genSpec4Faccebook(inputW, inputH);
	else if (type == APP_SM_YOUTUBE)
		genSpec4Youtube(inputW, inputH);
}

void VideoSpec::genSpec4Wechat(const int inputW, const int inputH)
{
	vRatios.clear();
	vRatios.push_back(AppRatio(16, 9));
	vRatios.push_back(AppRatio(1, 1));
	vRatios.push_back(AppRatio(4, 5));
	vRatios.push_back(AppRatio(2, 3));
	vRatios.push_back(AppRatio(9, 16));

	float r = (float)inputW/inputH;
	//to do generate sizes
	vImgSzHorizontalVideos[0] = ImgSize(320, 180);
	vImgSzHorizontalVideos[1] = ImgSize(640, 360);
	vImgSzHorizontalVideos[2] = ImgSize(1280, 720);
	vImgSzHorizontalVideos[3] = ImgSize(1280, 1024);
	vImgSzHorizontalVideos[4] = ImgSize(1920, 1080);
	defaultHorizontalSzId = 3;

	vImgSzVerticalVideos[0] = ImgSize(480, 720);    //2:3
	vImgSzVerticalVideos[1] = ImgSize(640, 800);    //4:5
	vImgSzVerticalVideos[2] = ImgSize(1080, 1920);  //9:16
	vImgSzVerticalVideos[3] = ImgSize(1080, 1920);  //9:16
	vImgSzVerticalVideos[4] = ImgSize(1080, 1920);  //9:16
	defaultVerticalSzId = 3;


	vImgSz1To1Videos[0] = ImgSize(inputW, inputW);
	vImgSz1To1Videos[1] = ImgSize(3*inputW/4, 3*inputW/4);
	vImgSz1To1Videos[2] = ImgSize(inputW/2, inputW/2);
	vImgSz1To1Videos[3] = ImgSize(inputW / 4, inputW / 4);
	vImgSz1To1Videos[4] = ImgSize(inputW / 4, inputW / 4);
	default1To1SzId = 0;

	maxFileSz_MB = 4000;
	maxLength_sec = 15;
}

void VideoSpec::genSpec4Tiktok(const int inputW, const int inputH)
{
	vRatios.clear();
	vRatios.push_back(AppRatio(16, 9));
	vRatios.push_back(AppRatio(9, 16));

	vImgSzHorizontalVideos[0] = ImgSize(1920, 1080);
	defaultHorizontalSzId = 0;

	vImgSzVerticalVideos[0] = ImgSize(1080, 1920);
	defaultVerticalSzId = 0;


	maxFileSz_MB = 287.6;
	maxLength_sec = 15;
}

void VideoSpec::genSpec4Tweeter(const int inputW, const int inputH)
{
	vRatios.clear();
	vRatios.push_back(AppRatio(16, 9));
	vRatios.push_back(AppRatio(4, 3));

	vImgSzHorizontalVideos[0] = ImgSize(320,180);
	vImgSzHorizontalVideos[1] = ImgSize(640, 360);
	vImgSzHorizontalVideos[2] = ImgSize(1280, 720);
	vImgSzHorizontalVideos[3] = ImgSize(1280, 1024);
	vImgSzHorizontalVideos[4] = ImgSize(1920, 1200);
	defaultHorizontalSzId = 3;

	vImgSzVerticalVideos[0] = ImgSize(240, 240);
	vImgSzVerticalVideos[1] = ImgSize(480, 480);
	vImgSzVerticalVideos[2] = ImgSize(640, 640);
	vImgSzVerticalVideos[3] = ImgSize(1200, 1900);
	defaultVerticalSzId = 3;

	maxFileSz_MB = 512;
	maxLength_sec = 140;
}

void VideoSpec::genSpec4Instagram(const int inputW, const int inputH)
{
	genSpec4Default(inputW, inputH);
}

void VideoSpec::genSpec4Faccebook(const int inputW, const int inputH)
{
	genSpec4Default(inputW, inputH);
}

void VideoSpec::genSpec4Youtube(const int inputW, const int inputH)
{
	vRatios.clear();
	vRatios.push_back(AppRatio(16, 9));
	vRatios.push_back(AppRatio(4, 3));

	vImgSzHorizontalVideos[0] = ImgSize(640,360);
	vImgSzHorizontalVideos[1] = ImgSize(854, 480);
	vImgSzHorizontalVideos[2] = ImgSize(1280,720);
	vImgSzHorizontalVideos[3] = ImgSize(1920,1080);
	vImgSzHorizontalVideos[4] = ImgSize(2560, 1440);
	vImgSzHorizontalVideos[5] = ImgSize(3840, 2160);
	defaultHorizontalSzId = 3;
}

void VideoSpec::genSpec4Default(const int inputW, const int inputH)
{
	vRatios.clear();
	vRatios.push_back(AppRatio(16, 9));
	vRatios.push_back(AppRatio(1, 1));	//square
	vRatios.push_back(AppRatio(4, 5));  //vertical
	vRatios.push_back(AppRatio(2, 3));  //vertical
	vRatios.push_back(AppRatio(9, 16)); //portrait
	minW = 32;
	maxW = 4096;

	defaultVerticalSzId = 0;
	defaultVerticalSzId = 0;
	default1To1SzId = 0;
	int w = 1920, h = 1080;
	for (int i = 0; i < APP_MAX_VIDEO_SZ_ITEMS; ++i) {
		vImgSzHorizontalVideos[i] = ImgSize(w, h);
		vImgSzVerticalVideos[i] = ImgSize(h, w);
		vImgSz1To1Videos[i] = ImgSize(w, w);

		w = w / 2;
		h = h / 2;
	}

	maxLength_sec = 140;
	maxFileSz_MB = 512;
	codec = "H264";
	fileType = "mp4";
	maxFps = 30;
	fps = 25;
}

