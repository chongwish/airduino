#include <airduino.h>

#define RED_PORT PA5
#define GREEN_PORT PA0
#define BLUE_PORT PA1

const uint8_t PINS_SIZE = 16;
const uint8_t PINS_ID_SELECTED_SIZE = 6;
uint8_t PINS[] = {PA0, PA1, PA2, PA3, PA4, PA5, PA6, PA7, PA13, PA14, PB0, PB1, PB2, PB3, PF0, PF1};
bool PINS_PWM[] = {true, true, true, true, false, true, true, false, false, false, true, true, false, false, false, false};
uint8_t PINS_ID_SELECTED[] = {0, 1, 2, 3, 4, 5};

void reselect() {
    for (size_t i = 0; i < PINS_ID_SELECTED_SIZE; ++i) {
        PINS_ID_SELECTED[i] = random(PINS_SIZE);
        for (size_t j = 0; j < i; ++j) {
            while (PINS_ID_SELECTED[i] == PINS_ID_SELECTED[j]) {
                PINS_ID_SELECTED[i] = random(PINS_SIZE);
            }
        }
    }
}

void setup() {
    for (size_t i = 0; i < PINS_SIZE; ++i) {
        pinMode(PINS[i], OUTPUT);
        digitalWrite(PINS[i], LOW);
    }
}

void light_with_pwm(uint8_t value) {
    for (size_t i = 0; i < PINS_ID_SELECTED_SIZE; ++i) {
        if (PINS_PWM[PINS_ID_SELECTED[i]]) {
            analogWrite(PINS[PINS_ID_SELECTED[i]], value);
        }
    }
}

void light_without_pwm(uint8_t value) {
    for (size_t i = 0; i < PINS_ID_SELECTED_SIZE; ++i) {
        if (!PINS_PWM[PINS_ID_SELECTED[i]]) {
            if (value >= 80) {
                digitalWrite(PINS[PINS_ID_SELECTED[i]], HIGH);
            } else {
                digitalWrite(PINS[PINS_ID_SELECTED[i]], LOW);
            }
        }
    }
}

void loop() {
    reselect();

    for (size_t i = 0; i < PINS_SIZE; ++i) {
        digitalWrite(PINS[i], LOW);
    }

    for (size_t t = 0; t < 6; ++t) {
        for (size_t v = 0; v <= 255; ++v) {
            light_with_pwm(v);
            light_without_pwm(v);
            delay(5);
        }
        for (size_t v = 254; v <= 254; --v) {
            light_with_pwm(v);
            light_without_pwm(v);
            delay(5);
        }
    }

    delay(300);
}