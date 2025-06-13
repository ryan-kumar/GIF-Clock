#ifndef CLOCK_H
#define CLOCK_H

#include <time.h>
#include <sys/time.h>
#include <Arduino.h>


void setTimeManually(int hours, int mins);
String pad(int val);
String getTime();
String getDate();


#endif