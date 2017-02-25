// MessageService.h

#ifndef _MESSAGESERVICE_h
#define _MESSAGESERVICE_h
#include "arduino.h"
class MessageService
{
	public:
		MessageService();
		~MessageService();
		void DisplayMessage(String message, bool defaultDisable = true);
		void DisplaySearchAddressFailedMessage();
		void DisplaySearchAddressSucceedMessage();
		void DisplayDeviceTypeMessage(String device);
		void DisplayTemperature(double temperature);
};

#endif

