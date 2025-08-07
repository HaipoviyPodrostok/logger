#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "logger.h"

static FILE* log_file = NULL;
static void current_time(char* cur_time_str);

logger_err_t log_open(const char* log_file_name) {
    assert(log_file_name);
    
    mkdir("log", 0755);
    chdir("./log");
    log_file = fopen(log_file_name, "a");
    if (!log_file) return LOGGER_ERR_FILE_OPEN_FAILED;  
    chdir("..");

    return LOGGER_ERR_SUCCESS;
}

void log_close(void) {
    fclose(log_file);
    log_file = NULL;

    return;
}

logger_err_t log_message(const char* log_lvl, bool isLogInfo, const char* file_from, 
                         int line_from, const char* func_from, const char* fmt, ...) {

    if (!log_file) return LOGGER_ERR_NULL_PTR_ERROR;

    char cur_time[DEFAULT_STR_SIZE] = "";
    current_time(cur_time);

    va_list args;
    va_start(args, fmt); 
    
    if (isLogInfo == true) {
        fprintf (log_file, "[%s] [%s] %s:%d, %s(): ", cur_time, log_lvl, file_from, line_from, func_from);
    }
    
    vfprintf(log_file, fmt, args);
    fprintf (log_file, "\n");
    va_end(args);

    fflush(log_file);

    return LOGGER_ERR_SUCCESS;
}

static void current_time(char* cur_time_str) {
    const time_t cur_time = time(NULL);
    struct tm* tm_info = localtime(&cur_time);

    strftime(cur_time_str, DEFAULT_STR_SIZE, "%d-%m-%Y %H:%M:%S", tm_info);
}
