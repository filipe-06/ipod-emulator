#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <Arduino.h>
#include <functional>
#include <vector>
#include "BluetoothAudio.h"

class BluetoothAudio; // Vorwärtsdeklaration

class SessionManager {
public:
    SessionManager();
    void begin(BluetoothAudio* btAudio);
    void loop();

    void handlePacket(const std::vector<uint8_t>& data);
    void sendSessionAck();
    void sendIdentify();

private:
    BluetoothAudio* _btAudio = nullptr;
    bool _sessionOpen = false;
};

#endif
