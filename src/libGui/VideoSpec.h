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
#ifndef _VIDEO_SPEC_H_
#define _VIDEO_SPEC_H_

#include "libUtil/libUtil.h"
#include "GuiDefs.h"

#define APP_MAX_VIDEO_SZ_ITEMS	7
namespace app {
	
	class GUI_EXPORT VideoSpec {
	
	public:
		VideoSpec( const AppSocialMedia_t socialMediaType = APP_SM_WECHAT);
		VideoSpec(const VideoSpec &x)=delete;
		~VideoSpec()=default;
		VideoSpec& operator=(const VideoSpec &x) = delete;

		void reset(const AppSocialMedia_t socialMediaType, const int inputW, const int inputH);

	protected:
		//give input video size, generate potential output video sizses 
		void genSpec(const int inputW, const int inputH);
		void genSpec4Wechat(const int inputW, const int inputH);
		void genSpec4Tiktok(const int inputW, const int inputH);
		void genSpec4Tweeter(const int inputW, const int inputH);
		void genSpec4Instagram(const int inputW, const int inputH);
		void genSpec4Faccebook(const int inputW, const int inputH);
		void genSpec4Youtube(const int inputW, const int inputH);
		void genSpec4Default(const int inputW, const int inputH);

	public:
		AppSocialMedia_t		type;
		std::string				name;   

		std::vector<AppRatio>	vRatios;
		int						minW;
		int						maxW;

		ImgSize					vImgSzHorizontalVideos[APP_MAX_VIDEO_SZ_ITEMS];
		int						defaultHorizontalSzId;    //default size is vImgSzHorizontalVideos[defaultHorizontalSzId]

		ImgSize					vImgSzVerticalVideos[APP_MAX_VIDEO_SZ_ITEMS];
		int						defaultVerticalSzId;    //default size is vImgSzVerticalVideos[defaultVerticalSzId]

		ImgSize					vImgSz1To1Videos[APP_MAX_VIDEO_SZ_ITEMS];
		int						default1To1SzId;    //default size is vImgSz1To1Videos[default1To1SzId]

		float					maxLength_sec;
		float					maxFileSz_MB;
		std::string				codec;		//H264
		std::string				fileType;   //mp4
		int						maxFps;
		int						fps;
	};
	typedef std::shared_ptr<VideoSpec>		VideoSpecPtr;
}
#endif

