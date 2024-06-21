#ifndef AIRDUNIO_LIB_TIME_AS_ACTION
#define AIRDUNIO_LIB_TIME_AS_ACTION 1

#include "../airduino.h"

class DelayCounter {
    using Condition = bool (*)();

    uint8_t time_unit = 10;
    uint8_t time_block = 50;

    Condition condition;

public:
    uint8_t getCount();
    DelayCounter(Condition condition) : condition(condition) {}
};

#endif