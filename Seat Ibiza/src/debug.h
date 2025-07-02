#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

class Debug {
public:
    static void begin(Stream& stream) {
        _stream = &stream;
    }

    template<typename... Args>
    static void info(const char* format, Args... args) {
        if (_stream) {
            char buf[256];
            snprintf(buf, sizeof(buf), format, args...);
            _stream->println(buf);
        }
    }

private:
    static Stream* _stream;
};

Stream* Debug::_stream = nullptr;

#endif
