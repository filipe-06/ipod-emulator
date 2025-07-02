#include "BluetoothAudio.h"
#include "BluetoothA2DPSink.h"
#include <driver/i2s.h>
#include "Debug.h"  // Optional für Logging

static BluetoothA2DPSink a2dp_sink;
static BluetoothAudio* self = nullptr;

// IDs, falls nicht im SDK enthalten
#ifndef ESP_AVRC_MD_ATTR_TITLE
#define ESP_AVRC_MD_ATTR_TITLE 0x01
#define ESP_AVRC_MD_ATTR_ARTIST 0x02
#define ESP_AVRC_MD_ATTR_ALBUM 0x04
#endif

void BluetoothAudio::avrc_metadata_callback(uint8_t id, const uint8_t* data) {
    if (!self || !data) return;
    String value = String((const char*)data);
    switch (id) {
        case ESP_AVRC_MD_ATTR_TITLE:
            self->currentMetadata.title = value;
            break;
        case ESP_AVRC_MD_ATTR_ARTIST:
            self->currentMetadata.artist = value;
            break;
        case ESP_AVRC_MD_ATTR_ALBUM:
            self->currentMetadata.album = value;
            break;
    }
    Debug::print("AVRCP Metadata: ");
    Debug::print("ID=");
    Debug::print(id);
    Debug::print(", Value=");
}

void BluetoothAudio::begin() {
    self = this;

    // I2S-Pin-Konfiguration für externen DAC
    i2s_pin_config_t i2s_pins = {
        .bck_io_num = 26,    // BCLK
        .ws_io_num  = 25,    // LRCK
        .data_out_num = 21,  // DATA
        .data_in_num = -1    // kein Eingang
    };

    a2dp_sink.set_pin_config(i2s_pins);
    a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
    a2dp_sink.start("Seat Ibiza 6L");

    Debug::println("BluetoothAudio gestartet.");
}
