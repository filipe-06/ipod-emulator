#ifndef IAPHANDLER_H
#define IAPHANDLER_H

#include <Arduino.h>

class IAPHandler {
public:
    void begin();
    void loop();
    void handlePacket(const uint8_t* data, size_t length);


private:
    void processIncomingPacket();
    void sendHandshake();
    void sendAck(uint8_t command);
    void sendIdentifyResponse();
    void sendNowPlaying();

    uint8_t buffer[256];
    size_t bufferLen = 0;
    unsigned long lastHeartbeat = 0;
    bool handshakeDone = false;

    void logResponse(const char* prefix, const uint8_t* data, size_t len);
};

#endif
