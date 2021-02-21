/*
*-------------------------------------------------------------------
* CfgRenderImg.h
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

#ifndef __CFG_RENDER_IMG_H__
#define __CFG_RENDER_IMG_H__

#include "libUtil/libUtil.h"
namespace app {
	struct CfgRenderImg {
		CfgRenderImg()
			: vFontFace{ 0/*cv::FONT_HERSHEY_SIMPLEX*/, 1 /*cv::FONT_HERSHEY_PLAIN*/ }
			, vFontScale{ 2, 1.2 }
			, vThickness{ 2, 2 }
			, imgBgColor(cv::Scalar(255, 0, 0))   //BGR
			, fontColor(cv::Scalar(255, 255, 255))
		{}

		CfgRenderImg(const CfgRenderImg &x)
			: imgBgColor(x.imgBgColor)
			, fontColor(x.fontColor)
		{
			for (int i = 0; i < 2; ++i) {
				vFontFace[i] = x.vFontFace[i];
				vFontScale[i] = x.vFontScale[i];
				vThickness[i] = x.vThickness[i];
			}
		}

		//level 0 for title, level 1 for rugular
		int						vFontFace[2];
		double					vFontScale[2];
		int						vThickness[2];
		cv::Scalar				imgBgColor;
		cv::Scalar				fontColor;
	};
	typedef std::shared_ptr<CfgRenderImg>		CfgRenderImgPtr;
}
#endif
