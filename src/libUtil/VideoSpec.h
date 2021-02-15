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

#include "DataTypes.h"
#include "AppEnums.h"
#include "UtilDefs.h"

#define APP_MAX_VIDEO_SZ_ITEMS	7
namespace app {
	
	class UTIL_EXPORT VideoSpec {
	
	public:
		VideoSpec( const AppSocialMedia_t socialMediaType );
		VideoSpec(const VideoSpec &x)=default;
		~VideoSpec()=default;

		VideoSpec& operator=(const VideoSpec &x);

		void reset(const AppSocialMedia_t socialMediaType);

	protected:
		void genSpec();
		void genSpec4Wechat();
		void genSpec4Tiktok();
		void genSpec4Tweeter();
		void genSpec4Instagram();
		void genSpec4Faccebook();
		void genSpec4Youtube();
		void genSpec4Default();

	public:
		AppSocialMedia_t		type;
		std::string				name;   

		std::vector<AppRatio>	vRatios;
		int						minW;
		int						maxW;

		ImgSize					vImgSz4HorizontalVideos[APP_MAX_VIDEO_SZ_ITEMS];
		int						defaultHorizontalSzId;    //default size is vImgSz4HorizontalVideos[defaultHorizontalSzId]

		ImgSize					vImgSz4VerticalVideos[APP_MAX_VIDEO_SZ_ITEMS];
		int						defaultVerticalSzId;    //default size is vImgSz4VerticalVideos[defaultVerticalSzId]
		
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

