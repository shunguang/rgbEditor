/*
*-------------------------------------------------------------------
* CfgDemuxingDecoding.h
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

//todo : extend to thread safe
#ifndef __CFG_DEMUXING_DECODING_H__
#define __CFG_DEMUXING_DECODING_H__

#include "libUtil/libUtil.h"
#include "CfgBase.h"
namespace app {
	class  CfgDemuxingDecoding : public CfgBase {

	public:
		CfgDemuxingDecoding();
		CfgDemuxingDecoding(const CfgDemuxingDecoding &x) = default;
		CfgDemuxingDecoding& operator = (const CfgDemuxingDecoding &x) = default;
		virtual ~CfgDemuxingDecoding() { CfgBase::~CfgBase(); };

		virtual boost::property_tree::ptree toPropertyTree();
		virtual void fromPropertyTree(const boost::property_tree::ptree &pt);

	public:
		bool demuxingVideo;
		bool dumpRawVideo;
		bool demuxingAudio;
		bool dumpRawAudio;
		bool storeRawAudioInMemo;
		bool storeRawVideoInMemo;

		bool storeThumbnailKeyFrms;
		int  thumbnailWidth;
		int  thumbnailHeight;
		int  outputImgWidth;    //-1, if keep the original image width
		int  outputImgHeight;	//-1, if keep the original image width	
		//for future using
		uint8 videoFmt;
	};
	typedef std::shared_ptr<CfgDemuxingDecoding>	CfgDemuxingDecodingPtr;
}
#endif
