#include <FEHLCD.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHServo.h>

AnalogInputPin sensor(FEHIO::P0_0);
DigitalEncoder rightEncoder(FEHIO::P2_0);
DigitalEncoder leftEncoder(FEHIO::P2_1);
DigitalInputPin frontLeftSwitch(FEHIO::P1_0);
DigitalInputPin frontRightSwitch(FEHIO::P1_1);
DigitalInputPin backLeftSwitch(FEHIO::P1_2);
DigitalInputPin backRightSwitch(FEHIO::P1_3);
FEHMotor rightMotor(FEHMotor::Motor1, 9.0);
FEHMotor leftMotor(FEHMotor::Motor0, 9.0);

void moveForward(int percent, int counts) //using encoders
{
   //Reset encoder counts
   rightEncoder.ResetCounts();
   leftEncoder.ResetCounts();

   //Set both motors to desired percent
   rightMotor.SetPercent(percent);
   leftMotor.SetPercent(percent);

   //While the average of the left and right encoder is less than counts,
   //keep running motors
   while((leftEncoder.Counts() + rightEncoder.Counts()) / 2. < counts);

   //Turn off motors
   rightMotor.Stop();
   leftMotor.Stop();
}

void moveBack(int percent, int counts) //using encoders
{
   //Reset encoder counts
   rightEncoder.ResetCounts();
   leftEncoder.ResetCounts();

   //Set both motors to desired percent
   rightMotor.SetPercent(-percent);
   leftMotor.SetPercent(-percent);

   //While the average of the left and right encoder is less than counts,
   //keep running motors
   while((leftEncoder.Counts() + rightEncoder.Counts()) / 2. < counts);

   //Turn off motors
   rightMotor.Stop();
   leftMotor.Stop();
}

void turnRight(int percent, int counts) //using encoders
{
   //Reset encoder counts
   rightEncoder.ResetCounts();
   leftEncoder.ResetCounts();

   //Set both motors to desired percent
   //hint: set right motor backwards, left motor forwards

   rightMotor.SetPercent(-percent);
   leftMotor.SetPercent(percent);

   //While the average of the left and right encoder is less than counts,
   //keep running motors

   while((leftEncoder.Counts() + rightEncoder.Counts()) / 2. < counts);

   //Turn off motors
   rightMotor.Stop();
   leftMotor.Stop();
}

void turnLeft(int percent, int counts) //using encoders
{
   //Reset encoder counts
   rightEncoder.ResetCounts();
   leftEncoder.ResetCounts();

   //Set both motors to desired percent

   rightMotor.SetPercent(percent);
   leftMotor.SetPercent(-percent);

   //While the average of the left and right encoder is less than counts,
   //keep running motors

   while((leftEncoder.Counts() + rightEncoder.Counts()) / 2. < counts);

   //Turn off motors
   rightMotor.Stop();
   leftMotor.Stop();
}

/*
Completes a back right turn
*/
void backRightTurnSwitch() {
   /*
    * Back robot up slightly and turn
   */
   while(true) {
       rightMotor.SetPercent(-15);
       leftMotor.SetPercent(-15);
       Sleep(0.2);
       break;
   }
   leftMotor.SetPercent(0);
   rightMotor.SetPercent(0);

   /*
    * Wait for robot to stop
   */
    Sleep(2.0);

    /*
     * Backward right turn
   */
   while(backRightSwitch.Value()) {
       rightMotor.SetPercent(-25);
   }
   rightMotor.SetPercent(0);
   rightMotor.SetPercent(0);

   while(backLeftSwitch.Value()) {
       leftMotor.SetPercent(-25);
   }
   leftMotor.SetPercent(0);
   Sleep(1.0);
}

/*
* Completes a back left turn
*/
void backLeftTurnSwitch() {
   /*Slight back up */
   while(true) {
       rightMotor.SetPercent(-15);
       leftMotor.SetPercent(-15);
       Sleep(0.2);
       break;
   }

   /*
    * Left motor until it hits the wall
   */
   leftMotor.SetPercent(0);
   rightMotor.SetPercent(0);
   while(backLeftSwitch.Value()) {
       leftMotor.SetPercent(-25);
   }
   leftMotor.SetPercent(0);
   while(backRightSwitch.Value()) {
       rightMotor.SetPercent(-25);
   }
   rightMotor.SetPercent(0);
   Sleep(1.0);

}

/*
* Drive the robot forward until it hits the wall
*/
void fullForwardSwitch() {
   /*
    * Drive forward until both front switches are hit
    */
   while(frontRightSwitch.Value() && frontLeftSwitch.Value()) {
       rightMotor.SetPercent(25);
       leftMotor.SetPercent(25);
   }
   leftMotor.SetPercent(0);
   rightMotor.SetPercent(0);

   /*
    * Wait for robot to stop
    */
    Sleep(1.0);
}

void driveToSink() {

}

void trayInSink() {

}

void driveToIceCream() {

}

void flipLeverDown() {

}

void driveToBurger() {

}

void flipBurger() {

}

void driveToTicket() {

}

void pushTicket() {

}

void driveToIceCream2() {

}

void flipLeverUp() {

}

void drivetoStart() {

}

void driveToJukebox() {
   //Drive forwards 7.5 inches
   moveForward(25, 395);
   //Turn left 45 degrees
   turnLeft(25, 110);
   //Drive forwards 12 inches
   moveForward(25, 484);
   //Turn left 90 degrees
   turnLeft(25, 220);
   moveBack(25, 130);
}

void pressJukeboxButton() {
   //Hit button
   if(sensor.Value() > 0.5) {
       //Blue
       turnLeft(25, 121);
       moveForward(25, 40);
       turnRight(25, 121);
   } else {
       //Red
       turnRight(25, 121);
       moveForward(25, 40);
       turnLeft(25, 121);
   }
   moveForward(25, 150);
   //Drive backwards 6 inches
   moveBack(25, 242);
}

int main(void) {
   float x, y;

   LCD.Clear();
   LCD.Write("Trevor smells like socks");
   /* Wait for touch */
   while(!LCD.Touch(&x,&y));
   /* Wait for release */
   while(LCD.Touch(&x,&y));

   driveToJukebox();
   Sleep(5.0);
   pressJukeboxButton();

   //Turn left 135 degrees
   turnLeft(25, 363);
   //Move forwards a lot up ramp
   moveForward(25, 1000);
}

