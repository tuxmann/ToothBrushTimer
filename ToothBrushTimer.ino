/*
 * Tooth Brush Timer ( TBT ) - Deluxe Edition (10 Animations)
 * 
 * Hardware: Attiny88
 * Power: USB Power Bank
 * 
 * Logic:
 * 1. Setup: Sweep LEDs.
 * 2. Idle: Cycle 1/10th brightness waiting for button.
 * 3. Timer: ~2 minutes fill up.
 * 4. End: RANDOMIZED celebration (No repeats!).
 */

const int buttonPin   = 8;
int  buttonState = 0;

// LED Array: G G G G G G G G G Y Y Y Y Y R R  (Green, Yellow, Red)
const int leds[] = {17,18,19,20,21,22,23,16,0,1,2,3,4,5,6,7};

// 7500ms * 16 LEDs = 120 Seconds (2 Minutes)
const int timer  = 7500; 
const int ztimer = 300;

// 15 seconds of celebration
const long celebrationDuration = 15000; 

// Memory variable to prevent repeating the same animation
int lastAnim = -1;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); 
  for (int i=0; i<16; i++) {        
    pinMode(leds[i], OUTPUT);
  }
  
  // Initial Startup Sweep
  for (int i=0; i<16; i++) {        
    digitalWrite(leds[i], HIGH);
    delay(25);
    digitalWrite(leds[i], LOW);
  }
  for (int i=15; i>=0; i--) {       
    digitalWrite(leds[i], HIGH);
    delay(25);
    digitalWrite(leds[i], LOW);
  }
}

void loop() {  
  // Idle Loop
  for (int i=0; i<16; i++) {        
    for (int j=0; j<ztimer; j++) {  
      buttonState = digitalRead(buttonPin); 
      
      if (buttonState == LOW) { 
        randomSeed(micros()); 
        runtimer();
      } else {                  
        // Dimming Pulse
        digitalWrite(leds[i], HIGH);
        delay(1);
        digitalWrite(leds[i], LOW);
        delay(10);
      }
    }
  }
}

void runtimer(){                
  clearLEDs();

  // 1. The Brushing Timer (Count Up)
  for (int i=0; i<16; i++) {    
    digitalWrite(leds[i], HIGH);
    delay(timer);
  }

  // 2. Select a NEW Animation (No Repeats!)
  int anim;
  do {
    anim = random(0, 10); // Now picks from 0 to 9
  } while (anim == lastAnim);
  
  lastAnim = anim; // Remember this for next time

  // 3. Play the Animation
  switch(anim) {
    case 0: animStrobe(celebrationDuration);    break;
    case 1: animConfetti(celebrationDuration);  break;
    case 2: animScanner(celebrationDuration);   break;
    case 3: animCurtain(celebrationDuration);   break;
    case 4: animFillDrain(celebrationDuration); break;
    // New Animations
    case 5: animMeteor(celebrationDuration);    break;
    case 6: animBreathing(celebrationDuration); break;
    case 7: animMiddleOut(celebrationDuration); break;
    case 8: animMarquee(celebrationDuration);   break;
    case 9: animBounce(celebrationDuration);    break;
  }

  clearLEDs();
}

// --- Helper Functions ---

void clearLEDs() {
  for (int i=0; i<16; i++) digitalWrite(leds[i], LOW);
}

void allHigh() {
  for (int i=0; i<16; i++) digitalWrite(leds[i], HIGH);
}

// --- Original 5 Animations ---

void animStrobe(long duration) {
  unsigned long startTime = millis();
  while(millis() - startTime < duration) {
    allHigh(); delay(200);
    clearLEDs(); delay(200);
  }
}

void animConfetti(long duration) {
  clearLEDs();
  unsigned long startTime = millis();
  while(millis() - startTime < duration) {
    int r = random(0, 16);
    digitalWrite(leds[r], HIGH);
    delay(30);
    digitalWrite(leds[r], LOW);
    delay(20);
  }
}

void animScanner(long duration) {
  clearLEDs();
  unsigned long startTime = millis();
  while(millis() - startTime < duration) {
    for (int i=0; i<16; i++) {
      digitalWrite(leds[i], HIGH); delay(30); digitalWrite(leds[i], LOW);
    }
    for (int i=14; i>=1; i--) {
      digitalWrite(leds[i], HIGH); delay(30); digitalWrite(leds[i], LOW);
    }
  }
}

void animCurtain(long duration) {
  clearLEDs();
  unsigned long startTime = millis();
  while(millis() - startTime < duration) {
    for (int i=0; i<8; i++) {
      digitalWrite(leds[i], HIGH); digitalWrite(leds[15-i], HIGH); delay(70);
    }
    delay(200);
    for (int i=7; i>=0; i--) {
      digitalWrite(leds[i], LOW); digitalWrite(leds[15-i], LOW); delay(70);
    }
  }
}

void animFillDrain(long duration) {
  clearLEDs();
  unsigned long startTime = millis();
  while(millis() - startTime < duration) {
    for (int i=0; i<16; i++) { digitalWrite(leds[i], HIGH); delay(20); }
    delay(100);
    for (int i=0; i<16; i++) { digitalWrite(leds[i], LOW); delay(20); }
    delay(100);
  }
}

// --- 5 New Animations ---

// 6. Meteor: A trail falling from Top (Red) to Bottom (Green)
void animMeteor(long duration) {
  clearLEDs();
  unsigned long startTime = millis();
  while(millis() - startTime < duration) {
    for(int i=15; i>=-2; i--) { // Start above top, go below bottom
      // Head
      if(i>=0 && i<16) digitalWrite(leds[i], HIGH);
      // Tail 1
      if(i+1>=0 && i+1<16) digitalWrite(leds[i+1], HIGH);
      // Tail 2 (Erase previous)
      if(i+2>=0 && i+2<16) digitalWrite(leds[i+2], LOW);
      delay(40);
    }
    clearLEDs();
    delay(100);
  }
}

// 7. Breathing: Smooth fade in and out using fast switching
void animBreathing(long duration) {
  unsigned long startTime = millis();
  while(millis() - startTime < duration) {
    // Fade In
    for(int b=1; b<20; b++) {
      for(int k=0; k<10; k++) { // Hold brightness level
        allHigh(); delayMicroseconds(b * 100); 
        clearLEDs(); delayMicroseconds((20-b) * 100);
      }
    }
    // Fade Out
    for(int b=19; b>1; b--) {
      for(int k=0; k<10; k++) {
        allHigh(); delayMicroseconds(b * 100); 
        clearLEDs(); delayMicroseconds((20-b) * 100);
      }
    }
  }
}

// 8. Middle Out: Explosion from center
void animMiddleOut(long duration) {
  clearLEDs();
  unsigned long startTime = millis();
  while(millis() - startTime < duration) {
    for (int i=0; i<8; i++) {
      digitalWrite(leds[7-i], HIGH); // Center-Left moving Left
      digitalWrite(leds[8+i], HIGH); // Center-Right moving Right
      delay(60);
      digitalWrite(leds[7-i], LOW);
      digitalWrite(leds[8+i], LOW);
    }
    delay(100);
  }
}

// 9. Marquee: Theater chasing lights
void animMarquee(long duration) {
  clearLEDs();
  unsigned long startTime = millis();
  while(millis() - startTime < duration) {
    for (int offset=0; offset<3; offset++) {
      for (int i=0; i<16; i++) {
        if ((i+offset) % 3 == 0) digitalWrite(leds[i], HIGH);
        else digitalWrite(leds[i], LOW);
      }
      delay(150);
    }
  }
}

// 10. Bounce: A single dot bouncing off the walls
void animBounce(long duration) {
  clearLEDs();
  unsigned long startTime = millis();
  int pos = 0;
  int dir = 1;
  while(millis() - startTime < duration) {
    digitalWrite(leds[pos], HIGH);
    delay(50);
    digitalWrite(leds[pos], LOW);
    
    pos += dir;
    if (pos == 15 || pos == 0) {
      dir = dir * -1; // Reverse direction
    }
  }
}
