#ifndef BLUETOOTH_AUDIO_H
#define BLUETOOTH_AUDIO_H

#include <Arduino.h>
#include <BluetoothA2DPSink.h>
#include <BluetoothA2DPSource.h>

struct Metadata {
    String title;
    String artist;
    String album;
};

class BluetoothAudio {
public:
    void begin();

    Metadata getMetadata() const { return currentMetadata; }
    bool isConnected() const { return connected; }
    bool isPlaying() const { return playing; }

    Metadata currentMetadata;
    bool connected = false;
    bool playing = false;

private:
    BluetoothA2DPSink a2dp_sink;
};

#endif // BLUETOOTH_AUDIO_H
