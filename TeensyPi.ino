#include <MIDI.h>

void setup() {
  // put your setup code here, to run once:
  MIDI.begin(MIDI_CHANNEL_OMNI);                                // Initialise the MIDI library (seperate to usbMIDI)
  // SWITCHES
  pinMode(1, INPUT_PULLUP);                                     // Filter Type
  pinMode(2, INPUT_PULLUP);                                     // Filter Type
  pinMode(3, INPUT_PULLUP);                                     // Modulation Destination
  pinMode(4, INPUT_PULLUP);                                     // Modulation Destination
  analogReadRes(7);                                             // Analog read resolution defaults to 10 bits, forcing 7 bit resolution gives us usable MIDI CC values
  analogReadAveraging(4);                                       // Average four readings from each input to get a more consistant reading
}

void loop() {
  // put your main code here, to run repeatedly:
  usbMIDI.sendControlChange(11, 0, 1);                          // Turn off notein and velocity in pd patch
  usbMIDI.sendControlChange(0, analogRead(0), 1);               // Pitch knob
  usbMIDI.sendControlChange(1, analogRead(1), 1);               // Unison knob
  usbMIDI.sendControlChange(2, analogRead(2), 1);               // Filter Frequency
  usbMIDI.sendControlChange(3, analogRead(3), 1);               // LFO 1 Rate
  usbMIDI.sendControlChange(4, analogRead(4), 1);               // LFO 1 Amount
  usbMIDI.sendControlChange(5, analogRead(5), 1);               // Attack
  usbMIDI.sendControlChange(6, analogRead(6), 1);               // Decay
  usbMIDI.sendControlChange(7, analogRead(7), 1);               // Sustain
  usbMIDI.sendControlChange(8, analogRead(8), 1);               // Release
  usbMIDI.sendControlChange(127, analogRead(9), 1);             // Master Gain
  if (digitalRead(1) == HIGH && digitalRead(2) == LOW) {        // Hipass Filter ON
    usbMIDI.sendControlChange(9, 1, 1);
    usbMIDI.sendControlChange(10, 0, 1);
  }
  else if (digitalRead(1) == LOW && digitalRead(2) == HIGH) {   // Lowpass Filter ON
    usbMIDI.sendControlChange(9, 0, 1);
    usbMIDI.sendControlChange(10, 1, 1); 
  }
  else {                                                        // Bandpass Filter ON
    usbMIDI.sendControlChange(9, 0, 1);
    usbMIDI.sendControlChange(10, 0, 1);
  }
  if (digitalRead(3) == HIGH && digitalRead(4) == LOW) {        // Filter Freq Modulation
    usbMIDI.sendControlChange(12, 1, 1);
    usbMIDI.sendControlChange(13, 0, 1);
  }
  else if (digitalRead(3) == LOW && digitalRead(4) == HIGH) {   // Pitch Modulation
    usbMIDI.sendControlChange(12, 0, 1);
    usbMIDI.sendControlChange(13, 1, 1); 
  }
  else {                                                        // No modulation
    usbMIDI.sendControlChange(12, 0, 1);
    usbMIDI.sendControlChange(13, 0, 1);
  }
  Serial.println(String("A0 = ") + analogRead(0));
  Serial.println(String("A1 = ") + analogRead(1));
  Serial.println(String("A2 = ") + analogRead(2));
  Serial.println(String("A3 = ") + analogRead(3));
  Serial.println(String("A4 = ") + analogRead(4));
  Serial.println(String("A5 = ") + analogRead(5));
  Serial.println(String("A6 = ") + analogRead(6));
  Serial.println(String("A7 = ") + analogRead(7));
  Serial.println(String("A8 = ") + analogRead(8));
  Serial.println(String("A9 = ") + analogRead(9));          
  delay(50);                                                    // Don't flood with constant MIDI messages; update every 50ms
}
