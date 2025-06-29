#include "NowPlaying.h"
#include "Debug.h"
#include <string.h>

void NowPlaying::begin() {
    packetLength = 0;
    Debug::println("NowPlaying started");
}

void NowPlaying::update(const char* artist, const char* album, const char* title) {
    buildNowPlayingPacket(artist, album, title);
    Debug::println("NowPlaying updated");
}

void NowPlaying::buildNowPlayingPacket(const char* artist, const char* album, const char* title) {
    // Simple example packet with metadata strings separated by 0x00
    // Real iPod uses a structured packet; replace with real iPod dumps if available

    size_t pos = 0;
    nowPlayingPacket[pos++] = 0x01; // Packet header example
    // Append artist string
    size_t len = strlen(artist);
    memcpy(&nowPlayingPacket[pos], artist, len);
    pos += len;
    nowPlayingPacket[pos++] = 0x00;

    // Append album string
    len = strlen(album);
    memcpy(&nowPlayingPacket[pos], album, len);
    pos += len;
    nowPlayingPacket[pos++] = 0x00;

    // Append title string
    len = strlen(title);
    memcpy(&nowPlayingPacket[pos], title, len);
    pos += len;
    nowPlayingPacket[pos++] = 0x00;

    packetLength = pos;
}

const uint8_t* NowPlaying::getNowPlayingPacket(size_t* outLen) {
    *outLen = packetLength;
    return nowPlayingPacket;
}
