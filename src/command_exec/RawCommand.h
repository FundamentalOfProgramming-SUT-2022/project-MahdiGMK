#ifndef _RAWCOMMAND
#define _RAWCOMMAND

#include <stdio.h>

#define LOG(str...) \
    printf(str);    \
    printf("\n");   \
    fflush(stdout);

int _CreateFile(char *address);

int _InsertStr(char *address, char *pattern, int l, int c);

void _CAT(char *address);

#endif