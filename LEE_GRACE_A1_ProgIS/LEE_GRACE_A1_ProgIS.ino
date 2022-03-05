#include <ezButton.h>
#define SWITCH_OFF 0
#define SWITCH_ON  1
//variables

int tilt;
int tempo;
int seqNo = 2;
int x=2;
int cycleCount=0;

ezButton button(7); // create ezButton object that attaches to pin 7;

int switch_state = SWITCH_OFF; // initial state

void setup() {
  Serial.begin(9600);
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  
  // declare the LED pins as outputs
  pinMode(2, OUTPUT); // yellow LED
  pinMode(3, OUTPUT); // green LED
  pinMode(4, OUTPUT); // red LED
  pinMode(5, OUTPUT); // blue LED
  pinMode(6, OUTPUT); // piezo

  pinMode(7, INPUT); // switch
}

void loop() {
  tilt = analogRead(A0);
  tempo = map(tilt, 0, 1023, 500, 3000);
  
  button.loop(); // MUST call the loop() function first

  if (button.isPressed()) {
    // change state of switch
    if (switch_state == SWITCH_OFF)
      switch_state = SWITCH_ON;
    else
      switch_state = SWITCH_OFF;
      Serial.println(switch_state);
  }
  
  if (switch_state == SWITCH_OFF) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW); 
    digitalWrite(5, LOW); 
  }else if (cycleCount > tempo) {
      Serial.println(tempo);
      for (x=2; x<=5; x++){
        if (x==seqNo){
          digitalWrite (x, HIGH);
          tone(6, 440*x, 20);
        } else
          digitalWrite (x, LOW);
      }
      if (seqNo==5){
        seqNo=2;
      }else{
        seqNo++;
      }
      cycleCount = 0;
   } 
   cycleCount++;
} 
