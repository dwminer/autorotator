#include <math.h>
//write our own round if math.h is too big?

#define XPIN  A0
#define YPIN  A1
#define ZPIN  A2
/*
 * Turning a normally oriented screen clockwise correponds to 
 * RR_Rotate_90
 * Assuming accelerometer is mounted upright, reversed on the back of the monitor:
 * 0: x = 0, y = -1
 * 90: x = -1, y = 0
 * 180: x = 0, y = 1
 * 270: x = 1, y = 0
 */
#define RR_Rotate_0             1
#define RR_Rotate_90            2
#define RR_Rotate_180           4
#define RR_Rotate_270           8

int vals[3]; //x,y,z
float scaledVals[3];
int x, y;
int current_rotation, new_rotation;
int i;
float scaledX;

void setup() {
  Serial.begin(9600);
  pinMode(XPIN, INPUT);
  pinMode(YPIN, INPUT);
  pinMode(ZPIN, INPUT);

  vals[0] = analogRead(XPIN);
  vals[1] = analogRead(YPIN);
  vals[2] = analogRead(ZPIN);
  
}

void loop() {
  vals[0] = analogRead(XPIN);
  vals[1] = analogRead(YPIN);
  vals[2] = analogRead(ZPIN);
  
  i = 0;
  for (i = 0; i < 3; i++)
  {
    scaledVals[i] = mapf(vals[i], 0, 675, -3.0, 3.0);
  }
  
  x = round(scaledVals[0]);
  y = round(scaledVals[1]);
  if (x == 0 && y == -1)
    new_rotation = RR_Rotate_0;
  else if (x == -1 && y == 0)
    new_rotation = RR_Rotate_90;
  else if (x == 0 && y == 1)
    new_rotation = RR_Rotate_180;
  else if (x == 1 && y == 0)
    new_rotation = RR_Rotate_270;

  if (current_rotation != new_rotation)
  {
    current_rotation = new_rotation;
    Serial.print(new_rotation);
    Serial.print("\n");
  }

  delay(500);
}

float mapf(long x, long in_min, long in_max, float out_min, float out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

