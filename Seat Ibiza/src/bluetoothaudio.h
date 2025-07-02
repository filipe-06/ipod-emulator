#ifndef BLUETOOTHAUDIO_H
#define BLUETOOTHAUDIO_H

#include <Arduino.h>
#include <vector>
#include <functional>

class SessionManager;
class NowPlaying;

class BluetoothAudio {
public:
    BluetoothAudio(SessionManager* session = nullptr, NowPlaying* nowPlaying = nullptr);
    void begin();
    void loop();

    void sendPacket(const std::vector<uint8_t>& pkt);

private:
    HardwareSerial& _serial = Serial2; // Beispiel: UART2 für iPod-Daten
    SessionManager* _sessionManager = nullptr;
    NowPlaying* _nowPlaying = nullptr;

    std::vector<uint8_t> _rxBuffer;

    void processIncoming();
    void onPacketReceived(const std::vector<uint8_t>& data);
};

#endif
