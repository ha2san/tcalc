#pragma once
#include <stdio.h>
#include <stdlib.h>

struct time {
    double secondes;
    double minutes;
    double hours;
    double days;
};

#define SECOND 60
#define MINUTE 60
#define HOUR 24

enum time_unit {day,hour,minut,second};

struct time* string_to_timer(char*,size_t);

void adding(double* time, double* upper_time,double* down_limit,double LIMIT,double);

void arrange(struct time* timer);

void main_function(void);

void print(const struct time* timer);

double conversion(const struct time* timer,enum time_unit unit);

double to_seconds(const struct time* timer);

double to_minuts(const struct time* timer);

double to_hours(const struct time* timer);

double to_days(const struct time* timer);

