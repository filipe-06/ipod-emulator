#include "BluetoothAudio.h"
#include <driver/i2s.h>
#include <esp_log.h>

static const char *TAG = "BluetoothAudio";

BluetoothAudio::BluetoothAudio() {
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = 44100,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S,
        .intr_alloc_flags = 0,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear = true,
        .fixed_mclk = 0
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = 25,
        .ws_io_num = 26,
        .data_out_num = 21,
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    ESP_ERROR_CHECK(i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL));
    ESP_ERROR_CHECK(i2s_set_pin(I2S_NUM_0, &pin_config));
}

void BluetoothAudio::start() {
    ESP_LOGI(TAG, "Starting A2DP sink");
    a2dp_sink.start("ESP32-iPod-Emu");
}

void BluetoothAudio::stop() {
    ESP_LOGI(TAG, "Stopping A2DP sink");
    a2dp_sink.stop();
}
