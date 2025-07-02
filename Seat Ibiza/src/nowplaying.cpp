#include "NowPlaying.h"
#include "Debug.h"
#include "PacketBuilder.h"

NowPlaying::NowPlaying() {}

void NowPlaying::begin(BluetoothAudio* btAudio) {
    _btAudio = btAudio;
    _playing = true;
    _lastUpdate = millis();
    _trackIndex = 0;
}

void NowPlaying::loop() {
    if (!_btAudio) return;

    unsigned long now = millis();
    if (now - _lastUpdate > 30000) { // alle 30 Sekunden Track wechseln
        _trackIndex = (_trackIndex + 1) % _titles.size();
        _playing = !_playing; // Status toggle als Beispiel
        sendNowPlaying();
        _lastUpdate = now;
    }
}

void NowPlaying::sendNowPlaying() {
    if (!_btAudio) return;

    String title = _titles[_trackIndex];
    String artist = _artists[_trackIndex];
    Debug::info("Sending NowPlaying: %s - %s, playing: %d", title.c_str(), artist.c_str(), _playing);

    // Konvertiere String in std::string für PacketBuilder
    std::string stitle = std::string(title.c_str());
    std::string sartist = std::string(artist.c_str());

    auto pkt = PacketBuilder::buildNowPlayingPacket(stitle, sartist, _playing);
    _btAudio->sendPacket(pkt);
}
