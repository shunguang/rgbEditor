/*
*-------------------------------------------------------------------
* RunAppGui.h
* Copyright(c) 2019, The RgbVideoEditor Author (Shunguang Wu).
* All Rights Reserved.
* You may not use this file except in compliance with the License:
*      GNU GENERAL PUBLIC LICENSE (Version 3), 29 June 2007
*/

#include "RunGuiDc.h"

using namespace app;
using namespace std;
RunGuiDc::RunGuiDc(AppCfgPtr &cfg, AppGuiPtr &ui)
	: m_cfg(cfg)
	, m_ui(ui)
{
	CfgGui gui = m_cfg->getGui();
	CfgDc  dc = m_cfg->getDc();

	m_sharedDC.reset(new DcUI(dc.qSize));
	m_dispFrm.reset(new DispFrm(gui.dispImgWidth, gui.dispImgHeight, CV_8UC3));

}

RunGuiDc :: ~RunGuiDc()
{
}

void  RunGuiDc::showDebugMsg(const char *fmt, ...)
{
	static char  tmpBuf[TMP_BUF_SIZE];
	va_list args;
	va_start(args, fmt);
	vsnprintf( tmpBuf, TMP_BUF_SIZE, fmt, args);
	va_end(args);

	showDebugMsg(std::string(tmpBuf));
}

void RunGuiDc::showDebugMsg(const std::string &msg)
{
	QString s("");
	if (!m_guiReady || !m_showDebugMsg) {
		return;
	}

	m_debugMsgMutex.lock();

	std::string ts = app::getPrettyTimeStamp(true) + ": " + msg;
	m_debugMsgQ.push_back(ts);
	if (m_debugMsgQ.size() > 5) {
		m_debugMsgQ.pop_front();
	}

	for (int i = 0; i < m_debugMsgQ.size(); i++) {
		s += QString::fromStdString(m_debugMsgQ.at(i)) + "\n";
	}
	m_debugMsgMutex.unlock();

	m_ui->showDebugMsgs(s);
	QApplication::processEvents();
}
