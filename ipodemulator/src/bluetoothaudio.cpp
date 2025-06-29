#include "BluetoothAudio.h"
#include "Debug.h"

static BluetoothAudio *self = nullptr;

static void avrc_metadata_callback(uint8_t id, const uint8_t *data) {
    if (!self) return;
    String value = (const char *)data;
    switch (id) {
        case ESP_AVRC_MD_ATTR_TITLE:  self->currentMetadata.title = value; break;
        case ESP_AVRC_MD_ATTR_ARTIST: self->currentMetadata.artist = value; break;
        case ESP_AVRC_MD_ATTR_ALBUM:  self->currentMetadata.album = value; break;
    }
}

static void avrc_connection_state_callback(bool connected) {
    if (!self) return;
    self->connected = connected;
    Debug::println(connected ? "AVRCP connected" : "AVRCP disconnected");
}

static void avrc_rn_playstatus_callback(uint8_t event_id, uint8_t *p_data, uint32_t data_len) {
    if (!self || event_id != ESP_AVRC_RN_PLAY_STATUS_CHANGE || data_len == 0) return;
    uint8_t status = p_data[0];
    self->playing = (status == ESP_AVRC_PLAY_STATUS_PLAYING);
    Debug::printf("Play status: %d\n", status);
}

void BluetoothAudio::begin() {
    self = this;
    a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
    a2dp_sink.set_avrc_connection_state_callback(avrc_connection_state_callback);
    a2dp_sink.set_avrc_rn_playstatus_callback(avrc_rn_playstatus_callback);

    // Use AudioTools I2S backend for external DAC on pins 25/26/21
    AudioStream *i2s = new I2SStream();  
    a2dp_sink.set_output(*i2s);
    a2dp_sink.start("ESP32-iPod-Emu");

    Debug::println("BluetoothAudio A2DP+AVRCP started");
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
