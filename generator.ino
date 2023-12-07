/*  Circuit Playground Prize Wheel

    This sketch was made to use a Circuit Playground Bluefruit as an activity generator for
    a collaborative Hour of Code activity at the Hagen Ranch Road library branch.

    The way to play is cupping the CPB in your hand and shaking it like a die. The Neopixel
    lights will sweep back and forth for a random number of runs, and then the Serial Monitor
    will display which activity the player must perform.

    7 December 2023

    Carmen Peterson

*/

#include <Adafruit_CircuitPlayground.h>
#include <math.h>

int timer = 100;
int lightVal;
int num;
int prize;

/*
   Establishing the probabilities within the Arduino sketch
   Options: Jumping, stomping, hopping on 1 foot, dancing
*/

int jump = 25;
int stomp = 25;
int hop = 25;
int dance = 25;

float X, Y, Z, totalAccel;


void setup() {
  // put your setup code here, to run once:
  CircuitPlayground.begin();
  Serial.begin(115200);

}

void loop() {

  /*
     Activate light sensor
  */

  lightVal = CircuitPlayground.lightSensor();

  /*
      Light Value Sensor Check (uncomment if you want to check)
  */

  //  Serial.print("Light Sensor: ");
  //  Serial.println(lightVal);

  /*
      If the light sensor in the CPB is covered, start the game
  */
  if (lightVal < 100) {

    /*
        Calculate the likelihood of winning each item
    */

    /*
        Select a random winning prize number & random number of times the lights will flash
    */

    activity = random(1, 100);
    num = random(1, 6);

    /*
        Check activity numbers (uncomment if you want to check)
    */

    //   Serial.print("The activity number is ");
    //   Serial.println(activity);
    //   Serial.print("And the num is ");
    //   Serial.println(num);

    /*
        Sensor values for the shaking
    */

    X = 0;
    Y = 0;
    Z = 0;
    for (int i = 0; i < 10; i++) {
      X += CircuitPlayground.motionX();
      Y += CircuitPlayground.motionY();
      Z += CircuitPlayground.motionZ();
      delay(1);
    }
    X /= 10;
    Y /= 10;
    Z /= 10;

    totalAccel = sqrt(X * X + Y * Y + Z * Z);

    /*
        Check shake values (uncomment if you want to check)
    */

    //   Serial.println(totalAccel);

    /*
        If they shook pretty hard, say something silly
    */

    if (totalAccel > 25) {
      //      Serial.println("Buddy, no need to shake so hard!");
    }

    /*
        If a general shake is detected, complete the game code & output the prize won
    */

    if (totalAccel > 15) {

      for (int j = 0; j < num; j++) {
        /*
          Have a neopixel color chase around the ring some random number of times
        */
        allColor(0, 128, 128);
      }

      /*
          Winning music tones
      */

            CircuitPlayground.playTone(523, 100);
            CircuitPlayground.playTone(659, 100);
            CircuitPlayground.playTone(784, 100);
            CircuitPlayground.playTone(1047, 100);

            Serial.println(prize);
            
      //      Serial.print("You are going to.... ");

      if (activity < 25) {
        //        Serial.println("Jump!!");
        allColor(255, 0, 255);
      }
      else if (activity >= 25 && activity < 50) {
        //        Serial.println("Stomp!!");
        allColor(255, 255, 0);
      }
      else if (activity >= 50 && activity < 75) {
        //        Serial.println("Hop!!");
        allColor(0, 255, 0);
      }
      else if (activity >= 75) {
        //        Serial.println("Dance!!");
        allColor(255, 255, 255);
      }

      /*
           Send activity value to Processing for the prettier output
      */
      
    }
    else {
      CircuitPlayground.setPixelColor(0, 0, 0, 0);
    }

  }

  /*
     Refresh every 100ms
  */
  delay(timer);

}

/*
   Function telling the Arduino how to have a Neopixel Chase
*/
void allColor(int r, int g, int b) {

  for (int i = 0; i < 10; i++) {
    CircuitPlayground.setPixelColor(i,   r, g, b);
    delay(timer);
    CircuitPlayground.setPixelColor(i,   0, 0, 0);
  }
  for (int i = 9; i >= 0; i--) {
    CircuitPlayground.setPixelColor(i,   r, g, b);
    delay(timer);
    CircuitPlayground.setPixelColor(i,   0, 0, 0);
  }

}
