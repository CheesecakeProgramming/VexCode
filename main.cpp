/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      7/17/2024, 12:47:17 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "math.h"
#include <string>

using namespace vex;


competition Competition;

brain Brain;
controller Controller;

motor frontLeftDrive = motor(PORT1, ratio18_1);
motor frontRightDrive = motor(PORT2, ratio18_1);
bumper frontBumper = bumper(Brain.ThreeWirePort.C);

int x = 0;

void driveForwardIndef(){

frontLeftDrive.spin(forward);
frontRightDrive.spin(reverse);

}
void stopMotors(){

frontRightDrive.stop();
frontLeftDrive.stop();
frontLeftDrive.setStopping(brake);
frontRightDrive.setStopping(brake);

}

void turnRight(int dist){

frontLeftDrive.spinFor(reverse, dist, degrees, false);
frontRightDrive.spinFor(reverse, dist, degrees);

}

void turnLeft(int dist){

frontLeftDrive.spinFor(forward, dist, degrees, false);
frontRightDrive.spinFor(forward, dist, degrees);

}

void driveForward(int dist){

frontLeftDrive.spinFor(forward, dist, degrees, false);
frontRightDrive.spinFor(reverse, dist, degrees);

}


void driveReverse(int dist){

frontLeftDrive.spinFor(reverse, dist, degrees, false);
frontRightDrive.spinFor(forward, dist, degrees);

}

void whenBumperPressed(){

  x++;
  stopMotors();
  wait(2, seconds);
  driveReverse(75);
  wait(1, seconds);
  turnRight(192.5);
  if(x<=2){
  driveForwardIndef();
  }
  else if(x==3){

    driveForward(250);
turnRight(192.5);
driveForward(120);
turnLeft(192.5);
driveForward(200);

  }

}

void pre_auton(void) {



}



void autonomous(void) {
frontLeftDrive.setVelocity(15, percent);
frontRightDrive.setVelocity(15, percent);
driveForwardIndef();  
frontBumper.pressed(whenBumperPressed);

while(true){


Brain.Screen.print(x);
wait(0.1, seconds);
Brain.Screen.clearScreen();



}



}

void usercontrol(void) {

  

  while (1) {

    wait(20, msec); 
  }
}


int main() {

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);


  pre_auton();

 
  while (true) {
    wait(100, msec);
  }
}
