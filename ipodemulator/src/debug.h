#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

namespace Debug {

void begin(unsigned long baud = 115200);

void print(const char *message);
void print(uint8_t byte);

void println();
void println(const char *message);

inline void print(uint8_t value, int base) {
    if (base == HEX) {
        if (value < 0x10) print("0");
        char buf[3];
        sprintf(buf, "%02X", value);
        print(buf);
    } else {
        print((int)value);
    }
}

inline void println(uint8_t value, int base) {
    print(value, base);
    println();
}

} // namespace Debug

#endif // DEBUG_H
