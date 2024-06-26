/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jokin                                                     */
/*    Created:      1/25/2024, 6:54:56 PM                                     */
/*    Description:  V5 project                                                */                                      
/*----------------------------------------------------------------------------*/

#include "math.h"
#include "vex.h"
#include <string>

using namespace vex;

// A global instance of competition
competition Competition;

controller Con;
brain Brn;

motor frontLeftDrive = motor(PORT11, ratio18_1);
motor middleLeftDrive = motor(PORT2, ratio18_1);
motor backLeftDrive = motor(PORT12, ratio18_1);
motor frontRightDrive = motor(PORT13, ratio18_1);
motor middleRightDrive = motor(PORT15, ratio18_1);
motor backRightDrive = motor(PORT14, ratio18_1);
motor lowerSpinnyThing = motor(PORT3, ratio6_1);
motor upperspinnyThing = motor(PORT4, ratio6_1);
motor claw = motor(PORT20, ratio18_1);
motor leftWing = motor(PORT1, ratio18_1);
motor rightWing = motor(PORT10, ratio18_1);
motor intake = motor(PORT17, ratio6_1);

// ALLIANCES: 0 = BlUE 1 = RED
bool fast = true, skills = false, leftDown = false, rightDown = false, R2pressingons = false;;
double leftDriveVel = 0, rightDriveVel = 0, alliance = 0;
std::string screen = "main", auton = "red2";
int p1dist = 0, p1vel = 75, x, clawvelABS = claw.velocity(percent);

void drawRectangle(int x, int y, int w, int h, std::string autonSelected) {
    // Draw the square
    Brn.Screen.drawRectangle(x, y, w, h);

    // Check if the square is pressed (selected)
    if (Brn.Screen.pressing()) {
        int touchX = Brn.Screen.xPosition();
        int touchY = Brn.Screen.yPosition();
        if (touchX >= x && touchX <= x + w && touchY >= y && touchY <= y + h) {
            // Change the value of the auton variable when the square is selected
            auton = autonSelected;
        }
    }
}

void drawButton(int x, int y, int w, int h, std::string t, std::string destination) {
        Brn.Screen.setFillColor(black);
        Brn.Screen.setPenWidth(1);     
      Brn.Screen.setPenColor(white);
    Brn.Screen.drawRectangle(x, y, w, h);
    int textWidth = Brn.Screen.getStringWidth(t.c_str());
    int textX = x + (w - textWidth) / 2;
    int textY = y + h / 2;
    Brn.Screen.setCursor(1, 1);
    Brn.Screen.printAt(textX, textY, false, t.c_str());

    // Check if button is pressed
    if (Brn.Screen.pressing()) {
        int touchX = Brn.Screen.xPosition();
        int touchY = Brn.Screen.yPosition();
        if (touchX >= x && touchX <= x + w && touchY >= y && touchY <= y + h) {
            screen = destination;
        }
    }
}

void UI() {
    if (screen != "main") {
      Brn.Screen.setPenWidth(1);     
       Brn.Screen.setFillColor(black);
      Brn.Screen.setPenColor(white);
      drawButton(429, 205, 50, 35, "Back", "main");
    }
    if(screen == "main"){
      Brn.Screen.setPenWidth(1);
            Brn.Screen.setFillColor(black);
      Brn.Screen.setPenColor(white);
    drawButton(0, 0, 159, 119, "Auton Selector", "auton");
    drawButton(0, 119, 159, 119, "Motor Temps", "temps");
    }
    else if(screen == "temps"){
      Brn.Screen.setPenWidth(1);
      Brn.Screen.setFillColor(black);
      Brn.Screen.setPenColor(white);
      Brn.Screen.setFont(mono40);
      Brn.Screen.setCursor(1, 1);
      Brn.Screen.print("Motor Temps (Celcius): ");
      Brn.Screen.setFont(mono20);
      Brn.Screen.setCursor(3,1);
      Brn.Screen.print("Front Left Drive: ");
      Brn.Screen.print(frontLeftDrive.temperature(celsius));
      Brn.Screen.print("°");
      Brn.Screen.setCursor(4,1);
      Brn.Screen.print("Middle Left Drive: ");
      Brn.Screen.print(middleLeftDrive.temperature(celsius));
      Brn.Screen.print("°");
      Brn.Screen.setCursor(5,1);
      Brn.Screen.print("Back Left Drive: ");
      Brn.Screen.print(backLeftDrive.temperature(celsius));
      Brn.Screen.print("°");
      Brn.Screen.setCursor(6,1);
      Brn.Screen.print("Front Right Drive: ");
      Brn.Screen.print(frontRightDrive.temperature(celsius));
      Brn.Screen.print("°");
      Brn.Screen.setCursor(7,1);
      Brn.Screen.print("Middle Right Drive: ");
      Brn.Screen.print(middleRightDrive.temperature(celsius));
      Brn.Screen.print("°");
      Brn.Screen.setCursor(8,1);
      Brn.Screen.print("Back Right Drive: ");
      Brn.Screen.print(backRightDrive.temperature(celsius));
      Brn.Screen.print("°");
      Brn.Screen.setCursor(9,1);
      Brn.Screen.print("intake: ");
      Brn.Screen.print(intake.temperature(celsius));
      Brn.Screen.print("°");
    }
    else if(screen == "auton"){
      Brn.Screen.setPenWidth(1);
      Brn.Screen.setFillColor(black);
      Brn.Screen.printAt(199, 53, "Blue Goal");
      Brn.Screen.printAt(206, 193, "Red Goal");


      if(auton == "red1"){
      Brn.Screen.setPenWidth(4);
      }
      else{
      Brn.Screen.setPenWidth(1);
      }
      Brn.Screen.setFillColor(red);
      drawRectangle(119, 22, 75, 50, "red1");

      if(auton == "blue1"){
      Brn.Screen.setPenWidth(4);
      }
      else{
      Brn.Screen.setPenWidth(1);
      }
      Brn.Screen.setFillColor(blue);
      drawRectangle(294, 22, 75, 50, "blue1");
      
      if(auton == "red2"){
      Brn.Screen.setPenWidth(4);
      }
      else{
      Brn.Screen.setPenWidth(1);
      }
      Brn.Screen.setFillColor(red);
      drawRectangle(119, 167, 75, 50, "red2");

       if(auton == "blue2"){
      Brn.Screen.setPenWidth(4);
      }
      else{
      Brn.Screen.setPenWidth(1);
      }
      Brn.Screen.setFillColor(blue);
      drawRectangle(294, 167, 75, 50, "blue2");

      

    }
}

void setTimeouts(int num) {
  frontLeftDrive.setTimeout(num, seconds);
  middleLeftDrive.setTimeout(num, seconds);
  backLeftDrive.setTimeout(num, seconds);
  frontRightDrive.setTimeout(num, seconds);
  middleRightDrive.setTimeout(num, seconds);
  backRightDrive.setTimeout(num, seconds);
}

void setRightVel(int vel) {
  vel = vel * -1;

  frontRightDrive.setVelocity(vel, percent);
  middleRightDrive.setVelocity(vel, percent);
  backRightDrive.setVelocity(vel, percent);
}

void setLeftVel(int vel) {
  frontLeftDrive.setVelocity(vel, percent);
  middleLeftDrive.setVelocity(vel, percent);
  backLeftDrive.setVelocity(vel, percent);
}

void driveForward(int distance, int velocity, int timeout) {
  setLeftVel(velocity);
  setRightVel(velocity);

  setTimeouts(timeout);

  frontLeftDrive.spinFor(forward, distance, degrees, false);
  middleLeftDrive.spinFor(forward, distance, degrees, false);
  backLeftDrive.spinFor(forward, distance, degrees, false);

  frontRightDrive.spinFor(reverse, distance, degrees, false);
  middleRightDrive.spinFor(reverse, distance, degrees, false);
  backRightDrive.spinFor(reverse, distance, degrees);

  frontLeftDrive.stop();
  middleLeftDrive.stop();
  backLeftDrive.stop();
  frontRightDrive.stop();
  middleRightDrive.stop();
  backRightDrive.stop();
};

void driveReverse(int distance, int velocity, int timeout) {
  setLeftVel(velocity);
  setRightVel(velocity);

  setTimeouts(timeout);

  frontLeftDrive.spinFor(reverse, distance, degrees, false);
  middleLeftDrive.spinFor(reverse, distance, degrees, false);
  backLeftDrive.spinFor(reverse, distance, degrees, false);

  frontRightDrive.spinFor(forward, distance, degrees, false);
  middleRightDrive.spinFor(forward, distance, degrees, false);
  backRightDrive.spinFor(forward, distance, degrees);

  frontLeftDrive.stop();
  middleLeftDrive.stop();
  backLeftDrive.stop();
  frontRightDrive.stop();
  middleRightDrive.stop();
  backRightDrive.stop();
}

void turnLeft(int distance, int velocity, int timeout) {
  setLeftVel(velocity);
  setRightVel(velocity);

  setTimeouts(timeout);

  frontLeftDrive.spinFor(reverse, distance, degrees, false);
  middleLeftDrive.spinFor(reverse, distance, degrees, false);
  backLeftDrive.spinFor(reverse, distance, degrees, false);

  frontRightDrive.spinFor(reverse, distance, degrees, false);
  middleRightDrive.spinFor(reverse, distance, degrees, false);
  backRightDrive.spinFor(reverse, distance, degrees);

  frontLeftDrive.stop();
  middleLeftDrive.stop();
  backLeftDrive.stop();
  frontRightDrive.stop();
  middleRightDrive.stop();
  backRightDrive.stop();
}

void turnRight(int distance, int velocity, int timeout) {
  setLeftVel(velocity);
  setRightVel(velocity);

  setTimeouts(timeout);

  frontLeftDrive.spinFor(forward, distance, degrees, false);
  middleLeftDrive.spinFor(forward, distance, degrees, false);
  backLeftDrive.spinFor(forward, distance, degrees, false);

  frontRightDrive.spinFor(forward, distance, degrees, false);
  middleRightDrive.spinFor(forward, distance, degrees, false);
  backRightDrive.spinFor(forward, distance, degrees);

  frontLeftDrive.stop();
  middleLeftDrive.stop();
  backLeftDrive.stop();
  frontRightDrive.stop();
  middleRightDrive.stop();
  backRightDrive.stop();
}

void wingsUp(bool left, bool right) {
  leftWing.setTimeout(1, seconds);
  rightWing.setTimeout(1, seconds);
  rightWing.setVelocity(100, percent);
  leftWing.setVelocity(100, percent);
  if (right == true) {
    rightWing.spinFor(reverse, 180, degrees, true);
  }
  if (left == true) {
    leftWing.spinFor(forward, 180, degrees, true);
  }
  leftWing.setStopping(hold);
  rightWing.setStopping(hold);
  leftWing.stop();
  rightWing.stop();
}

void leftWingDown(int t) {
      leftWing.setMaxTorque(100, percent);
      leftWing.setVelocity(100, percent);
      leftWing.setTimeout(t, seconds);
      leftWing.spinFor(reverse, 180, degrees, true);
      leftWing.stop(hold);

      
}

void pre_auton() {
  /**
    Brn.Screen.clearScreen();
    while(true){
    Brn.Screen.setFillColor(blue);
    Brn.Screen.drawRectangle(140, 75, 100, 100);
      Brn.Screen.setFillColor(red);
    Brn.Screen.drawRectangle(240, 75, 100, 100);
    Brn.Screen.setFillColor(black);
    Brn.Screen.setCursor(1, 1);
    Brn.Screen.print("0 = Blue, 1 = red Current Aliance Selected ");
  Brn.Screen.print(alliance);

    }
    */
}

void autonomous() {
  if(auton == "red1"){
  driveForward(200, 40, 3);
  turnLeft(300, 30, 5);
  driveForward(2000, 60, 4);
  turnLeft(100, 40, 4);
  driveReverse(300, 70, 3);
  turnLeft(130, 50, 4);
  driveReverse(1400, 70, 3);
  driveForward(100, 40, 1);
  turnRight(40, 80, 1);
  driveReverse(100, 80, 1);
  turnRight(400, 80, 2);

  driveForward(1200, 80, 5);
  }
else if(auton == "red2"){

   driveForward(200, 40, 3);
  turnRight(300, 30, 5);
  driveForward(1500, 60,2);
  driveReverse(200, 100, 1);
  driveForward(300, 100, 1);
  turnRight(100, 40, 4);
  driveReverse(300, 70, 3);
  turnRight(130, 50, 4);
  driveReverse(1400, 70, 3);
  driveForward(890, 80, 5);
  turnLeft(390, 60, 2);
  driveForward(750, 80, 2); 
  leftWingDown(1);
  driveForward(800, 70, 3);

}
} 

void usercontrol() {


  intake.setVelocity(0, percent);
  frontLeftDrive.spin(forward);
  middleLeftDrive.spin(reverse);
  backLeftDrive.spin(forward);
  frontRightDrive.spin(reverse);
  middleRightDrive.spin(forward);
  backRightDrive.spin(reverse);

  while (true) {

//Brn.Screen.print();

    leftDriveVel = Con.Axis3.position();
    rightDriveVel = Con.Axis2.position();

    if (Con.ButtonA.pressing()) {
      if (!Con.ButtonL1.pressing()) {
        upperspinnyThing.setVelocity(75, percent);
        lowerSpinnyThing.setVelocity(70, percent);
      }
      if (Con.ButtonL1.pressing()) {
        upperspinnyThing.setVelocity(65, percent);
        lowerSpinnyThing.setVelocity(60, percent);
      }
     

      lowerSpinnyThing.spin(forward);
      upperspinnyThing.spin(forward);

    } else {
      lowerSpinnyThing.setVelocity(0, percent);
      upperspinnyThing.setVelocity(0, percent);
      lowerSpinnyThing.setStopping(brake);
      upperspinnyThing.setStopping(brake);
    }
 if(Con.ButtonX.PRESSED){
        
        intake.setVelocity(100, percent);
        intake.spin(forward);

      }

       if(Con.ButtonB.PRESSED){
        
        intake.setVelocity(100, percent);
        intake.spin(reverse);

      }
      if(Con.ButtonB.RELEASED){

        intake.setVelocity(0, percent);

      }
      if(Con.ButtonX.RELEASED){

        intake.setVelocity(0, percent);

      }
      
    if (Con.ButtonR1.pressing()) {
      frontLeftDrive.setVelocity(leftDriveVel * 0.45, percent);
      frontRightDrive.setVelocity(rightDriveVel * -0.45, percent);
      backLeftDrive.setVelocity(leftDriveVel * 0.45, percent);
      backRightDrive.setVelocity(rightDriveVel * -0.45, percent);
      middleLeftDrive.setVelocity(leftDriveVel * 0.45, percent);
      middleRightDrive.setVelocity(rightDriveVel * -0.45, percent);

    } else {
      frontLeftDrive.setVelocity(leftDriveVel* 1, percent);
      frontRightDrive.setVelocity(rightDriveVel* -1, percent);
      middleLeftDrive.setVelocity(leftDriveVel* 1, percent);
      middleRightDrive.setVelocity(rightDriveVel* -1, percent);
      backLeftDrive.setVelocity(leftDriveVel* 1, percent);
      backRightDrive.setVelocity(rightDriveVel* -1, percent);
    }

    if (Con.ButtonDown.PRESSED) {
      claw.setMaxTorque(70, percent);
      claw.setTimeout(1, seconds);
      claw.spinFor(forward, 180, degrees, false);

    } else {
      if (clawvelABS <= 5 && claw.position(degrees) >= 90 &&
          !Con.ButtonUp.pressing()) {
        claw.stop(coast);
      }
    }

    if (Con.ButtonUp.PRESSED) {
      claw.setMaxTorque(90, percent);
      claw.setTimeout(1, seconds);
      claw.spinFor(reverse, 180, degrees, false);

    } else {
      if (clawvelABS <= 5 && claw.position(degrees) <= 10 &&
          !Con.ButtonDown.pressing()) {
        claw.stop(coast);
      }
    }

    if (Con.ButtonR2.PRESSED) {
      rightWing.setMaxTorque(100, percent);
      rightWing.setVelocity(100, percent);
      if (rightWing.position(degrees) <= 45) {
        rightWing.spinFor(forward, 180, degrees, false);
      }
      if (rightWing.position(degrees) > 45) {
        rightWing.spinFor(reverse, 180, degrees, false);
      }
    }

    if (!Con.ButtonR2.pressing()) {
      rightWing.stop(hold);
    }

    if (Con.ButtonL2.PRESSED) {
      leftWing.setMaxTorque(100, percent);
      leftWing.setVelocity(100, percent);
      if (leftWing.position(degrees) <= -45) {
        leftWing.spinFor(forward, 180, degrees, false);
      }
      if (leftWing.position(degrees) > -45) {
        leftWing.spinFor(reverse, 180, degrees, false);
      }
    }

    if (!Con.ButtonL2.pressing()) {
      leftWing.stop(hold);
}
  }
}

int main() {
  while(true){
  UI();
  Brn.Screen.render(false);
  Brn.Screen.clearScreen();
  }
  Brn.Screen.render(false);

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
}
