/*
 * Tooth Brush Timer ( TBT )
 * 
 * The TBT powers on and then waits for the button to be pressed 
 * before counting up to two minutes. The LEDs will go from the lowest
 * green to yellow, then red. At the end, it will flash all LEDs a few 
 * times and lower all LEDs off.
 */

const int buttonPin = 8;
const int leds[] = {17,18,19,20,21,22,23,16,0,1,2,3,4,5,6,7};

const int timer = 5000;
int buttonState = 0;

void setup() {
  for (int i=0; i<16; i++) {    // Set LEDs as outputs.
    pinMode(leds[i], OUTPUT);
  }
  for (int i=0; i<16; i++) {    // Move lit LED bottom to top
    digitalWrite(leds[i], HIGH);
    delay(100);
    digitalWrite(leds[i], LOW);
  }
  for (int i=15; i>=0; i--) {   // Move lit LED top to bottom
    digitalWrite(leds[i], HIGH);
    delay(100);
    digitalWrite(leds[i], LOW);
  }
  for (int i=0; i<16; i++) {    // Set all LEDs high
    digitalWrite(leds[i], HIGH);
  }

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    for (int i=0; i<16; i++) {    // Set all LEDs low
      digitalWrite(leds[i], LOW);
    }
    for (int i=0; i<16; i++) {
      delay(timer);
      digitalWrite(leds[i], HIGH);
    }
    for (int i=0; i<16; i++) {    // Set all LEDs low
      for (int i=0; i<16; i++) {    // Set all LEDs low
        digitalWrite(leds[i], LOW);
        delay(10);
      }
      delay(500);
      for (int i=0; i<20; i++) {    // Set all LEDs low
        digitalWrite(leds[i], HIGH);
        delay(10);
      }
      delay(500);
    }
  } else {
    // do nothing.
  }
}
