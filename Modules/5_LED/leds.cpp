#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    int time_high = 5000000;
    int time_low = 5000000;

    int LED = 0;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            time_high = 1000000 * atoi(argv[++i]);
        }
        if (strcmp(argv[i], "-l") == 0)
        {
            time_low = 1000000 * atoi(argv[++i]);
        }
        if (strcmp(argv[i], "-led") == 0)
        {
            LED = atoi(argv[++i]);
        }
    }

    FILE *LEDHandle = NULL;

    const char *LED0Trigger = "/sys/class/leds/beaglebone:green:usr0/trigger";
    const char *LED1Trigger = "/sys/class/leds/beaglebone:green:usr1/trigger";
    const char *LED2Trigger = "/sys/class/leds/beaglebone:green:usr2/trigger";
    const char *LED3Trigger = "/sys/class/leds/beaglebone:green:usr3/trigger";

    const char *LED0Brightness = "/sys/class/leds/beaglebone:green:usr0/brightness";
    const char *LED1Brightness = "/sys/class/leds/beaglebone:green:usr1/brightness";
    const char *LED2Brightness = "/sys/class/leds/beaglebone:green:usr2/brightness";
    const char *LED3Brightness = "/sys/class/leds/beaglebone:green:usr3/brightness";

    const char *LEDTrigger;
    const char *LEDBrightness;

    switch (LED)
    {
    case (0):
        LEDTrigger = LED0Trigger;
        LEDBrightness = LED0Brightness;
        break;
    case (1):
        LEDTrigger = LED1Trigger;
        LEDBrightness = LED1Brightness;
        break;
    case (2):
        LEDTrigger = LED2Trigger;
        LEDBrightness = LED2Brightness;
        break;
    case (3):
        LEDTrigger = LED3Trigger;
        LEDBrightness = LED3Brightness;
        break;
    }

    if ((LEDHandle = fopen(LEDTrigger, "r+")) != NULL)
    {
        fwrite("none", sizeof(char), 4, LEDHandle);
        fclose(LEDHandle);
    }

    cout << "LED: " << LEDTrigger << endl;
    cout << "LED: " << LEDBrightness << endl;
    cout << "LED Flash Start" << endl;
    for (int i = 0; i < 10; i++)
    {
        if ((LEDHandle = fopen(LEDBrightness, "r+")) != NULL)
        {
            fwrite("1", sizeof(char), 1, LEDHandle);
            fclose(LEDHandle);
        }
        usleep(time_high);
        if ((LEDHandle = fopen(LEDBrightness, "r+")) != NULL)
        {
            fwrite("0", sizeof(char), 1, LEDHandle);
            fclose(LEDHandle);
        }
        usleep(time_low);
    }
    cout << "LED Flash End" << endl;
}