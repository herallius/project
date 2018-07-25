#include <stdio.h>
#include "sensor.h"
#include "camera.h"
#include <unistd.h>
#include <time.h>

int main(void)
{
	sensorInit();
	sensorLaunchThread();
	cameraLaunchThread();

	while(1)
	{
		nanosleep((const struct timespec[]){{0, 500000000L}}, NULL);
	}

	sensorExitThread();
	cameraExitThread();

	return 0;
}