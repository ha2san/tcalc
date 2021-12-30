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
    int point = 1;
    int afterPoint = 10;

    for (size_t i = 0; i < length; ++i) {
        if(!isdigit(string[i])) point = 1;
        if(isdigit(string[i])) {
            space = 0;
            digit = 0;
            afterPoint = 0;
            
        }else if(string[i] == '.'){
            if(!point) return SYNTAX_ERROR;
            afterPoint = 1;
            point = 0;
        }else if (isalpha(string[i])) {
            if(i==0)return SYNTAX_ERROR;
            if(afterPoint) return SYNTAX_ERROR;
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
    double value = 0;
    int afterPoint = 0;
    int afterPointDecimal = 10;
    for (size_t i = 0; i < length; ++i) {
        if(isdigit(string[i])) {
            if(!afterPoint) value = value * 10 + (string[i] - '0');
            else {
                double add = ((double) (string[i] - '0'))/ afterPointDecimal;
                value += add;
                afterPointDecimal *= 10;
            }
        }else if (string[i] == '.'){
            afterPoint=1;
        } else if(isspace(string[i])) {

        } else {
            afterPoint = 0;
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

void adding(double* time, double* upper_time,double* down_time,double limit,double down_limit)
{
    double decimal = *time - (int)*time;
    if(down_time && decimal > 0){
        *down_time += decimal * down_limit;
        *time -= decimal;
    }

    while(upper_time && *time >= limit)
    {
        *time -= limit;
        *upper_time += 1;
    }
}


void arrange(struct time* timer)
{
    adding(&timer->secondes,&timer->minutes,NULL,SECOND,0);
    adding(&timer->minutes,&timer->hours,&timer->secondes,MINUTE,SECOND);
    adding(&timer->hours,&timer->days,&timer->minutes,HOUR,MINUTE);
    adding(&timer->days,NULL,&timer->hours,-1,HOUR);
}

void print_helper(const char* str,const double* value)
{
    if(*value != 0) {
        printf("%g %s",*value,str);
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
        arrange(time);
        print(time);
        printf("%lf days %lf hours %lf minutes %lf seconds\n",to_days(time),to_hours(time),to_minuts(time),to_seconds(time));
    }
    if(time) free(time);
    if(stime) free(stime);
}
