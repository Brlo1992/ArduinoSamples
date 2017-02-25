// Device.h

#ifndef _DEVICE_h
#define _DEVICE_h
#include "arduino.h"
#include <OneWire.h>
class DeviceService
{
	private:
		byte i;
		byte present;
		byte type_s;
		byte data[12];
		byte addr[8];
		int16_t raw;
		double celsius;
	public:
		DeviceService();
		~DeviceService();
		bool CheckDeviceIsFault(OneWire &oneWir);
		bool PrepareDevice(OneWire &oneWire);
		void ReadData(OneWire &oneWire); 
		void ConvertData();
		double GetConvertedData();
		String GetDeviceType();
	
};
#endif

