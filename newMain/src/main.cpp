/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       jokin                                                     */
/*    Created:      9/26/2023, 6:42:56 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "math.h"
#include "vex.h"
#include <string>

using namespace vex;

// A global instance of competition
competition Competition;

controller Con;
brain Brn;

motor frontLeftDrive = motor(PORT11, ratio6_1);
motor middleLeftDrive = motor(PORT12, ratio6_1);
motor backLeftDrive = motor(PORT13, ratio6_1);
motor frontRightDrive = motor(PORT14, ratio6_1);
motor middleRightDrive = motor(PORT15, ratio6_1);
motor backRightDrive = motor(PORT16, ratio6_1);
motor intake = motor(PORT1, ratio6_1);
motor launcher = motor(PORT2, ratio36_1);

digital_out leftWing = digital_out(Brn.ThreeWirePort.A);
digital_out rightWing = digital_out(Brn.ThreeWirePort.B);

// ALLIANCES: 0 = BlUE 1 = RED
bool fast = true, skills = false, leftDown = false, rightDown = false, R2pressingons = false, invert = false, leftOut = false, rightOut = false, launching = false;
std::string screen = "main", auton = "red1";
int p1dist = 0, p1vel = 75, x;
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
      Brn.Screen.setCursor(10,1);
      Brn.Screen.print("launcher: ");
      Brn.Screen.print(launcher.temperature(celsius));
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
};

void driveReverse(int distance, int velocity, int timeout) {
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
}

void turnLeft(int distance, int velocity, int timeout) {
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

void turnRight(int distance, int velocity, int timeout) {
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
/**
void wingsUp(bool left, bool right) {
  rightWing.setTimeout(1, seconds);
  rightWing.setTimeout(1, seconds);
  rightWing.setVelocity(100, percent);
  rightWing.setVelocity(100, percent);
  if (right == true) {
    rightWing.spinFor(reverse, 180, degrees, true);
  }
  if (left == true) {
    rightWing.spinFor(forward, 180, degrees, true);
  }
  rightWing.setStopping(hold);
  rightWing.setStopping(hold);
  rightWing.stop();
  rightWing.stop();
}

void wingsDown(bool left, bool right) {
  rightWing.setTimeout(1, seconds);
  rightWing.setTimeout(1, seconds);
  rightWing.setVelocity(100, percent);
  rightWing.setVelocity(100, percent);
  if (right == true) {
    rightWing.spinFor(forward, 180, degrees, false);
  }
  if (left == true) {
    rightWing.spinFor(forward, 180, degrees, true);
  }
  rightWing.setStopping(hold);
  rightWing.setStopping(hold);
  rightWing.stop();
  rightWing.stop();
}
*/

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
  driveForward(200, 50, 3);
  turnLeft(460, 50, 5);
  driveForward(1500, 50, 4);
  intake.setVelocity(100, percent);
  intake.spin(forward);
  wait(1000, msec);
  driveForward(1500, 50, 3);
  driveReverse(150, 75, 1);
  driveForward(250, 75, 1);
  turnLeft(100, 50, 4);
  driveReverse(300, 50, 3);
  turnLeft(130, 50, 4);
  driveReverse(1700, 50, 4);
  driveReverse(900, 25, 2);
  turnRight(750, 50, 2);
  driveForward(1150,50, 5);
  intake.stop();
  }
else if(auton == "red2"){

   driveForward(200, 40, 3);
  turnRight(300, 30, 5);
  driveForward(1500, 60,2);
  driveReverse(200, 100, 1);
  driveForward(300, 100, 1);
  driveReverse(190, 40, 1);
  turnRight(100, 40, 4);
  driveReverse(300, 70, 3);
  turnRight(130, 50, 4);
  driveReverse(2200, 70, 3);
  driveForward(890, 80, 5);
  turnLeft(390, 60, 2);
  driveForward(750, 80, 2); 
  leftWing.set(true);
  driveForward(800, 70, 3);

}

} 

void usercontrol() {
  vex::pneumatics leftWing = vex::pneumatics(Brn.ThreeWirePort.A);
  vex::pneumatics rightWing = vex::pneumatics(Brn.ThreeWirePort.B);

  intake.setVelocity(0, percent);

  while (true) {
  if(invert == false){
  frontLeftDrive.spin(reverse, Con.Axis3.position()*0.12, volt);
  middleLeftDrive.spin(reverse, Con.Axis3.position()*0.12, volt);
  backLeftDrive.spin(reverse, Con.Axis3.position()*0.12, volt);
  frontRightDrive.spin(forward, Con.Axis2.position()*0.12, volt);
  middleRightDrive.spin(forward, Con.Axis2.position()*0.12, volt);
  backRightDrive.spin(forward, Con.Axis2.position()*0.12, volt);

  }
  else{
  frontLeftDrive.spin(forward, Con.Axis3.position()*0.12, volt);
  middleLeftDrive.spin(forward, Con.Axis3.position()*0.12, volt);
  backLeftDrive.spin(forward, Con.Axis3.position()*0.12, volt);
  frontRightDrive.spin(reverse, Con.Axis2.position()*0.12, volt);
  middleRightDrive.spin(reverse, Con.Axis2.position()*0.12, volt);
  backRightDrive.spin(reverse, Con.Axis2.position()*0.12, volt);
  }

   if(Con.ButtonY.PRESSED){

    if(launching == false){

      launching = true;
      launcher.setVelocity(66, percent);
      launcher.spin(forward);

    }
    else if(launching == true){

      launching = false;
      launcher.setStopping(brake);
      launcher.stop();


    }
  

   }
   




    if(Con.ButtonR2.PRESSED){

      if(rightOut == false){

        
        rightOut = true;
        rightWing.set(true);
        
        screen = "main";

      }
      else{
        
        rightOut = false;
        rightWing.set(false);
 



      }

    }
    if(Con.ButtonL2.PRESSED){

      if(leftOut == false){

        leftOut = true;
        leftWing.set(true);

      }
      else{

        leftOut = false;
        leftWing.set(false);


      }

    }

     if(Con.ButtonR1.PRESSED){
        
        intake.setVelocity(100, percent);
        intake.spin(reverse);

      }

       if(Con.ButtonL1.PRESSED){
        
        intake.setVelocity(100, percent);
        intake.spin(forward);

      }

      if(Con.ButtonR1.RELEASED){
        intake.setVelocity(0, percent);

      }
      if(Con.ButtonL1.RELEASED){

        intake.setVelocity(0, percent);

      }
    
    if(Con.ButtonRight.pressing()){

      invert = true;

    }
    else{

      invert = false;

    }
/**
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
      rightWing.setMaxTorque(100, percent);
      rightWing.setVelocity(100, percent);
      if (rightWing.position(degrees) <= -45) {
        rightWing.spinFor(forward, 180, degrees, false);
      }
      if (rightWing.position(degrees) > -45) {
        rightWing.spinFor(reverse, 180, degrees, false);
      }
    }

    if (!Con.ButtonL2.pressing()) {
      rightWing.stop(hold);
    }
    */
  
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
