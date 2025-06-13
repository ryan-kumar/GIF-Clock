#ifndef CLOCK_H
#define CLOCK_H

#include <time.h>
#include <sys/time.h>
#include <Arduino.h>


void setTimeManually();
String pad(int val);
String getTime();


#endif