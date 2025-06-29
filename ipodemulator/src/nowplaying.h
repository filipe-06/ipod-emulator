#ifndef NOWPLAYING_H
#define NOWPLAYING_H

#include <Arduino.h>

class NowPlaying {
public:
    void begin();
    void update(const char* artist, const char* album, const char* title);
    const uint8_t* getNowPlayingPacket(size_t* outLen);

private:
    uint8_t nowPlayingPacket[256];
    size_t packetLength;

    void buildNowPlayingPacket(const char* artist, const char* album, const char* title);
};

#endif
