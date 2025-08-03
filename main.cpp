#include <stdio.h>

#include "logger.h"

int main() {
    log_open("debug.log");
    LOG(DEBUG, true, "fmbkdgb");
    log_close();
    return 0;
}