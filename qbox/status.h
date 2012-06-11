/*
 * status.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef STATUS_H_
#define STATUS_H_

#include "commModel.h"

class Status
:public CommModel
{

public:
	Status();
	virtual ~Status();

	virtual uint32_t onMsgReq(MsgInfo *msg,uint32_t connID);


private:

	void onUserLogin(MsgInfo *msg,uint32_t connID);
	void onUserPing(MsgInfo *msg,uint32_t connID);

	uint32_t name;

};


#endif /* USER_H_ */
