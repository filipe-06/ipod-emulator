#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <Arduino.h>

class SessionManager {
public:
    void begin();
    void handlePacket(const uint8_t* data, size_t len);
    bool isSessionOpen() const;

private:
    void processHandshake(const uint8_t* data, size_t len);
    void processSessionOpen(const uint8_t* data, size_t len);
    void sendSessionAck();

    bool sessionOpen = false;
};

#endif
