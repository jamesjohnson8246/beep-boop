#include <FEHLCD.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHServo.h>

/*
 Completes a back right turn
*/
void backRightTurn(FEHMotor left,DigitalInputPin backLeft,
                   FEHMotor right, DigitalInputPin backRight) {
    /*
     * Back robot up slightly and turn
    */
    while(true) {
        right.SetPercent(-15);
        left.SetPercent(-15);
        Sleep(0.2);
        break;
    }
    left.SetPercent(0);
    right.SetPercent(0);

    /*
     * Wait for robot to stop
    */
     Sleep(2.0);

     /*
      * Backward right turn
    */
    while(backRight.Value()) {
        right.SetPercent(-25);
    }
    right.SetPercent(0);
    right.SetPercent(0);

    while(backLeft.Value()) {
        left.SetPercent(-25);
    }
    left.SetPercent(0);
    Sleep(1.0);
}

/*
 * Completes a back left turn
 */
void backLeftTurn(FEHMotor left, DigitalInputPin backLeft,
                  FEHMotor right, DigitalInputPin backRight) {
    /*Slight back up */
    while(true) {
        right.SetPercent(-15);
        left.SetPercent(-15);
        Sleep(0.2);
        break;
    }

    /*
     * Left motor until it hits the wall
    */
    left.SetPercent(0);
    right.SetPercent(0);
    while(backLeft.Value()) {
        left.SetPercent(-25);
    }
    left.SetPercent(0);
    while(backRight.Value()) {
        right.SetPercent(-25);
    }
    right.SetPercent(0);
    Sleep(1.0);

}

/*
 * Drive the robot forward until it hits the wall
 */
void fullForward(FEHMotor left, DigitalInputPin frontLeft,
                 FEHMotor right, DigitalInputPin frontRight) {
    /*
     * Drive forward until both front switches are hit
     */
    while(frontRight.Value() && frontLeft.Value()) {
        right.SetPercent(25);
        left.SetPercent(25);
    }
    left.SetPercent(0);
    right.SetPercent(0);

    /*
     * Wait for robot to stop
     */
     Sleep(1.0);
}

int main(void) {
    /*Declare microswitches */
    DigitalInputPin frontRight(FEHIO::P0_1);
    DigitalInputPin backRight(FEHIO::P0_0);
    DigitalInputPin frontLeft(FEHIO::P3_6);
    DigitalInputPin backLeft(FEHIO::P3_7);

    /* Declare microswitches */
    FEHMotor right(FEHMotor::Motor1, 9.0);
    FEHMotor left(FEHMotor::Motor0, 9.0);
    float x, y;

    LCD.Clear();
    LCD.Write("Trevor smells like socks");
    /* Wait for touch*/
    while(!LCD.Touch(&x,&y));
    /* Wait for release*/
    while(LCD.Touch(&x,&y));

     fullForward(left, frontLeft, right, frontRight);

     backRightTurn(left, backLeft,  right, backRight);

     fullForward(left, frontLeft, right, frontRight);

     backLeftTurn(left, backLeft, right, backRight);
}
