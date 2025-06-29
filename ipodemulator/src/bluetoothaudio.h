#ifndef BLUETOOTHAUDIO_H
#define BLUETOOTHAUDIO_H

#include <BluetoothA2DPSink.h>

class BluetoothAudio {
public:
    BluetoothAudio();
    void start();
    void stop();

private:
    BluetoothA2DPSink a2dp_sink;
};

#endif // BLUETOOTHAUDIO_H
