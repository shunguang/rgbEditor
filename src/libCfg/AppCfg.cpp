/*
*-------------------------------------------------------------------
* AppCfg.cpp
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
#include "AppCfg.h"

using namespace std;
using namespace app;

AppCfg::AppCfg()
	: m_toolbarTaskId(-1)       //must be set as -1, see APP_TOOLBAR_UNKN def in GuiUtil.h
	, m_demux( new CfgDemuxingDecoding() )
	, m_gui(new CfgGui() )
	, m_log(new CfgLog())
	, m_dc(new CfgDc())
{
	m_vInput[APP_TOOLBAR_CUT].reset(new CfgCutInput() );
	m_vInput[APP_TOOLBAR_EDIT].reset(new CfgEditInput());
	m_vInput[APP_TOOLBAR_COMBINE].reset(new CfgCombineInput());

	m_vOutput[APP_TOOLBAR_CUT].reset(new CfgCutOutput());
	m_vOutput[APP_TOOLBAR_EDIT].reset(new CfgEditOutput());
	m_vOutput[APP_TOOLBAR_COMBINE].reset(new CfgCombineOutput());
}

AppCfg::~AppCfg()
{
}

void AppCfg::getInput(CfgCutInput &x)
{
	boost::mutex::scoped_lock lock(m_mutexCfg);
	x = *(dynamic_cast<CfgCutInput *> (m_vInput[APP_TOOLBAR_CUT].get()));
}

void AppCfg::getInput(CfgEditInput &x)
{
	boost::mutex::scoped_lock lock(m_mutexCfg);
	x = *(dynamic_cast<CfgEditInput *> (m_vInput[APP_TOOLBAR_EDIT].get()));
}

void AppCfg::getInput(CfgCombineInput &x)
{
	boost::mutex::scoped_lock lock(m_mutexCfg);
	x = *(dynamic_cast<CfgCombineInput *> (m_vInput[APP_TOOLBAR_COMBINE].get()));
}

void AppCfg::getOutput(CfgCutOutput &out)
{
	boost::mutex::scoped_lock lock(m_mutexCfg);
	out = *(dynamic_cast<CfgCutOutput *>(m_vOutput[APP_TOOLBAR_CUT].get()));
}

void AppCfg::getOutput(CfgEditOutput &x)
{
	boost::mutex::scoped_lock lock(m_mutexCfg);
	x = *(dynamic_cast<CfgEditOutput *>(m_vOutput[APP_TOOLBAR_EDIT].get()));
}

void AppCfg::getOutput(CfgCombineOutput &x)
{
	boost::mutex::scoped_lock lock(m_mutexCfg);
	x = *(dynamic_cast<CfgCombineOutput *>(m_vOutput[APP_TOOLBAR_COMBINE].get()));
}


void AppCfg::readFromFile(const char *fname)
{
	boost::property_tree::ptree pt;
	boost::property_tree::xml_parser::read_xml(fname, pt, boost::property_tree::xml_parser::no_comments);
	this->fromPropertyTree(pt.get_child("cfg"));
}

void AppCfg::writeToFile(const char *fname)
{
	boost::property_tree::ptree pt = toPropertyTree();
	boost::property_tree::xml_parser::xml_writer_settings<std::string> settings(' ', 4);
	boost::property_tree::xml_parser::write_xml(fname, pt, std::locale(), settings);
}

std::string AppCfg::toStr()
{
	boost::property_tree::ptree pt = toPropertyTree();

	std::ostringstream oss;
	boost::property_tree::xml_parser::xml_writer_settings<std::string> settings(' ', 4);
	boost::property_tree::xml_parser::write_xml(oss, pt, settings);
	return oss.str();
}


void AppCfg::fromPropertyTree(const boost::property_tree::ptree &pt0)
{
	boost::property_tree::ptree pt;
	boost::property_tree::ptree pt1;

	//---------------------------------
	for (int i = 0; i < APP_TOOLBAR_ITEM_CNT; ++i) {
		const string &tag = m_vToobarNames[i];
		pt = pt0.get_child( "input" + tag );
		m_vInput[i]->fromPropertyTree(pt);

		pt = pt0.get_child("output" + tag );
		m_vOutput[i]->fromPropertyTree(pt);
	}

	pt = pt0.get_child("gui");
	m_gui->fromPropertyTree(pt);

	pt = pt0.get_child("dc");
	m_dc->fromPropertyTree(pt);

	pt = pt0.get_child("log");
	m_log->fromPropertyTree(pt);
}


boost::property_tree::ptree AppCfg::toPropertyTree()
{
	boost::property_tree::ptree pt1 = m_demux->toPropertyTree();
	boost::property_tree::ptree pt4 = m_gui->toPropertyTree();
	boost::property_tree::ptree pt5 = m_dc->toPropertyTree();
	boost::property_tree::ptree pt6 = m_log->toPropertyTree();

	boost::property_tree::ptree pt;
	pt.add_child("cfg.demux",	pt1);
	for (int i = 0; i < APP_TOOLBAR_ITEM_CNT; ++i) {
		const string &tag = m_vToobarNames[i];
		boost::property_tree::ptree ptIn = m_vInput[i]->toPropertyTree();
		pt.add_child("cfg.input"+tag, ptIn);

		boost::property_tree::ptree ptOut = m_vOutput[i]->toPropertyTree();
		pt.add_child("cfg.output"+tag, ptOut);
	}
	pt.add_child("cfg.gui",		pt4);
	pt.add_child("cfg.dc",		pt5);
	pt.add_child("cfg.log",		pt6);

	return pt;
}

