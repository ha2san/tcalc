#include <stdio.h>
#include "time.h"
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define SYNTAX_ERROR 1

int check_syntax(const char* string, size_t length)
{
    char array[] = {'d','h','m','s'};
    size_t max_length = sizeof(array)/sizeof(*array);
    size_t j = 0;
    int space = 0;
    int digit = 0;

    for (size_t i = 0; i < length; ++i) {
        if(isdigit(string[i])) {
            space = 0;
            digit = 0;
        } else if (isalpha(string[i])) {
            if(i==0)return SYNTAX_ERROR;
            if(digit) return SYNTAX_ERROR;
            while(string[i] != array[j]) {
                j++;
                if(j>=max_length) return SYNTAX_ERROR;
            }
            j++;
            space = 1;
            digit = 1;

        } else if (isspace(string[i])) {
            if(space); else return SYNTAX_ERROR;
        } else return SYNTAX_ERROR;
    }
    return 0;
}


struct time* string_to_timer(char* string, size_t length)
{
    int check = check_syntax(string,length);
    if(check) {
        printf("syntax error\n");
        return NULL;
    }

    struct time* time = calloc(1,sizeof(struct time));
    size_t value = 0;
    for (size_t i = 0; i < length; ++i) {
        if(isdigit(string[i])) {
            value = value * 10 + ((size_t) string[i] - '0');
        } else if(isspace(string[i])) {

        } else {
            switch (string[i]) {
                case 'd': time->days = value; break;
                case 'h': time->hours = value; break;
                case 'm': time->minutes = value; break;
                case 's': time->secondes = value; break;
            }
            value = 0;
        }
    }
    return time;
}

void adding(size_t* time, size_t* upper_time,size_t LIMIT)
{
    if(*time >= LIMIT) {
        size_t new_value = *time % LIMIT;
        size_t add_upper_value = *time / LIMIT;
        *time = new_value;
        *upper_time += add_upper_value;
    }
}


void arrange(struct time* timer)
{
    adding(&timer->secondes,&timer->minutes,SECOND);
    adding(&timer->minutes,&timer->hours,MINUTE);
    adding(&timer->hours,&timer->days,HOUR);
}

void print_helper(const char* str,const size_t* value)
{
    if(*value != 0) {
        printf("%zu %s",*value,str);
        if(*value > 1)
            printf("s ");
        else putchar(' ');
    }
}

void print(const struct time* const timer)
{
    print_helper("day",&timer->days);
    print_helper("hour",&timer->hours);
    print_helper("minute",&timer->minutes);
    print_helper("second",&timer->secondes);
    putchar('\n');
}

double to_seconds(const struct time* const timer)
{
    return (double)(60 * (timer->minutes + 60 * (timer->hours + 24 * timer->days))+ timer->secondes) ;
}

double to_minuts(const struct time* const timer)
{
    return to_seconds(timer) / (double) SECOND;
}

double to_hours(const struct time* const timer)
{
    return (to_minuts(timer) / (double)MINUTE);
}

double to_days(const struct time* const timer)
{
    return to_hours(timer)/ (double)HOUR;
}

void main_function()
{
    char* stime = readline("(time mode)>");
    struct time* time = string_to_timer((char*)stime,strlen(stime));
    if(time){
        arrange(time);
        print(time);
        printf("%lf days %lf hours %lf minutes %lf seconds\n",to_days(time),to_hours(time),to_minuts(time),to_seconds(time));
    }
    if(time) free(time);
    if(stime) free(stime);
}
