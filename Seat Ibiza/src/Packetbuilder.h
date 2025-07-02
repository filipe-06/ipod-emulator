#ifndef PACKET_BUILDER_H
#define PACKET_BUILDER_H

#include <vector>
#include <string>

class PacketBuilder {
public:
    static std::vector<uint8_t> buildSessionAck();
    static std::vector<uint8_t> buildIdentifyPacket();
    static std::vector<uint8_t> buildNowPlayingPacket(const std::string& title, const std::string& artist, bool playing);
    static std::vector<uint8_t> buildHeartbeat();
};

#endif
