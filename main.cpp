/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Student                                                   */
/*    Created:      7/18/2024, 9:59:02 AM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;


competition Competition;
brain Brain;
controller Controller;

motor leftHammer = motor(PORT4, ratio18_1);
motor rightHammer = motor(PORT3, ratio18_1);
motor leftDrive = motor(PORT1, ratio18_1);
motor rightDrive = motor(PORT2, ratio18_1);

void pre_auton(void) {


}


void autonomous(void) {

}



void usercontrol(void) {
while(true){

leftDrive.spin(vex::directionType::fwd, (Controller.Axis3.value() + Controller.Axis1.value()*2), vex::velocityUnits::pct);
rightDrive.spin(vex::directionType::rev, (Controller.Axis3.value()- Controller.Axis1.value()*2), vex::velocityUnits::pct);

if(Controller.ButtonR1.pressing()){

rightHammer.setVelocity(55, percent);
rightHammer.setMaxTorque(65, percent);
rightHammer.spin(reverse);


}
else if(Controller.ButtonR2.pressing()){

  rightHammer.setVelocity(100, percent);
  rightHammer.setMaxTorque(100, percent);
  rightHammer.spin(forward);

}
else{

rightHammer.stop();
rightHammer.setStopping(brake);

}

if(Controller.ButtonL1.pressing()){

leftHammer.setVelocity(55, percent);
leftHammer.setMaxTorque(65, percent);
leftHammer.spin(forward);


}
else if(Controller.ButtonL2.pressing()){

  leftHammer.setVelocity(100, percent);
  leftHammer.setMaxTorque(100, percent);
  leftHammer.spin(reverse);

}
else{

leftHammer.stop();
leftHammer.setStopping(brake);

}


}
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
