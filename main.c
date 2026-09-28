#include <LPC21xx.h>				                                                                        
#include <string.h>
#include "rtc.h"
#include "lcd.h"
#include "keypad_defines.h"
#include "delay.h"
#include "menu.h"
#include "i2c.h"
#include "i2c_eeprom.h"
#include "i2c_eeprom_defines.h"
#include "dht11.h"
#include "uart.h"

int pwd;
char pass[5]="1234";
int p;
char lastTemp = 0;
char tempSPoint=37,newtempSPoint;
char humiditySPoint=70;
char mobile_number[15] = "9392608638",new_mobile_number[15];

void gsm_init(void);
void Enable_EINT0(void);
void itoa(int,char *,int);
unsigned char humidity_integer, humidity_decimal, temp_integer, temp_decimal, checksum;

int myatoi(const char *str) {
    int i=0;
    int num=0;
    int sign=1;
    if(str[i]=='-'){
        sign=-1;
        i++;
    }else if(str[i]=='+'){
        i++;
    }
    while(str[i]>='0'&&str[i]<='9'){
        num=num*10+(str[i]-'0');
        i++;
    }
    return sign * num;
}

int verifyPWD(void){
	cmdLCD(0x01);
	cmdLCD(0x80);
	stringLCD("PASSWORD: ");
	cmdLCD(0xC0);
	pwd=readnum();
	i2c_eeprom_seqread(I2C_EEPROM_SA1,0x00,pass,4);
	delay_ms(10);
	pass[4]='\0';
	p=myatoi(pass);
	return (pwd==p);
}

int main(){
	delay_s(10);
	init_LCD();
	init_RTC();
	KeyPdInit();
	Init_I2C();
	InitUART0();
	delay_s(5);
	gsm_init();
	IODIR0|=1<<17;
	IODIR0|=1<<18;
	Enable_EINT0();
	set_RTC_Time(10,20,0);
	set_RTC_Date(12,02,2026);
	i2c_eeprom_pagewrite(I2C_EEPROM_SA1,0x00,pass,4);
	delay_ms(10);
	I2C_eeprom_ByteWrite(I2C_EEPROM_SA1,0x20,tempSPoint);
	delay_ms(10);
	I2C_eeprom_ByteWrite(I2C_EEPROM_SA1,0x30,humiditySPoint);
	delay_ms(10);
	i2c_eeprom_pagewrite(I2C_EEPROM_SA1,0x40,mobile_number,10);
	delay_ms(10);
	while(1){
		handle_uart_sms();
		display_RTC_Time_On_LCD(HOUR,MIN,SEC);
		display_RTC_Date_On_LCD(DOM,MONTH,YEAR);
		display_Temp_Hum();
		dht11_request();
		dht11_response();
		humidity_integer = dht11_data();
		humidity_decimal = dht11_data();
		temp_integer = dht11_data();
		temp_decimal = dht11_data();
		checksum = dht11_data();
		if( (humidity_integer + humidity_decimal + temp_integer + temp_decimal) != checksum ){
			cmdLCD(0x01);
			stringLCD("Checksum Error");
			delay_s(1);
			continue;
		}
		cmdLCD(0x89);
		stringLCD("H:");
		integerLCD(humidity_integer);
		charLCD('.');
		integerLCD(humidity_decimal);
		stringLCD("%RH");
		cmdLCD(0xC9);
		stringLCD("T:");
		integerLCD(temp_integer);
		charLCD('.');
		integerLCD(temp_decimal);
		charLCD(223);
		stringLCD("C");
		delay_ms(900);
		if(temp_integer>tempSPoint){
			if(temp_integer>lastTemp){
				IOCLR0=1<<18;
				UART0_Str("AT+CMGF=1\r\n");
				delay_ms(1000);

				UART0_Str("AT+CMGS=\"");
				UART0_Str(mobile_number);
				UART0_Str("\"\r\n");
				delay_ms(1000);

				UART0_Str("ALERT: TEMP HIGH TEMP: ");
				UART0_Int(temp_integer);
				UART0_Tx(' ');
				UART0_Tx('C');
				UART0_Tx('\n');
				UART0_Str("TIME: ");
				UART0_Tx((HOUR/10)+48);
				UART0_Tx((HOUR%10)+48);
				UART0_Tx(':');
				UART0_Tx((MIN/10)+48);
				UART0_Tx((MIN%10)+48);
				UART0_Tx(':');
				UART0_Tx((SEC/10)+48);
				UART0_Tx((SEC%10)+48);
				UART0_Tx('\t');
				UART0_Str("Date: ");
				UART0_Tx((DOM/10)+48);
				UART0_Tx((DOM%10)+48);
				UART0_Tx('/');
				UART0_Tx((MONTH/10)+48);
				UART0_Tx((MONTH%10)+48);
				UART0_Tx('/');
				UART0_Int(YEAR%100);

				UART0_Tx(0x1A);
				delay_s(3);
				UART0_Str("\r\n");
				UART0_Str("AT+CMGD=1\r\n");
				lastTemp = temp_integer;
			}
		}else{
			lastTemp = 0;
			IOSET0=1<<18;
			delay_ms(200);
		}
		if(humidity_integer>humiditySPoint){
			IOCLR0=1<<17;
			delay_ms(200);
		}else{
		 	IOSET0=1<<17;
			delay_ms(200);
		}
	}
}
