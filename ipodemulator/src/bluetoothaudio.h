#ifndef BLUETOOTH_AUDIO_H
#define BLUETOOTH_AUDIO_H

#include <BluetoothA2DPSink.h>

struct Metadata {
    String title;
    String artist;
    String album;
};

class BluetoothAudio {
public:
    void begin();
    Metadata getMetadata() const;
    bool isConnected() const;
    bool isPlaying() const;

private:
    BluetoothA2DPSink a2dp_sink;
    Metadata currentMetadata;
    bool connected = false;
    bool playing = false;
};

#endif // BLUETOOTH_AUDIO_H
