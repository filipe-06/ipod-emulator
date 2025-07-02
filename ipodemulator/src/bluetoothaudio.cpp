#include "BluetoothAudio.h"
#include "Debug.h"
#include "AudioTools.h"

I2SStream i2s;
BluetoothA2DPSink a2dp_sink(i2s);

// Lokale Definitionen, falls die Library sie nicht enthält
#define ESP_AVRC_MD_ATTR_TITLE 0x01
#define ESP_AVRC_MD_ATTR_ARTIST 0x02
#define ESP_AVRC_MD_ATTR_ALBUM 0x04

static BluetoothAudio *self = nullptr;

// AVRCP-Metadaten Callback
static void avrc_metadata_callback(uint8_t id, const uint8_t *data) {
    if (!self) return;
    String value = (const char*)data;
    switch (id) {
        case ESP_AVRC_MD_ATTR_TITLE:  self->currentMetadata.title = value; break;
        case ESP_AVRC_MD_ATTR_ARTIST: self->currentMetadata.artist = value; break;
        case ESP_AVRC_MD_ATTR_ALBUM:  self->currentMetadata.album = value; break;
    }
    Debug::print("Metadata updated: ID=");
    Debug::print(id);
    Debug::print(", Value=");
    Debug::println(value.c_str());
}


// BluetoothAudio initialisieren
void BluetoothAudio::begin() {
    self = this;

    a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
    a2dp_sink.start("ESP32-iPod-Emu");

    Debug::println("BluetoothAudio started");
}
