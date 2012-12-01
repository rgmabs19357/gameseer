/*
 * devC772.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "devC772.h"
#include "devC772Addr.h"

using namespace chip;


DriverChip772::DriverChip772()
{

}

DriverChip772::~DriverChip772()
{

}



void DriverChip772::set480(uint32_t chn)
{

	list<map<uint8_t,uint8_t> > value;

	map<uint8_t,uint8_t> bank0;

	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;
	bank0[CP_IP00C772_B0_OHCYCL_ADDR1] = 0x58;
	bank0[CP_IP00C772_B0_OHCYCL_ADDR2] = 0x03;
	bank0[CP_IP00C772_B0_OVCYCL_ADDR1] = 0x0b;
	bank0[CP_IP00C772_B0_OVCYCL_ADDR2] = 0x02;
	bank0[CP_IP00C772_B0_OHSCT_ADDR] = 0x1e;
	bank0[CP_IP00C772_B0_OVSCT_ADDR] = 0x05;
	bank0[CP_IP00C772_B0_OACTHST_ADDR1] = 0x7b;
	bank0[CP_IP00C772_B0_OACTHST_ADDR2] = 0x00;
	bank0[CP_IP00C772_B0_OACTVST_ADDR1] = 0x24;
	bank0[CP_IP00C772_B0_OACTVST_ADDR2] = 0x00;

	bank0[CP_IP00C772_B0_OACTHW_ADDR1] = 0xc6;
	bank0[CP_IP00C772_B0_OACTHW_ADDR2] = 0x02;
	bank0[CP_IP00C772_B0_OACTVW_ADDR1] = 0xe7;
	bank0[CP_IP00C772_B0_OACTVW_ADDR2] = 0x01;
	bank0[CP_IP00C772_B0_OIMGCT_ADDR] = 0x80;


	value.push_back(bank0);

	map<uint8_t,uint8_t> bank1;
	bank1[CP_IP00C772_RGBNK_ADDR] = 0x01;
	bank1[CP_IP00C772_B1_IACTHST_ADDR1] = 0x49;
	bank1[CP_IP00C772_B1_IACTHST_ADDR2] = 0x00;
	bank1[CP_IP00C772_B1_IACTHW_ADDR1] = 0xd0;
	bank1[CP_IP00C772_B1_IACTHW_ADDR2] = 0x02;
	bank1[CP_IP00C772_B1_IACTVST_ADDR1] = 0x12;
	bank1[CP_IP00C772_B1_IACTVST_ADDR2] = 0x00;
	bank1[CP_IP00C772_B1_IACTVW_ADDR1] = 0xe4;
	bank1[CP_IP00C772_B1_IACTVW_ADDR2] = 0x01;


	value.push_back(bank1);


	map<uint8_t,uint8_t> bank2;
	bank2[CP_IP00C772_RGBNK_ADDR] = 0x02;
	bank2[CP_IP00C772_B2_OADJCT_ADDR] = 0x08;
	bank2[CP_IP00C772_B2_PDCTRL_ADDR] = 0xfd;
	bank2[CP_IP00C772_B2_PDMV22TH_ADDR] = 0x08;
	bank2[CP_IP00C772_B2_PD23RSTTH_ADDR] = 0x3c;
	bank2[CP_IP00C772_B2_PDSQTH_ADDR] = 0x41;
	bank2[CP_IP00C772_B2_MVACCSEL_ADDR] = 0x35;
	bank2[CP_IP00C772_B2_PDACTSEL_ADDR] = 0x03;
	bank2[CP_IP00C772_B2_PD22RSTCT_ADDR] = 0x61;
	bank2[CP_IP00C772_B2_PDMV23TH_ADDR] = 0x14;

	value.push_back(bank2);

	map<uint8_t,uint8_t> bank3;
	bank3[CP_IP00C772_RGBNK_ADDR] = 0x00;
	bank3[CP_IP00C772_MEMCT_ADDR] = 0x29;

	value.push_back(bank3);

	dev_SPI_WriteMult(chn,value);

}

void DriverChip772::set576(uint32_t chn)
{
	list<map<uint8_t,uint8_t> > value;
	map<uint8_t,uint8_t> bank0;

	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;
	bank0[CP_IP00C772_B0_OHCYCL_ADDR1] = 0x5e;
	bank0[CP_IP00C772_B0_OHCYCL_ADDR2] = 0x03;
	bank0[CP_IP00C772_B0_OVCYCL_ADDR1] = 0x6f;
	bank0[CP_IP00C772_B0_OVCYCL_ADDR2] = 0x02;
	bank0[CP_IP00C772_B0_OHSCT_ADDR] = 0x1f;
	bank0[CP_IP00C772_B0_OVSCT_ADDR] = 0x04;
	bank0[CP_IP00C772_B0_OACTHST_ADDR1] = 0x82;
	bank0[CP_IP00C772_B0_OACTHST_ADDR2] = 0x00;
	bank0[CP_IP00C772_B0_OACTVST_ADDR1] = 0x2a;
	bank0[CP_IP00C772_B0_OACTVST_ADDR2] = 0x00;
	bank0[CP_IP00C772_B0_OACTHW_ADDR1] = 0xbc;
	bank0[CP_IP00C772_B0_OACTHW_ADDR2] = 0x02;
	bank0[CP_IP00C772_B0_OACTVW_ADDR1] = 0x43;
	bank0[CP_IP00C772_B0_OACTVW_ADDR2] = 0x02;
	bank0[CP_IP00C772_B0_OCCFTGB_ADDR1] = 0xea;
	bank0[CP_IP00C772_B0_OCCFTGB_ADDR2] = 0x01;
	bank0[CP_IP00C772_B0_OIMGCT_ADDR] = 0x80;

	value.push_back(bank0);

	map<uint8_t,uint8_t> bank1;
	bank1[CP_IP00C772_RGBNK_ADDR] = 0x01;
	bank1[CP_IP00C772_B1_IACTHST_ADDR1] = 0x51;
	bank1[CP_IP00C772_B1_IACTHST_ADDR2] = 0x00;
	bank1[CP_IP00C772_B1_IACTHW_ADDR1] = 0xd0;
	bank1[CP_IP00C772_B1_IACTHW_ADDR2] = 0x02;
	bank1[CP_IP00C772_B1_IACTVST_ADDR1] = 0x17;
	bank1[CP_IP00C772_B1_IACTVST_ADDR2] = 0x00;
	bank1[CP_IP00C772_B1_IACTVW_ADDR1] = 0x40;
	bank1[CP_IP00C772_B1_IACTVW_ADDR2] = 0x02;




	value.push_back(bank1);


	map<uint8_t,uint8_t> bank2;
	bank2[CP_IP00C772_RGBNK_ADDR] = 0x02;
	bank2[CP_IP00C772_B2_OADJCT_ADDR] = 0x09;
	bank2[CP_IP00C772_B2_PDCTRL_ADDR] = 0x7d;
	bank2[CP_IP00C772_B2_PDMV22TH_ADDR] = 0x0c;
	bank2[CP_IP00C772_B2_PD23RSTTH_ADDR] = 0x40;
	bank2[CP_IP00C772_B2_PDSQTH_ADDR] = 0x41;
	bank2[CP_IP00C772_B2_MVACCSEL_ADDR] = 0x45;
	bank2[CP_IP00C772_B2_PDACTSEL_ADDR] = 0x03;
	bank2[CP_IP00C772_B2_PD22RSTCT_ADDR] = 0x21;
	bank2[CP_IP00C772_B2_PDMV23TH_ADDR] = 0x16;


	value.push_back(bank2);

	map<uint8_t,uint8_t> bank3;
	bank3[CP_IP00C772_RGBNK_ADDR] = 0x00;
	bank3[CP_IP00C772_MEMCT_ADDR] = 0x29;

	value.push_back(bank3);


	dev_SPI_WriteMult(chn,value);

}

//void DriverChip772::dev_InitIP00c772(uint32_t chn)
//{
//	list<map<uint8_t,uint8_t> > value;
//
//	map<uint8_t,uint8_t> bank;
//
//	bank[CP_IP00C772_MCT_ADDR] = 0x03;
//	bank[CP_IP00C772_RTCT_ADDR] = 	0x00;
//	bank[CP_IP00C772_MISC_ADDR] = 	0x08;
//	bank[CP_IP00C772_MEMCT_ADDR] = 0x29;
//	bank[CP_IP00C772_RSTCT_ADDR] = 0x00;
//
//	value.push_back(bank);
//
//
//	map<uint8_t,uint8_t> bank0;
//	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;
//
//	bank0[CP_IP00C772_B0_OSYCT_ADDR] = 		0x41;
//	bank0[CP_IP00C772_B0_OHCYCL_ADDR1] =   	0x5e;
//	bank0[CP_IP00C772_B0_OHCYCL_ADDR2] =  	0x03;
//	bank0[CP_IP00C772_B0_OVCYCL_ADDR1] = 	0x6f;
//	bank0[CP_IP00C772_B0_OVCYCL_ADDR2] =	0x02;
//	bank0[CP_IP00C772_B0_OHSCT_ADDR]   =   	0x1e;
//	bank0[CP_IP00C772_B0_OVSCT_ADDR]   =   	0x05;
//	bank0[CP_IP00C772_B0_SYRDLY_ADDR]  =   	0x20;
//	bank0[CP_IP00C772_B0_OVCYCLMIN_ADDR1] =   	0x0b;
//	bank0[CP_IP00C772_B0_OVCYCLMIN_ADDR2] =   	0x02;
//	bank0[CP_IP00C772_B0_OSWP_ADDR]      =   	0x00;
//
//	bank0[CP_IP00C772_B0_OFILL_RED_ADDR]  =   	0x00;
//	bank0[CP_IP00C772_B0_OFILL_GREEN_ADDR]  =   0x00;
//	bank0[CP_IP00C772_B0_OFILL_BLUE_ADDR]  =   	0xff;
//
////	bank0[CP_IP00C772_B0_OBKGD0_ADDR]  =   	0x00;
////	bank0[CP_IP00C772_B0_OBKGD1_ADDR]  =   	0x00;
//
//	bank0[CP_IP00C772_B0_OIMGCT_ADDR]  =   	0x00;
////	bank0[CP_IP00C772_B0_BGCT_ADDR]  =   0x03;
////	bank0[CP_IP00C772_B0_GAINR_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_GAING_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_GAINB_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_BIASR_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_BIASG_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_BIASB_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_GAIN2R_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_GAIN2G_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_GAIN2B_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_BIAS2R_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_BIAS2G_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_BIAS2B_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_GMCT_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_GMBNKSEL_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_GMAD_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_GMDT_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_ERDFCT_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_ACTCT_ADDR]  =   0x05;
////	bank0[CP_IP00C772_B0_HISTGRAMCT_ADDR]  =   0x05;
//
//	bank0[CP_IP00C772_B0_POCLKOCT_ADDR]  =   0x01;
//	bank0[CP_IP00C772_B0_POPLLCT_ADDR]  =   0x01;
//	bank0[CP_IP00C772_B0_POREFDIV_ADDR]  =   0x02;
//	bank0[CP_IP00C772_B0_POFBDIV_ADDR]  =   0x07;
//
//	bank0[CP_IP00C772_B0_GIO1SEL_ADDR]  =   0x03;
////	bank0[CP_IP00C772_B0_GIO1DATA_ADDR]  =   0x05;
//
//	value.push_back(bank0);
//
//
//	map<uint8_t,uint8_t> bank1;
//	bank1[CP_IP00C772_RGBNK_ADDR] = 0x01;
//	bank1[CP_IP00C772_B1_IIMGCT_ADDR] = 0x41;
//	bank1[CP_IP00C772_B1_ISYCT_ADDR] = 0x02;
//	bank1[CP_IP00C772_B1_HVPHMSR_ADDR] = 0x00;
//	bank1[CP_IP00C772_B1_IVLNDLY_ADDR1] = 0x00;
//	bank1[CP_IP00C772_B1_IVLNDLY_ADDR2] = 0x0;
//	bank1[CP_IP00C772_B1_IVSKDLY_ADDR1] = 0x0;
//	bank1[CP_IP00C772_B1_IVSKDLY_ADDR2] = 0x0;
//	bank1[CP_IP00C772_B1_IHSKDLY_ADDR1] = 0x0;
//	bank1[CP_IP00C772_B1_IHSKDLY_ADDR2] = 0x0;
//	bank1[CP_IP00C772_B1_AUTOFLD_ADDR] = 0x80;
//	bank1[CP_IP00C772_B1_IACTHST_ADDR1] = 0x4e;
//	bank1[CP_IP00C772_B1_IACTHST_ADDR2] = 0x00;
//	bank1[CP_IP00C772_B1_IACTHW_ADDR1] = 0xd0;
//	bank1[CP_IP00C772_B1_IACTHW_ADDR2] = 0x02;
//	bank1[CP_IP00C772_B1_IACTVST_ADDR1] = 0x14;
//	bank1[CP_IP00C772_B1_IACTVST_ADDR2] = 0x00;
//	bank1[CP_IP00C772_B1_IACTVW_ADDR1] = 0xf3;
//	bank1[CP_IP00C772_B1_IACTVW_ADDR2] = 0x00;
//
//	value.push_back(bank1);
//
//
//	map<uint8_t,uint8_t> bank2;
//	bank2[CP_IP00C772_RGBNK_ADDR] = 0x02;
//
//	bank2[CP_IP00C772_B2_TMPPXNRCT_ADDR]=0x03;
//	bank2[CP_IP00C772_B2_TPXNRTH1_ADDR]=0x32;
//	bank2[CP_IP00C772_B2_TPXNRTH2_ADDR]=0x75;
//	bank2[CP_IP00C772_B2_TPXNRTH3_ADDR]=0xb9;
//	bank2[CP_IP00C772_B2_TPXNRTH4_ADDR]=0xfd;
//	bank2[CP_IP00C772_B2_TPXNRCF1_ADDR]=0x10;
//	bank2[CP_IP00C772_B2_TPXNRCF2_ADDR]=0x12;
//	bank2[CP_IP00C772_B2_TPXNRCF3_ADDR]=0x14;
//	bank2[CP_IP00C772_B2_TPXNRCF4_ADDR]=0x16;
//	bank2[CP_IP00C772_B2_TPXNRCF5_ADDR]=0x18;
//	bank2[CP_IP00C772_B2_TPXNRCF6_ADDR]=0x1a;
//	bank2[CP_IP00C772_B2_TPXNRCF7_ADDR]=0x1c;
//	bank2[CP_IP00C772_B2_TPXNRCF8_ADDR]=0x1f;
//	bank2[CP_IP00C772_B2_HVPXNRCT_ADDR]=0x00;
//	bank2[CP_IP00C772_B2_VPXNRCF1_ADDR]=0x00;
//	bank2[CP_IP00C772_B2_VPXNRCF2_ADDR]=0x00;
//	bank2[CP_IP00C772_B2_HPXNRCF1_ADDR]=0x00;
//	bank2[CP_IP00C772_B2_HPXNRCF2_ADDR]=0x00;
//	bank2[CP_IP00C772_B2_MVNRCT_ADDR]=0x1f;
//	bank2[CP_IP00C772_B2_HMVNRCFA_ADDR]=0x01;
//	bank2[CP_IP00C772_B2_HMVNRCFB_ADDR]=0x01;
//	bank2[CP_IP00C772_B2_HMVNRCFC_ADDR]=0x02;
//	bank2[CP_IP00C772_B2_HMVNRCFD_ADDR]=0x08;
//	bank2[CP_IP00C772_B2_VFILCFA_ADDR]=0x08;
//	bank2[CP_IP00C772_B2_VFILCFB_ADDR]=0x08;
//	bank2[CP_IP00C772_B2_VFILCFC_ADDR]=0x08;
//	bank2[CP_IP00C772_B2_VFILCFD_ADDR]=0x10;
//	bank2[CP_IP00C772_B2_HFILCFA_ADDR]=0x08;
//	bank2[CP_IP00C772_B2_HFILCFB_ADDR]=0x08;
//	bank2[CP_IP00C772_B2_HFILCFC_ADDR]=0x10;
//	bank2[CP_IP00C772_B2_HFILCFD_ADDR]=0x18;
//	bank2[CP_IP00C772_B2_XVFILMD_ADDR]=0x07;
//	bank2[CP_IP00C772_B2_XNRCUT_ADDR]=0x01;
////	bank2[CP_IP00C772_B2_LUTWAD_ADDR]=0x02;
////	bank2[CP_IP00C772_B2_LUTCOEF_ADDR]=0x02;
////	bank2[CP_IP00C772_B2_LUTWR_ADDR]= 0x02;
//
//	bank2[CP_IP00C772_B2_IPTEST_ADDR]=0x00;
//	bank2[CP_IP00C772_B2_OADJCT_ADDR]=0x08;
//	bank2[CP_IP00C772_B2_PDCTRL_ADDR]=0xfd;
//	bank2[CP_IP00C772_B2_PDMV22TH_ADDR]=0x08;
//	bank2[CP_IP00C772_B2_PD23RSTTH_ADDR]=0x3c;
//	bank2[CP_IP00C772_B2_PDSQTH_ADDR]=0x41;
//	bank2[CP_IP00C772_B2_MVACCSEL_ADDR]=0x35;
//	bank2[CP_IP00C772_B2_PDACTSEL_ADDR]=0x03;
//	bank2[CP_IP00C772_B2_PD22RSTCT_ADDR]=0x61;
//	bank2[CP_IP00C772_B2_PDMV23TH_ADDR]=0x14;
//
//	bank2[CP_IP00C772_B2_DIAGCT1_ADDR]=0x37;
//	bank2[CP_IP00C772_B2_DIAGCT2_ADDR]=0xcf;
//	bank2[CP_IP00C772_B2_DIAGCT3_ADDR]=0xe6;
//
//	bank2[CP_IP00C772_B2_DIAGTH0_ADDR]=0x00;
//	bank2[CP_IP00C772_B2_DIAGTH1_ADDR]=0x09;
//	bank2[CP_IP00C772_B2_DIAGTH2_ADDR]=0x12;
//	bank2[CP_IP00C772_B2_DIAGTH3_ADDR]=0x03;
//	bank2[CP_IP00C772_B2_DIAGTH4_ADDR]=0x08;
//	bank2[CP_IP00C772_B2_DIAGTH5_ADDR]=0x05;
//	bank2[CP_IP00C772_B2_DIAGTH6_ADDR]=0x12;
//	bank2[CP_IP00C772_B2_DIAGTH7_ADDR]=0x04;
//	bank2[CP_IP00C772_B2_DIAGTH8_ADDR]=0x04;
//	bank2[CP_IP00C772_B2_DIAGTH9_ADDR]=0x04;
//	bank2[CP_IP00C772_B2_DIAGTH10_ADDR]=0x09;
//	bank2[CP_IP00C772_B2_DIAGTH11_ADDR]=0x10;
//	bank2[CP_IP00C772_B2_DIAGTH12_ADDR]=0x32;
//
//	value.push_back(bank2);
//
//	dev_C772_InitColorConversion(chn);
//	dev_C772_InitIPConversion(chn);
//	dev_C772_InitLUT(chn);
//
//
//	dev_SPI_WriteMult(chn,value);
//}

void DriverChip772::initColorConversion(uint32_t chn)
{

	list<map<uint8_t,uint8_t> > value;

	map<uint8_t,uint8_t> bank0;

	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;

//	bank0[CP_IP00C772_B0_OCCFTR_ADDR1]  =   0x9d;
	bank0[CP_IP00C772_B0_OCCFTR_ADDR1]  =   0x9d;
	bank0[CP_IP00C772_B0_OCCFTR_ADDR2]  =   0x05;
	bank0[CP_IP00C772_B0_OCCFTB_ADDR1]  =   0x18;
	bank0[CP_IP00C772_B0_OCCFTB_ADDR2]  =   0x07;
	bank0[CP_IP00C772_B0_OCCFTGR_ADDR1]  =   0x25;
	bank0[CP_IP00C772_B0_OCCFTGR_ADDR2]  =   0x1d;
	bank0[CP_IP00C772_B0_OCCFTGB_ADDR1]  =   0xea;
	bank0[CP_IP00C772_B0_OCCFTGB_ADDR2]  =   0x01;

	bank0[CP_IP00C772_B0_OCCFTRB_ADDR1]  =   0x00;
	bank0[CP_IP00C772_B0_OCCFTRB_ADDR2]  =   0x00;
	bank0[CP_IP00C772_B0_OCCFTBR_ADDR1]  =   0x00;
	bank0[CP_IP00C772_B0_OCCFTBR_ADDR2]  =   0x00;


	value.push_back(bank0);
	dev_SPI_WriteMult(chn,value);
}

void DriverChip772::initIPConversion(uint32_t chn)
{
	list<map<uint8_t,uint8_t> > value;

	map<uint8_t,uint8_t> bank0;

	bank0[CP_IP00C772_RGBNK_ADDR] = 0x03;

	bank0[CP_IP00C772_B3_IPOSFLD1_ADDR1] = 0x00;
	bank0[CP_IP00C772_B3_IPOSFLD1_ADDR2] = 0x00;
	bank0[CP_IP00C772_B3_IPOSFLD1_ADDR3] = 0x18;

	bank0[CP_IP00C772_B3_IPISFLD0_ADDR1] = 0x00;
	bank0[CP_IP00C772_B3_IPISFLD0_ADDR2] = 0x08;
	bank0[CP_IP00C772_B3_IPISFLD0_ADDR3] = 0x00;

	bank0[CP_IP00C772_B3_IPISFLD2_ADDR1] = 0x00;
	bank0[CP_IP00C772_B3_IPISFLD2_ADDR2] = 0x08;
	bank0[CP_IP00C772_B3_IPISFLD2_ADDR3] = 0x18;

	bank0[CP_IP00C772_B3_IPISFLD3_ADDR1] = 0x00;
	bank0[CP_IP00C772_B3_IPISFLD3_ADDR2] = 0x00;
	bank0[CP_IP00C772_B3_IPISFLD3_ADDR3] = 0x18;

	bank0[CP_IP00C772_B3_IPMWI_ADDR] = 0x08;
	bank0[CP_IP00C772_B3_MVFLD_ADDR1] = 0x00;
	bank0[CP_IP00C772_B3_MVFLD_ADDR2] = 0x00;
	bank0[CP_IP00C772_B3_MVFLD_ADDR3] = 0x30;
	bank0[CP_IP00C772_B3_TMSASEL_ADDR] = 0x01;


	value.push_back(bank0);
	dev_SPI_WriteMult(chn,value);
}

void DriverChip772::initLUT(uint32_t chn)
{
	list<map<uint8_t,uint8_t> > value;
	map<uint8_t,uint8_t> bank0;

	SPI_Write(chn,CP_IP00C772_RGBNK_ADDR,0x02);
	// C772B2 LUTCOEF 00042000h

	SPI_Write(chn,CP_IP00C772_LUTCOEF_a,0x00);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_b,0x20);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_c,0x04);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_d,0x00);

	SPI_Write(chn,CP_IP00C772_LUTWAD,0x00);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);

    // C772B2 LUTCOEF 00139c01h

	SPI_Write(chn,CP_IP00C772_LUTCOEF_a,0x01);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_b,0x9c);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_c,0x13);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_d,0x00);

	SPI_Write(chn,CP_IP00C772_LUTWAD,0x01);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x02);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);



    // C772B2 LUTCOEF 00231802h
	SPI_Write(chn,CP_IP00C772_LUTCOEF_a,0x02);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_b,0x18);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_c,0x23);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_d,0x00);

	SPI_Write(chn,CP_IP00C772_LUTWAD,0x03);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x04);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);



    // C772B2 LUTCOEF 00329403h
	SPI_Write(chn,CP_IP00C772_LUTCOEF_a,0x03);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_b,0x94);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_c,0x32);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_d,0x00);

	SPI_Write(chn,CP_IP00C772_LUTWAD,0x05);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x06);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x07);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);




    // C772B2 LUTCOEF 00421004h

	SPI_Write(chn,CP_IP00C772_LUTCOEF_a,0x04);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_b,0x10);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_c,0x42);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_d,0x00);

	SPI_Write(chn,CP_IP00C772_LUTWAD,0x08);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x09);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x0a);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x0b);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);



    // C772B2 LUTCOEF 00518c05h
	SPI_Write(chn,CP_IP00C772_LUTCOEF_a,0x05);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_b,0x8c);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_c,0x51);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_d,0x00);

	SPI_Write(chn,CP_IP00C772_LUTWAD,0x0c);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x0d);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x0e);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x0f);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);



    // C772B2 LUTCOEF 00610806h

	SPI_Write(chn,CP_IP00C772_LUTCOEF_a,0x06);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_b,0x08);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_c,0x61);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_d,0x00);

	SPI_Write(chn,CP_IP00C772_LUTWAD,0x10);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x11);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x12);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x13);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);



    // C772B2 LUTCOEF 00708407h
	SPI_Write(chn,CP_IP00C772_LUTCOEF_a,0x07);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_b,0x84);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_c,0x70);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_d,0x00);


	SPI_Write(chn,CP_IP00C772_LUTWAD,0x14);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x15);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x16);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x17);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);



   // C772B2 LUTCOEF 00800008h
	SPI_Write(chn,CP_IP00C772_LUTCOEF_a,0x08);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_b,0x00);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_c,0x80);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_d,0x00);


	SPI_Write(chn,CP_IP00C772_LUTWAD,0x18);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x19);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x1a);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x1b);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x1c);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x1d);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x1e);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x1f);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);



    // C772B2 LUTCOEF 00004000h
	SPI_Write(chn,CP_IP00C772_LUTCOEF_a,0x00);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_b,0x40);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_c,0x00);
	SPI_Write(chn,CP_IP00C772_LUTCOEF_d,0x00);


//
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x20);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x21);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x22);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x23);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x24);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x25);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x26);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x27);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x28);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x29);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x2a);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x2b);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x2c);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x2d);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x2e);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x2f);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);


	SPI_Write(chn,CP_IP00C772_LUTWAD,0x30);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x31);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x32);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x33);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x34);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x35);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x36);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x37);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x38);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x39);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x3a);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x3b);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x3c);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x3d);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x3e);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);
	SPI_Write(chn,CP_IP00C772_LUTWAD,0x3f);
	SPI_Write(chn,CP_IP00C772_LUTWR,0xff);


//    value.push_back(bank0);
//    dev_SPI_WriteMult(chn,value);
}

void DriverChip772::reset(uint32_t chn)
{

}



void DriverChip772::changeModel(uint32_t chn,uint32_t byVideoModel)
{

}


void DriverChip772::setInputSize(uint32_t chn,uint32_t wACTHStart,uint32_t wACTHWidth,uint32_t wACTVStart,uint32_t wACTVWidth)
{
	list<map<uint8_t,uint8_t> > value;
	map<uint8_t,uint8_t> bank0;
	bank0[CP_IP00C772_RGBNK_ADDR] = 0x01;

	uint8_t byValue = 0;

	byValue = wACTHStart & MASK_LOW8;
	bank0[CP_IP00C772_B1_IACTHST_ADDR1] = byValue;

	byValue = (wACTHStart & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B1_IACTHST_ADDR2] = byValue;

	byValue = wACTHWidth & MASK_LOW8;
	bank0[CP_IP00C772_B1_IACTHW_ADDR1] = byValue;

	byValue = (wACTHWidth & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B1_IACTHW_ADDR2] = byValue;


	byValue = wACTVStart & MASK_LOW8;
	bank0[CP_IP00C772_B1_IACTVST_ADDR1] = byValue;

	byValue = (wACTVStart & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B1_IACTVST_ADDR2] = byValue;

	byValue = wACTVWidth & MASK_LOW8;
	bank0[CP_IP00C772_B1_IACTVW_ADDR1] = byValue;

	byValue = (wACTVWidth & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B1_IACTVW_ADDR2] = byValue;

	value.push_back(bank0);

	dev_SPI_WriteMult(chn,value);
}

void DriverChip772::setOutputSize(uint32_t chn,uint32_t wACTHStart,uint32_t wACTHWidth,uint32_t wACTVStart,uint32_t wACTVWidth)
{
	list<map<uint8_t,uint8_t> > value;
	map<uint8_t,uint8_t> bank0;
	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;

	uint8_t byValue = 0;

	byValue = wACTHStart & MASK_LOW8;
	bank0[CP_IP00C772_B0_OACTHST_ADDR1] = byValue;

	byValue = (wACTHStart & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B0_OACTHST_ADDR2] = byValue;

	byValue = wACTHWidth & MASK_LOW8;
	bank0[CP_IP00C772_B0_OACTHW_ADDR1]  = byValue;

	byValue = (wACTHWidth & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B0_OACTHW_ADDR2]  = byValue;


	byValue = wACTVStart & MASK_LOW8;
	bank0[CP_IP00C772_B0_OACTVST_ADDR1] = byValue;

	byValue = (wACTVStart & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B0_OACTVST_ADDR2] = byValue;

	byValue = wACTVWidth & MASK_LOW8;
	bank0[CP_IP00C772_B0_OACTVW_ADDR1] = byValue;

	byValue = (wACTVWidth & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B0_OACTVW_ADDR2] = byValue;

	value.push_back(bank0);
	dev_SPI_WriteMult(chn,value);

}


void DriverChip772::setOutputSyncCycle(uint32_t chn,uint32_t wHSyncCycle,uint32_t wVSyncCycle)
{
	list<map<uint8_t,uint8_t> > value;
	map<uint8_t,uint8_t> bank0;
	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;

	uint8_t byValue = 0;


	byValue = wHSyncCycle & MASK_LOW8;
	bank0[CP_IP00C772_B0_OHCYCL_ADDR1] = byValue;

	byValue = (wHSyncCycle & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B0_OHCYCL_ADDR2] = byValue;

	byValue = wHSyncCycle & MASK_LOW8;
	bank0[CP_IP00C772_B0_OVCYCL_ADDR1] = byValue;

	byValue = (wHSyncCycle & MASK_HIGH8) >> 8;
	bank0[CP_IP00C772_B0_OVCYCL_ADDR2] = byValue;

	value.push_back(bank0);
	dev_SPI_WriteMult(chn,value);
}

void DriverChip772::setBlueScreen(uint32_t chn,uint32_t byFlg)
{



	list<map<uint8_t,uint8_t> > value;
	map<uint8_t,uint8_t> bank0;
	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;

	bank0[CP_IP00C772_B0_OFILL_RED_ADDR] = 0x00;
	bank0[CP_IP00C772_B0_OFILL_GREEN_ADDR] = 0x00;
	bank0[CP_IP00C772_B0_OFILL_BLUE_ADDR] = 0xff;

	value.push_back(bank0);
	dev_SPI_WriteMult(chn,value);

	uint8_t byValue = 0;

	SPI_Read(chn,CP_IP00C772_B0_OIMGCT_ADDR,byValue);

	if(byFlg == 1)
	{
		byValue = byValue | 0x01;
		SPI_Write(chn,CP_IP00C772_B0_OIMGCT_ADDR,byValue);
	}
	else
	{
		byValue = byValue & 0xfe;
		SPI_Write(chn,CP_IP00C772_B0_OIMGCT_ADDR,byValue);
	}
	SPI_Write(chn,CP_IP00C772_RGBNK_ADDR,0);


}

void DriverChip772::setHorAndVerSyncCtrl(uint32_t chn,uint32_t byHorPolarity,uint32_t byHorWidth,uint32_t byVerPolarty,uint32_t byVerWidth)
{
	list<map<uint8_t,uint8_t> > value;
	map<uint8_t,uint8_t> bank0;
	bank0[CP_IP00C772_RGBNK_ADDR] = 0x00;

	uint8_t byValue = 0;

	byValue = byValue | (byHorWidth & 0x7f);
	byValue = byValue | (byHorPolarity << 7);

	bank0[CP_IP00C772_B0_OHSCT_ADDR] = byValue;

	byValue = 0;
	byValue = byValue | (byVerWidth & 0x0f);
	byValue = byValue | (byVerPolarty << 4);

	bank0[CP_IP00C772_B0_OVSCT_ADDR] = byValue;


	value.push_back(bank0);
	dev_SPI_WriteMult(chn,value);
}


void DriverChip772::setBankRegister(uint32_t chn,uint8_t byVal)
{
	SPI_Write(chn,CP_IP00C772_RGBNK_ADDR,byVal);
}
void DriverChip772::getBankRegister(uint32_t chn,uint8_t &byVal)
{
	SPI_Read(chn,CP_IP00C772_RGBNK_ADDR,byVal);
}

void DriverChip772::initBaseReg(uint32_t byChannel)
{
	SPI_Write(byChannel,CP_IP00C772_RGBNK_ADDR,0x00);

	SPI_Write(byChannel,CP_IP00C772_MCT_ADDR,0x03);
	SPI_Write(byChannel,CP_IP00C772_RTCT_ADDR,0x00);
	SPI_Write(byChannel,CP_IP00C772_MISC_ADDR,0x00);
	SPI_Write(byChannel,CP_IP00C772_MEMCT_ADDR,0x29);
	SPI_Write(byChannel,CP_IP00C772_RSTCT_ADDR,0x00);

}

void DriverChip772::dev_C772_Init(uint32_t byChannel)
{
	initBaseReg(byChannel);

	SPI_Write(byChannel,CP_IP00C772_B0_OSYCT_ADDR,0x41);
	SPI_Write(byChannel,CP_IP00C772_B0_OSWP_ADDR,0x04);

	setOutputSyncCycle(byChannel,858,525);
	setHorAndVerSyncCtrl(byChannel,POL_LOW,30,POL_LOW,5);
	//Dev_C772_SetForcedSyncReset(byChannel,0x20,523);
	setForcedSyncReset(byChannel,0x20,523);

	setOutputSize(byChannel,122,710, 36, 484);


	setBlueScreen(byChannel,0);
	initColorConversion(byChannel);
	initCLK(byChannel);
	initPurposPortIO(byChannel);


	initInputPara(byChannel);
	setInputSize(byChannel,73,710, 18, 484);

	setPulldown(byChannel,1);
	initPixelNR(byChannel);

	initIPConversion(byChannel);
	initLUT(byChannel);

}

void DriverChip772::setForcedSyncReset(uint32_t byChannel,uint8_t byDelay,uint16_t wOVCyclMin)
{
	uint8_t byValue = 0;
	SPI_Write(byChannel,CP_IP00C772_RGBNK_ADDR,0x0);
	SPI_Write(byChannel,CP_IP00C772_B0_SYRDLY_ADDR,byDelay);

	byValue = (uint8_t)(wOVCyclMin & 0x00ff);
	SPI_Write(byChannel,CP_IP00C772_B0_OVCYCLMIN_ADDR1,byValue);

	byValue = (uint8_t)((wOVCyclMin & 0xff00) >> 8);
	SPI_Write(byChannel,CP_IP00C772_B0_OVCYCLMIN_ADDR2,byValue);


}

void DriverChip772::initCLK(uint32_t byChannel)
{

	SPI_Write(byChannel,CP_IP00C772_RGBNK_ADDR,0x0);
	SPI_Write(byChannel,CP_IP00C772_B0_POCLKOCT_ADDR,0x11);
	SPI_Write(byChannel,CP_IP00C772_B0_POPLLCT_ADDR,0x01);
	SPI_Write(byChannel,CP_IP00C772_B0_POREFDIV_ADDR,0x02);
	SPI_Write(byChannel,CP_IP00C772_B0_POFBDIV_ADDR,0x07);


}


void DriverChip772::initPurposPortIO(uint32_t byChannel)
{

	SPI_Write(byChannel,CP_IP00C772_RGBNK_ADDR,0x0);
	SPI_Write(byChannel,CP_IP00C772_B0_GIO1SEL_ADDR,0x03);
	SPI_Write(byChannel,CP_IP00C772_B0_GIO1DATA_ADDR,0x00);


}

void DriverChip772::initInputPara(uint32_t byChannel)
{
	SPI_Write(byChannel,CP_IP00C772_RGBNK_ADDR,0x01);

	SPI_Write(byChannel,CP_IP00C772_B1_IIMGCT_ADDR,0x41);
	SPI_Write(byChannel,CP_IP00C772_B1_ISYCT_ADDR,0x2);
	SPI_Write(byChannel,CP_IP00C772_B1_HVPHMSR_ADDR,0x0);
	SPI_Write(byChannel,CP_IP00C772_B1_IVLNDLY_ADDR1,0x0);
	SPI_Write(byChannel,CP_IP00C772_B1_IVLNDLY_ADDR2,0x0);
	SPI_Write(byChannel,CP_IP00C772_B1_IVSKDLY_ADDR1,0x0);
	SPI_Write(byChannel,CP_IP00C772_B1_IVSKDLY_ADDR2,0x0);
	SPI_Write(byChannel,CP_IP00C772_B1_IHSKDLY_ADDR1,0x0);
	SPI_Write(byChannel,CP_IP00C772_B1_IHSKDLY_ADDR2,0x0);

	SPI_Write(byChannel,CP_IP00C772_B1_AUTOFLD_ADDR,0x80);

	SPI_Write(byChannel,CP_IP00C772_RGBNK_ADDR,0x00);
}

void DriverChip772::setPulldown(uint32_t byChannel,uint32_t byModel)
{


	SPI_Write(byChannel,CP_IP00C772_RGBNK_ADDR,0x02);

	if(byModel == 0)
	{

		SPI_Write(byChannel,CP_IP00C772_B2_OADJCT_ADDR,0x09);
		SPI_Write(byChannel,CP_IP00C772_B2_PDCTRL_ADDR,0x7d);
		SPI_Write(byChannel,CP_IP00C772_B2_PDMV22TH_ADDR,0x0c);
		SPI_Write(byChannel,CP_IP00C772_B2_PD23RSTTH_ADDR,0x40);
		SPI_Write(byChannel,CP_IP00C772_B2_PDSQTH_ADDR,0x041);
		SPI_Write(byChannel,CP_IP00C772_B2_MVACCSEL_ADDR,0x45);
		SPI_Write(byChannel,CP_IP00C772_B2_PDACTSEL_ADDR,0x03);
		SPI_Write(byChannel,CP_IP00C772_B2_PD22RSTCT_ADDR,0x21);
		SPI_Write(byChannel,CP_IP00C772_B2_PDMV23TH_ADDR,0x16);
	}
	else if(byModel == 1)
	{

		SPI_Write(byChannel,CP_IP00C772_B2_OADJCT_ADDR,0x08);
		SPI_Write(byChannel,CP_IP00C772_B2_PDCTRL_ADDR,0xfd);
		SPI_Write(byChannel,CP_IP00C772_B2_PDMV22TH_ADDR,0x08);
		SPI_Write(byChannel,CP_IP00C772_B2_PD23RSTTH_ADDR,0x3c);
		SPI_Write(byChannel,CP_IP00C772_B2_PDSQTH_ADDR,0x41);
		SPI_Write(byChannel,CP_IP00C772_B2_MVACCSEL_ADDR,0x35);
		SPI_Write(byChannel,CP_IP00C772_B2_PDACTSEL_ADDR,0x03);
		SPI_Write(byChannel,CP_IP00C772_B2_PD22RSTCT_ADDR,0x61);
		SPI_Write(byChannel,CP_IP00C772_B2_PDMV23TH_ADDR,0x14);
	}

	SPI_Write(byChannel,CP_IP00C772_RGBNK_ADDR,0x00);

}

void DriverChip772::initPixelNR(uint32_t byChannel)
{
	SPI_Write(byChannel,CP_IP00C772_RGBNK_ADDR,0x02);
	SPI_Write(byChannel,CP_IP00C772_B2_TMPPXNRCT_ADDR,0x03);
	SPI_Write(byChannel,CP_IP00C772_B2_TPXNRTH1_ADDR,0x32);
	SPI_Write(byChannel,CP_IP00C772_B2_TPXNRTH2_ADDR,0x75);
	SPI_Write(byChannel,CP_IP00C772_B2_TPXNRTH3_ADDR,0xb9);
	SPI_Write(byChannel,CP_IP00C772_B2_TPXNRTH4_ADDR,0xfd);
	SPI_Write(byChannel,CP_IP00C772_B2_TPXNRCF1_ADDR,0x10);
	SPI_Write(byChannel,CP_IP00C772_B2_TPXNRCF2_ADDR,0x12);
	SPI_Write(byChannel,CP_IP00C772_B2_TPXNRCF3_ADDR,0x14);
	SPI_Write(byChannel,CP_IP00C772_B2_TPXNRCF4_ADDR,0x16);
	SPI_Write(byChannel,CP_IP00C772_B2_TPXNRCF5_ADDR,0x18);
	SPI_Write(byChannel,CP_IP00C772_B2_TPXNRCF6_ADDR,0x1a);
	SPI_Write(byChannel,CP_IP00C772_B2_TPXNRCF7_ADDR,0x1c);
	SPI_Write(byChannel,CP_IP00C772_B2_TPXNRCF8_ADDR,0x1f);
	SPI_Write(byChannel,CP_IP00C772_B2_HVPXNRCT_ADDR,0x00);
	SPI_Write(byChannel,CP_IP00C772_B2_VPXNRCF1_ADDR,0x00);
	SPI_Write(byChannel,CP_IP00C772_B2_VPXNRCF2_ADDR,0x00);
	SPI_Write(byChannel,CP_IP00C772_B2_HPXNRCF1_ADDR,0x00);
	SPI_Write(byChannel,CP_IP00C772_B2_HPXNRCF2_ADDR,0x0);
	SPI_Write(byChannel,CP_IP00C772_B2_MVNRCT_ADDR,0x1f);
	SPI_Write(byChannel,CP_IP00C772_B2_HMVNRCFA_ADDR,0x1);
	SPI_Write(byChannel,CP_IP00C772_B2_HMVNRCFB_ADDR,0x1);
	SPI_Write(byChannel,CP_IP00C772_B2_HMVNRCFC_ADDR,0x2);

	SPI_Write(byChannel,CP_IP00C772_B2_HMVNRCFD_ADDR,0x8);

	SPI_Write(byChannel,CP_IP00C772_B2_VFILCFA_ADDR,0x8);
	SPI_Write(byChannel,CP_IP00C772_B2_VFILCFB_ADDR,0x8);
	SPI_Write(byChannel,CP_IP00C772_B2_VFILCFC_ADDR,0x8);
	SPI_Write(byChannel,CP_IP00C772_B2_VFILCFD_ADDR,0x10);
	SPI_Write(byChannel,CP_IP00C772_B2_HFILCFA_ADDR,0x8);
	SPI_Write(byChannel,CP_IP00C772_B2_HFILCFB_ADDR,0x8);
	SPI_Write(byChannel,CP_IP00C772_B2_HFILCFC_ADDR,0x10);
	SPI_Write(byChannel,CP_IP00C772_B2_HFILCFD_ADDR,0x18);

	SPI_Write(byChannel,CP_IP00C772_B2_XVFILMD_ADDR,0x07);
	SPI_Write(byChannel,CP_IP00C772_B2_XNRCUT_ADDR,0x1);

	SPI_Write(byChannel,CP_IP00C772_B2_DIAGCT1_ADDR,0x37);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGCT2_ADDR,0xcf);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGCT3_ADDR,0xe6);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGTH0_ADDR,0x00);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGTH1_ADDR,0x09);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGTH2_ADDR,0x12);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGTH3_ADDR,0x03);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGTH4_ADDR,0x08);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGTH5_ADDR,0x05);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGTH6_ADDR,0x12);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGTH7_ADDR,0x04);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGTH8_ADDR,0x04);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGTH9_ADDR,0x04);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGTH10_ADDR,0x9);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGTH11_ADDR,0x10);
	SPI_Write(byChannel,CP_IP00C772_B2_DIAGTH12_ADDR,0x32);


}
