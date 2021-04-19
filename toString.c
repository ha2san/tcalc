#include <string.h>
#include <stdlib.h>
#include <stdio.h>


size_t getUntil(size_t from, char* input);
size_t isNumber(size_t from, char* input);

char** toString(char* input)
{
    size_t index = 0;
    size_t length_input = strlen(input);
    char** ret = calloc(sizeof(char*),length_input);

    size_t from = 0;
    size_t until = 0;

    while (until <= strlen(input))
    {
        ret[index] = calloc(sizeof(char),length_input);
        until = getUntil(from,input);
        strncpy(ret[index],input+from,until-from);
        from = until;
        index++;
    }
    for (size_t i = 0; i < length_input; ++i)
    {
        printf("%s\n",ret[i]);
    }
    return ret;
}

//int main(void)
//{
//    char* input = "33+5+6*721+(-3333+2)";
//    toString(input);
//}
//

size_t getUntil(size_t from,char* input)
{
    size_t until = from+1;
    if(until == strlen(input))
    {
        return until;
    }
    else
    {
        switch (input[from])
        {
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
            return until;
            break;
        default:
            return isNumber(from,input);
        }
    }
}


size_t isNumber(size_t from, char* input)
{
    size_t until = from+1;
    while (until <= strlen(input))
    {
        switch (input[until])
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            until++;
            break;
        default:
            return until;
        }
    }
    return until;
}

