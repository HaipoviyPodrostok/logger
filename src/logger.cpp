#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "logger.h"
#include "../utils/error_handling.h"

static FILE* log_file = NULL;

logger_err_t log_open(const char* file_name) {
    assert(file_name);
    
    log_file = fopen(file_name, "a");
    if (!log_file) return LOGGER_ERR_FILE_OPEN_FAILED;  

    return LOGGER_ERR_SUCCES;
}

logger_err_t log_close(void) {
    fclose(log_file);
    return LOGGER_ERR_SUCCES;
}

logger_err_t LOG(const char* message, ) {
    fprintf(log_file, "%s:%d, %s(): %s\n", __FILE__, __LINE__, __func__, message); 

}