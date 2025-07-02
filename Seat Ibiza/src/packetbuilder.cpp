#include "PacketBuilder.h"

// Session ACK: 0x02 0x01 0x01
std::vector<uint8_t> PacketBuilder::buildSessionAck() {
    return {0x02, 0x01, 0x01};
}

// Identify packet with Apple services strings
std::vector<uint8_t> PacketBuilder::buildIdentifyPacket() {
    std::vector<uint8_t> pkt;
    const std::vector<std::string> services = {
        "com.apple.iPod",
        "com.apple.iPod.ipod-accessory",
        "com.apple.iPod.media-player",
        "com.apple.iPod.nowplaying",
        "com.apple.iPod.music",
        "com.apple.iPod.battery",
        "com.apple.iPod.deviceinfo",
        "com.apple.iPod.authentication"
    };
    pkt.push_back(0x02);
    pkt.push_back(static_cast<uint8_t>(services.size()));
    for (const auto& s : services) {
        pkt.push_back(static_cast<uint8_t>(s.length()));
        pkt.insert(pkt.end(), s.begin(), s.end());
    }
    return pkt;
}

// NowPlaying with title, artist and playing flag
std::vector<uint8_t> PacketBuilder::buildNowPlayingPacket(const std::string& title, const std::string& artist, bool playing) {
    std::vector<uint8_t> pkt;
    pkt.push_back(0x06);
    pkt.push_back(static_cast<uint8_t>(title.length()));
    pkt.insert(pkt.end(), title.begin(), title.end());
    pkt.push_back(static_cast<uint8_t>(artist.length()));
    pkt.insert(pkt.end(), artist.begin(), artist.end());
    pkt.push_back(playing ? 1 : 0);
    return pkt;
}

// Heartbeat packet (type 0x07)
std::vector<uint8_t> PacketBuilder::buildHeartbeat() {
    return {0x07, 0x00, 0x00};
}
