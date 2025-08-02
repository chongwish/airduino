#include <airduino.h>

#include <devices/button.hpp>
#include <devices/led.hpp>
#include <devices/motor.hpp>
#include <drivers/l9110s.hpp>
#include <drivers/tb6612fng.hpp>
#include <libs/pressing.hpp>
#include <libs/rainbow_led.hpp>

#define BOARD_BOTTON_PIN PA_13

#define LED_RED_PIN PA_0
#define LED_GREEN_PIN PA_1
#define LED_BLUE_PIN PB_2

// #define MOTOR_A_IN1_PIN PF_0
// #define MOTOR_A_IN2_PIN PF_1
// #define MOTOR_A_PWM_PIN PB_6

#define MOTOR_A_IN_PIN PB_6
#define MOTOR_B_IN_PIN PB_3

#define MAX_DURATION 6200
#define LONG_DURATION 1200

Button button{BOARD_BOTTON_PIN, GPIO_PULLDOWN, HIGH};
Pressing pressing;

LedRgb led_rgb{LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN};
RainbowLed rainbow_led;

// Tb6612fng tb6612fng{MOTOR_A_IN1_PIN, MOTOR_A_IN2_PIN, MOTOR_A_PWM_PIN};
L9110s l9110s{MOTOR_A_IN_PIN, MOTOR_B_IN_PIN};
Motor motor;

void setup() {
    button.initialize();
    pressing.use(&button, RISING, []() { pressing.count(); });

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
            motor.rotateForward(255 * percent / 100);
        }
    } else {
        if (pressing.isFinish()) {
            uint8_t counter = pressing.getCount();
            pressing.clear();

            if (counter == 1) {
                rainbow_led.changeToNextColor();
                motor.rotateForward(255 * rainbow_led.getLevel() / 6);
            } else if (counter == 2) {
                motor.stop();
                rainbow_led.turnOff();
            }
        }
    }
}