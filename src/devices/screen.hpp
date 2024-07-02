#ifndef AIRDUNIO_DEVICE_SCREEN
#define AIRDUNIO_DEVICE_SCREEN 1

#include "../airduino.h"
#include "../libs/coordinate.hpp"

template <typename P, typename C>
class ScreenDisplay {
public:
    virtual void display(const P &x, const P &y, const C &color) = 0;
    virtual void display(const P &x1, const P &y1, const P &x2, const P &y2, const C &color) = 0;
    virtual void display(const P &x1, const P &y1, const P &x2, const P &y2, Coordinate<C, P> &coordinate) = 0;
    virtual void display(const P &x1, const P &y1, const P &x2, const P &y2, C (*mapColorFn)(const P &x, const P &y)) = 0;
    virtual void display() = 0;

    virtual void cache(const P &x, const P &y, const C &color) = 0;
    virtual void cache(const P &x1, const P &y1, const P &x2, const P &y2, const C &color) = 0;
    virtual void cache(const P &x1, const P &y1, const P &x2, const P &y2, Coordinate<C, P> &coordinate) = 0;
    virtual void cache(const P &x1, const P &y1, const P &x2, const P &y2, C (*mapColorFn)(const P &x, const P &y)) = 0;

    virtual P getWidth() = 0;
    virtual P getHeight() = 0;
};

template <typename P, typename C>
class ScreenDriver : public Driver {
public:
    virtual void display(const P &x1, const P &y1, const P &x2, const P &y2, const C &color) = 0;
    virtual void display(const P &x1, const P &y1, const P &x2, const P &y2, Coordinate<C, P> &coordinate) = 0;
    virtual void display(const P &x1, const P &y1, const P &x2, const P &y2, C (*mapColorFn)(const P &x, const P &y)) = 0;
};

template <typename P, P W, P H, typename C = uint16_t>
class Screen : public Device<ScreenDriver<P, C>>, public ScreenDisplay<P, C> {
public:
    void display(const P &x, const P &y, const C &color) {
        display(x, y, x, y, color);
    }

    void display(const P &x1, const P &y1, const P &x2, const P &y2, const C &color) {
        this->driver->display(x1, y1, x2, y2, color);
    }

    void display(const P &x1, const P &y1, const P &x2, const P &y2, Coordinate<C, P> &coordinate) {
        this->driver->display(x1, y1, x2, y2, coordinate);
    }

    void display(const P &x1, const P &y1, const P &x2, const P &y2, C (*mapColorFn)(const P &x, const P &y)) {
        this->driver->display(x1, y1, x2, y2, mapColorFn);
    }

    void display() {}

    void cache(const P &x, const P &y, const C &color) {
        display(x, y, x, y, color);
    }

    void cache(const P &x1, const P &y1, const P &x2, const P &y2, const C &color) {
        display(x1, y1, x2, y2, color);
    }

    void cache(const P &x1, const P &y1, const P &x2, const P &y2, Coordinate<C, P> &coordinate) {
        display(x1, y1, x2, y2, coordinate);
    }

    void cache(const P &x1, const P &y1, const P &x2, const P &y2, C (*mapColorFn)(const P &x, const P &y)) {
        display(x1, y1, x2, y2, mapColorFn);
    }

    P getWidth() { return W; }

    P getHeight() { return H; }
};

#endif