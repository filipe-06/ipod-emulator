#include "ipodemulator.h"

IPodEmulator::IPodEmulator(HardwareSerial& serial) : _serial(serial) {}

void IPodEmulator::begin() {
    _packetIndex = 0;
    _state = WAIT_SHAKE;
}

void IPodEmulator::loop() {
    // Sende Heartbeat alle 3 Sekunden, wenn verbunden
    if (_state == RUNNING && millis() - _lastHeartbeat > 3000) {
        pktHeartbeat();
        _lastHeartbeat = millis();
    }
}

void IPodEmulator::handleByte(uint8_t byte) {
    if (_packetIndex >= MAX_PACKET_SIZE) {
        _packetIndex = 0;
    }
    _packetBuffer[_packetIndex++] = byte;

    // Beispiel: Warte mindestens 2 Bytes und parsen
    if (_packetIndex >= 2) {
        parsePacket();
    }
}

void IPodEmulator::parsePacket() {
    // Minimaler Paketcheck (Anpassung je nach Protokoll nötig)
    if (_packetIndex < 2) return;

    processPacket(_packetBuffer, _packetIndex);

    _packetIndex = 0;
}

void IPodEmulator::processPacket(const uint8_t* data, int len) {
    if (len < 2) return;

    uint8_t cmd = data[0];
    uint8_t subCmd = data[1];

    Serial.printf("Empfangen CMD=0x%02X SUBCMD=0x%02X LEN=%d\n", cmd, subCmd, len);

    switch (_state) {
        case WAIT_SHAKE:
            if (cmd == 0x00 && subCmd == 0x00) {
                pktHandshakeACK();
                _state = SEND_SHAKE_ACK;
                debugPrint("WAIT_SHAKE -> SEND_SHAKE_ACK");
            }
            break;

        case SEND_SHAKE_ACK:
            if (cmd == 0x01 && subCmd == 0x00) {
                sendACK(cmd, subCmd, 0x00);
                pktIdentifyWithServiceID();
                _state = SEND_IDENTIFY;
                debugPrint("SEND_SHAKE_ACK -> SEND_IDENTIFY");
            }
            break;

        case SEND_IDENTIFY:
            if (cmd == 0x04 && subCmd == 0x01 && len > 2 && data[2] == 0x01) {
                sendACK(cmd, subCmd, 0x01);
                pktAvailableServices();
                _state = RUNNING;
                debugPrint("SEND_IDENTIFY -> RUNNING");
            }
            break;

        case RUNNING:
            // Immer ACK senden, je nach Cmd kann man noch erweitern
            sendACK(cmd, subCmd, 0x01);
            break;

        default:
            break;
    }
}

void IPodEmulator::sendACK(uint8_t cmd, uint8_t subCmd, uint8_t param) {
    uint8_t buf[4] = {0x02, cmd, subCmd, param};
    _serial.write(buf, 4);
    Serial.printf("ACK gesendet CMD=0x%02X SUBCMD=0x%02X PARAM=0x%02X\n", cmd, subCmd, param);
}

void IPodEmulator::pktHandshakeACK() {
    // Beispiel: Handshake ACK Paket aus deinem Code
    uint8_t buf[] = {0x02, 0x00, 0x00, 0x00};
    _serial.write(buf, sizeof(buf));
    Serial.println("Handshake ACK gesendet");
}

void IPodEmulator::pktIdentifyWithServiceID() {
    // Original aus deinem Repo, z.B. aus ipodemulator.cpp
    const uint8_t pkt[] = {
        0x0D, // CMD IdentifyWithServiceID (Beispiel)
        // Strings mit Null-Terminatoren:
        'i','P','o','d',' ','5','G',0x00,
        '1','.','3',0x00,
        'S','N','1','2','3','4','5','6',0x00,
        'A','p','p','l','e',' ','I','n','c','.',0x00
    };
    _serial.write(pkt, sizeof(pkt));
    Serial.println("IdentifyWithServiceID gesendet");
}

void IPodEmulator::pktAvailableServices() {
    const uint8_t pkt[] = {
        0x13, // CMD AvailableServices
        'c','o','m','.','a','p','p','l','e','.','n','o','w','p','l','a','y','i','n','g',0x00,
        'c','o','m','.','a','p','p','l','e','.','c','o','m','m','s',0x00,
        'c','o','m','.','a','p','p','l','e','.','a','v','r','e','m','o','t','e',0x00
    };
    _serial.write(pkt, sizeof(pkt));
    Serial.println("AvailableServices gesendet");
}

void IPodEmulator::pktHeartbeat() {
    uint8_t hb = 0x0D;
    _serial.write(&hb, 1);
    Serial.println("Heartbeat gesendet");
}

void IPodEmulator::debugPrint(const char* msg) {
    Serial.println(msg);
}
