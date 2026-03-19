#include <airduino.h>

#include <devices/button.hpp>
#include <devices/led.hpp>
#include <devices/motor.hpp>
#include <drivers/rz7889.hpp>

#define SPI_CS_PIN PA4
#define SPI_CLK_PIN PA5
#define SPI_MISO_PIN PA6
#define SPI_MOSI_PIN PA7

#define KEY_POWER_PIN PB0
#define KEY_CHANGE_PIN PB1

#define SWDIO_PIN PA13
#define SWCLK_PIN PA14

#define STATUS_BLUE_PIN PB3
#define STATUS_RED_PIN PB5
#define STATUS_GREEN_PIN PB6

#define RX_PIN PA4
#define TX_PIN PA3

#define MOTOR_P_PIN PA1
#define MOTOR_M_PIN PA0

#define I2C_SDA_PIN PF1
#define I2C_SCL_PIN PF0

Button power_button{KEY_POWER_PIN, INPUT, LOW};
Button change_button{KEY_CHANGE_PIN, INPUT, LOW};

Rz7889 rz7889{MOTOR_M_PIN, MOTOR_P_PIN};
Motor motor;

bool power_status{false};
uint8_t fan_level{0};

void light(uint32_t red_status, uint32_t green_status, uint32_t blue_status) {
    digitalWrite(STATUS_GREEN_PIN, red_status);
    digitalWrite(STATUS_BLUE_PIN, green_status);
    digitalWrite(STATUS_RED_PIN, blue_status);
}

void setHandler() {
    attachInterrupt(
        digitalPinToInterrupt(power_button.getPin()),
        []() {
            power_status = !power_status;
            fan_level = 0;
        },
        RISING);

    attachInterrupt(
        digitalPinToInterrupt(change_button.getPin()),
        []() {
            if (power_status) {
                fan_level = (fan_level % 3) + 1;
            } else {
                fan_level = 0;
            }
        },
        RISING);
}

void setup() {
    pinMode(STATUS_RED_PIN, OUTPUT);
    pinMode(STATUS_BLUE_PIN, OUTPUT);
    pinMode(STATUS_GREEN_PIN, OUTPUT);

    power_button.initialize();
    change_button.initialize();

    motor.loadDriver(&rz7889);

    setHandler();
}

void loop() {
    switch (fan_level) {
        case 1:
            motor.rotateForward(150);
            light(HIGH, LOW, LOW);
            break;
        case 2:
            motor.rotateForward(200);
            light(LOW, HIGH, LOW);
            break;
        case 3:
            motor.rotateForward(250);
            light(LOW, LOW, HIGH);
            break;

        default:
            motor.rotateForward(0);
            if (power_status) {
                light(HIGH, HIGH, HIGH);
            } else {
                light(LOW, LOW, LOW);
            }
            break;
    }
}