#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <stdbool.h>

void sensorInit(void);
void sensorLaunchThread(void);
void sensorExitThread(void);
void sensorSetValue(_Bool i);
_Bool sensorGetValue(void);

#endif