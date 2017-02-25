#include "DeviceService.h"
#include <OneWire.h>

enum DeviceTypes
{
	DS18S20 = 0x10,
	DS18B20 = 0x28,
	DS18B22 = 0x22
};

struct TemperatureResult
{
	double Celsius;
	double Fahrenheir;
} temperatureResult;

DeviceService::DeviceService()
{
	present = 0;
}

DeviceService::~DeviceService()
{
}

bool DeviceService::CheckDeviceIsFault(OneWire &oneWire)
{
	return !oneWire.search(addr)? true : false;
}

bool DeviceService::PrepareDevice(OneWire & oneWire)
{

	oneWire.reset();
	oneWire.select(addr);
	oneWire.write(0x44, 1);
	delay(1000);    
	present = oneWire.reset();
	oneWire.select(addr);
	oneWire.write(0xBE);         
	return (bool) present;
}

void DeviceService::ReadData(OneWire & oneWire)
{
	for (i = 0; i < 9; i++) {           // we need 9 bytes
		data[i] = oneWire.read();
	}
	Serial.print(OneWire::crc8(data, 8), HEX);
}

void DeviceService::ConvertData()
{
	raw = (data[1] << 8) | data[0];
	if (type_s) {
		raw = raw << 3; 
		if (data[7] == 0x10) {
			raw = (raw & 0xFFF0) + 12 - data[6];
		}
	}
	else {
		byte cfg = (data[4] & 0x60);
		if (cfg == 0x00) raw = raw & ~7;  
		else if (cfg == 0x20) raw = raw & ~3; 
		else if (cfg == 0x40) raw = raw & ~1; 
	}
}

double DeviceService::GetConvertedData()
{
	celsius = (double)raw / 16.0;

	return celsius;
}

String DeviceService::GetDeviceType()
{
	String deviceType;
	switch (addr[0]) {
		case DS18S20:
			deviceType = DS18S20;
			type_s = 1;
			break;
		case DS18B20:
			deviceType = DS18B20;
			type_s = 0;
			break;
		case DS18B22:
			deviceType = DS18B22;
			type_s = 0;
			break;
		default:
			deviceType = "Device is not a DS18x20 family device.";
	}
	return deviceType;
}

