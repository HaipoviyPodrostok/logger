#include <stdio.h>
#include <stdlib.h>

#include "error_handling.h"

#define CASE_ENUM_TO_STRING(error) case error: return #error

const char* tree_error_str(logger_err_t error) {
    switch(error) {
        CASE_ENUM_TO_STRING(LOGGER_ERR_SUCCES);

        default:
            return "LOGGER_ERR_UNKNOWN_ERROR";
        return "LOGGER_ERR_UNKNOWN_ERROR";
    }
}

#undef CASE_ENUM_TO_STRING
