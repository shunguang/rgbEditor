/*
*-------------------------------------------------------------------
* test_AutoCut.cpp
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
#include "libUtil/libUtil.h"
#include "libyuv/libyuv.h"
#include "libCfg/AppCfg.h"

#include "libRun/RunGuiMain.h"

using namespace std;
using namespace app;
using namespace libyuv;

std::string locateCfgFile(const std::string &f0);

int test_rgbEditor(int argc, char **argv)
{
	int ret = -1;
	//--------------------------------------------------------------------
	//read cfg file
	//--------------------------------------------------------------------
	const std::string CfgFile = locateCfgFile("cfgVideoEditor.xml");
	if (CfgFile.empty()) {
		return ret;
	}
	cout << "CfgFile=" << CfgFile << endl;

	AppCfgPtr cfg(new AppCfg());
	cfg->readFromFile(CfgFile.c_str());

	//--------------------------------------------------------------------
	//create log file
	//--------------------------------------------------------------------
	CfgLog log = cfg->getLog();
	myCreateDir(log.logFolder);
	string ymd0 = getPrettyTimeStamp();
	string logFile = log.logFolder + "/log_" + ymd0 + ".txt";
	startLogThread(logFile, log.isShowLogInConsole, true);

	//dump current cfg into log file
	dumpLog("----------cfg----------------");
	string cfgStr = cfg->toStr();
	std::vector<std::string> v;
	string_to_vector2(v, cfgStr, "\n", false);
	BOOST_FOREACH(const std::string &s, v) {
		dumpLog(s);
	}

	//--------------------------------------------------------------------
	//run AutoCut
	//--------------------------------------------------------------------
	QApplication app(argc, argv);
	//qRegisterMetaType<std::string>();
	CfgGui gui = cfg->getGui();

	QFont font;
	font.setFamily(font.defaultFamily());
	font.setPointSize( gui.fontSize );
	app.setFont(font);

	RunGuiMain runGui(cfg);
	runGui.show();
	ret = app.exec();
#if 0
	//--backup the old config file and save the current settings 
	std::string head, ext;
	splitExt(CfgFile, head, ext);
	string oldToSave = head + ymd0 + "." + ext;
	dumpLog( "copy current cfg file: " + oldToSave );
	boost::filesystem::copy_file(boost::filesystem::path(CfgFile), boost::filesystem::path(oldToSave));
	dumpLog("update current cfg file: " + CfgFile);
	cfg->writeToFile( CfgFile.c_str() );
#endif
	return ret;
}

std::string locateCfgFile(const std::string &f0)
{
	//install folder
	string cfgFile1 = "../cfg/" + f0;

	//developing folder
	string cfgFile2 = "C:/Projects/rgbEditor/src/unitTest/res/" + f0;

	string cfgFile;
	if (boost::filesystem::exists(cfgFile1)) {
		cfgFile = cfgFile1;
	}
	else if (boost::filesystem::exists(cfgFile2)) {
		cfgFile = cfgFile2;
	}
	else {
		printf("Error: Both config files <%s> and <%s> are not available!", cfgFile1.c_str(), cfgFile2.c_str());
		return "";
	}
	return cfgFile;
}
