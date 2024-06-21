#ifndef AIRDUINO
#define AIRDUINO 1

#include <Arduino.h>

class Driver {
public:
    virtual void initialize() = 0;
};

template <typename T>
class Device {
public:
    T *driver;

public:
    virtual void loadDriver(T *driver) {
        this->driver = driver;
        driver->initialize();
    }
};

#endif