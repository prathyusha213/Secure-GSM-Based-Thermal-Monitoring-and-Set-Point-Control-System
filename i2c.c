#include <LPC21xx.h>
#include "i2c_defines.h"

void Init_I2C(void){
		PINSEL0|=((SCL_PIN)|(SDA_PIN));
		I2SCLL=I2C_DIVIDER;
		I2SCLH=I2C_DIVIDER;
		I2CONSET=1<<I2EN_BIT;
}

void I2C_Start(void){
		I2CONSET=1<<STA_BIT;
		while(((I2CONSET>>SI_BIT)&1)==0);
		I2CONCLR=1<<STAC_BIT;
}

void I2C_Restart(void){
		I2CONSET=1<<STA_BIT;
		I2CONCLR=1<<SIC_BIT;
		while(((I2CONSET>>SI_BIT)&1)==0);
		I2CONCLR=1<<STAC_BIT;
}

void I2C_Stop(void){
		I2CONSET=1<<STO_BIT;
		I2CONCLR=1<<SIC_BIT;
}

void I2C_Write(unsigned char data){
		I2DAT=data;
		I2CONCLR=1<<SIC_BIT;
		while(((I2CONSET>>SI_BIT)&1)==0);
}

unsigned char I2C_nack(void){
		I2CONCLR=1<<SIC_BIT;
		while(((I2CONSET>>SI_BIT)&1)==0);
		return I2DAT;
}

unsigned char I2C_mack(void){
		I2CONSET=1<<AA_BIT;
		I2CONCLR=1<<SIC_BIT;
		while(((I2CONSET>>SI_BIT)&1)==0);
		I2CONCLR=1<<AAC_BIT;
		return I2DAT;
}


