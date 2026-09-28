## TITTLE : Secure GSM-Based Thermal Monitoring and Set-Point Control System

## Overview
This project is a Secure GSM-Based Thermal Monitoring and Set-Point Control System developed using the LPC2148 ARM7 Microcontroller. It continuously monitors temperature and humidity using the DHT11 sensor, displays real-time readings on a 16x2 LCD, stores configuration settings securely in AT24C256 EEPROM, and sends SMS alerts through the M660A GSM module whenever abnormal temperature conditions occur.
The system includes password-protected remote access through SMS commands, allowing authorized users to change the temperature set point, update the registered mobile number, and request current sensor information. The RTC (Real-Time Clock) provides accurate timestamps for all alert messages, making the system suitable for industrial safety and remote environmental monitoring applications.
## Features
Real-time temperature monitoring using DHT11 sensor.
Humidity monitoring using DHT11 sensor.
16x2 LCD display for live sensor readings and system status.
GSM (M660A) module for SMS alerts and remote monitoring.
Password-protected SMS commands for secure remote access.
EEPROM (AT24C256) stores temperature set point, password, and mobile number.
RTC provides date and time for SMS alerts.
Keypad-based local configuration of set point and password.
LED/Buzzer alert when temperature exceeds the predefined limit.
Continuous monitoring and automatic fault notification.

 ## 📊 Project Block Diagram
 
![Project Block Diagram](Screenshot%202026-09-28%20083319.png)

## Hardware Components Used

LPC2148 ARM7 Microcontroller

DHT11 Temperature & Humidity Sensor

GSM Module (M660A)

AT24C256 EEPROM (I2C)

16x2 LCD Display

4x4 Matrix Keypad

LED Indicators

Buzzer

Power Supply (3.3V / 5V)

USB-UART Converter / DB9 Cable

## Software Used

Keil µVision IDE

Flash Magic

Embedded C Programming

## Working of the Project

## Step 1: System Initialization

When power is supplied to the LPC2148 microcontroller, it initializes all the required peripherals and hardware modules.

LCD is initialized to display sensor values and system messages.

UART is initialized for communication with the GSM module.

I2C interface is initialized for EEPROM communication.

RTC is initialized to maintain current date and time.

Keypad interface is initialized for password entry.

DHT11 sensor is initialized for temperature and humidity measurement.

After successful initialization, the LCD displays that the system is ready for monitoring.

## Step 2: Temperature and Humidity Measurement Using DHT11

The DHT11 sensor continuously senses the surrounding temperature and humidity.

LPC2148 reads temperature data from DHT11.

LPC2148 reads humidity data from DHT11.

The values are updated continuously on the LCD display.

## Step 3: Real-Time Clock (RTC) Operation

The RTC maintains the current date and time.

RTC provides accurate timestamps.

Every alert message includes date and time information.

Timestamp helps in monitoring historical fault events.

## Step 4: LCD Display

The 16×2 LCD displays real-time system information.

The LCD shows:

Current Temperature.

Current Humidity.

Date and Time.

System Status.

Alert Messages.

Password/Menu Options.

This allows users to monitor the system without a computer.

## Step 5: Temperature Set Point and EEPROM Storage

A temperature set point is permanently stored in AT24C256 EEPROM.

LPC2148 reads the stored set point during startup.

User can modify the set point through the keypad.

Updated value is written into EEPROM using I2C.

EEPROM retains data even after power OFF.

The EEPROM also stores:

Temperature Set Point.

Authorized Mobile Number.

Security Password.

## Step 6: Threshold Comparison and Alarm Generation

LPC2148 continuously compares the measured temperature with the stored set point.

Condition: Temperature exceeds the predefined set point.

If the condition becomes TRUE:

Buzzer turns ON.

Red LED turns ON.

Warning message is displayed on LCD.

SMS alert is prepared with timestamp.

If temperature is within the limit:

LED remains OFF.

Buzzer remains OFF.

Monitoring continues continuously.

## Step 7: GSM Communication

The GSM module communicates with LPC2148 using UART AT commands.

Communication sequence:

AT
ATE0
AT+CMGF=1
AT+CNMI=2,1,0,0,0
AT+CMGS="Mobile Number"

Functions performed by GSM:

Send alert SMS.

Receive password-protected SMS commands.

Delete processed SMS.

Send current sensor information on request.

## Step 8: Secure SMS-Based Remote Control

Authorized users can control the system remotely using SMS.

SMS Command Format

SMS Command	

Function

0786T38$	

Update temperature set point to 38°C

0786M9876543210$
Update authorized mobile number

0786I$

Request current sensor information

Security Features

Only registered mobile number is allowed.

4-digit password authentication.

Invalid syntax messages are ignored.

Unauthorized mobile numbers cannot modify settings.

## Step 9: Local Password-Protected Configuration

Users can also configure the system locally using the keypad.

Menu options:

Temperature Set Point Change.

Password Change.

Process:

Enter current password.

Verify password.

Enter new set point or password.

Save data into EEPROM.

If password is incorrect:

Red LED/Buzzer turns ON.

Three consecutive wrong attempts temporarily block the system.

## Step 10: SMS Alert Generation

Whenever temperature exceeds the configured limit:

The system sends an SMS containing:

Alert Message.

Current Temperature.

Current Humidity.

Date.

Time.

Example SMS:

ALERT!
Temperature High: 39°C
Humidity: 65%
Date: 25/09/2026
Time: 10:45 AM
Step 11: Continuous Monitoring Loop

The complete system works continuously in a loop.

Read Temperature.

Read Humidity.

Read RTC Time.

Display Values on LCD.

Read Set Point from EEPROM.

Compare Temperature with Set Point.

Turn ON LED/Buzzer if Temperature exceeds limit.

Send SMS Alert through GSM.

Check Incoming SMS Commands.

Update EEPROM if authorized changes are received.

Repeat the monitoring process continuously.

## Project Flow

Initialize LCD.

Initialize UART.

Initialize I2C.

Initialize RTC.

Initialize EEPROM.

Initialize DHT11.

Initialize Keypad.

Read Temperature.

Read Humidity.

Display Values on LCD.

Read Set Point from EEPROM.

Compare Temperature with Set Point.

If Temperature High:

Turn ON LED/Buzzer.

Send SMS Alert.

Check Incoming SMS.

Update EEPROM if authorized.

Repeat Monitoring.

## Project Structure

├── main.c
├── lcd.c
├── lcd.h
├── delay.c
├── delay.h
├── keypad.c
├── keypad.h
├── uart.c
├── uart.h
├── i2c.c
├── i2c.h
├── eeprom.c
├── eeprom.h
├── dht11.c
├── dht11.h
├── gsm.c
├── gsm.h
├── rtc.c
├── rtc.h

## Project Output

The system provides the following outputs:

Real-time Temperature Monitoring.

Real-time Humidity Monitoring.

LCD Display with Sensor Readings.

RTC Date and Time Display.

EEPROM-based Permanent Configuration Storage.

Password-Protected Local Configuration.

GSM SMS Alert Generation.

Remote Temperature Set Point Update.

Remote Mobile Number Update.

Current Sensor Information through SMS.

GSM Integration

The GSM module communicates with LPC2148 using UART AT commands.

SMS Functions

Send Temperature Alert SMS.

Receive Secure SMS Commands.

Update EEPROM Configuration.

Send Current Sensor Status.

Delete Processed Messages.

Hardware Connections and Output

## Hardware Output

![LCD Output](Images/Output_LCD.jpg)

## Applications

Industrial Temperature Monitoring.

Industrial Safety Systems.

Remote Environmental Monitoring.

Laboratory Temperature Monitoring.

Warehouse Monitoring.

Cold Storage Monitoring.

Server Room Monitoring.

Medical Equipment Monitoring.

Smart Monitoring Systems.

## Advantages

Real-time temperature and humidity monitoring.

Instant SMS alerts during abnormal conditions.

Password-protected secure remote access.

EEPROM stores configuration permanently.

RTC provides accurate timestamps.

Easy local configuration using keypad.

Low-cost embedded monitoring solution.

Suitable for industrial and remote applications.

## Disadvantages

GSM network is required for SMS communication.

DHT11 provides limited sensing accuracy.

SMS communication may have network delay.

Supports only limited environmental parameters.

Requires authorized mobile number configuration.

## Future Improvements

Cloud integration using ESP8266/ESP32.

ThingSpeak or MQTT dashboard support.

Android mobile application for monitoring.

Email and Push Notifications.

SD Card data logging.

Multiple temperature sensor support.

High accuracy DHT22/DS18B20 sensor integration.

Web dashboard with historical graphs.

Relay control for automatic cooling/heating devices.

## Author

**G.Prathyusha** 

Embedded Systems Project using LPC2148 ARM7 Microcontroller
Secure GSM-Based Thermal Monitoring and Set-Point Control System.
