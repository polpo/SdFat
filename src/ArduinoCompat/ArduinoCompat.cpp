#include "./Arduino.h"

uint32_t millis(void) {
    return time_us_32() / 1000;
}
