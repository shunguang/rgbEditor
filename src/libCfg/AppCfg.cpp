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
	, m_demux(0)
	, m_input(0)
	, m_output(0)
	, m_gui(0)
	, m_log(0)
	//, m_imgRender(0)
{
}

AppCfg::~AppCfg()
{
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
	pt = pt0.get_child("input");
	m_input->fromPropertyTree(pt);

	pt = pt0.get_child("output");
	m_output->fromPropertyTree(pt);

	pt = pt0.get_child("gui");
	m_gui->fromPropertyTree(pt);

	pt = pt0.get_child("log");
	m_log->fromPropertyTree(pt);
}


boost::property_tree::ptree AppCfg::toPropertyTree()
{
	boost::property_tree::ptree pt1 = m_demux->toPropertyTree();
	boost::property_tree::ptree pt2 = m_input->toPropertyTree();
	boost::property_tree::ptree pt3 = m_output->toPropertyTree();
	boost::property_tree::ptree pt4 = m_gui->toPropertyTree();
	boost::property_tree::ptree pt5 = m_log->toPropertyTree();

	boost::property_tree::ptree pt;
	pt.add_child("cfg.demux",	pt1);
	pt.add_child("cfg.input",	pt2);
	pt.add_child("cfg.output",	pt3);
	pt.add_child("cfg.gui",		pt4);
	pt.add_child("cfg.log",		pt5);

	return pt;
}

