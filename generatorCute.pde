/* 
 
 A little cute output screen for Hour of Code event at HRR.
 
 
 Please run the Arduino sketch "generator.ino" before running this sketch. 
 
 This sketch was made to as a cute output screen for the Circuit Playground Bluefruit being used as 
 an activity generator, encouraging play during an Hour of Code.
 
 The way to play is cupping the CPB in your hand and shaking it like a die. The Neopixel
 lights will sweep back and forth for a random number of runs, and then the Serial Monitor
 will output the activity our player must perform.
 
 Our activities include:
 
 Jumping
 Stomping
 Hopping
 Dancing
 
 Confetti background animation is an adaptation of Christy Garreau's "Meh Confetti Processing" code:
 https://gist.github.com/christygarreau/1a1aa1f23053d1562000e0b5ef4ebd96
 
 7 Dec 2023
 Carmen Peterson
 
 */

/*

 Import the Serial library into Processing so it can connect with the Arduino code
 
 */
import processing.serial.*;

Serial myPort;  // Create object from Serial class
static String val;    // Data received from the serial port
int activityNum = 0;
PFont f;

int readingTime = 10000;
int drawTime;
int prevTime;

float y;

int[] colors = {#13ADA7, #F69421, #FCF47C};
int bg = #F5F3DA;

void setup()
{
  
  size(1440, 900);
  noStroke();

  y = 0;

  myPort = new Serial(this, Serial.list()[1], 115200);

  f = createFont("Futura", 16, true);
}

void draw()
{
  /* 
   Code I took from an example on the Arduino site: 
   https://www.arduino.cc/education/visualization-with-arduino-and-processing/
   */
  if ( myPort.available() > 0) {  // If data is available,
    val = myPort.readStringUntil('\n'); 
    try {
      activityNum = Integer.valueOf(val.trim());
    }
    catch(Exception e) {
      ;
    }
    println(activityNum); // confirm receipt of prize num!
    prevTime = millis(); // note the time we received the num
    println("prevTime is");
    println(prevTime);
  }  
  
  /*
  
  Code in the probabilities of winning each prize
  
  */

  /* 
   Code to announce the prize that was won
   */

  background(bg);
  textFont(f, 90);
  textAlign(CENTER);
  fill(colors[0]);

  if (activityNum == 0) {
    text("Shake the \nCircuit Playground!", width/2, height/2-120);
  } else {
    
    if (activityNum > 0 && activityNum < 25) {
      background(bg);
      text("Jump up and down!", width/2, height/2-100);

    } else if (activityNum >=25 && activityNum < 50) {
      background(bg);
      text("Stomp your feet!", width/2, height/2-100);

    } else if (activityNum >= 50 && activityNum < 75) {
      background(bg);
      text("Hop on one foot!", width/2, height/2-100);

    } else if (activityNum >= 75) {
      background(bg);
      text("Dance around!", width/2, height/2-100);

    }
    
      drawTime = millis();
      println("drawtime is ");
      println(drawTime);

      confetti();
  }

  println("time passed is");
  println(drawTime - prevTime);

  if (drawTime - prevTime > readingTime) {
    activityNum = 0;
    y = 0;
  }
}

void confetti() {
  for (int i = 0; i < width / 50; i++) {
    for (int j = 0; j < height/50; j++) {
      float rand1 = random(30);
      float rand2 = random(30);
      noStroke();
      fill(colors[round(random(0,2))]);
      ellipse(i*100 + rand1-rand2+15, y+rand1-rand2 + (j*50) - 100, 10, 15);
    }
  }
  y += 10;
}
