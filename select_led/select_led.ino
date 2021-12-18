int buttons[] = {28, 30, 32};
int leds[] = {22, 24, 26};
int n;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  for(int i = 0; i<3;i++){
    pinMode(leds[i], OUTPUT);
    pinMode(buttons[i], INPUT);
    digitalWrite(leds[i], LOW);
  }

  randomSeed(analogRead(0));
  n = random(0,3);
  Serial.println("LED is : " + String(n));
}

void loop() {
  // put your main code here, to run repeatedly:
  int code = is_right_led(n);

  if(code == 1)
    digitalWrite(leds[n], HIGH);
  else if(code == 2)
    for(int i = 0; i<3; i++)
      digitalWrite(leds[i], HIGH);
    
  delay(100);
}


int is_right_led(int pin){
  if(digitalRead(buttons[0])){
    if(pin == 0) return 1;
    else return 2;
  }
  if(digitalRead(buttons[1])){
    if(pin == 1) return 1;
    else return 2;
  }
  if(digitalRead(buttons[2])){
    if(pin == 2) return 1;
    else return 2;
  }
  return 0;
}
