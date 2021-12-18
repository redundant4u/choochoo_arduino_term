#include <pitches.h>

#define READPIN 62
#define SPEAKER 63

int pitch;
int ipitches[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};
char cpitches[] = "CDEFGAB";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  randomSeed(analogRead(0));
  Serial.println(analogRead(0));

  pitch = random(7);
  Serial.println(pitch);

  tone(SPEAKER, ipitches[pitch], 250);
  delay(250);
  noTone(SPEAKER);

  Serial.println(cpitches[pitch]);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
