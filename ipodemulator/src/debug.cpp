#include "Debug.h"

namespace Debug {

void begin(unsigned long baud) {
    Serial.begin(baud);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB
    }
}

void print(const char *message) {
    Serial.print(message);
}

void print(uint8_t byte) {
    if (byte < 0x10) Serial.print("0");
    Serial.print(byte, HEX);
    Serial.print(" ");
}

void println() {
    Serial.println();
}

void println(const char *message) {
    Serial.println(message);
}

} // namespace Debug
