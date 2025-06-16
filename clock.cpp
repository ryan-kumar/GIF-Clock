#include "clock.h"

void setTimeManually(int hours, int mins) {
  struct tm tm;
  tm.tm_year = 2025 - 1900; 
  tm.tm_mon = 5;         
  tm.tm_mday = 16;
  tm.tm_hour = hours;
  tm.tm_min = mins;
  tm.tm_sec = 0;
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
  return "(" + pad(timeinfo->tm_mon + 1) + "/" + pad(timeinfo->tm_mday) + "/" + String(1900 + timeinfo->tm_year) + ")";
}

