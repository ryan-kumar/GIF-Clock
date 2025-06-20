#include "clock.h"

void setTimeManually(int hours, int mins, int seconds, int month, int day, int year) {
  struct tm tm;
  tm.tm_year = year; 
  tm.tm_mon = month;         
  tm.tm_mday = day;
  tm.tm_hour = hours;
  tm.tm_min = mins;
  tm.tm_sec = seconds;
  time_t t = mktime(&tm);
  struct timeval now = { .tv_sec = t };
  settimeofday(&now, NULL);
}

String pad(int val) {
  return val < 10 ? "0" + String(val) : String(val);
}

String getTime() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);
  int hours = timeinfo->tm_hour % 12 == 0 ?  12 : (timeinfo->tm_hour % 12);
  String denotion = (timeinfo->tm_hour > 11) ? " PM" : " AM";
  return pad(hours) + ":" + pad(timeinfo->tm_min) + ":"  + pad(timeinfo->tm_sec) + denotion;
}

String getDate() {
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);
  return "(" + pad(timeinfo->tm_mon + 1) + "/" + pad(timeinfo->tm_mday + 1) + "/" + String(1900 + timeinfo->tm_year) + ")";
}

