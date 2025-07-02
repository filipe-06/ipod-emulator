#pragma once

#include <Arduino.h>

class IPodEmulator {
public:
    explicit IPodEmulator(HardwareSerial& serial);

    void begin();
    void loop();
    void handleByte(uint8_t byte);

private:
    HardwareSerial& _serial;

    static const int MAX_PACKET_SIZE = 256;
    uint8_t _packetBuffer[MAX_PACKET_SIZE];
    int _packetIndex = 0;

    enum State {
        WAIT_SHAKE,
        SEND_SHAKE_ACK,
        SEND_IDENTIFY,
        WAIT_SESSION_OPEN,
        SEND_SESSION_ACK,
        SEND_AVAILABLE_SERVICES,
        RUNNING
    };

    State _state = WAIT_SHAKE;
    unsigned long _lastHeartbeat = 0;

    void parsePacket();
    void processPacket(const uint8_t* data, int len);

    // Deine originalen Paketfunktionen:
    void pktIdentifyWithServiceID();
    void pktSessionACK();
    void pktHandshakeACK();
    void pktAvailableServices();
    void pktHeartbeat();

    void sendACK(uint8_t cmd, uint8_t subCmd, uint8_t param);

    void debugPrint(const char* msg);
};
