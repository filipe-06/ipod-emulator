#include "PacketBuilder.h"
#include "Debug.h"

size_t PacketBuilder::writeUint16(uint8_t* buf, uint16_t value) {
    buf[0] = (value >> 8) & 0xFF;
    buf[1] = value & 0xFF;
    return 2;
}

size_t PacketBuilder::writeString(uint8_t* buf, const char* str) {
    size_t len = strlen(str);
    memcpy(buf, str, len);
    return len;
}

size_t PacketBuilder::buildHandshake(uint8_t* buffer, size_t maxLen) {
    // Example handshake packet (needs real data)
    const uint8_t handshakeData[] = { 0x02, 0x01, 0x01 };
    size_t len = sizeof(handshakeData);
    if (len > maxLen) return 0;
    memcpy(buffer, handshakeData, len);
    Debug::println("PacketBuilder: Built handshake");
    return len;
}

size_t PacketBuilder::buildIdentifyResponse(uint8_t* buffer, size_t maxLen) {
    // Simplified example identify response
    const char* deviceName = "iPod5,1";
    size_t nameLen = strlen(deviceName);

    if (nameLen + 3 > maxLen) return 0;

    buffer[0] = 0x06;  // Packet type
    buffer[1] = 0x02;  // Command
    buffer[2] = (uint8_t)nameLen;
    memcpy(&buffer[3], deviceName, nameLen);

    Debug::println("PacketBuilder: Built identify response");
    return 3 + nameLen;
}

size_t PacketBuilder::buildAck(uint8_t* buffer, uint8_t command, size_t maxLen) {
    if (maxLen < 3) return 0;
    buffer[0] = 0x04;  // ACK packet type
    buffer[1] = command;
    buffer[2] = 0x01;  // Success
    Debug::println("PacketBuilder: Built ACK");
    return 3;
}

size_t PacketBuilder::buildNowPlaying(uint8_t* buffer, size_t maxLen, const char* artist, const char* album, const char* title) {
    // Simplified NowPlaying packet
    // Format: [PacketType][Command][ArtistLen][Artist][AlbumLen][Album][TitleLen][Title]
    size_t offset = 0;
    size_t artistLen = strlen(artist);
    size_t albumLen = strlen(album);
    size_t titleLen = strlen(title);

    size_t totalLen = 2 + 1 + artistLen + 1 + albumLen + 1 + titleLen;
    if (totalLen > maxLen) return 0;

    buffer[offset++] = 0x07;  // NowPlaying packet type (example)
    buffer[offset++] = 0x03;  // Command (example)

    buffer[offset++] = (uint8_t)artistLen;
    memcpy(&buffer[offset], artist, artistLen);
    offset += artistLen;

    buffer[offset++] = (uint8_t)albumLen;
    memcpy(&buffer[offset], album, albumLen);
    offset += albumLen;

    buffer[offset++] = (uint8_t)titleLen;
    memcpy(&buffer[offset], title, titleLen);
    offset += titleLen;

    Debug::println("PacketBuilder: Built NowPlaying");
    return offset;
}
