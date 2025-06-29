#include "SessionManager.h"
#include "Debug.h"

void SessionManager::begin() {
    sessionOpen = false;
    Debug::println("SessionManager started");
}

void SessionManager::handlePacket(const uint8_t* data, size_t len) {
    if (len == 0) return;

    uint8_t command = data[0];

    switch (command) {
    case 0x02: // Handshake command example
        processHandshake(data, len);
        break;
    case 0x04: // Session open example
        processSessionOpen(data, len);
        break;
    default:
        Debug::print("SessionManager: Unknown command ");
        Debug::println(command, HEX);
        break;
    }
}

void SessionManager::processHandshake(const uint8_t* data, size_t len) {
    Debug::println("SessionManager: Handshake received");
    // respond accordingly or forward to IAPHandler
}

void SessionManager::processSessionOpen(const uint8_t* data, size_t len) {
    Debug::println("SessionManager: Session open request received");
    sessionOpen = true;
    sendSessionAck();
}

void SessionManager::sendSessionAck() {
    uint8_t ack[] = { 0x04, 0x01, 0x01 }; // ACK session open
    Serial.write(ack, sizeof(ack));
    Debug::println("SessionManager: Session ACK sent");
}

bool SessionManager::isSessionOpen() const {
    return sessionOpen;
}
