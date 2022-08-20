/*
 * Tooth Brush Timer ( TBT )
 * 
 * The TBT powers on. The 16 LEDs turn on one at a time going from the 
 * first green to the last red and then backwards. Then the TBT waits 
 * for the button to be pressed. While waiting, the TBT will cycle 
 * through all the LEDs at 1/10th power. When the button is pushed, 
 * the timer will run for about two minutes. At full brightness, the 
 * LEDs will go from the lowest green to yellow, then red. At the end, 
 * it will flash all LEDs a few times and lower all LEDs off.
 */

const int buttonPin   = 8;
int  buttonState = 0;
//                  G  G  G  G  G  G  G  G  G Y Y Y Y Y R R   Green,Yellow, Red.
const int leds[] = {17,18,19,20,21,22,23,16,0,1,2,3,4,5,6,7};
const int timer  = 6000;
const int ztimer = 300;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Set internal pullup resistor.
  for (int i=0; i<16; i++) {        // Set LEDs as outputs.
    pinMode(leds[i], OUTPUT);
  }
  for (int i=0; i<16; i++) {        // Move lit LED from bottom to top.
    digitalWrite(leds[i], HIGH);
    delay(75);
    digitalWrite(leds[i], LOW);
  }
  for (int i=15; i>=0; i--) {       // Move lit LED from top to bottom.
    digitalWrite(leds[i], HIGH);
    delay(75);
    digitalWrite(leds[i], LOW);
  }
}

void loop() {  // Waiting for the button to be pressed.
  for (int i=0; i<16; i++) {        // Cycle through LEDs at 1/10th power 
    for (int j=0; j<ztimer; j++) {  // Count to ztimer value before going to next LED.
      buttonState = digitalRead(buttonPin); // Check if the pushbutton is pressed.
      if (buttonState == LOW) { // Start Timer for brushing teeth.
        runtimer();
      } else {                  // Continue waiting for  button press.
        digitalWrite(leds[i], HIGH);
        delay(1);
        digitalWrite(leds[i], LOW);
        delay(10);
      }
    }
  }
}

void runtimer(){                // Start Toothbrush counting.
  for (int i=0; i<16; i++) {    // Set all LEDs low
    digitalWrite(leds[i], LOW);
  }
  for (int i=0; i<16; i++) {    // Turn on LEDs one at a time.
    digitalWrite(leds[i], HIGH);
    delay(timer);
  }
  for (int i=0; i<16; i++) {    // End of timer, flash LEDS
    for (int i=0; i<16; i++) {    // Set all LEDs high.
      digitalWrite(leds[i], HIGH);
      delay(5);
    }
    delay(500);
    for (int i=0; i<16; i++) {    // Set all LEDs low
      digitalWrite(leds[i], LOW);
      delay(5);
    }
    delay(500);
  }
}
