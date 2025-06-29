#include "BluetoothAudio.h"

static BluetoothAudio *self = nullptr;

void BluetoothAudio::begin() {
    self = this;

    a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
    a2dp_sink.set_avrc_connection_state_callback(avrc_connection_state_callback, this);
    a2dp_sink.set_avrc_playback_state_callback(avrc_playback_callback, this);

    a2dp_sink.start("ESP32-iPod-Emu");
}

void BluetoothAudio::setMetadata(const String &title, const String &artist, const String &album) {
    currentMetadata.title = title;
    currentMetadata.artist = artist;
    currentMetadata.album = album;
}

Metadata BluetoothAudio::getMetadata() const {
    return currentMetadata;
}

bool BluetoothAudio::isConnected() const {
    return connected;
}

bool BluetoothAudio::isPlaying() const {
    return playing;
}

void BluetoothAudio::avrc_metadata_callback(uint8_t id, const uint8_t *data) {
    if (!self) return;
    String value = String((const char *)data);
    switch (id) {
        case ESP_AVRC_MD_ATTR_TITLE:  self->currentMetadata.title  = value; break;
        case ESP_AVRC_MD_ATTR_ARTIST: self->currentMetadata.artist = value; break;
        case ESP_AVRC_MD_ATTR_ALBUM:  self->currentMetadata.album  = value; break;
    }
}

void BluetoothAudio::avrc_connection_state_callback(esp_a2d_connection_state_t state, void *user_data) {
    BluetoothAudio *instance = static_cast<BluetoothAudio *>(user_data);
    if (!instance) return;
    instance->connected = (state == ESP_A2D_CONNECTION_STATE_CONNECTED);
}

void BluetoothAudio::avrc_playback_callback(esp_avrc_playback_stat_t state, void *user_data) {
    BluetoothAudio *instance = static_cast<BluetoothAudio *>(user_data);
    if (!instance) return;
    instance->playing = (state == ESP_AVRC_PLAYBACK_PLAYING);
}
