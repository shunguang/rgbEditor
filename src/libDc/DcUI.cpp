/*
*-------------------------------------------------------------------
* DcUI.cpp
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
#include "DcUI.h"

using namespace app;
using namespace std;


DcUI::DcUI(int qSize)
: m_videoFrmQ( qSize )
, m_audioFrmQ( qSize )
, m_dispFrmQ( qSize )
{
}

DcUI::~DcUI()
{
}

void DcUI::respReset()
{
m_videoFrmQ.clear();
m_audioFrmQ.clear();
m_dispFrmQ.clear();
}

void DcUI::pushVideoFrm(const RawFrmPtr &f) 
{
m_videoFrmQ.push(f);
}

bool DcUI::tryPopVideoFrm(RawFrmPtr &f) 
{
return m_videoFrmQ.try_pop(f);
}

bool DcUI::waitPopVideoFrm(RawFrmPtr &f)
{
m_videoFrmQ.wait_and_pop(f);
return true;
}

void DcUI::pushAudioFrm(const RawFrmPtr &f) 
{
m_audioFrmQ.push(f);
}

bool DcUI::tryPopAudioFrm(RawFrmPtr &f) 
{
return m_audioFrmQ.try_pop(f);
}

bool DcUI::waitPopAudioFrm(RawFrmPtr &f)
{
m_audioFrmQ.wait_and_pop(f);
return true;
}

void DcUI::pushDispFrm(const DispFrmPtr &f)
{
m_dispFrmQ.push(f);
}

bool DcUI::tryPopDispFrm(DispFrmPtr &f)
{
return m_dispFrmQ.try_pop(f);
}

bool DcUI::waitPopDispFrm(DispFrmPtr &f)
{
m_dispFrmQ.wait_and_pop(f);
return true;
}


bool  DcUI:: rawFrm2DispFrm(const RawFrmPtr &raw, DispFrm &disp)
{
if (raw == 0) {
return false;
}

disp.m_fn = raw->fn_;
disp.m_keyFrmIdx = raw->keyFrmId_;
disp.m_timeStamp_ms = 0;

cv::Size &desSz = disp.m_img.size();
if (raw->w_ != desSz.width || raw->h_ != desSz.height) {
cv::Mat oriImg;
raw->toBGR(oriImg);
cv::resize(oriImg, disp.m_img, desSz );
}
else {
raw->toBGR(disp.m_img);
}
return true;
}
