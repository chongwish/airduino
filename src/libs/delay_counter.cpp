#include "delay_counter.hpp"

uint8_t DelayCounter::getCount() {
    int count = 0, precount = 0;
    int time_keeping = 0;

    while (time_keeping < time_block - 1) {
        if (count > precount) {
            precount = count;
            time_keeping = 0;
        } else {
            ++time_keeping;
        }

        if (condition()) {
            time_keeping = 0;
            precount = count++;
        }

        delay(time_unit);
    }

    return count;
}
