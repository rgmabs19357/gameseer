#include "appScale.h"
#include "dev.h"
#include "devFPGA.h"
#include "devICS307.h"
#include "chipCommon.h"

#include "devTVP5160.h"
#include "devC772.h"

#ifdef __cplusplus
    extern "C"{


using namespace chipApp;


void set753(uint8_t byAdd,uint8_t byVal)
{
	AppScale s_c753;
	debug_msg("Test C753 addr=%02x,byVal=%02x\n",byAdd,byVal);
	s_c753.SPI_Write(TYPE_CHIP_C753,byAdd,byVal);
}


void get753(uint8_t byAdd)
{

	uint8_t byVal=0;
	AppScale s_c753;
	s_c753.SPI_Read(TYPE_CHIP_C753,byAdd,byVal);
	debug_msg("addr=%02x,val=%02x\n",byAdd,byVal);
}

void set5160(uint32_t chid,uint8_t byAdd,uint8_t byVal)
{
	debug_msg("chid=%d,addr=%02x,val=%02x\n",chid,byAdd,byVal);
	dev_5160_Write(chid,byAdd,byVal);
}


void get5160(uint32_t chid,uint8_t byAdd)
{
	uint8_t byVal=0;
	dev_5160_Read(chid,byAdd,&byVal);
	debug_msg("chid=%d,addr=%02x,val=%02x\n",chid,byAdd,byVal);
}

void set772(uint32_t chid,uint8_t byAdd,uint8_t byVal)
{
	DriverChip772 s_c772;
	debug_msg("chid=%d,addr=%02x,val=%02x\n",chid,byAdd,byVal);
	s_c772.SPI_Write(chid,byAdd,byVal);
}


void get772(uint32_t chid,uint8_t byAdd)
{
	uint8_t byVal=0;
	DriverChip772 s_c772;
	s_c772.SPI_Read(chid,byAdd,byVal);
	debug_msg("chid=%d,addr=%02x,val=%02x\n",chid,byAdd,byVal);
}


void chipSetFPGATest(uint16_t addr,uint16_t wVal)
{

	DriverChipFPGA s_FPGA;

	debug_msg("Test FPGA set addr=%04x,byVal=%04x\n",addr,wVal);

	s_FPGA.FPGA_Write(addr,wVal);

	uint16_t byVal=0;
	s_FPGA.FPGA_Read(addr,byVal);
	debug_msg("Read addr=%04x,val1=%04x\n",addr,byVal);

}


void chipGetFPGATest(uint16_t addr)
{
	uint16_t byVal=0;
	DriverChipFPGA s_FPGA;
	s_FPGA.FPGA_Read(addr,byVal);
	debug_msg("addr=%04x,val1=%04x\n",addr,byVal);
}

void test753SPI()
{
	debug_msg("\n-------------------------------test753SPI----------------------------------\n");
	uint8_t byVal=0x0a;
	uint8_t byVal1=0x00;
	dev_SPI_Write(DEV_SPI_C753_CHANNEL,0,byVal);
	dev_SPI_Read(DEV_SPI_C753_CHANNEL,0,&byVal1);
	if(byVal!=byVal1)
	{
		debug_msg("753SPI ERROR! TEST Reg write = %02x ,read=%02x \n",byVal,byVal1);
	}


}


void test772SPI()
{
	debug_msg("\n---------------------------test772SPI----------------------------------\n");
	uint8_t byVal=0x0a;
	uint8_t byVal1=0x00;
	dev_SPI_Write(DEV_SPI_C772_CHANNEL_1,0,byVal);
	dev_SPI_Read(DEV_SPI_C772_CHANNEL_1,0,&byVal1);
	if(byVal!=byVal1)
	{
		debug_msg("772CHANNEL_1 ERROR! TEST Reg write = %02x ,read=%02x \n",byVal,byVal1);
	}

	byVal=0x0a;


	byVal1=0x00;
	dev_SPI_Write(DEV_SPI_C772_CHANNEL_2,0,byVal);
	dev_SPI_Read(DEV_SPI_C772_CHANNEL_2,0,&byVal1);
	if(byVal!=byVal1)
	{
		debug_msg("772CHANNEL_2 ERROR! TEST Reg write = %02x ,read=%02x \n",byVal,byVal1);
	}

	byVal=0x0a;
	byVal1=0x00;
	dev_SPI_Write(DEV_SPI_C772_CHANNEL_3,0,byVal);
	dev_SPI_Read(DEV_SPI_C772_CHANNEL_3,0,&byVal1);
	if(byVal!=byVal1)
	{
		debug_msg("772CHANNEL_3 ERROR! TEST Reg write = %02x ,read=%02x \n",byVal,byVal1);
	}

	byVal=0x0a;
	byVal1=0x00;
	dev_SPI_Write(DEV_SPI_C772_CHANNEL_4,0,byVal);
	dev_SPI_Read(DEV_SPI_C772_CHANNEL_4,0,&byVal1);
	if(byVal!=byVal1)
	{
		debug_msg("772CHANNEL_4 ERROR! TEST Reg write = %02x ,read=%02x \n",byVal,byVal1);
	}

	byVal=0x0a;
	byVal1=0x00;
	dev_SPI_Write(DEV_SPI_C772_CHANNEL_5,0,byVal);
	dev_SPI_Read(DEV_SPI_C772_CHANNEL_5,0,&byVal1);
	if(byVal!=byVal1)
	{
		debug_msg("772CHANNEL_5 ERROR! TEST Reg write = %02x ,read=%02x \n",byVal,byVal1);
	}

	byVal=0x0a;
	byVal1=0x00;
	dev_SPI_Write(DEV_SPI_C772_CHANNEL_6,0,byVal);
	dev_SPI_Read(DEV_SPI_C772_CHANNEL_6,0,&byVal1);
	if(byVal!=byVal1)
	{
		debug_msg("772CHANNEL_6 ERROR! TEST Reg write = %02x ,read=%02x \n",byVal,byVal1);
	}

}

void test5160IIC()
{
	debug_msg("\n--------------------5160IIC------------------------------\n");
	DriverChipFPGA s_FPGA;

	DriverChip5160 s_c5160;
	uint8_t val1 = 0x40;
	uint8_t val = 0x00;
	s_c5160.dev_5160_SetInputType(DEV_5160_CHANNEL_1,val1);
	s_c5160.dev_5160_GetInputType(DEV_5160_CHANNEL_1,val);
	if(val1!=val)
	{
		debug_msg("test5160 channel 1 error val1=%02x,val=%02x\n",val1,val);
	}
	else
	{
		debug_msg("test5160 channel 1! TEST OK! \n");
	}

	val1 = 0x40;
	val = 0x00;
	s_c5160.dev_5160_SetInputType(DEV_5160_CHANNEL_2,val1);
	s_c5160.dev_5160_GetInputType(DEV_5160_CHANNEL_2,val);
	if(val1!=val)
	{
		debug_msg("test5160 channel 2 error val1=%02x,val=%02x\n",val1,val);
	}
	else
	{
		debug_msg("test5160 channel 2! TEST OK! \n");
	}

	val1 = 0x40;
	val = 0x00;
	s_c5160.dev_5160_SetInputType(DEV_5160_CHANNEL_3,val1);
	s_c5160.dev_5160_GetInputType(DEV_5160_CHANNEL_3,val);
	if(val1!=val)
	{
		debug_msg("test5160 channel 3 error val1=%02x,val=%02x\n",val1,val);
	}
	else
	{
		debug_msg("test5160 channel 3! TEST OK! \n");
	}

	val1 = 0x40;
	val = 0x00;
	s_c5160.dev_5160_SetInputType(DEV_5160_CHANNEL_4,val1);
	s_c5160.dev_5160_GetInputType(DEV_5160_CHANNEL_4,val);
	if(val1!=val)
	{
		debug_msg("test5160 channel 4 error val1=%02x,val=%02x\n",val1,val);
	}
	else
	{
		debug_msg("test5160 channel 4! TEST OK! \n");
	}

	val1 = 0x40;
	val = 0x00;
	s_c5160.dev_5160_SetInputType(DEV_5160_CHANNEL_5,val1);
	s_c5160.dev_5160_GetInputType(DEV_5160_CHANNEL_5,val);
	if(val1!=val)
	{
		debug_msg("test5160 channel 5 error val1=%02x,val=%02x\n",val1,val);
	}
	else
	{
		debug_msg("test5160 channel 5! TEST OK! \n");
	}

	val1 = 0x40;
	val = 0x00;
	s_c5160.dev_5160_SetInputType(DEV_5160_CHANNEL_6,val1);
	s_c5160.dev_5160_GetInputType(DEV_5160_CHANNEL_6,val);
	if(val1!=val)
	{
		debug_msg("test5160 channel 6 error val1=%02x,val=%02x\n",val1,val);
	}
	else
	{
		debug_msg("test5160 channel 6! TEST OK! \n");
	}



}

void testFPGASPI()
{
	debug_msg("\n---------------------------------testFPGA--------------------------------\n");
	DriverChipFPGA s_FPGA;

	uint16_t byVal=0x0a;
	uint16_t byVal1=0x00;

	s_FPGA.setTestReg(byVal);
	s_FPGA.getTestReg(byVal1);
	if(byVal!=byVal1)
	{
		debug_msg("FPGA ERROR! TEST Reg write = %02x ,read=%02x \n",byVal,byVal1);
	}
	else
	{
		debug_msg("FPGA  TEST OK! \n");
	}

}

void testAllDev()
{

	testFPGASPI();
	test5160IIC();
	test772SPI();
	test753SPI();
}



void testFPGADetail()
{
	debug_msg("testFPGA\n");
	DriverChipFPGA s_FPGA;

	uint16_t byVal=0x0a;
	uint16_t byVal1=0x00;

	s_FPGA.setTestReg(byVal);
	s_FPGA.getTestReg(byVal1);
	if(byVal!=byVal1)
	{
		debug_msg("FPGA ERROR! TEST Reg write = %02x ,read=%02x \n",byVal,byVal1);
	}

	for(uint32_t i=1;i<=6;i++)
	{
		InputInfoT info;
		s_FPGA.getInputInfo(i,info);
		debug_msg("------FPGA CHID:%d--------\n",i);
		debug_msg("------HSFreq:%d--------\n",info.HSFreq);
		debug_msg("------VSFreq:%d--------\n",info.VSFreq);
		debug_msg("------PxielFreq:%d--------\n",info.PxielFreq);
		debug_msg("------HSRegister:%d--------\n",info.HSRegister);
		debug_msg("------VSRegister:%d--------\n",info.VSRegister);
		debug_msg("------ImgPol:%d--------\n",info.ImgPol);
		debug_msg("------HorSync:%d--------\n",info.HorSync);
		debug_msg("------VerSync:%d--------\n",info.VerSync);
		debug_msg("------HorFP:%d--------\n",info.HorFP);
		debug_msg("------HorBP:%d--------\n",info.HorBP);
		debug_msg("------VerFP:%d--------\n",info.VerFP);
		debug_msg("------VerBP:%d--------\n",info.VerBP);
		debug_msg("----------------------------------\n",i);
	}

	for(uint32_t i=1;i<=4;i++)
	{
		uint16_t inputValue=0;
		s_FPGA.getSelectInput(i,inputValue);
		debug_msg("FPGA CHID:%d select input:%d\n",i,inputValue);
	}


}

void setFpgaSelectChn(uint32_t chn,uint32_t input)
{
	DriverChipFPGA s_FPGA;
	s_FPGA.setSelectInput(chn,input);

}


void getC753ChnInput(uint32_t chn)
{
	debug_msg("getC753ChnInput\n");
	AppScale s_c753;

	uint16_t wHsFreq=0;
	s_c753.C753GetInputPortHorizontalSyncFrequency(chn,wHsFreq);

	uint16_t wVsFreq=0;
	s_c753.C753GetInputPortVerticalSyncFrequency(chn,wVsFreq);

	uint8_t byHsWidth=0;
	s_c753.C753GetInputPortHorizontalSyncPulseWidth(chn,byHsWidth);

	uint8_t byVsWidth=0;
	s_c753.C753GetInputPortVerticalSyncPulseWidth(chn,byVsWidth);

	debug_msg("\n--------------C753 CHN=%d INFO-----------------\n",chn);
	debug_msg("\nwHsFreq:%d,wVsFreq:%d,byHsWidth:%d,byVsWidth:%d\n",wHsFreq,wVsFreq,byHsWidth,byVsWidth);



}



void initMoney(uint32_t chn)
{
	AppScale s_c753;

	if(chn == 1)
	{
		s_c753.C753SetOutputField0MemoryReadStartAddress(1, 0x00c00000);
		s_c753.C753SetOutputField1MemoryReadStartAddress(1, 0x00000000);
		s_c753.C753SetOutputField2MemoryReadStartAddress(1, 0x00400000);
		s_c753.C753SetOutputField3MemoryReadStartAddress(1, 0x00800000);
		s_c753.C753SetInputField0MemoryWriteStartAddress(1, 0x00000000);
		s_c753.C753SetInputField1MemoryWriteStartAddress(1, 0x00400000);
		s_c753.C753SetInputField2MemoryWriteStartAddress(1, 0x00800000);
		s_c753.C753SetInputField3MemoryWriteStartAddress(1, 0x00C00000);
	}

	if(chn == 2)
	{
		s_c753.C753SetOutputField0MemoryReadStartAddress(2, 0x01c00000);
		s_c753.C753SetOutputField1MemoryReadStartAddress(2, 0x01000000);
		s_c753.C753SetOutputField2MemoryReadStartAddress(2, 0x01400000);
		s_c753.C753SetOutputField3MemoryReadStartAddress(2, 0x01800000);
		s_c753.C753SetInputField0MemoryWriteStartAddress(2, 0x01000000);
		s_c753.C753SetInputField1MemoryWriteStartAddress(2, 0x01400000);
		s_c753.C753SetInputField2MemoryWriteStartAddress(2, 0x01800000);
		s_c753.C753SetInputField3MemoryWriteStartAddress(2, 0x01C00000);
	}
}



void initTest1400()
{
	debug_msg("initTest1400\n");
	AppScale s_c753;
	DriverChipICS307 s_ics307;

	s_ics307.setPOCLK(ICS307_FREQUENCY_121750KHZ);
	s_c753.initTest1400();
	debug_msg("showWnd\n");
	s_c753.showWnd(1);
}

void selectOutPut(uint32_t model)
{
	AppScale s_c753;
	s_c753.selectOutPutModel(model);
}



void setC753OutPutOAI1(uint32_t hStar,uint32_t hWidth,uint32_t VStar,uint32_t VWidth)
{
	AppScale s_c753;
	s_c753.C753SetOutputPortOAOI1HorizontalStart((uint16_t)hStar);
	s_c753.C753SetOutputPortOAOI1HorizontalEnd((uint16_t)hWidth);
	s_c753.C753SetOutputPortOAOI1VerticalStart((uint16_t)VStar);
	s_c753.C753SetOutputPortOAOI1VerticalEnd((uint16_t)VWidth);
}

void setC753OutPutOAI0(uint32_t hStar,uint32_t hWidth,uint32_t VStar,uint32_t VWidth)
{
	AppScale s_c753;
	s_c753.C753SetOutputPortOAOI0HorizontalStart((uint16_t)hStar);
	s_c753.C753SetOutputPortOAOI0HorizontalEnd((uint16_t)hWidth);
	s_c753.C753SetOutputPortOAOI0VerticalStart((uint16_t)VStar);
	s_c753.C753SetOutputPortOAOI0VerticalEnd((uint16_t)VWidth);
}



void testMACRO()
{
	#ifdef __unix__
		cout<<"unix!"<<endl;
	#else
		cout<<"vxWork!"<<endl;
	#endif

}

void C753SetOutFill(uint32_t chn,uint32_t color,uint8_t model)
{
	debug_msg("C753SetOutFill\n");
	AppScale s_c753;
	s_c753.C753SetOutputFill(chn,color);
	s_c753.C753SetOutputImageControl(chn,model);

	s_c753.showWnd(chn);
}


void C753SetInputFill(uint32_t flg,uint32_t chid,uint32_t color)
{
	debug_msg("C753SetInputFill\n");
	AppScale s_c753;

	s_c753.C753SetInputFill(chid,color);
	if(flg == 1)
	{

		s_c753.C753SetInputImageControl(chid,0x10);
	}
	else
	{
		s_c753.C753SetInputImageControl(chid,0);
	}




}

void demo()
{
	AppScale s_c753;
	s_c753.initHardware();
	s_c753.initMemoryLineFeedWidth(1);
	s_c753.initMemoryLineFeedWidth(2);

	s_c753.setOutputBGColor(0x000000ff,0x000000ff);
	s_c753.setOutputImage(TYPE_OUTPUT_AOI0,TYPE_OUTPUT_SIZE_1024_768);


	s_c753.setInputChannelACT(1,1024,768,303,36);
	s_c753.setOutputChannelACT(1,1024,768,20,10);
	s_c753.showWnd(1);

	s_c753.setInputChannelACT(2,1024,768,303,36);
	s_c753.setOutputChannelACT(2,1024,768,350,300);
	s_c753.showWnd(2);


}





void topChannel(uint32_t channel)
{
	AppScale s_c753;
	s_c753.topChannel(channel);
}


void testScale(uint32_t chId,uint32_t hInput,uint32_t vInput,uint32_t hOutput,uint32_t vOutput)
{
	AppScale &s_c753=*AppScale::Instance();

//	s_c753.C753SetInputPortACTHorizontalWidth(chId,hInput);
//	s_c753.C753SetInputPortACTVerticalWidth(chId,vInput);

//	s_c753.C753SetOutputPortACTHorizontalWidth(chId, hOutput);
//	s_c753.C753SetOutputPortACTVerticalWidth(chId,vOutput);


//	s_c753.initScaleTable(chId);
	s_c753.initScal(chId,hInput,hOutput,vInput,vOutput);



}

void setC753OutPutACT(uint32_t chid,uint32_t hWidth,uint32_t VWidth,uint32_t hStar,uint32_t VStar)
{

	AppScale s_c753;
	s_c753.setOutputChannelACT(chid,hWidth,VWidth,hStar,VStar);
}


void setC753InputACT(uint32_t chid,uint32_t hWidth,uint32_t VWidth,uint32_t hStar,uint32_t VStar)
{
	AppScale s_c753;
	s_c753.setInputChannelACT(chid,hWidth,VWidth,hStar,VStar);

}

void moveOutput(uint32_t chid,int hPoint,int vPoint)
{
	AppScale s_c753;
	s_c753.moveChannelOutput(chid,hPoint,vPoint);

}

void moveInput(uint32_t chid,int hPoint,int vPoint)
{
	AppScale s_c753;
	s_c753.moveChannelInput(chid,hPoint,vPoint);
}

void setOutputSize(uint32_t chid,int hw,int vw)
{
	AppScale s_c753;
	s_c753.C753SetOutputPortACTHorizontalWidth(chid,hw);
	s_c753.C753SetOutputPortACTVerticalWidth(chid,vw);

}

void setInputSize(uint32_t chid,int hw,int vw)
{
	AppScale s_c753;
	s_c753.C753SetInputPortACTHorizontalWidth(chid,hw);
	s_c753.C753SetInputPortACTVerticalWidth(chid,vw);
}

void test5160()
{
	DriverChip5160 s_c5160;
	uint8_t val1 = 0x40;
	uint8_t val = 0x00;
	s_c5160.dev_5160_SetInputType(1,val1);
	s_c5160.dev_5160_GetInputType(1,val);
	if(val1!=val)
	{
		debug_msg("test5160 error val1=%02x,val=%02x\n",val1,val);
	}
}

void testC772()
{
	DriverChip772 s_c772;
	uint8_t val1 = 0x0a;
	uint8_t val = 0x00;

	s_c772.SetBankRegister(1,val1);
	s_c772.SetBankRegister(1,val);
	if(val1!=val)
	{
		debug_msg("testC772 error val1=%02x,val=%02x\n",val1,val);
	}

}


void initSD480(uint32_t chn)
{
	debug_msg("initSD480\n");
	DriverChip5160 s_c5160;
	DriverChip772 s_c772;

	s_c5160.dev_5160_InitTVP5160(chn);
	s_c772.dev_InitIP00c772(chn);
	s_c772.dev_C772_Set480(chn);
}



void initSD576(uint32_t chn)
{
	debug_msg("initSD576\n");
	DriverChip5160 s_c5160;
	DriverChip772 s_c772;

	s_c5160.dev_5160_InitTVP5160(chn);
	s_c772.dev_InitIP00c772(chn);
	s_c772.dev_C772_Set576(chn);
}

void init5160(uint32_t chn)
{
	DriverChip5160 s_c5160;
	s_c5160.dev_5160_InitTVP5160(chn);
}

void init772(uint32_t chn,uint32_t flg)
{

	DriverChip772 s_c772;

	s_c772.dev_InitIP00c772(chn);
	if(flg == 0)
	{
		s_c772.dev_C772_Set576(chn);
	}
	else
	{
		s_c772.dev_C772_Set480(chn);
	}
}

void blue5160(uint32_t chn,uint32_t flg)
{
	DriverChip5160 s_c5160;
	if(flg==1)
	{
		set5160(chn,0x34,0x19);
	}
	else
	{
		set5160(chn,0x34,0x11);
	}
}

void blue772Out(uint32_t chn,uint32_t flg)
{
	DriverChip772 s_c772;
	s_c772.dev_C772_SetBlueScreen(chn,flg);
}



void init772more(uint32_t chn,uint32_t flg)
{
	DriverChip772 s_c772;

	if(flg ==1)
	{
		s_c772.dev_C772_InitIPConversion(chn);

	}

	if(flg ==2)
	{
		s_c772.dev_C772_InitColorConversion(chn);
	}

	if(flg ==3)
	{
		s_c772.dev_C772_InitLUT(chn);
	}

}


void demoSD()
{
	AppScale &s_c753=*AppScale::Instance();
	s_c753.initHardware();
//	initMoney(1);
//	initMoney(2);
	s_c753.initMemoryLineFeedWidth(1);
	s_c753.initMemoryLineFeedWidth(2);

	s_c753.initScaleTable(1);
	s_c753.initScaleTable(2);



	s_c753.setOutputBGColor(0x000000ff,0x000000ff);
	s_c753.setOutputImage(TYPE_OUTPUT_AOI1,TYPE_OUTPUT_SIZE_1024_768);

	init5160(1);
	init5160(2);
	init772(1,1);
	init772(2,1);
//	init772more(2,1);
//	init772more(2,2);
//	init772more(2,3);

//	setFpgaSelectChn(2,1);

	s_c753.setInputChannelACT(1,702,480,137,45);
	s_c753.setOutputChannelACT(1,700,480,0,0);
	s_c753.showWnd(1);

//	s_c753.setInputChannelACT(2,1024,768,303,36);
//	s_c753.setOutputChannelACT(2,1024,768,350,300);
//	s_c753.showWnd(2);


}

void demoRing()
{
	AppScale &s_c753=*AppScale::Instance();
	s_c753.initHardware();

	s_c753.initMemoryLineFeedWidth(1);
	s_c753.initMemoryLineFeedWidth(2);

	s_c753.initScaleTable(1);
	s_c753.initScaleTable(2);


	s_c753.setOutputBGColor(0x000000ff,0x000000ff);
	s_c753.setOutputImage(TYPE_OUTPUT_AOI1,TYPE_OUTPUT_SIZE_1024_768);


	s_c753.setInputChannelACT(1,1024,768,303,36);
	s_c753.setOutputChannelACT(1,1024,768,0,0);
	s_c753.showWnd(1);




}

//int setmac()
//{
// struct in_ifaddr* ia;
// for (ia = in_ifaddr; ia != 0; ia = ia->ia_next)
// {
//  struct ifnet* ifp = ia->ia_ifa.ifa_ifp;
//  if (ifp != 0)
//  {
//   int level;
//   IP_DRV_CTRL *pDrvCtrl;
//   END_OBJ *pEnd;
//   unsigned char PhyAddr[10]={0x08,0x09,0x10,0x11,0x12,0x13};
//
//   if(ifp->if_type != M2_ifType_ethernetCsmacd)
//   {
//    continue;
//   }
//   level = intLock();
//
//   pDrvCtrl = (IP_DRV_CTRL *)ifp->pCookie;
//
//   pEnd = PCOOKIE_TO_ENDOBJ(pDrvCtrl->pIpCookie);
//
//   pEnd->pFuncTable->ioctl(pEnd, EIOCSADDR, PhyAddr); /*此函数中会将PhyAddr中的值写到arm9200的寄存器中，但是ifShow看到的mac地址还是旧的，因为ifShow取的                                                                                                        不是寄存器中的MAC，而是一个全局变量ifnet中的MAC*/
//   //printf("%x:%x:%x:%x:%x:%x\n", PhyAddr[0], PhyAddr[1], PhyAddr[2], PhyAddr[3], PhyAddr[4], PhyAddr[5]);
//
//   intUnlock(level);
//   break;
//  }
// }
//}

}
#endif /* __cplusplus */



