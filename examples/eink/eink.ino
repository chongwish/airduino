#include <GxEPD2.h>
#include <GxEPD2_3C.h>
// #include <GxEPD2_4C.h>
// #include <GxEPD2_7C.h>
// #include <GxEPD2_BW.h>
#include <GxEPD2_EPD.h>
// #include <GxEPD2_GFX.h>

#ifdef ARDUINO_ARCH_AIRMCU
#define CS_PIN PA4
#define DC_PIN PA1
#define RST_PIN PB1
#define BUSY_PIN PA0
#else
#define CS_PIN SS
#define DC_PIN 9
#define RST_PIN 8
#define BUSY_PIN 7
#endif

#define ENABLE_GxEPD2_GFX 0
#define MAX_DISPLAY_BUFFER_SIZE 800
// 213 3 color
// #define MAX_HEIGHT(EPD) (EPD::HEIGHT <= MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8) ? EPD::HEIGHT : MAX_DISPLAY_BUFFER_SIZE / (EPD::WIDTH / 8))
// 420 3 color
#define MAX_HEIGHT_3C(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))

// 213 3 color
// GxEPD2_3C<GxEPD2_213c, MAX_HEIGHT_3C(GxEPD2_213c)> display(GxEPD2_213c(/*CS=*/CS_PIN, /*DC=*/DC_PIN, /*RST=*/RST_PIN, /*BUSY=*/BUSY_PIN));              // GDEW0213Z16 104x212, UC8151 (IL0373)
// GxEPD2_3C<GxEPD2_213_Z19c, MAX_HEIGHT_3C(GxEPD2_213_Z19c)> display(GxEPD2_213_Z19c(/*CS=*/CS_PIN, /*DC=*/DC_PIN, /*RST=*/RST_PIN, /*BUSY=*/BUSY_PIN));  // GDEH0213Z19 104x212, UC8151D

// 420 3 color
// GxEPD2_3C<GxEPD2_420c, MAX_HEIGHT_3C(GxEPD2_420c)> display(GxEPD2_420c(/*CS=*/CS_PIN, /*DC=*/DC_PIN, /*RST=*/RST_PIN, /*BUSY=*/BUSY_PIN));                                   // GDEW042Z15 400x300, UC8176 (IL0398)
GxEPD2_3C<GxEPD2_420c_Z21, MAX_HEIGHT_3C(GxEPD2_420c_Z21)> display(GxEPD2_420c_Z21(/*CS=*/CS_PIN, /*DC=*/DC_PIN, /*RST=*/RST_PIN, /*BUSY=*/BUSY_PIN));  // GDEQ042Z21 400x300, UC8276
// GxEPD2_3C<GxEPD2_420c_GDEY042Z98, MAX_HEIGHT_3C(GxEPD2_420c_GDEY042Z98)> display(GxEPD2_420c_GDEY042Z98(/*CS=*/DC_PIN, /*DC=*/DC_PIN, /*RST=*/RST_PIN, /*BUSY=*/BUSY_PIN));  // GDEY042Z98 400x300, SSD1683 (no inking)

#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMonoBold9pt7b.h>

const char HelloWorld[] = "Hello World!";

void setup() {
    display.init(9600);
    display.setRotation(1);
    display.setTextWrap(false);

    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);

    int16_t tbx, tby;                                                 // 文本框的x，y坐标
    uint16_t tbw, tbh;                                                // 文本框的宽度，高度
    display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);  // 计算渲染后的文本框的

    uint16_t x = ((display.width() - tbw) / 2) - tbx;   // 文本框的x坐标
    uint16_t y = ((display.height() - tbh) / 2) - tby;  // 文本框的y坐标
    display.setFullWindow();

    do {
        display.fillScreen(GxEPD_WHITE);
        display.setCursor(x, y);
        display.print(HelloWorld);
    } while (display.nextPage());

    // delay(5000);
    // display.hibernate();
}

uint16_t colors[3] = {GxEPD_BLACK, GxEPD_RED, GxEPD_WHITE};
int i = 0;

void loop() {
    delay(5000);
    do {
        display.fillScreen(colors[i]);
    } while (display.nextPage());
    i = ++i % 3;
}