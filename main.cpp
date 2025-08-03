#include <stdio.h>

#include "logger.h"

int main() {
    log_open("debug.log");
    LOG(DEBUG, LOG_INFO, "fmbkdgb");
    LOG(DEBUG, NO_LOG_INFO, "jvjfvfnv");
    log_close();
    return 0;
}