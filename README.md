# Robot Custom kinematics

## Overview
This repository contains the code, simulation files, wiring diagrams, and video demonstrations for a custom-built, 4-servo robot. Powered by an Arduino Uno, this project focuses on developing a software-based kinematics engine to control precise leg movements, manage hardware offsets, and ensure stable, synchronized motion.

## Repository Structure
* 📁 **Code:** Contains the Arduino `.ino` files for calibration and specific movement sequences.
* 📁 **Simulation:** Tinkercad and web-based simulation setups used to test logic before hardware deployment.
* 📁 **Wiring Diagram:** Schematics detailing the power distribution and logic connections.
* 📁 **Robot Moves Videos:** Real-world video demonstrations of the robot executing programmed kinematics.

---

## Engineering Challenges & Solutions

Building this robot involved overcoming several physical and electrical hurdles. Rather than rebuilding the chassis, we solved hardware imperfections using software engineering:

* **The "Startup Jerk" (Servo Snapping):** * *Issue:* When powering on or uploading new code, the servos would violently snap to their default positions at maximum speed, causing the robot to fall over or risk gear damage.
    * *Solution:* We pre-loaded the target positions into the Arduino's memory using `servo.write()` *before* engaging the power with `servo.attach()` in the `setup()` function. This completely eliminated the startup snap.

* **Hardware Asymmetry (The Crooked Motor):** * *Issue:* The Back Right (BR) servo was mechanically mounted at a -70 degree offset compared to the other legs, making symmetrical movement impossible with standard math.
    * *Solution:* Instead of disassembling the robot, we built a calibration layer into the software. We established a "True Physical Neutral" (FL: 50°, FR: 66°, BL: 90°, BR: 20°) and used a `constrain()` function to safely calculate all movements from this new baseline, preventing the offset motor from crashing into its 0-degree physical limit.

* **Power Distribution & Brownouts:**
    * *Issue:* Powering four servos directly from the Arduino's 5V pin caused sudden current spikes, resulting in voltage drops (brownouts) that crashed the board and caused erratic twitching.
    * *Solution:* We decoupled the power supplies. The servos are powered by an external 6V (4x AA) battery pack to handle the heavy lifting, while the Arduino handles the logic. All grounds were tied together on the breadboard to ensure a clean reference signal.

---

## Kinematics Demonstrations

Below are the video demonstrations of the robot executing our custom movement functions. 

### Move 1: The Symmetrical Wide Stance Stretch
*This move pushes the legs outward to widen the robot's center of gravity, testing the symmetrical offset math.*
[https://drive.google.com/file/d/1ehsMpyoqLA4xMyz3gcPDM7Q1kiL989w7/view?usp=sharing]

### Move 2: The Alternating March
*A foundational tap-dance motion where the robot lifts and plants alternating legs while maintaining chassis stability.*
[Insert Link to Video 2 Here https://drive.google.com/file/d/1HOvBtzyv6HtMpX2Xqff50qX2n-gcYYO7/view?usp=sharing]

### Move 3: Take a Bow
*By pulling the front legs inward (Front Left to 90°, Front Right to 26°) while keeping the back legs locked as a sturdy kickstand, the robot dynamically dips its front chassis.*
[Insert Link to Video 3 Here]

---

## Getting Started
To replicate this project:
1.  Review the **Wiring Diagram** to ensure your external battery pack is correctly routed to the servos and sharing a ground with the Arduino.
2.  Run the Calibration Test code in the **Code** folder to find your specific hardware's "True Neutral" resting angles.
3.  Upload any of the movement sequences, ensuring your robot is propped up on a block during the first upload to verify leg direction safely.
