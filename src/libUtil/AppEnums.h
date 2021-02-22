/*
*-------------------------------------------------------------------
* AppEnums.h
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

#ifndef __APP_ENUMS_H__
#define __APP_ENUMS_H__

#include <stdio.h>
namespace app {
	enum AutoCutMethod {
		AUTO_CUT_MANMUAL = 0,
		AUTO_CUT_SEMI_AUTO,
		AUTO_CUT_FULL_AUTO,
		AUTO_CUT_UNKN
	};

	enum DetectMethod {
		DETECT_APPLAUSING = 0,
		DETECT_OTHER,
	};

	enum ThreadId_t {
		Thread_ONE = 0,
		Thread_TWO,
		Thread_THREE,
		Thread_FOUR,
		Thread_FIVE,
	};

	enum AppSocialMedia_t {
		APP_SM_WECHAT = 0,
		APP_SM_YOUTUBE,
		APP_SM_TIKTOK,
		APP_SM_TWEETER,
		APP_SM_INSTAGRAM,
		APP_SM_FACEBOOK,
		APP_SM_CNT
	};
	static std::vector<std::string> g_AppSocialMediaName = { "WeChat",  "YouTube",  "Tiktok", "Tweeter", "Instagram", "Facebook", "APP_SM_CNT" };


	struct ImgSize {
		ImgSize(int w_ = 0, int h_ = 0) : w(w_), h(h_) {}
		ImgSize(const ImgSize &x) :w(x.w), h(x.h) {}
		void set(int w_, int h_) {
			w = w_;
			h = h_;
		}
		bool isSame(int w_, int h_) const {
			return ((w == w_) && (h == h_));
		}

		ImgSize getSize(int L) const {
			ImgSize sz(w >> L, h >> L);
			return sz;
		}

		std::string toString() {
			std::string s = std::to_string(w) + " x " + std::to_string(h);
			return s;
		}

		int w;
		int h;
	};

	struct AppRatio {
		AppRatio(int num_ = 0, int den_ = 1) : num(num_), den(den_) {}
		void set(int num_, int den_) {
			num = num_;
			den = den_;
		}
		bool isSame(int num_, int den_) const {
			return ((num == num_) && (den == den_));
		}
		float getRatio() const {
			return (float)num / den;
		}
		int num;
		int den;
	};
}
#endif
