#include "../airduino.h"

#ifndef AIRDUNIO_LIB_TIME_AS_ACTION

#define AIRDUNIO_LIB_TIME_AS_ACTION 1

class TimerAsAction {
    public:
      template<typename Fn> void capture(Fn && condition);
      uint8_t increase();
      void clean();
      uint8_t getCount();
    private:
      uint8_t action_time_keeping = 0;
      uint8_t action_count = 0;
      uint8_t action_time_block = 50;
      uint8_t action_time_unit = 10;

      void keepActionTime();
};

#endif