#include <Servo.h>

// We are isolating the test to ONLY the back legs
Servo backLeft;    // Pin 5 
Servo backRight;   // Pin 3 (This one has the crooked hardware!)

// The mechanical offset for the Back Right leg
int offsetBR = -70;

// Trackers for the Kinematics Engine 
int currentBL = 90;
int currentBR = 20; // MUST start at 20 (which is 90 + offsetBR) to prevent the snap!

void setup() {
  // Pre-load the exact resting positions so they don't jump when attached
  backLeft.write(currentBL);
  backRight.write(currentBR);

  // Attach Pins 
  backLeft.attach(5);
  backRight.attach(3);

  delay(1000); // Give the robot a second to stabilize
}

void loop() {
  // The Command Center: Run the march exactly 4 times
  for (int i = 0; i < 4; i++) {
    alternatingMarch();
  }

  // Permanent Stop: Freeze the processor when the test is finished
  while (true) {}
}

// --- MOVEMENT FUNCTIONS ---

void alternatingMarch() {
  // 1. Lift Back Left, Plant Back Right
  moveBackLegsSlowly(60, 90);
  delay(300); // Short pause at the top of the step

  // 2. Plant Back Left, Lift Back Right
  moveBackLegsSlowly(90, 120);
  delay(300); // Short pause at the top of the step
  
  // 3. Return both to Neutral at the end of a cycle
  moveBackLegsSlowly(90, 90);
}


// --- KINEMATICS ENGINE ---
// Slices the movements into tiny steps so the robot moves smoothly
void moveBackLegsSlowly(int targetBL, int targetBR) {
  
  // Apply offset for Back Right and constrain to prevent 0-degree crashes
  int actualTargetBR = constrain(targetBR + offsetBR, 0, 180);

  // Keep stepping until the back legs reach their target
  while (currentBL != targetBL || currentBR != actualTargetBR) {
    
    if (currentBL < targetBL) currentBL++; else if (currentBL > targetBL) currentBL--;
    if (currentBR < actualTargetBR) currentBR++; else if (currentBR > actualTargetBR) currentBR--;

    backLeft.write(currentBL);
    backRight.write(currentBR);

    // Adjust this delay to change the speed (higher = slower, 12 is nice and snappy for a march)
    delay(12); 
  }
}