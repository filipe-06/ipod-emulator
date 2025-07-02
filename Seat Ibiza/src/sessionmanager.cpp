#include "SessionManager.h"
#include "Debug.h"
#include "PacketBuilder.h"

SessionManager::SessionManager() {}

void SessionManager::begin(BluetoothAudio* btAudio) {
    _btAudio = btAudio;
    _sessionOpen = false;
}

void SessionManager::loop() {
    // Hier könnte Timeout-Handling oder Wiederholungen kommen
}

void SessionManager::handlePacket(const std::vector<uint8_t>& data) {
    if (data.size() < 1) return;

    uint8_t cmd = data[0];
    Debug::info("SessionManager received packet with cmd: 0x%02X", cmd);

    if (cmd == 0x04) {  // Session Open Request
        Debug::info("Session Open Request received");
        _sessionOpen = true;
        sendSessionAck();
        sendIdentify();
    } else if (cmd == 0x05) {  // Session Close Request
        Debug::info("Session Close Request received");
        _sessionOpen = false;
    }
}

void SessionManager::sendSessionAck() {
    if (_btAudio) {
        auto pkt = PacketBuilder::buildSessionAck();
        _btAudio->sendPacket(pkt);
        Debug::info("Sent Session ACK");
    }
}

void SessionManager::sendIdentify() {
    if (_btAudio) {
        auto pkt = PacketBuilder::buildIdentifyPacket();
        _btAudio->sendPacket(pkt);
        Debug::info("Sent Identify packet");
    }
}
