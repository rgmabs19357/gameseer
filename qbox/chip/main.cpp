#include "appC753.h"
#include "dev.h"
#include "devFPGA.h"
#include "devICS307.h"
#include "chipCommon.h"

#ifdef __cplusplus
    extern "C"{


using namespace chipApp;



void chipTest()
{
	debug_msg("chipTest\n");
	AppC753 s_c753;
	s_c753.chipTest();
}

void chipSetBankTest(uint8_t byAdd,uint8_t byVal)
{

	AppC753 s_c753;
	debug_msg("Test C753 addr=%02x,byVal=%02x\n",byAdd,byVal);
	s_c753.SPI_Write(TYPE_CHIP_C753,byAdd,byVal);


}


void chipGetBankTest(uint8_t byAdd)
{

	uint8_t byVal=0;
	AppC753 s_c753;
	s_c753.SPI_Read(TYPE_CHIP_C753,byAdd,byVal);
	debug_msg("addr=%02x,val=%02x\n",byAdd,byVal);
}

void chipSetFPGA(uint16_t addr,uint16_t wVal)
{

	DriverChipFPGA s_FPGA;

	debug_msg("Test FPGA addr=%04x,byVal=%04x\n",addr,wVal);

	s_FPGA.FPGA_Write(addr,wVal);


}


void chipGetFPGATest(uint16_t addr)
{
	uint16_t byVal=0;
	DriverChipFPGA s_FPGA;
	s_FPGA.FPGA_Read(addr,byVal);
	debug_msg("addr=%04x,val1=%04x\n",addr,byVal);
}
void testSPI()
{
	debug_msg("testSPI\n");
	uint8_t byVal=0x0a;
	uint8_t byVal1=0x00;
	dev_SPI_Write(DEV_SPI_C753_CHANNEL,0,byVal);
	dev_SPI_Read(DEV_SPI_C753_CHANNEL,0,&byVal1);
	debug_msg("val1=%02x\n",byVal1);
}


void initHardware()
{
	debug_msg("initHardware\n");
	AppC753 s_c753;
	ScaleConfigT config;
//	config.byStandardType;
	config.wHorResolution = 1024;
	config.wVerResolution = 768;

	s_c753.initHardware(1,&config);
	debug_msg("showWnd\n");
	s_c753.showWnd(1);
}

void testFPGA()
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
	AppC753 s_c753;

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


void openChannel()
{
	debug_msg("openChannel\n");
	AppC753 s_c753;

	s_c753.openChannelTest();
	debug_msg("showWnd\n");
	s_c753.showWnd(1);
}

void initTest1024()
{
	debug_msg("initTest1024\n");
	AppC753 s_c753;
	DriverChipICS307 s_ics307;

	s_ics307.setPOCLK(ICS307_FREQUENCY_65000KHZ);
	s_c753.initTest1024();
	debug_msg("showWnd\n");
	s_c753.showWnd(1);
}

void initTest1400()
{
	debug_msg("initTest1400\n");
	AppC753 s_c753;
	DriverChipICS307 s_ics307;

	s_ics307.setPOCLK(ICS307_FREQUENCY_121750KHZ);
	s_c753.initTest1400();
	debug_msg("showWnd\n");
	s_c753.showWnd(1);
}



void C753SetInputFill()
{
	debug_msg("C753SetInputFill\n");
	AppC753 s_c753;
	s_c753.C753SetInputPortACTHorizontalStart(1,163);
	s_c753.C753SetInputPortACTHorizontalWidth(1,1024);
	s_c753.C753SetInputPortACTVerticalStart(1,34);
	s_c753.C753SetInputPortACTVerticalWidth(1,768);



	s_c753.C753SetInputFill(1,0xff0000);
	s_c753.C753SetInputImageControl(1,0x10);



	s_c753.showWnd(1);
}

}
#endif /* __cplusplus */



