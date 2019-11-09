/*
 * Creation & Computation 
 * read Orientation value from arduino using AP-Sync
 * Uses Arduino Nano33 IOT
 */
import apsync.*; // Include the AP sync library
import processing.serial.*; //Include Processing Serial
import controlP5.*;

float minHue, maxHue;
PGraphics bg;


 String serialPort = "/dev/cu.usbmodem14101";
 
 //variables that will hold value from arduino. These must be the same name as the ones used in the .sync command on the Arduino side
 //THESE MUST BE DECLARED AS PUBLIC
 public float ax;
 public float ay;
 public float az;
 
 //acceleration values
// public float sx;
// public float sy;
// public float sz;
 
//float speedX = abs(sx);
//float speedY = abs(sy);
//float speedZ = abs(sz);
 
// images display and animation 
PImage dahliaImg;
 
AP_Sync readVals; //create apsync variable to read from  
 
 void setup()
 {
   fullScreen(); //create the window
   
   // read values from AP_Sync
   readVals = new AP_Sync(this, serialPort, 9600); //initialize the port and attach it to APsync. port speed must match the arduino side
    
   // new instance of PImage
   dahliaImg = loadImage("dahlia.png");
 
 }
 
 void draw()
 {

 
//translate(ax, ay);
// ellipse(ax, az, ay, ay);
// 
translate(ax, ay);
//ellipse(ax, az, ay, ay);

stroke(ax,ay);
fill(ax, ay, az);
translate(ax,ay);
rotate(ax/100.0);
rect(-500, 0, width*2, 20);

translate(ax,ay);
rotate(ax/100.0);
rect(-500, 0, width*2, 20);


 //ellipse(ax/width, 0, 150, 150);


 
  //image(dahliaImg, 0, angleY, angleX, angleX);
  
  
 }
 
 void setHue() {
  float rdn0 = random(255);
  float rdn1 = random(255);
  minHue = min(rdn0, rdn1);
  maxHue = max(rdn0, rdn1);
}


void createBackground() {
  bg = createGraphics(width, height);
  bg.beginDraw();
  bg.noStroke();
  for (float diam = 1.5*width; diam > 0.5*width; diam -= 20) {
    bg.fill(map(diam, 0.5*width, 1.5*width, 255, 210));
    bg.ellipse(width/2, height/2, diam, diam);
  }
  bg.endDraw();
}
