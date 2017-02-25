#include "MessageService.h"

MessageService::MessageService()
{
}

MessageService::~MessageService()
{
}

void MessageService::DisplayMessage(String message, bool defaultDisable = true)
{
	if (defaultDisable == false)
	{
		Serial.println(message);
	}
}

void MessageService::DisplaySearchAddressFailedMessage()
{
	DisplayMessage("No more addresses");
}

void MessageService::DisplaySearchAddressSucceedMessage()
{
	DisplayMessage("Everything ok");
}

void MessageService::DisplayDeviceTypeMessage(String device)
{
	DisplayMessage("Chip: " + device);
}

void MessageService::DisplayTemperature(double temperature)
{
	DisplayMessage("\r\nTemperature: " + (String) temperature, false);
}
