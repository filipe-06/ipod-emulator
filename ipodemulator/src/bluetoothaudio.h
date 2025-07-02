#pragma once

#include <BluetoothA2DPSink.h>

struct Metadata {
    String title;
    String artist;
    String album;
};

class BluetoothAudio {
public:
    void begin();
    Metadata currentMetadata;

private:
    static void avrc_metadata_callback(uint8_t id, const uint8_t* data);
};
