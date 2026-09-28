#include <LPC21XX.h>
#include "i2c.h"
#include "delay.h"

typedef unsigned char u8;
typedef unsigned short int u16;

void I2C_eeprom_ByteWrite(u8 slaveAddr,u16 BuffAddr,u8 data){
		I2C_Start();
		I2C_Write(slaveAddr<<1);
		I2C_Write(BuffAddr>>8);
		I2C_Write(BuffAddr);
		I2C_Write(data);
		I2C_Stop();
}

u8 I2C_eeprom_randomRead(u8 slaveAddr,u16 BuffAddr){
		u8 dat;
		I2C_Start();
		I2C_Write(slaveAddr<<1);
		I2C_Write(BuffAddr>>8);
		I2C_Write(BuffAddr);
		I2C_Restart();
		I2C_Write(slaveAddr<<1|1);
		dat=I2C_nack();
		I2C_Stop();
		return dat;
}

void i2c_eeprom_pagewrite(u8 slaveAddr,
	                        u16 wBufStartAddr,
                          s8 *p,
                          u8 nBytes) 
{ 
  u8 i; 
  I2C_Start();	 
  I2C_Write(slaveAddr<<1);
	I2C_Write(wBufStartAddr>>8);	
  I2C_Write(wBufStartAddr);   
  for(i=0;i<nBytes;i++) 
  { 
   I2C_Write(p[i]);              
  } 
  I2C_Stop(); 
    delay_ms(10); 
}


void i2c_eeprom_seqread(u8 slaveAddr,
	                      u16 rBufStartAddr,
                        s8 *p,
                        u8 nBytes) 
{ 
   u8 i; 
   I2C_Start();	 
   I2C_Write(slaveAddr<<1);
	I2C_Write(rBufStartAddr>>8);
   I2C_Write(rBufStartAddr); 
   I2C_Restart();	 
   I2C_Write(slaveAddr<<1|1);
   for(i=0;i<nBytes-1;i++) 
   { 
     p[i]=I2C_mack();	 
   }
   p[i]=I2C_nack(); 
   I2C_Stop(); 
} 
