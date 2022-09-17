#include <stdio.h>

#include "defines.h"

#if !defined (LOG_NAME)

    #define LOG_NAME "log.txt"

#endif

int ()
{

}


FILE* open_log()
{
    FILE* def_and_check(log_file, fopen(LOG_NAME, "a"), NULL);

    if (log_file == NULL)
    {
        printf("ERROR: log file not found\n")
    }

    return log_file;
}
