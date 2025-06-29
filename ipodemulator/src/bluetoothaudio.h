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
    void setMetadata(const String &title, const String &artist, const String &album);
    Metadata getMetadata() const;
    bool isConnected() const;
    bool isPlaying() const;

private:
    BluetoothA2DPSink a2dp_sink;
    Metadata currentMetadata;
    bool connected = false;
    bool playing = false;

    static void avrc_metadata_callback(uint8_t id, const uint8_t *data);
    static void avrc_connection_state_callback(esp_a2d_connection_state_t state, void *user_data);
    static void avrc_playback_callback(esp_avrc_playback_stat_t state, void *user_data); // ✅ Fixed type
};

#endif // BLUETOOTH_AUDIO_H
