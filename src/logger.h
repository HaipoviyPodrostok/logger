#ifndef SRC_LOGGER_H
#define SRC_LOGGER_H

#include "logger_err_handle.h"

#define DEFAULT_STR_SIZE 50 

#define LOG_INFO    true
#define NO_LOG_INFO false

#define LOG(log_lvl, isTime, ...) log_message(#log_lvl, isTime, __FILE__, __LINE__, __func__, __VA_ARGS__)

logger_err_t log_open(const char* file_name);
void log_close(void);
logger_err_t log_message(const char* log_lvl, bool isLogInfo, const char* file_from, 
                         int line_from, const char* func_from, const char* fmt, ...);
const char* current_time(void);

typedef enum {
    DEBUG =     1,
    INFO =      2,
    WARNING =   3,
    ERROR =     4,
    FATAL =     5,
} log_lvl_t;

#endif //SRC_LOGGER_H