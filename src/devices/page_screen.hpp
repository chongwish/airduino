#ifndef AIRDUNIO_DEVICE_PAGESCREEN
#define AIRDUNIO_DEVICE_PAGESCREEN 1

#include "../airduino.h"
#include "../libs/coordinate.hpp"
#include "./screen.hpp"

template <typename P, typename C>
class PageScreenDriver : public Driver {
public:
    virtual void display(const P &page_x, const P &page_y, Coordinate<C, P> &coordinate, const P &size) = 0;
};

template <typename P, P W, P H, typename C = uint8_t, C N = 8>
class PageScreen : public Device<PageScreenDriver<P, C>>, public ScreenDisplay<P, C> {
    Coordinate<C, P> coordinate{W, H / N};

    P cached_page_y1{H / N - 1};
    P cached_page_y2{0};
    P cached_x1{W - 1};
    P cached_x2{0};

    inline C calculatePageValue(const P &x, const P &y, const C &value) {
        P page_index = y / N;
        P page_value = coordinate.getMark(x, page_index);
        page_value = value ? (page_value | (1 << (y % N))) : (page_value & (0xFF ^ (1 << (y % N))));
        coordinate.mark(x, page_index, page_value);
        return page_value;
    }

public:
    void display(const P &x, const P &y, const C &value) {
        calculatePageValue(x, y, value);
        const P page_y = y / N;
        this->driver->display(x, page_y, coordinate, 1);
    }

    void display(const P &x1, const P &y1, const P &x2, const P &y2, const C &value) {
        for (P x = x1; x <= x2; ++x) {
            for (P y = y1; y <= y2; ++y) {
                calculatePageValue(x, y, value);
            }
        }

        const P page_y1 = y1 / N;
        const P page_y2 = y2 / N;
        const P x_size = x2 - x1 + 1;

        for (P page_y = page_y1; page_y <= page_y2; ++page_y) {
            this->driver->display(x1, page_y, coordinate, x_size);
        }
    }

    void display() {
        if (cached_page_y1 == cached_page_y2 && cached_x1 == cached_x2) return;

        for (P page_y = cached_page_y1; page_y <= cached_page_y2; ++page_y) {
            this->driver->display(cached_x1, page_y, coordinate, cached_x2 - cached_x1 + 1);
        }
        cached_page_y1 = H / N - 1;
        cached_page_y2 = 0;
        cached_x1 = W - 1;
        cached_x2 = 0;
    }

    void cache(const P &x, const P &y, const C &value) {
        calculatePageValue(x, y, value);
        const P page_y = y / N;

        if (x <= cached_x1) cached_x1 = x;
        if (x >= cached_x2) cached_x2 = x;
        if (page_y <= cached_page_y1) cached_page_y1 = page_y;
        if (page_y >= cached_page_y2) cached_page_y2 = page_y;
    }

    void cache(const P &x1, const P &y1, const P &x2, const P &y2, const C &value) {
        for (P x = x1; x <= x2; ++x) {
            for (P y = y1; y <= y2; ++y) {
                calculatePageValue(x, y, value);
            }
        }

        const P page_y1 = y1 / N;
        const P page_y2 = y2 / N;

        if (x1 <= cached_x1) cached_x1 = x1;
        if (x2 >= cached_x2) cached_x2 = x2;
        if (page_y1 <= cached_page_y1) cached_page_y1 = page_y1;
        if (page_y2 >= cached_page_y2) cached_page_y2 = page_y2;
    }

    P getWidth() { return W; }
    P getHeight() { return H; }
};

#endif