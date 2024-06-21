# Airduino

Some libraries, drivers and demos using arduino framework for **air001** board & **arduino** board.

---

Last week, I start to learn embedded development by myself. And luckily, I apply to [luatos](https://wiki.luatos.com/chips/air001/board.html) and get a air001 board from them **without any costs** ^o^!

![Air001](./images/air001.jpg)

## Description

### `apps`

The `apps` provide usefil functionality to the user:

- Graphics: drawing simple graphics in a screen
- Text: printing simple character in a screen
- ...

### `devices`

The `devices` describe how a device works, no matter who the producer is. They uses the driver provided by the producer to drive the device. They provides a common interface for app & `.ino` file:

- Screen: displaying something
  - PageScreen: displaying something in page mode
- Gyroscope
  - 6 Axis Gyroscope: fetching 6-axis data
- ...

### `drivers`

Every device has many different hardwares. And the `drivers` provide a way to initialize and use these hardware:

- SSD1306 Hardware I2C: OLED/PLED Display
- ST7789 Software SPI: LCD Display
- MPU6050 Hardware I2C: Accelerometer Gyroscope Sensor
- ...
   
### `libs`

The `libs` provides device-independent functions:

- Coordinate
- Color
- DelayCounter
- ...

### `thirds`

Third party dependency.

## Demo

Airduino provides a **uniform** method for using devices, for example:

```c++
// a screen device which size is 128 x 64 in page mode
PageScreen<uint8_t, 128, 64> screen;

// select display driver
Ssd1306 driver;
// Ssd1305 driver;

void setup() {
    ...
    // nothing need to change
    screen.loadDriver(&driver);
    ...
}

void loop() {
    ...
    screen.display(x, y, color.white);
    ...
}
```

**Decoupling** driver/device & function:

```c++
// device
PageScreen<uint8_t, 128, 64> screen;

// function
Graphics<uint8_t, uint8_t> graphics;
Text<uint8_t, uint8_t> text;

void setup() {
    ...
    graphics.use(&screen);
    text.use(&screen);
    ...
}

void loop() {
    ...
    graphics.drawRectangle(7, 7, 119, 27, color.black);
    graphics.drawCircle(63, 47, 16, color.black);
    text.color(color.black);
    text.at(21, 13).print("Chongwish");
    text.at(39, 39).print("AirMCU!");
    ...
}
```

There are some examples to show how they work, such as `./examples/screen-display`:

https://github.com/chongwish/airdunio/assets/9025604/5c2c9f4d-4fcc-4b12-9aee-3da777bea04d

As a practice, they are all written in modern c++ language.