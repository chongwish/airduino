#include "timer_as_action.hpp"

void TimerAsAction::keepActionTime() {
    action_time_keeping = action_count > 0 ? (++action_time_keeping) % action_time_block : 0;
}

template<typename Fn>
void TimerAsAction::capture(Fn && condition) {
    clean();
    while (action_time_keeping < action_time_block - 1) {
        keepActionTime();
        condition() && increase();
        delay(action_time_unit);
    }
}

inline uint8_t TimerAsAction::increase() {
    action_time_keeping = 0;
    return ++action_count;
}

inline void TimerAsAction::clean() {
    action_count = 0;
    action_time_keeping = 0;
}

uint8_t TimerAsAction::getCount() {
    return action_count;
}