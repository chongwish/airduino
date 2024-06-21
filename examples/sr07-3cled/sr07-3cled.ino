#ifdef ARDUINO_ARCH_AIRMCU
#define BOARD_LED_GREEN_PIN PB_0
#define BOARD_LED_RED_PIN PB_1
#define BOARD_LED_BLUE_PIN PB_3
#define LED_RED_PIN PA_0
#define LED_GREEN_PIN PA_1
#define LED_BLUE_PIN PA_7
#define TRIG_PIN PF_1
#define ECHO_PIN PF_0
#else
#define BOARD_LED_GREEN_PIN PIN3
#define BOARD_LED_RED_PIN PIN4
#define BOARD_LED_BLUE_PIN PIN5
#define LED_RED_PIN PIN_A1
#define LED_GREEN_PIN PIN_A2
#define LED_BLUE_PIN PIN_A3
#define TRIG_PIN PIN_WIRE_SCL
#define ECHO_PIN PIN_WIRE_SDA
#endif

static int MAX_VALUE = 240;
static int UNIT = 6;
static int STEP = MAX_VALUE / UNIT;
static int LEVEL[6] = {2, -1, 3, -2, 1, -3};

void turnOnBoardLed() {
    digitalWrite(BOARD_LED_GREEN_PIN, HIGH);
    digitalWrite(BOARD_LED_RED_PIN, HIGH);
    digitalWrite(BOARD_LED_BLUE_PIN, HIGH);
}

double calcDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    return pulseIn(ECHO_PIN, HIGH) * 0.034 / 2;
}

void makeLedColorful(double distance) {
    if (distance >= UNIT * 6) {
        distance = UNIT * 6.0 - 1;
    }

    int colors[3] = {0, 0, 0};

    int level_value = LEVEL[(int)(distance) / UNIT];
    int unit_value = (int)(distance) % UNIT;
    int index = level_value - 1;
    int value = unit_value * STEP;
    int max_value_index = (index - 1 + 3) % 3;

    if (level_value < 0) {
        value = MAX_VALUE - unit_value * STEP;
        index = level_value * -1 - 1;
        max_value_index = (index + 1) % 3;
    }

    colors[max_value_index] = MAX_VALUE;
    colors[index] = value;

    analogWrite(LED_RED_PIN, colors[0]);
    analogWrite(LED_GREEN_PIN, colors[1]);
    analogWrite(LED_BLUE_PIN, colors[2]);
}

void setup() {
    pinMode(BOARD_LED_GREEN_PIN, OUTPUT);
    pinMode(BOARD_LED_RED_PIN, OUTPUT);
    pinMode(BOARD_LED_BLUE_PIN, OUTPUT);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    digitalWrite(BOARD_LED_GREEN_PIN, LOW);
    digitalWrite(BOARD_LED_RED_PIN, LOW);
    digitalWrite(BOARD_LED_BLUE_PIN, LOW);

    analogWrite(LED_RED_PIN, 0);
    analogWrite(LED_GREEN_PIN, 0);
    analogWrite(LED_BLUE_PIN, 0);

    turnOnBoardLed();
}

void loop() {
    double distance = calcDistance();

    makeLedColorful(distance);

    delay(500);
}