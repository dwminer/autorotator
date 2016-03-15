#define XPIN  A0
#define YPIN  A1
#define ZPIN  A2


int vals[3]; //x,y,z
int offsets[3];
float scaledVals[3];
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

  i = 0;
  for (i = 0; i < 3; i++)
  {
    offsets[i] = 0;//675/2 - vals[i];
  }
  
}

void loop() {
  vals[0] = analogRead(XPIN);
  vals[1] = analogRead(YPIN);
  vals[2] = analogRead(ZPIN);
  
  i = 0;
  for (i = 0; i < 3; i++)
  {
    scaledVals[i] = mapf(vals[i] + offsets[i], 0, 675, -3.0, 3.0);
    Serial.print(scaledVals[i]);
    Serial.print(" ");
  }
  Serial.print("\n\n");

  delay(500);
}

float mapf(long x, long in_min, long in_max, float out_min, float out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

