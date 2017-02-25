/*
 Name:		Thermometer.ino
 Created:	2/24/2017 10:22:04 PM
 Author:	Barlo
*/
#include "DelayTimeService.h"
#include "MessageService.h"
#include "DeviceService.h"
#include "DelayTimeService.h"
#include <OneWire.h>

MessageService messageService;
DeviceService deviceService;
DelayTimeService delayTimeService;
OneWire oneWire(10);

void setup() {
	deviceService = DeviceService();
	messageService = MessageService();
	delayTimeService = DelayTimeService();
	Serial.begin(9600);
	messageService.DisplayMessage("Turn on device ..", false);
}

void loop() {
	CheckAddress();
	CheckDeviceType();
	CheckDeviceIsReady();
	ReadDataFromDevice();
	ConvertDataFromDevice();
	GetDataFromDevice();
	DefaultDelay();
}

void exit(bool everthingOk){
	if (everthingOk == false)
	{
		messageService.DisplayMessage("Shutting down device ..");
		return;
	}
}

void CheckAddress() {
	if (deviceService.CheckDeviceIsFault(oneWire))
	{
		oneWire.reset_search();
		messageService.DisplaySearchAddressFailedMessage();
		exit(false);
	}
	else
	{
		messageService.DisplaySearchAddressSucceedMessage();
	}
	delayTimeService.OneSecondDelay();
}

void CheckDeviceType() {
	String deviceType = deviceService.GetDeviceType();
	messageService.DisplayDeviceTypeMessage(deviceType);
}

void CheckDeviceIsReady() {
	bool devicePrepared = deviceService.PrepareDevice(oneWire);
	exit(devicePrepared);
}

void ReadDataFromDevice() {
	deviceService.ReadData(oneWire);
}

void ConvertDataFromDevice() {
	deviceService.ConvertData();
}

void GetDataFromDevice() {
	double temp = deviceService.GetConvertedData();
	messageService.DisplayTemperature(temp);
}

void DefaultDelay() {
	delayTimeService.CustomDelay(500);
}
