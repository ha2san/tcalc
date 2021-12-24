#pragma once
#include <stdio.h>
#include <stdlib.h>

struct time {
    size_t secondes;
    size_t minutes;
    size_t hours;
    size_t days;
};

#define SECOND 60
#define MINUTE 60
#define HOUR 24

enum time_unit {day,hour,minut,second};

struct time* string_to_timer(char*,size_t);

void adding(size_t* time, size_t* upper_time,size_t LIMIT);

void arrange(struct time* timer);

void print(const struct time* timer);

double conversion(const struct time* timer,enum time_unit unit);

double to_seconds(const struct time* timer);

double to_minuts(const struct time* timer);

double to_hours(const struct time* timer);

double to_days(const struct time* timer);

