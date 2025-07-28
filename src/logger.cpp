#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#include "logger.h"

static FILE* log_file = NULL;

static void current_time(char* cur_time_str);
static logger_err_t log_message(const char* log_type, const char* file_from, int line_from, const char* func_from, const char* fmt, ...);

logger_err_t log_open(const char* log_file_name) {
    assert(log_file_name);
    
    log_file = fopen(log_file_name, "a");
    if (!log_file) return LOGGER_ERR_FILE_OPEN_FAILED;  

    return LOGGER_ERR_SUCCES;
}

logger_err_t log_close(void) {
    fclose(log_file);
    log_file = NULL;

    return LOGGER_ERR_SUCCES;
}

static logger_err_t log_message(const char* log_lvl,   const char* file_from, int line_from,
                         const char* func_from, const char* fmt, ...) {

    if (!log_file) return LOGGER_ERR_FILE_PRINT_FAILED;

    char cur_time[DEFAULT_STR_SIZE] = "";
    current_time(cur_time);

    va_list args;
    va_start(args, fmt);
    
    fprintf (log_file, "[%s] [%s] %s:%d, %s(): ", cur_time, log_lvl, file_from, line_from, func_from);
    vfprintf(log_file, fmt, args);
    fprintf (log_file, "\n");
    
    va_end(args);

    return LOGGER_ERR_SUCCES;
}

static void current_time(char* cur_time_str) {
    const time_t cur_time = time(NULL);
    struct tm* tm_info = localtime(&cur_time);

    strftime(cur_time_str, DEFAULT_STR_SIZE, "%d-%m-%Y %H:%M:%S", tm_info);
}