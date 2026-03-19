
#include <airduino.h>

#include <devices/button.hpp>
#include <devices/led.hpp>
#include <devices/motor.hpp>
#include <drivers/l9110s.hpp>
#include <drivers/tb6612fng.hpp>
#include <libs/pressing2.hpp>
#include <libs/rainbow_led.hpp>

#define BOARD_BOTTON_PIN PA13

#define LED_RED_PIN PB2
#define LED_GREEN_PIN PB0
#define LED_BLUE_PIN PB1

// #define MOTOR_A_IN1_PIN PF_0
// #define MOTOR_A_IN2_PIN PF_1
// #define MOTOR_A_PWM_PIN PB_6

#define MOTOR_A_IN_PIN PA0
#define MOTOR_B_IN_PIN PA1

#define MAX_DURATION 6200
#define LONG_DURATION 1200
#define GAP_DURATION 300

Button button{BOARD_BOTTON_PIN, INPUT_PULLDOWN, HIGH};
Pressing pressing{LONG_DURATION, GAP_DURATION};

LedRgb led_rgb{LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN};
RainbowLed rainbow_led;

// Tb6612fng tb6612fng{MOTOR_A_IN1_PIN, MOTOR_A_IN2_PIN, MOTOR_A_PWM_PIN};
L9110s l9110s{MOTOR_A_IN_PIN, MOTOR_B_IN_PIN};
Motor motor;

void setup() {
    button.initialize();
    pressing.use(&button);

    led_rgb.initialize();
    rainbow_led.use(&led_rgb);

    // motor.loadDriver(&tb6612fng);
    motor.loadDriver(&l9110s);
}

void loop() {
    uint32_t duration = pressing.getDuration();

    if (duration > LONG_DURATION) {
        if (duration <= MAX_DURATION) {
            uint8_t percent = (duration - LONG_DURATION) * 100 / (MAX_DURATION - LONG_DURATION);

            rainbow_led.changeGradually(percent);
            motor.rotateForward(100 * percent / 100 + 140);
        }
    } else {
        if (pressing.isFinish()) {
            uint8_t counter = pressing.getCountAndClear();

            if (counter == 1) {
                rainbow_led.changeToNextColor();
                motor.rotateForward(20 * rainbow_led.getLevel() + 120);
            } else if (counter == 2) {
                motor.stop();
                rainbow_led.turnOff();
            }
        }
    }
}