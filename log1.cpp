#include <stdio.h>

#include "defines.h"

#if !defined (LOG_NAME)

    #define LOG_NAME "log.txt"

#endif

#define log(text_file, action)                             \
{                                                          \
    fprintf(text_file, "In file %s in %s (line %d): %s\n", \
                        __FILE__,                          \
                        __PRETTY_FUNCTION__,               \
                        __LINE__,                          \
                        #action)                           \
}

#define StackDump(stk)                                     \
{                                                          \
    fprintf(LOG_NAME, "%s at %s(%d):\n",                   \
                       __PRETTY_FUNCTION__,                \
                       __FILE__,                           \
                       __LINE__);                          \
                                                           \
    fprintf(LOG_NAME, "Stack [%p] ", stk->Ptr);            \
                                                           \
    int err_code = 0;                                      \
                                                           \
    if (err_code = !verify_stack)                          \
    {                                                      \
        $g;                                                \
        fprintf(LOG_NAME, "OK\n");                         \
    }                                                      \
    else                                                   \
    {                                                      \
        $r;                                                \
        fprintf(LOG_NAME, "ERROR\n");                      \
    }                                                      \
    $d;                                                    \
                                                           \
    fprintf(LOG_NAME, "Originally '%s' from %s at %s",     \
                       stk->name_info.Orig_name,           \
                       stk->name_info.Func_calling,        \
                       stk->name_info.File_calling);       \
                                                           \
}



int ()
{

}


FILE* open_log()
{
    FILE* log_file = fopen(LOG_NAME, "a");

    if (log_file == NULL)
    {
        fprintf(stderr, "ERROR: log file not found while opening\n");
    }

    return log_file;
}

FILE* close_log()
{
    FILE* log_file = fclose(LOG_NAME);

    if (log_file == NULL)
    {
        fprintf(stderr, "ERROR: log file not found while closing\n");
    }

    return log_file;
}
