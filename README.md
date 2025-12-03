# ToothBrushTimer
A simple two minute tooth brush timer for the kids.

No Repeats: Added a do...while loop that forces the randomizer to pick a new number if it matches the previous one.
Time-Based Animations: Instead of counting loops (e.g., "do this 5 times"), the animations now accept a duration (set to 15 seconds). They will keep repeating their specific pattern until that time is up.
Random Seeding: Added randomSeed(micros()); right when the button is pressed. This ensures the animation is truly random every time you brush.

The Animations:
Party Mode: Random LEDs popping fast (Confetti).
Pulse: All LEDs fading in and out (Simulated breathing).
Scanner: The "Knight Rider" back-and-forth sweep.
The Curtains: LEDs closing in from the outside to the center.
Strobe: Your original flashing, but timed to fit the window.
Meteor: A trail of light falling from the top (Red) to the bottom (Green).
Breathing: All LEDs smoothly fading in and out (using a software trick).
Middle-Out: An explosion effect starting from the center.
Marquee: "Theater lights" chasing pattern.
Bouncing Ball: A single dot bouncing back and forth off the edges.
