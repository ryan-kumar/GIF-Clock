#ifndef CLOCK_H
#define CLOCK_H

#include <time.h>
#include <sys/time.h>
#include <Arduino.h>


void setTimeManually(int hours, int mins, int seconds, int month, int day, int year);
String pad(int val);
String getTime();
String getDate();


#endif