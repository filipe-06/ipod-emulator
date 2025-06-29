#ifndef PACKETBUILDER_H
#define PACKETBUILDER_H

#include <Arduino.h>

class PacketBuilder {
public:
    static size_t buildHandshake(uint8_t* buffer, size_t maxLen);
    static size_t buildIdentifyResponse(uint8_t* buffer, size_t maxLen);
    static size_t buildAck(uint8_t* buffer, uint8_t command, size_t maxLen);
    static size_t buildNowPlaying(uint8_t* buffer, size_t maxLen, const char* artist, const char* album, const char* title);

private:
    static size_t writeUint16(uint8_t* buf, uint16_t value);
    static size_t writeString(uint8_t* buf, const char* str);
};

#endif
