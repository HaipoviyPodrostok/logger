#include <stdio.h>

#include "logger.h"

int main() {
    log_open("log.txt");
    LOG(DEBUG, "vse norm\n");
    log_close();
    return 0;
}