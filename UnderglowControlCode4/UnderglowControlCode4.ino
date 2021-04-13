int loopCounter = 0;
//500 when testing, 100? normally
const int sampleDelay = 100;
int tick = 1;

//Button Pins
const int button1Pin = 2;
//A0 = pot1
//A1 = pot2
const int switch2Pin = A2;
const int switch1Pin = A3;
const int button3Pin = A5;
const int button2Pin = A4;

//Transistors R-G-B
const int redT = 9;
const int greenT = 11;
const int blueT = 10;

const int fbRedT = 3;
const int fbGreenT = 5;
const int fbBlueT = 6;

//Analog Storage
int sensorA0 = 0;
int sensorA1 = 0;

//Switches
int switch1State = 0;
int switch2State = 0;
int button1State = 0;
int button2State = 0;
int button3State = 0; // red button not working


//Button booleans
boolean red = false;
boolean green = false;
boolean blue = false;

//Brightness
int brightness = 0; // out of 255
int FADESPEED = 50; // in ms

// color variable turned into LED voltage value at end using analogWrite()
// stored: R G B
int color[] = {0,0,0};
int color2[] = {0,0,0};

//Misc Variables:
boolean start = true;

void setup() {
  Serial.begin(9600);
  pinMode(button1Pin,INPUT);
  pinMode(switch2Pin, INPUT);
  pinMode(switch1Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(button2Pin, INPUT);

//Sides
  pinMode(redT, OUTPUT);
  pinMode(greenT, OUTPUT);
  pinMode(blueT, OUTPUT);
//FrontBack
  pinMode(fbRedT, OUTPUT);
  pinMode(fbGreenT, OUTPUT);
  pinMode(fbBlueT, OUTPUT);
  }
  

void loop() {
  
  //--------------------READ__ANALOG__VALUES---------------------
  sensorA0 = analogRead(A0);
  sensorA1 = analogRead(A1);

  brightness = map(sensorA0, 0 ,1023, 0, 255);
  FADESPEED = map(sensorA1, 0, 1023, sampleDelay, 1000); 

  switch1State = digitalRead(switch1Pin);
  switch2State = digitalRead(switch2Pin);
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);
  

  
  /*
  Serial.print("Pot1: ");
  Serial.println(sensorA0);
  Serial.print("Pot2: ");
  Serial.println(sensorA1);
  */
  /*
  Serial.print(switch1State);
  Serial.print(switch2State);
  Serial.print(button1State);
  Serial.print(button2State); 
  Serial.println(button3State);
  */
 
  

  
  
//------------------------BUTTONS------------------------
  //RED
  if (button1State == 1 && !red && loopCounter > 5) {
    red = true;
    Serial.println("Red On");
    loopCounter = 0;
  } 
  if (button1State == 1 && red && loopCounter > 5) {
    red = false;
    Serial.println("Red Off");
    loopCounter = 0;
  }

  //GREEN 
  if (button2State == 1 && !green && loopCounter > 5) {
    green = true;
    Serial.println("Green On");
    loopCounter = 0;
  } 
  
  if (button2State == 1 && green && loopCounter > 5) {
    green = false;
    Serial.println("Green Off");
    loopCounter = 0;
  }

  //BLUE
  if (button3State == 1 && !blue && loopCounter > 5) {
    blue = true;
    Serial.println("Blue On");
    loopCounter = 0;
  } 
  
  if (button3State == 1 && blue && loopCounter > 5) {
    blue = false;
    Serial.println("Blue Off");
    loopCounter = 0;
  }


//------------------------INDIVIDUAL__COLOR---------------------------
if (red) {
  color[0] = brightness;
}
if (green) {
  color[1] = brightness;
}
if (blue) {
  color[2] = brightness;
}
if (red) {
  color2[0] = brightness;
}
if (green) {
  color2[1] = brightness;
}
if (blue) {
  color2[2] = brightness;
}


//-------------------------SWITCH__1---------------------------
if (switch1State == 1) {

  //SCAN COLORS
  if (blue) {
  int r, g, b;
 
  // fade from blue to violet
  for (r = 0; r < brightness+1; r++) { 
    analogWrite(redT, r);
    analogWrite(fbRedT, r);
    delay(FADESPEED/40);
  } 
  // fade from violet to red
  for (b = brightness; b > 0; b--) { 
    analogWrite(blueT, b);
    analogWrite(fbBlueT, b);
    delay(FADESPEED/40);
  } 
  // fade from red to yellow
  for (g = 0; g < brightness+1; g++) { 
    analogWrite(greenT, g);
    analogWrite(fbGreenT, g);
    delay(FADESPEED/40);
  } 
  // fade from yellow to green
  for (r = brightness; r > 0; r--) {  
    analogWrite(redT, r);
    analogWrite(fbRedT, r);
    delay(FADESPEED/40);
  } 
  // fade from green to teal
  for (b = 0; b < brightness+1; b++) { 
    analogWrite(blueT, b);
    analogWrite(fbBlueT, b);
    delay(FADESPEED/40);
  } 
  // fade from teal to blue
  for (g = brightness; g > 0; g--) { 
    analogWrite(greenT, g);
    analogWrite(fbGreenT, g);
    delay((FADESPEED-sampleDelay)/40);
  }
  }
  //RED WHITE AND BLUE 4th July
  /*
  if (green) {
    analogWrite(redT,brightness);
    analogWrite(greenT,0);
    analogWrite(blueT, 0);
    analogWrite(fbRedT, brightness);
    analogWrite(fbGreenT,0);
    analogWrite(fbBlueT,0);
    delay(FADESPEED);
    analogWrite(redT,brightness);
    analogWrite(greenT,brightness);
    analogWrite(blueT, brightness);
    analogWrite(fbRedT, brightness);
    analogWrite(fbGreenT,brightness);
    analogWrite(fbBlueT,brightness);
    delay(FADESPEED);
    analogWrite(redT,0);
    analogWrite(greenT,0);
    analogWrite(blueT, brightness);
    analogWrite(fbRedT, 0);
    analogWrite(fbGreenT,0);
    analogWrite(fbBlueT,  brightness);
    delay(FADESPEED-sampleDelay);
  }
  */
  //----------------HALLOWEEN --- SPOOKY SCARY SKELETONS------------
  //Set based on speed of song
  const int bpm = 780; // ms delay between base beats
  int gOrange = brightness/3;
  int bOrange = 0;

  if (green) {
    if (start) {
      //red yellow green -> song!
      analogWrite(redT, brightness);
      analogWrite(greenT, 0);
      analogWrite(blueT, 0);
      analogWrite(fbRedT, brightness);
      analogWrite(fbGreenT, 0);
      analogWrite(fbBlueT, 0);
      delay(1000);
      analogWrite(redT, brightness);
      analogWrite(greenT, gOrange);
      analogWrite(blueT, bOrange);
      analogWrite(fbRedT, brightness);
      analogWrite(fbGreenT, gOrange);
      analogWrite(fbBlueT, bOrange);
      delay(1000);
      analogWrite(redT, 0);
      analogWrite(greenT, brightness);
      analogWrite(blueT, 0);
      analogWrite(fbRedT, 0);
      analogWrite(fbGreenT, brightness);
      analogWrite(fbBlueT, 0);
      delay(1000);
      start = false;
    }
    //Start of song
    analogWrite(redT, brightness);
    analogWrite(greenT, gOrange);
    analogWrite(blueT, bOrange);
    analogWrite(fbRedT, brightness);
    analogWrite(fbGreenT, gOrange);
    analogWrite(fbBlueT, bOrange);
    delay(577);
    analogWrite(redT, 0);
    analogWrite(greenT, brightness);
    analogWrite(blueT, 0);
    analogWrite(fbRedT, 0);
    analogWrite(fbGreenT, brightness);
    analogWrite(fbBlueT, 0);
    delay(629);
    analogWrite(redT, brightness);
    analogWrite(greenT, gOrange);
    analogWrite(blueT, bOrange);
    analogWrite(fbRedT, brightness);
    analogWrite(fbGreenT, gOrange);
    analogWrite(fbBlueT, bOrange);
    delay(604);
    analogWrite(redT, 0);
    analogWrite(greenT, brightness);
    analogWrite(blueT, 0);
    analogWrite(fbRedT, 0);
    analogWrite(fbGreenT, brightness);
    analogWrite(fbBlueT, 0);
    delay(656);
    analogWrite(redT, brightness);
    analogWrite(greenT, gOrange);
    analogWrite(blueT, bOrange);
    analogWrite(fbRedT, brightness);
    analogWrite(fbGreenT, gOrange);
    analogWrite(fbBlueT, bOrange);
    delay(585);
    analogWrite(redT, 0);
    analogWrite(greenT, brightness);
    analogWrite(blueT, 0);
    analogWrite(fbRedT, 0);
    analogWrite(fbGreenT, brightness);
    analogWrite(fbBlueT, 0);
    delay(591);
    analogWrite(redT, brightness);
    analogWrite(greenT, gOrange);
    analogWrite(blueT, bOrange);
    analogWrite(fbRedT, brightness);
    analogWrite(fbGreenT, gOrange);
    analogWrite(fbBlueT, bOrange);
    delay(272);
    analogWrite(redT, 0);
    analogWrite(greenT, brightness);
    analogWrite(blueT, 0);
    analogWrite(fbRedT, 0);
    analogWrite(fbGreenT, brightness);
    analogWrite(fbBlueT, 0);
    delay(242);
    analogWrite(redT, brightness);
    analogWrite(greenT, gOrange);
    analogWrite(blueT, bOrange);
    analogWrite(fbRedT, brightness);
    analogWrite(fbGreenT, gOrange);
    analogWrite(fbBlueT, bOrange);
    delay(555-sampleDelay);
    analogWrite(redT, 0);
    analogWrite(greenT, 0);
    analogWrite(blueT, 0);
    analogWrite(fbRedT, 0);
    analogWrite(fbGreenT, 0);
    analogWrite(fbBlueT, 0);
  }
}


//-----------------------------SWITCH__2--------------------------------------
if (switch2State == 1) {
  //Blue and Yellow between fb and sides (Go Bears)
    if (green) {
      analogWrite(redT,0);
      analogWrite(greenT,0);
      analogWrite(blueT, brightness);
      analogWrite(fbRedT, brightness);
      analogWrite(fbGreenT,brightness);
      analogWrite(fbBlueT,0);
      delay(FADESPEED);
      analogWrite(redT,brightness);
      analogWrite(greenT,brightness);
      analogWrite(blueT, 0);
      analogWrite(fbRedT, 0);
      analogWrite(fbGreenT,0);
      analogWrite(fbBlueT,brightness);
      delay(FADESPEED-sampleDelay);  
    }

    if (blue) {
      // Use FADESPEED as a color wheel chooser
      //Red
      if (FADESPEED < sampleDelay+100) {
        analogWrite(redT, brightness);
        analogWrite(greenT, 0);
        analogWrite(blueT,0);
        analogWrite(fbRedT,brightness);
        analogWrite(fbGreenT,0);
        analogWrite(fbBlueT,0);
      }
      //Green
      if (FADESPEED < sampleDelay + 200 && FADESPEED > sampleDelay + 100) {
        analogWrite(redT,0);
        analogWrite(greenT,brightness);
        analogWrite(blueT,0);
        analogWrite(fbRedT,0);
        analogWrite(fbGreenT,brightness);
        analogWrite(fbBlueT,0);
      }
      //Blue
      if (FADESPEED < sampleDelay + 300 && FADESPEED > sampleDelay + 200) {
        analogWrite(redT,0);
        analogWrite(greenT,0);
        analogWrite(blueT,brightness);
        analogWrite(fbRedT,0);
        analogWrite(fbGreenT,0);
        analogWrite(fbBlueT,brightness);
      }
      //Yellow
      if (FADESPEED < sampleDelay + 400 && FADESPEED > sampleDelay + 300) {
        analogWrite(redT,brightness);
        analogWrite(greenT,brightness);
        analogWrite(blueT,0);
        analogWrite(fbRedT,brightness);
        analogWrite(fbGreenT,brightness);
        analogWrite(fbBlueT,0);
      }
      //Purple
      if (FADESPEED < sampleDelay + 500 && FADESPEED > sampleDelay + 400) {
        analogWrite(redT,brightness/2);
        analogWrite(greenT,0);
        analogWrite(blueT,brightness);
        analogWrite(fbRedT,brightness/2);
        analogWrite(fbGreenT,0);
        analogWrite(fbBlueT,brightness);
      }
      //Teal
      if (FADESPEED < sampleDelay + 600 && FADESPEED > sampleDelay + 500) {
        analogWrite(redT,0);
        analogWrite(greenT,brightness);
        analogWrite(blueT,brightness);
        analogWrite(fbRedT,0);
        analogWrite(fbGreenT,brightness);
        analogWrite(fbBlueT,brightness);
      }
      //Pink
      if (FADESPEED < sampleDelay + 700 && FADESPEED > sampleDelay + 600) {
        analogWrite(redT,brightness);
        analogWrite(greenT,brightness * 105/255);
        analogWrite(blueT,brightness * 180/255);
        analogWrite(fbRedT,brightness);
        analogWrite(fbGreenT,brightness * 105/255);
        analogWrite(fbBlueT,brightness * 180/255);
      }
      //Orange
      if (FADESPEED < sampleDelay + 800 && FADESPEED > sampleDelay + 700) {
        analogWrite(redT,brightness);
        analogWrite(greenT,brightness/2);
        analogWrite(blueT,0);
        analogWrite(fbRedT,brightness);
        analogWrite(fbGreenT,brightness/2);
        analogWrite(fbBlueT,0);
      }
    }
}

//Individual Color AWrite
if (switch2State == 0 && switch1State == 0) {
  analogWrite(redT,color[0]);
  analogWrite(greenT,color[1]);
  analogWrite(blueT,color[2]);
  analogWrite(fbRedT,color[0]);
  analogWrite(fbGreenT,color[1]);
  analogWrite(fbBlueT,color[2]);
}
 
  delay(sampleDelay);
  Serial.println(loopCounter);
  loopCounter++;
}
