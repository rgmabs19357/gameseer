/*****************************************************

	Macro Define
	
******************************************************/
/* Macro define for the SPI  */
#define DEV_SPI_FLASH_CHANNEL	0x7   /* 0111'b */
#define DEV_SPI_C753_CHANNEL 	0x6   /* 0110'b */
#define DEV_SPI_C722_CHANNEL	0x0	  /* 0000'b */
#define DEV_SPI_FPGA_CHANNEL    0x8   /* 1000'b */





/***********************************************

	��������: SPI �ӿڳ�ʼ������ϵͳʹ��GPIO����SPI
				   ʱ��ģ��
	��������:
		��
	��������ֵ:
		��
************************************************/
void dev_SpiInit(void);


/*********************************************** 
	��������: SPI д�����ӿ�
	��������:
		chn:		SPI ͨ��
		addr: 	SPI �豸�Ĵ�����ַ
		value:	SPI д��Ĵ�����ֵ
	��������ֵ:
		��
	
************************************************/
void dev_SPI_Write(uint32_t chn,uint8_t addr,uint8_t value);


/***********************************************

	��������: SPI ���ӿ�
	��������:
		chn:		SPI ͨ��
		addr:	SPI �豸�Ĵ�����ַ
		value:	SPI �Ĵ���ֵ
	��������ֵ:
		��
************************************************/
void dev_SPI_Read(uint32_t chn,uint8_t addr,uint8_t *value);


/***********************************************

	��������: FPGA  д �ӿ�(ͨ��SPI ����)
	��������:
		chn:		SPI ͨ�� (FPGA��дҲ�Ǿ���SPI ����ͨ���Ź̶�)
		addr:	FPGA �豸�Ĵ�����ַ
		value:	FPGA �Ĵ���ֵ
	��������ֵ:
		��
************************************************/
void dev_FPGA_Write(uint32_t chn,uint16_t addr,uint16_t value);


/***********************************************

	��������: FPGA ���ӿ�
	��������:
		chn:		SPI ͨ��(FPGA��дҲ�Ǿ���SPI ����ͨ���Ź̶�)
		addr:	FPGA �豸�Ĵ�����ַ
		value:	FPGA �Ĵ���ֵ
	��������ֵ:
		��
************************************************/
void dev_FPGA_Read(uint32_t chn,uint16_t addr,uint16_t *value);


/***************************************************************

	��������: 	I2C ��ʼ���� ��ϵͳʹ��GPIO ģ��I2C ʱ��
	
	��������:
		��
	��������ֵ:
		��

***************************************************************/
void dev_I2cInit(void);



/******************************************************

	��������: 	I2C �豸д��������
	��������: 	
		chn:	
				I2C ͨ����, ϵͳʹ����·I2C ͨ��0 Ϊ���ذ�
				ͨ��1 ΪԶ��

		chipType:
				I2C �豸��ַ��I2CΪ�������ߣ�ÿһ��������
				���豸���ж�Ӧ�ĵ�ַ
		addr:
				��Ҫ���ʵļĴ���ƫ��
		value:
				д��Ĵ�����ֵ
	��������ֵ
		��


*******************************************************/
void dev_I2C_Write(uint32_t chn,uint32_t chipType,uint8_t addr,uint8_t value);


/*************************************************************

	��������:	I2C �豸����������
	��������:    
		chn:
				I2C ͨ���ţ�ϵͳ ʹ������ͨ��, ͨ��1Ϊ���ذ�
				ͨ����ͨ��1ΪԶ�˷���ͨ��
		chipType:
				I2C �豸��ַ��I2CΪ����ʽ���ߣ�ÿһ�������ϵ�
				�豸���ж�Ӧ�ĵ�ַ
		addr:
				I2C�豸�ļĴ���ƫ�Ƶ�ַ
		value:
				��ȡ�Ĵ�����ֵ
	��������ֵ:
		��

**************************************************************/
void dev_I2C_Read(uint32_t chn,uint32_t chipType,uint8_t addr,uint8_t *value);



