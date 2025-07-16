#ifndef SRC_LOGGER_H
#define SRC_LOGGER_H

#include "../utils/error_handling.h"

#define LOG(...) log_message(__FILE__, __LINE__, __func__, __VA__ARGS__)

logger_err_t log_open(const char* file_name);
logger_err_t log_close(void);
logger_err_t log_message(const char* log_type, const char* file_from, int line_from, const char* func_from, const char* fmt, ...);
const char* current_time(void);


#endif //SRC_LOGGER_H