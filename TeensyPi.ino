#include <MIDI.h>

void setup() {
  // put your setup code here, to run once:
  // External MIDI would use pins 0 (Rx) and 1 (Tx)
  pinMode(2, INPUT_PULLUP);     // MIDI Input Switch
  pinMode(3, INPUT_PULLUP);     // Switch One               
  pinMode(4, INPUT_PULLUP);     // Switch One
  pinMode(5, INPUT_PULLUP);     // Switch Two
  pinMode(6, INPUT_PULLUP);     // Switch Two

  analogReadRes(7);             // Read Resolution set to 7-bit, 0-127; the range MIDI messages use.
  analogReadAveraging(4);       // Average four readings for a more stable reading.
}

void loop() {
  // If MIDI switch is off use Pitch knob, else use MIDI input.
  if (digitalRead(2) == LOW) {
    usbMIDI.sendControlChange(0, analogRead(0), 1); // Pitch
  } else {
    if (MIDI.read()) {
      byte type = MIDI.getType();
      switch (type) {
        case NoteOn:
          usbMIDI.sendNoteOn(MIDI.getData1(), MIDI.getData2(), MIDI.getChannel());
        case NoteOff:
          usbMIDI.sendNoteOff(MIDI.getData1(), MIDI.getData2(), MIDI.getChannel());
      }
    }
  }
  usbMIDI.sendControlChange(1, analogRead(1), 1); // Unison
  usbMIDI.sendControlChange(2, analogRead(2), 1); // LFO Rate
  usbMIDI.sendControlChange(3, analogRead(3), 1); // LFO Amount
  usbMIDI.sendControlChange(4, analogRead(4), 1); // Filter Freq.
  // Pot 5 and 7 were installed the wrong way round, too lazy to switch.
  usbMIDI.sendControlChange(5, analogRead(7), 1); // Scale Root
  usbMIDI.sendControlChange(6, analogRead(6), 1); // Attack
  usbMIDI.sendControlChange(7, analogRead(5), 1); // Decay
  usbMIDI.sendControlChange(8, analogRead(8), 1); // Sustain
  usbMIDI.sendControlChange(9, analogRead(9), 1); // Release

  if (digitalRead(3) == HIGH && digitalRead(4) == LOW) {
    usbMIDI.sendControlChange(10, 127, 1);
    usbMIDI.sendControlChange(11, 0, 1);
  }
  else if (digitalRead(3) == LOW && digitalRead(4) == HIGH) {
    usbMIDI.sendControlChange(10, 0, 1);
    usbMIDI.sendControlChange(11, 127, 1);
  }
  else {
    usbMIDI.sendControlChange(10, 0, 1);
    usbMIDI.sendControlChange(11, 0, 1);
  }

  if (digitalRead(5) == HIGH && digitalRead(6) == LOW) {
    usbMIDI.sendControlChange(12, 127, 1);
    usbMIDI.sendControlChange(13, 0, 1);
  }
  else if (digitalRead(5) == LOW && digitalRead(6) == HIGH) {
    usbMIDI.sendControlChange(12, 0, 1);
    usbMIDI.sendControlChange(13, 127, 1);
  }
  else {
    usbMIDI.sendControlChange(12, 0, 1);
    usbMIDI.sendControlChange(13, 0, 1);
  }
  // Delay to stop MIDI message flood.
  delay(100);  
}
