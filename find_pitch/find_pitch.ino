#include <pitches.h>

#define READPIN 62
#define SPEAKER 63

int rpitch;
int ipitches[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};
char cpitches[] = "CDEFGABC";
unsigned long time_prev, time_cur;
int tflag = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  randomSeed(analogRead(0));

  rpitch = random(8);

  Serial.println(cpitches[rpitch]);
  tone(SPEAKER, ipitches[rpitch], 1000);
  delay(1000);
  noTone(SPEAKER);
}

void loop() {
  // put your main code here, to run repeatedly:
  int adc = analogRead(READPIN);
  int spitch = map(adc, 0, 1023, 0, 7);
  
  if(rpitch == spitch){
    if(tflag == 0){
      time_prev = millis();
      tflag = 1;
    }
    else{
      time_cur = millis();
      if(time_cur-time_prev >= 3000){
        Serial.println("Correct!");
        tflag = 0;
        while(true) noTone(SPEAKER);
      }
    }
  }else{
    tflag = 0;
  }
  
  tone(SPEAKER, ipitches[spitch]);
  Serial.println("ADC : "+String(spitch));
  delay(100);
}
