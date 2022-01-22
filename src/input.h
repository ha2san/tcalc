#pragma once
#include <stdlib.h>
#include <stdbool.h>

enum input {STDIN,ARGV};

char* sanitize_input(char* input,size_t length,enum input where);

void help(void);

double run_argument(const char* argv);


bool map_free(const void *item, void *udata);


bool show_map(const void *item, void *udata);

int run_stdin(void);
