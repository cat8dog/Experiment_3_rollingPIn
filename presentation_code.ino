/*
 * Creation & Computation 
 * Send orientation & accel data to Processing using AP-Sync
 * Uses Arduino Nano33 IOT
 */

#include <Arduino_LSM6DS3.h>
#include <AP_Sync.h>

AP_Sync sendGyro(Serial); // Create an Object named sendGyro of type APsync
AP_Sync sendAccel(Serial); // Create an Object named sendAccel of type APsync

long lastRead;  //use this to measure time since last sensor reading
long lastSend; // use calculate time since last sent to Processing
int sendRate; // timer

//these will hold the calculated angle value (gyroscope)
float angleX;
float angleY;
float angleZ;


//these will hold the speed values (accelerometer)
float speedX;
float speedY; 
float speedZ;


void setup() 
{
  Serial.begin(9600);

  //test to see if it's working
  if(!IMU.begin())  //initalize the sensor print an error if it doesn't turn on
  {
  Serial.println("IMU isn't working....");   
  } 

}

void loop() 
{

float acX, acY, acZ; // temporary variables for holding the time incriments 
float dsX, dsY, dsZ;  //temporary variables for holding the degrees
  
  if (IMU.gyroscopeAvailable()) { //check if values are available
    
   IMU.readGyroscope(dsX, dsY, dsZ);  //read them and store the values into the variables
   float readAngleInterval = ((millis()-lastRead)/1000.0);
   
    angleX += dsX*readAngleInterval;
    angleY += dsY*readAngleInterval;
    angleZ += dsZ*readAngleInterval;
   
    //sendValue to Processing
    Serial.println("the angle values");
    sendGyro.sync("ax",map((abs(angleX)), 0, 1000, 0, 255));
    sendGyro.sync("ay",map((abs(angleY)), 0, 1000, 0, 255));
    sendGyro.sync("az",map((abs(angleZ)), 0, 1000, 0, 255)); 
    Serial.println('\t');

    lastRead=millis(); //save the time to calculate the readInterval;
    }

    // for the life of me I can't send the accel data to Processing!!! 
//
//if (IMU.accelerationAvailable()) {
//    IMU.readAcceleration(acX, acY, acZ);
//
//
//    float readSpeedInterval = ((millis()-lastSend)/100.0);
//    speedX += acX*readSpeedInterval;
//    speedY += acY*readSpeedInterval; 
//    speedZ += acZ*readSpeedInterval;
//
//    //abs(speedX);
////    abs(speedY);
////    abs(speedZ);
//
//    //map(speedX,0,400,0,255);
//
//    Serial.println("the speed values");
//    sendAccel.sync("sx", abs(speedX));
//    sendAccel.sync("sy", abs(speedY));
//    sendAccel.sync("sz", abs(speedZ));
//    Serial.println('\t');
//    lastSend=millis();
//    }
  
}
