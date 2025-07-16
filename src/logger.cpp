#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <time.h>

#include "logger.h"

static FILE* log_file = NULL;

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

logger_err_t log_message(const char* log_type, const char* file_from, int line_from, const char* func_from, const char* fmt, ...) {
    if (!log_file) return LOGGER_ERR_FILE_PRINT_FAILED;

    const char* cur_time = current_time();

    va_list args;
    va_start(args, fmt);
    fprintf(log_file, "[%s] %s:%d, %s(): ", cur_time, file_from, line_from, func_from);

    vfprintf(log_file, fmt, args);
    va_end(args);

    return LOGGER_ERR_SUCCES;
}

const char* current_time(void) {
    const time_t cur_time = time(NULL);
    const char* cur_time_str = ctime(&cur_time);

    return cur_time_str;
}