#include "BluetoothAudio.h"
#include "Debug.h"
#include "SessionManager.h"
#include "NowPlaying.h"

BluetoothAudio::BluetoothAudio(SessionManager* session, NowPlaying* nowPlaying) 
    : _sessionManager(session), _nowPlaying(nowPlaying) {}

void BluetoothAudio::begin() {
    _serial.begin(115200, SERIAL_8N1, 16, 17); // GPIO16 RX, GPIO17 TX Beispiel
    Debug::info("BluetoothAudio UART started");
}

void BluetoothAudio::loop() {
    processIncoming();
}

void BluetoothAudio::processIncoming() {
    while (_serial.available()) {
        uint8_t b = _serial.read();
        _rxBuffer.push_back(b);

        // Beispiel: Paketende erkennen (terminiert mit 0x00?)
        if (b == 0x00) {
            Debug::info("Packet received, size=%d", (int)_rxBuffer.size());
            if (_sessionManager) {
                _sessionManager->handlePacket(_rxBuffer);
            }
            _rxBuffer.clear();
        }
    }
}

void BluetoothAudio::sendPacket(const std::vector<uint8_t>& pkt) {
    if (pkt.empty()) return;

    Debug::info("Sending packet, size=%d", (int)pkt.size());

    for (auto b : pkt) {
        _serial.write(b);
    }
    _serial.write(0x00); // Packet Ende markieren
    _serial.flush();
}
