#include <Servo.h>

// We are isolating the test to ONLY the back legs
Servo backLeft;    // Pin 5 
Servo backRight;   // Pin 3 (This one has the crooked hardware!)

// The mechanical offset for the Back Right leg
int offsetBR = -70;

// Trackers for the Kinematics Engine (Front legs removed)
int currentBL = 90;
int currentBR = 20; // MUST start at 20 (which is 90 + offsetBR) to prevent the snap!

void setup() {
  // Pre-load the exact resting positions so they don't jump when attached
  backLeft.write(currentBL);
  backRight.write(currentBR);

  // Attach Pins (Only the back legs are attached now)
  backLeft.attach(5);
  backRight.attach(3);

  delay(1000); // Give the robot a second to stabilize
}

void loop() {
  // The Command Center: Run the stretch exactly 2 times
  for (int i = 0; i < 2; i++) {
    backLegStretch();
  }

  // Permanent Stop: Freeze the processor when the test is finished
  while (true) {}
}

// --- MOVEMENT FUNCTIONS ---

void backLegStretch() {
  // 1. Stretch Back Legs by 25 degrees (Targeting 115)
  // Mirrored Math: BL goes to 65, BR goes to 115
  moveBackLegsSlowly(65, 115);
  delay(1000); // Hold the stretch for a second

  // 2. Return to Neutral
  moveBackLegsSlowly(90, 90);
  delay(1000); // Wait a second before the next loop
}


// --- KINEMATICS ENGINE ---
// This function slices the movements into tiny steps so the robot moves smoothly
void moveBackLegsSlowly(int targetBL, int targetBR) {
  
  // Apply offset for Back Right and constrain to prevent 0-degree crashes
  int actualTargetBR = constrain(targetBR + offsetBR, 0, 180);

  // Keep stepping until the back legs reach their target
  while (currentBL != targetBL || currentBR != actualTargetBR) {
    
    if (currentBL < targetBL) currentBL++; else if (currentBL > targetBL) currentBL--;
    if (currentBR < actualTargetBR) currentBR++; else if (currentBR > actualTargetBR) currentBR--;

    backLeft.write(currentBL);
    backRight.write(currentBR);

    // Adjust this delay to change the speed (higher = slower, 15 is a good baseline)
    delay(15); 
  }
}