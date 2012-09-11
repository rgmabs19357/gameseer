/*
 * windows.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "windows.h"
#include "protocol/protocol.h"
#include "msgHandler.h"
#include "toString.h"
#include "entSetting.h"
#include <set>
#include "common.h"

using namespace msg;
using namespace ent;
using namespace std;

Windows::Windows():_updateid(0)
{

}

Windows::~Windows()
{

}


uint32_t Windows::onMsgReq(MsgInfo *msg,uint32_t connID)
{

    switch(msg->msgType)
    {
        case PGetWindowsHandleReq::uri:
            onPGetWindowsHandleReq(msg,connID);
            break;

        case PGetWindowsInfoReq::uri:
        	onPGetWindowsInfoReq(msg,connID);
            break;

        case PCreateWindowsReq::uri:
            onPCreateWindowsReq(msg,connID);
            break;

        case PSetWindowsLayerReq::uri:
        	onPSetWindowsLayerReq(msg,connID);
            break;

        case PSetWindowsShowStateReq::uri:
        	onPSetWindowsShowStateReq(msg,connID);
        	break;

        case PDelWindowsReq::uri:
        	onPDelWindowsReq(msg,connID);
        	break;

        case PMoveWindowsReq::uri:
        	onPMoveWindowsReq(msg,connID);
        	break;

        case PCloseAllReq::uri:
        	onCloseAllReq(msg,connID);
        	break;

        case PUpdateQboxReq::uri:
        	onPUpdateQboxReq(msg,connID);
        	break;

        default:
            //cout<<"URI UNKOWN!"<<" msg->msgType="<<msg->msgType <<endl;
        	break;
    }

    return 0;
}

void Windows::onPUpdateQboxReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPUpdateQboxReq"<<" connID="<<connID <<endl;
    cout<<msg->info["totalLen"]<<" "<<msg->info["name"]<<endl;

    MsgInfo rsp;
    rsp.msgType = PUpdateQboxRsp::uri;
    if ( connID != _updateid  && _updateid != 0){
        //if there is already an other user occupied update process, return error
        rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }else{
        rsp.msgType = PUpdateQboxRsp::uri;
        rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
        string name = rsp.info["name"] = msg->info["name"];
        rsp.info["start"] = msg->info["start"];
        rsp.info["end"] = msg->info["end"];
        string bin = msg->info["binary"];
        string eof = rsp.info["eof"] = msg->info["eof"];
        if ( eof == "0" ){
            if ( _updateid == 0){
                _update.open(name.c_str(), ios::binary|ios::out);
                _updateid = connID;
            }
            _update.write(bin.c_str(), bin.length() );
        } else{
            _updateid = 0;
            _update.write(bin.c_str(), bin.length() );
            _update.close();
        }
    }
    MsgHandler::Instance()->sendMsg(connID,&rsp);
}

void Windows::onPGetWindowsHandleReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPGetWindowsHandleReq"<<" connID="<<connID <<endl;
    MsgInfo rsp;
    rsp.msgType = PGetWindowsHandleRsp::uri;

    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);

    rsp.info["total"] =  EntSetting::Instance()->getWindowsTotal();

    std::set<uint32_t> handle;
    EntSetting::Instance()->getWindowsHandle(handle);

    uint32_t handleNum=0;
    for(std::set<uint32_t>::iterator it=handle.begin();it!=handle.end();it++)
    {
        string key = "handleNum" + tostring(handleNum);
        rsp.info[key] = (*it);
    }

    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Windows::onPGetWindowsInfoReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPGetWindowsInfoReq"<<" connID="<<connID <<endl;
    MsgInfo rsp;
    rsp.msgType = PGetWindowsInfoRsp::uri;

    uint32_t winHandle  = atoi(msg->info["winHandle"].c_str());

    WindowInfo info;
    if( EntSetting::Instance()->getWindowsInfo(winHandle,info))
    {
        rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
        rsp.info["winHandle"]  =msg->info["winHandle"];

        rsp.info["x"]  = tostring(info.winX);
        rsp.info["y"]  = tostring(info.winY);
        rsp.info["w"]  = tostring(info.width);
        rsp.info["h"]  = tostring(info.height);
        rsp.info["in"]  = tostring(info.channelIn);
        rsp.info["out"]  = tostring(info.channelOut);
        rsp.info["layer"]  = tostring(info.layer);
    }
    else
    {
        rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
        rsp.info["winHandle"]  =msg->info["winHandle"];
    }

    MsgHandler::Instance()->sendMsg(connID,&rsp);


}

void Windows::onPCreateWindowsReq(MsgInfo *msg,uint32_t connID)
{



    uint32_t winX = atoi(msg->info["x"].c_str());
    uint32_t winY = atoi(msg->info["y"].c_str());
    uint32_t winW = atoi(msg->info["w"].c_str());
    uint32_t winH = atoi(msg->info["h"].c_str());
    uint32_t winOut = atoi(msg->info["out"].c_str());

    test_msg("onPCreateWindowsReq winX=%d,winY=%d,winW=%d,winH=%d,winOut=%d!\n",winX,winY,winW,winH,winOut);


    MsgInfo rsp;
    rsp.msgType = PCreateWindowsRsp::uri;

    uint32_t winHandle = 0;

    winHandle = EntSetting::Instance()->createWindow(winX,winY,winW,winH);
    if(winHandle!=0)
    {
        test_msg("onPCreateWindowsReq winHandle=%d!\n",winHandle);
    	setOutputChannel(winHandle,winW,winH,winX,winY);
        rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
        rsp.info["winHandle"] = tostring(winHandle);
    }
    else
    {
    	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }

    if(!EntSetting::Instance()->setLayer(winHandle,DEFINE_WINDOW_LAYER))
    {
        rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }

    if(!EntSetting::Instance()->setOutput(winHandle,winOut))
    {
        rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }

    if(!EntSetting::Instance()->setShowStatus(winHandle,TYPE_WINDOW_STATUS_HIDE))
    {
        rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }







    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Windows::onPSetWindowsLayerReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPSetWindowsLayerReq"<<" connID="<<connID <<endl;

    uint32_t winHandle = atoi(msg->info["winHandle"].c_str());
    uint32_t layer = atoi(msg->info["layer"].c_str());

    MsgInfo rsp;
    rsp.msgType = PSetWindowsLayerRsp::uri;


    if(!EntSetting::Instance()->setLayer(winHandle,layer))
    {
        rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }
    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);



    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Windows::onPSetWindowsShowStateReq(MsgInfo *msg,uint32_t connID)
{

    uint32_t winHandle = atoi(msg->info["winHandle"].c_str());
    test_msg("onPSetWindowsShowStateReq winHandle=%d,showState=%s!\n",winHandle,msg->info["showState"].c_str());


    MsgInfo rsp;
    rsp.msgType = PSetWindowsShowStateRsp::uri;

    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);

    if("show" == msg->info["showState"])
    {
        if(!EntSetting::Instance()->setShowStatus(winHandle,TYPE_WINDOW_STATUS_SHOW))
        {
            rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
        }
        showChannel(winHandle);
    }

    if("hide" == msg->info["showState"])
    {
        if(!EntSetting::Instance()->setShowStatus(winHandle,TYPE_WINDOW_STATUS_HIDE))
        {
            rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
        }
        hideChannel(winHandle);
    }


    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Windows::onPDelWindowsReq(MsgInfo *msg,uint32_t connID)
{


    uint32_t winHandle = atoi(msg->info["winHandle"].c_str());
    test_msg("onPDelWindowsReq winHandle=%d!\n",winHandle);


    MsgInfo rsp;
    rsp.msgType = PDelWindowsRsp::uri;

    if(!EntSetting::Instance()->delWindow(winHandle))
    {
        rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
        test_msg("onPDelWindowsReq winHandle=%d Error!\n",winHandle);
    }
    else
    {
        rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
        test_msg("onPDelWindowsReq winHandle=%d OK!\n",winHandle);
        hideChannel(winHandle);
    }

    MsgHandler::Instance()->sendMsg(connID,&rsp);

}


void Windows::onPMoveWindowsReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPMoveWindowsReq"<<" connID="<<connID <<endl;

    uint32_t winHandle = atoi(msg->info["winHandle"].c_str());
    uint32_t winX = atoi(msg->info["x"].c_str());
    uint32_t winY = atoi(msg->info["y"].c_str());
    uint32_t winW = atoi(msg->info["w"].c_str());
    uint32_t winH = atoi(msg->info["h"].c_str());

    MsgInfo rsp;
    rsp.msgType = PMoveWindowsRsp::uri;


    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);

    if(EntSetting::Instance()->setWindowPosition(winHandle,winX,winY,winW,winH))
    {
        rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }



    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Windows::onCloseAllReq(MsgInfo *msg,uint32_t connID)
{
    test_msg("onCloseAllReq !\n");


    MsgInfo rsp;
    rsp.msgType = PCloseAllRsp::uri;


    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
    EntSetting::Instance()->delWindow(1);
    EntSetting::Instance()->delWindow(2);
    hideChannel(1);
    hideChannel(2);



    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

