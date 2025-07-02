#include <Arduino.h>
#include "BluetoothAudio.h"
#include "SessionManager.h"
#include "NowPlaying.h"
#include "Debug.h"

BluetoothAudio* btAudio;
SessionManager* sessionManager;
NowPlaying* nowPlaying;

void setup() {
  Serial.begin(115200);
  Debug::begin(Serial);
  Debug::info("iPod Emulator starting...");

  sessionManager = new SessionManager();
  nowPlaying = new NowPlaying();
  btAudio = new BluetoothAudio(sessionManager, nowPlaying);

  sessionManager->begin(btAudio);
  nowPlaying->begin(btAudio);
  btAudio->begin();
}

void loop() {
  btAudio->loop();
  sessionManager->loop();
  nowPlaying->loop();
}
