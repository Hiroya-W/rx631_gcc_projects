/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
//#include "typedefine.h"
#include "iodefine.h"
#include <sci.h>
#include <spi.h>

#ifdef __cplusplus
//#include <ios>                        // Remove the comment when you use ios
//_SINT ios_base::Init::init_cnt;       // Remove the comment when you use ios
#endif

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void)
{
	/*****************************************************************************************
	�N���b�N�ݒ�
		
	*****************************************************************************************/
	SYSTEM.PRCR.WORD = 0xa50b;		//�N���b�N�\�[�X�I���̕ی�̉���

	SYSTEM.PLLCR.WORD = 0x0F00;		/* PLL ���{�~16 ����1���� (12.000MHz * 16 = 192MHz)*/
	SYSTEM.PLLCR2.BYTE = 0x00;		/* PLL ENABLE */
	
	SYSTEM.PLLWTCR.BYTE     = 0x0F;		/* 4194304cycle(Default) */
	
	
	// ICK   : 192/2 = 96MHz 		// �V�X�e���N���b�N CPU DMAC DTC ROM RAM
	// PCLKA : 192/2 = 96MHz 		// ���Ӄ��W���[���N���b�NA ETHERC�AEDMAC�ADEU
	// PCLKB : 192/4 = 48MHz 		// ���Ӄ��W���[���N���b�NB ��L�ȊO PCLKB=PCLK
/*	
	SYSTEM.SCKCR.BIT.FCK=0x02;		//FCLK MAX 50MHz  192/4
	SYSTEM.SCKCR.BIT.ICK=0x01;		//ICLK MAX 100MHz 192/2
	SYSTEM.SCKCR.BIT.PSTOP1=0x01;		//BCLK �o�͒�~
	SYSTEM.SCKCR.BIT.PSTOP0=0x01;		//SDCLK �o�͒�~
	SYSTEM.SCKCR.BIT.BCK=0x02;		//BCLK MAX 100MHz ICLK�ȉ��ɂ���K�v������192/4
	SYSTEM.SCKCR.BIT.PCKA=0x01;		//PCLKA MAX 100MHz 192/2
	SYSTEM.SCKCR.BIT.PCKB=0x02;		//PCLKB MAX 50MHz 192/4
	//��L�̐ݒ�ł͐�����clock�ݒ肪�ł��Ȃ����߉��L�̂悤�Ɉꊇ�Őݒ肷�邱��
*/
	SYSTEM.SCKCR.LONG = 0x21C21211;		//FCK1/4 ICK1/2 BCLK��~ SDCLK��~ BCK1/4 PCLKA1/2 PCLKB1/4
/*
	SYSTEM.SCKCR2.BIT.UCK=0x03;		//UCLK MAX 48MHz 192/4
	SYSTEM.SCKCR2.BIT.IEBCK=0x02;		//IECLK MAX 50MHz 192/4
*/
	SYSTEM.SCKCR2.WORD = 0x0032;		/* UCLK1/4 IEBCK1/4 */
	SYSTEM.BCKCR.BYTE = 0x01;		/* BCLK = 1/2 */
	
	SYSTEM.SCKCR3.WORD = 0x0400;		//PLL��H�I��


	/*****************************************************************************************
	I/O�ݒ�
		LED�̐ݒ�	
	*****************************************************************************************/

	//sci�̃C�j�V�����C�Y
	init_sci();	
	//��ʃN���A�V�[�P���X
	SCI_printf("\x1b[2J");				//�N���A�X�N���[��[CLS]
	SCI_printf("\x1b[0;0H");			//�J�[�\����0,0�Ɉړ�
	
	//spi�̃C�j�V�����C�Y
	init_spi_gyro();

	unsigned long i = 0;
	long data = 0;
	for(i = 0; i < 100*1000*10; i++);
	preprocess_spi_gyro(0x062100);
	data = read_gyro_data();
	for(i = 0; i < 100*1000*10; i++);
	
	while(1){
		SCI_printf("data_H,%d\n\r",(data & 0x00FF00) >> 8);
		SCI_printf("data_L,%d\n\r\n\r",(data & 0x0000FF));	

		SCI_printf("Ang_Velocity[deg/s],%d\n\r",((int)((2000.0*((float)data))/32767.0)));
		
		for(i = 0; i < 100*1000*10; i++);
		for(i = 0; i < 100*1000*100; i++);
		//��ʃN���A�V�[�P���X
		SCI_printf("\x1b[2J");				//�N���A�X�N���[��[CLS]
		SCI_printf("\x1b[0;0H");			//�J�[�\����0,0�Ɉړ�
		preprocess_spi_gyro(0xB70000);
		data = (short)(read_gyro_data()&0x0000FFFF);
	}
	

}

#ifdef __cplusplus
void abort(void)
{

}
#endif
