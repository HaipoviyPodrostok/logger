#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdio.h>

#define ERROR_HANDLE(call_func, ...) ({                                             \
    logger_err_t error = call_func;                                                 \
    if (error) {                                                                    \
        fprintf(stderr, "[" #call_func "] Error: %s\n", tree_error_str(error));     \
        __VA_ARGS__;                                                                \
        return error;                                                               \
    }                                                                               \
});

typedef enum {
    LOGGER_ERR_SUCCES = 0,
    LOGGER_ERR_DUMP_FAILED = 1,
    LOGGER_ERR_ALLOCATION_FAILED = 2,
    LOGGER_ERR_FILE_READING_FAILED = 3,
    LOGGER_ERR_FILE_OPEN_FAILED = 4,
    LOGGER_ERR_FILE_PRINT_FAILED = 5,
    LOGGER_ERR_NULL_PTR_ERROR = 6,
    LOGGER_ERR_FILE_CLOSE_FAILED = 7,
    LOGGER_ERR_STR_PRINT_FAILED = 8,
    LOGGER_ERR_INSERTION_FAILED = 9,
    LOGGER_ERR_INPUT_FILE_INCORRECT = 10,
    LOGGER_ERR_FILL_NODE_FAILED = 11,
    LOGGER_ERR_INPUT_SCAN_FAILED = 12,
    LOGGER_ERR_TOO_FEW_COMMAND_LINE_ARGUMENTS = 13,
    LOGGER_ERR_UNKNOWN_ERROR = 14,
    LOGGER_ERR_INCORRECT_STATUS = 15,
} logger_err_t;

const char* tree_error_str(logger_err_t error);

#endif //ERROR_HANDLING_H