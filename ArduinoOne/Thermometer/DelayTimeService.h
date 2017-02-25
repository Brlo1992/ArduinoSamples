// DelayTimeService.h

#ifndef _DELAYTIMESERVICE_h
#define _DELAYTIMESERVICE_h
#include "arduino.h"
class DelayTimeService
{
public:
	DelayTimeService();
	~DelayTimeService();
	void OneSecondDelay();
	void CustomDelay(int time);
};

#endif

