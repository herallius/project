#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "sensor.h"

#define GPIO_EXPORT_FILE_NAME "/sys/class/gpio/export"

#define SENSOR_DIRECTION_FILE_NAME "/sys/class/gpio/gpio49/direction"

#define SENSOR_VALUE_FILE_NAME "/sys/class/gpio/gpio49/value"

#define SENSOR_GPIO_NUMBER 49

#define BUFFER_MAX_SIZE 5

static void *sensorReadValue(void *arg);
static void readFromFile(char *fileName, char *buffer, int bufferSize);

static pthread_t thread_id;
static pthread_mutex_t sensor_mutex = PTHREAD_MUTEX_INITIALIZER;
static _Bool sensor_stop = false;
static _Bool sensor_motionDected = false;


void sensorLaunchThread(void)
{
	pthread_create(&thread_id, NULL, &sensorReadValue, NULL);
}

void sensorExitThread(void)
{
	sensor_stop = true;
	pthread_join(thread_id,NULL);
}

void sensorInit(void)
{
//	printf("Exporting GPIO %d...\n", gpioNumber);
	FILE *pExportFile = fopen(GPIO_EXPORT_FILE_NAME, "w");
	if (pExportFile == NULL) {
		printf("ERROR: Unable to open export file.\n");
	}
	fprintf(pExportFile, "%d", SENSOR_GPIO_NUMBER);
	fclose(pExportFile);

	FILE *pWriteFile = fopen(SENSOR_DIRECTION_FILE_NAME, "w");
	if (pWriteFile == NULL) {
		printf("ERROR OPENING %s FOR WRITE.\n", SENSOR_DIRECTION_FILE_NAME);
	}

	int charWritten = fprintf(pWriteFile, "%s", "in");
	if (charWritten <= 0) {
		printf("ERROR WRITING DATA TO %s.\n", SENSOR_DIRECTION_FILE_NAME);
	}

	fclose(pWriteFile);
}



void sensorSetValue(_Bool i)
{
	sensor_motionDected = i;
}

_Bool sensorGetValue(void)
{
	return sensor_motionDected;
}

static void *sensorReadValue(void *arg)
{
	char buffer[BUFFER_MAX_SIZE];
	while (!sensor_stop) {
		readFromFile(SENSOR_VALUE_FILE_NAME, buffer, BUFFER_MAX_SIZE);
		if (strncmp(buffer, "1", 1) == 0) {
			printf("Motioin detected!\n");
			pthread_mutex_lock(&sensor_mutex);
		    sensorSetValue(true);
		    pthread_mutex_unlock(&sensor_mutex);
			//nanosleep((const struct timespec[]){{0, 500000000L}}, NULL);
			sleep(5);
		}
	}
	return NULL;
}

static void readFromFile(char *fileName, char *buffer, int bufferSize)
{
	FILE *pReadFile = fopen(fileName, "r");
	if (pReadFile == NULL) {
		printf("ERROR OPENING %s FOR READ.\n", fileName);
	}

	fgets(buffer, bufferSize, pReadFile);

	fclose(pReadFile);
}