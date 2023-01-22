#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "FileHandling.h"

FileHandlingStatus ReadFileNoAlloc(const char *fileAddress, char *str)
{
    FILE *rfile = fopen(fileAddress, "r");
    if (rfile == NULL)
    {
        *str = 0;
        return FILE_DIDNT_EXIST;
    }

    char *ptr = str;
    while (1)
    {
        *ptr = fgetc(rfile);

        if (*ptr == EOF)
        {
            *ptr = 0;
            break;
        }
        ptr++;
    }
    fclose(rfile);
    return FILE_EXISTED;
}

FileHandlingStatus WriteFile(const char *fileAddress, char *str)
{
    CreateDirectory(fileAddress);

    FILE *cfile = fopen(fileAddress, "r");
    if (cfile)
        fclose(cfile);

    FILE *wfile = fopen(fileAddress, "w");
    fprintf(wfile, "%s", str);
    fclose(wfile);

    if (cfile == NULL)
        return FILE_CREATED;
    return FILE_EXISTED;
}

FileHandlingStatus CreateFile(const char *fileAddress)
{
    FILE *cfile = fopen(fileAddress, "r");
    if (cfile)
        fclose(cfile);

    if (cfile == NULL)
    {
        WriteFile(fileAddress, "");
        return FILE_CREATED;
    }
    return FILE_EXISTED;
}

FileHandlingStatus CreateDirectory(const char *fileAddress)
{
    char str[100] = {};
    int existed = 0;
    for (int i = 0; i < 100; i++)
        if (fileAddress[i] == 0)
            break;
        else
        {
            if (fileAddress[i] == '/')
                existed = mkdir(str, 0777) == -1;
            str[i] = fileAddress[i];
        }
    if (existed)
        return FILE_EXISTED;
    return FILE_CREATED;
}