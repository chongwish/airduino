#define BOARD_LED_GREEN_PIN PB_0
#define BOARD_LED_RED_PIN PB_1
#define BOARD_LED_BLUE_PIN PB_3

int air_leds[] = {BOARD_LED_RED_PIN, BOARD_LED_GREEN_PIN, BOARD_LED_BLUE_PIN};

void setup() {
    for (int i = 0; i < 3; i++) {
        pinMode(air_leds[i], OUTPUT);
        digitalWrite(air_leds[i], LOW);
    }
}

void loop() {
    for (int i = 0; i < 3; i++) {
        digitalWrite(air_leds[(i + 1) % 3], LOW);
        delay(1000);
        digitalWrite(air_leds[(i + 2) % 3], LOW);
        delay(1000);
        digitalWrite(air_leds[i], HIGH);
        delay(1000);
    }
}