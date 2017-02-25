#include "DelayTimeService.h"
enum DelayTime
{
	HalfSecond = 500,
	OneSecond = 1000,
	TwoSeconds = 2000
};
DelayTimeService::DelayTimeService()
{
}

DelayTimeService::~DelayTimeService()
{
}
void DelayTimeService::OneSecondDelay()
{
	delay(OneSecond);
}

void DelayTimeService::CustomDelay(int time)
{
	delay(time);
}
