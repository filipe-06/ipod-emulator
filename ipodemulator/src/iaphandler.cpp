#include "IAPHandler.h"
#include "Debug.h"

// Example device info (realistic, 5G iPod)
static const uint8_t iPodSerial[] = { '9','A','B','C','D','E','F','1','2','3','4','5','6','7' };
static const uint8_t iPodName[] = "iPod5,1";

void IAPHandler::begin() {
    Debug::println("IAPHandler started");
    handshakeDone = false;
    bufferLen = 0;
}

void IAPHandler::loop() {
    static uint8_t buffer[64];
    static size_t bufferIndex = 0;

    // Read bytes as they arrive
    while (Serial.available() > 0) {
        uint8_t byte = Serial.read();
        buffer[bufferIndex++] = byte;

        // For simplicity, assume packet length is known or use a delimiter
        // For iAP, packets usually have structure but for demo assume fixed length or timeout

        if (bufferIndex >= 3) { // minimal packet length example
            handlePacket(buffer, bufferIndex);
            bufferIndex = 0; // reset buffer after processing
        }
    }
    if (!handshakeDone) {
        sendHandshake();
        handshakeDone = true;
    }
    // Process incoming packets here...
}

void IAPHandler::sendHandshake() {
    Debug::println("Sending handshake packets");
    // Construct and send iAP handshake packets here
    // Use Serial to communicate with Kenwood headunit
    // For example:
    uint8_t handshakePacket[] = { 0x02, 0x01, 0x01 }; // Sample
    Serial.write(handshakePacket, sizeof(handshakePacket));
    logResponse("Sent Handshake", handshakePacket, sizeof(handshakePacket));
}

void IAPHandler::sendAck(uint8_t command) {
    uint8_t ack[] = { 0x04, command, 0x01 };
    Serial.write(ack, sizeof(ack));
    logResponse("Sent ACK", ack, sizeof(ack));
}

void IAPHandler::sendIdentifyResponse() {
    // Build and send identify response packet with real iPod info
    // (this is simplified, real iPod packets are complex)
    uint8_t identify[] = { 0x06, 0x02, 0x00 }; // placeholder
    Serial.write(identify, sizeof(identify));
    logResponse("Sent Identify Response", identify, sizeof(identify));
}

void IAPHandler::sendNowPlaying() {
    // Send NowPlaying metadata
    uint8_t nowPlaying[] = { /*...*/ };
    Serial.write(nowPlaying, sizeof(nowPlaying));
    logResponse("Sent NowPlaying", nowPlaying, sizeof(nowPlaying));
}

void IAPHandler::logResponse(const char* prefix, const uint8_t* data, size_t len) {
    Debug::print(prefix);
    Debug::print(": ");
    for (size_t i = 0; i < len; ++i) {
        if (data[i] < 0x10) Debug::print("0");
char buf[3];
sprintf(buf, "%X", data[i]);
Debug::print(buf);
Debug::print(" ");

    }
    Debug::println();
}
void IAPHandler::handlePacket(const uint8_t* data, size_t length) {
    Debug::print("Received packet: ");
    for (size_t i = 0; i < length; ++i) {
        if (data[i] < 0x10) Debug::print("0");
        Debug::print(data[i], HEX);
        Debug::print(" ");
    }
    Debug::println();

    if (length < 2) {
        Debug::println("Packet too short");
        return;
    }

    uint8_t command = data[0];
    uint8_t subCommand = data[1];

    switch (command) {
        case 0x02:  // Handshake commands
            if (subCommand == 0x01) {
                Debug::println("Handshake start received");
                sendAck(command);
                sendIdentifyResponse();
            }
            break;

        case 0x04:  // ACK from head unit
            Debug::println("ACK received");
            // Could handle session confirmation here
            break;

        case 0x06:  // Identify related commands
            if (subCommand == 0x02) {
                Debug::println("Identify request received");
                sendIdentifyResponse();
            }
            break;

        case 0x0A: // NowPlaying request or similar
            Debug::println("NowPlaying request");
            sendNowPlaying();
            break;

        default:
            Debug::print("Unknown command: ");
            Debug::println(command, HEX);
            break;
    }
}