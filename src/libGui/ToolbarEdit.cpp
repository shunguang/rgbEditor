/*
*-------------------------------------------------------------------
* AppGui.h
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
#include "ToolbarEdit.h"
using namespace app;
using namespace std;
ToolbarEdit::ToolbarEdit( QGroupBox *parentGrp )
	:ToolbarBase(APP_TOOLBAR_EDIT, parentGrp)
{
}


void ToolbarEdit::enableVisibility(const bool isVisiable)
{
}

void ToolbarEdit::retranslateUI()
{
	ToolbarBase::retranslateUI();
}

void ToolbarEdit::resizeUI(const bool isInit)
{
	if (!isActive()) return;

	calToolbarRects(isInit);
	ToolbarBase::resizeUI(isInit);
}

void ToolbarEdit::calToolbarRects(const bool isInit)
{
	ToolbarBase::calToolbarRects(isInit);
}

void ToolbarEdit::createWidgets()
{
	ToolbarBase::createWidgets();
}
