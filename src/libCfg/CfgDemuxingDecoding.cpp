/*
*------------------------------------------------------------------------
*CfgDemuxingDecoding.cpp
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

#include "CfgDemuxingDecoding.h"
using namespace app;
using namespace std;
CfgDemuxingDecoding::CfgDemuxingDecoding()
	: CfgBase()
	, demuxingVideo(false)
	, dumpRawVideo(false)
	, demuxingAudio(true)
	, dumpRawAudio(true)
	, storeRawAudioInMemo(false)
	, storeRawVideoInMemo(false)
	, videoFmt(0)
	, storeThumbnailKeyFrms(false)
	, thumbnailWidth(64)
	, thumbnailHeight(64)
	, outputImgWidth(1280)
	, outputImgHeight(720)
{}


boost::property_tree::ptree CfgDemuxingDecoding::toPropertyTree()
{
	boost::property_tree::ptree pt;
	return pt;
}

void CfgDemuxingDecoding::fromPropertyTree(const boost::property_tree::ptree &pt)
{
}
