/*
 * entSetting.cpp
 *
 *  Created on: 2012-1-10
 *      Author: icecoffee
 */

#include "entSetting.h"


using namespace ent;



EntSetting* EntSetting::m_instance = 0;
EntSetting::EntSetting()
:m_windowNum(0)
{
	m_version = "1.0.0.1";

	m_ip = "192.168.1.190";


	for(int i=0;i<6;i++)
	{
		setInputInfoFlg(i,USE_FLG_OFFLINE);
		setInputInfoType(i,VIDEO_TYPE_DEFAULT);
		setInputInfoSize(i,0,0);
	}

	for(int i=0;i<3;i++)
	{
		setOutputInfoFlg(i,USE_FLG_OFFLINE);
		setOutputInfoType(i,VIDEO_TYPE_DEFAULT);
		setOutputInfoSize(i,0,0);
	}


}

EntSetting::~EntSetting()
{

}


EntSetting* EntSetting::Instance()
{
	if(m_instance == NULL)
	{
		m_instance = new EntSetting();
	}
	return m_instance;
}


void EntSetting::setInputInfoFlg(uint32_t chId,uint32_t iFlg)
{
	m_inputType[chId].useFlg = iFlg;
}

void EntSetting::setInputInfoType(uint32_t chId,string sType)
{
	m_inputType[chId].type = sType;
}

void EntSetting::setInputInfoSize(uint32_t chId,uint32_t width,uint32_t height)
{
	m_inputType[chId].width = width;
	m_inputType[chId].height = height;
}


uint32_t EntSetting::getInputInfoFlg(uint32_t chId)
{
	return m_inputType[chId].useFlg;
}

string EntSetting::getInputInfoType(uint32_t chId)
{
	return m_inputType[chId].type;
}

void EntSetting::getInputInfoSize(uint32_t chId,uint32_t &width,uint32_t &height)
{
	width = m_inputType[chId].width;
	height = m_inputType[chId].height;

}


void EntSetting::setOutputInfoFlg(uint32_t chId,uint32_t iFlg)
{
	m_outputType[chId].useFlg = iFlg;
}

void EntSetting::setOutputInfoType(uint32_t chId,string sType)
{
	m_outputType[chId].type = sType;
}


void EntSetting::setOutputInfoSize(uint32_t chId,uint32_t width,uint32_t height)
{
	m_outputType[chId].width = width;
	m_outputType[chId].height = height;
}


uint32_t EntSetting::getOutputInfoFlg(uint32_t chId)
{
	return m_outputType[chId].useFlg;
}

string EntSetting::getOutputInfoType(uint32_t chId)
{
	return m_outputType[chId].type;
}

void EntSetting::getOutputInfoSize(uint32_t chId,uint32_t &width,uint32_t &height)
{
	width = m_outputType[chId].width;
	height = m_outputType[chId].height;
}


uint32_t EntSetting::getInputTotal()
{
	uint32_t total = 0;
	for(map<uint32_t,ChannelInfo>::iterator it = m_inputType.begin();it !=  m_inputType.end();it++)
	{
		if(it->second.useFlg == USE_FLG_ONLINE)
		{
			total++;
		}
	}


	return total;
}

uint32_t EntSetting::getOutputTotal()
{

	uint32_t total=0;

	for(map<uint32_t,ChannelInfo>::iterator it = m_outputType.begin();it !=  m_outputType.end();it++)
	{
		if(it->second.useFlg == USE_FLG_ONLINE)
		{
			total++;
		}
	}


	return total;

}

void EntSetting::setVersion(string version)
{
	m_version = version;
}


string EntSetting::getVersion()
{
	return m_version;
}


void EntSetting::setSysIp(string ip)
{
	m_ip = ip;
}


string EntSetting::getSysIp()
{
	return m_ip;
}

uint32_t EntSetting::getWindowsTotal()
{
	return m_windowInfo.size();
}


void EntSetting::getWindowsHandle(std::set<uint32_t> &handle)
{
	for(map<uint32_t,WindowInfo>::iterator it=m_windowInfo.begin();it!=m_windowInfo.end();it++)
	{
		handle.insert(it->first);
	}
}

bool EntSetting::getWindowsInfo(uint32_t winHandle,WindowInfo &windowInfo)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		windowInfo = it->second;
	}

	return true;
}

uint32_t EntSetting::createWindow(uint32_t winX,uint32_t winY,uint32_t width,uint32_t height)
{
	m_windowNum++;

	WindowInfo info;
	info.winX = winX;
	info.winY = winY;
	info.width = width;
	info.height = height;

	m_windowInfo.insert(make_pair(m_windowNum,info));

	return m_windowNum;
}

bool EntSetting::delWindow(uint32_t winHandle)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		m_windowInfo.erase(winHandle);
	}
	return true;
}


bool EntSetting::setLayer(uint32_t winHandle,uint32_t layer)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		m_windowInfo[winHandle].layer = layer;
	}
	return true;
}


bool EntSetting::getLayer(uint32_t winHandle,uint32_t &layer)
{

	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		layer = m_windowInfo[winHandle].layer;
	}

	return true;

}

bool EntSetting::setOutput(uint32_t winHandle,uint32_t channelOut)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		m_windowInfo[winHandle].channelOut = channelOut;
	}
	return true;
}


bool EntSetting::getOutput(uint32_t winHandle,uint32_t &channelOut)
{

	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		channelOut = m_windowInfo[winHandle].channelOut;
	}

	return true;

}

bool EntSetting::setInput(uint32_t winHandle,uint32_t channelIn)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		m_windowInfo[winHandle].channelIn = channelIn;
	}
	return true;
}


bool EntSetting::getInput(uint32_t winHandle,uint32_t &channelIn)
{

	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		channelIn = m_windowInfo[winHandle].channelIn;
	}

	return true;

}

bool EntSetting::setShowStatus(uint32_t winHandle,uint32_t status)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		m_windowInfo[winHandle].showStatus = status;
	}
	return true;
}


bool EntSetting::getShowStatus(uint32_t winHandle,uint32_t &status)
{

	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		status = m_windowInfo[winHandle].showStatus;
	}

	return true;

}


bool EntSetting::setWindowPosition(uint32_t winHandle,uint32_t winX,uint32_t winY,uint32_t width,uint32_t height)
{
	map<uint32_t,WindowInfo>::iterator it;
	it = m_windowInfo.find(winHandle);
	if(it == m_windowInfo.end())
	{
		return false;
	}
	else
	{
		m_windowInfo[winHandle].winX = winX;
		m_windowInfo[winHandle].winY = winY;
		m_windowInfo[winHandle].width = width;
		m_windowInfo[winHandle].height = height;

	}

	return true;
}