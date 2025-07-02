#ifndef NOW_PLAYING_H
#define NOW_PLAYING_H

#include <Arduino.h>
#include <vector>
#include "BluetoothAudio.h"

class BluetoothAudio; // Vorwärtsdeklaration

class NowPlaying {
public:
    NowPlaying();
    void begin(BluetoothAudio* btAudio);
    void loop();

    void sendNowPlaying();

private:
    BluetoothAudio* _btAudio = nullptr;

    unsigned long _lastUpdate = 0;
    bool _playing = false;
    int _trackIndex = 0;

    const std::vector<String> _titles = {
        "Track One",
        "Track Two",
        "Track Three"
    };
    const std::vector<String> _artists = {
        "Artist A",
        "Artist B",
        "Artist C"
    };
};

#endif
