#include <Servo.h>

// Define all 4 legs
Servo frontLeft;   // Pin 9 
Servo frontRight;  // Pin 6 
Servo backLeft;    // Pin 5 
Servo backRight;   // Pin 3 (The crooked motor)

// The mechanical offset for the Back Right leg
int offsetBR = -70;

// Trackers for the Kinematics Engine (Set to your Calibrated Neutrals)
int currentFL = 50; 
int currentFR = 66; 

void setup() {
  // 1. LOCK THE BACK LEGS (Make them a sturdy kickstand)
  backLeft.write(90);
  backRight.write(90 + offsetBR); // Safely sets physical 20 degrees
  
  // 2. Pre-load the Front legs to their True Neutrals
  frontLeft.write(currentFL);
  frontRight.write(currentFR);

  // 3. Attach all Pins 
  frontLeft.attach(9);
  frontRight.attach(6);
  backLeft.attach(5);
  backRight.attach(3);

  delay(1000); // Give the robot a second to stand up and stabilize
}

void loop() {
  // Run the Inward Stretch exactly 3 times
  for (int i = 0; i < 3; i++) {
    frontInwardStretch();
  }

  // Permanent Stop: Freeze the processor when finished
  while (true) {}
}

// --- MOVEMENT FUNCTIONS ---

void frontInwardStretch() {
  // 1. Pull FRONT legs INWARD (The Opposite Direction)
  // FL goes from 50 down to 10. FR goes from 66 up to 106.
  moveFrontLegsSlowly(10, 106);
  
  // Hold the inward stretch for 2 seconds
  delay(2000); 

  // 2. Return exactly to True Neutral
  moveFrontLegsSlowly(50, 66);
  
  delay(1000); // Wait a second before the next stretch
}


// --- KINEMATICS ENGINE ---
// This smoothly steps the front legs based on their current positions
void moveFrontLegsSlowly(int targetFL, int targetFR) {
  
  // Keep stepping until the front legs reach their target
  while (currentFL != targetFL || currentFR != targetFR) {
    
    if (currentFL < targetFL) currentFL++; else if (currentFL > targetFL) currentFL--;
    if (currentFR < targetFR) currentFR++; else if (currentFR > targetFR) currentFR--;

    frontLeft.write(currentFL);
    frontRight.write(currentFR);

    // Speed control (15 is a smooth, safe speed)
    delay(15); 
  }
}