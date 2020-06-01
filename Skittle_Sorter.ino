#include <Servo.h>
#define S0 2
#define S1 3
#define S2 4
#define S3 5
#define sensorOut 6

Servo topServo;
Servo bottomServo;
Servo aux;

int frequency = 0;
int color = 0;

int frequency(S2_value, S3_value) {
  digitalWrite (S2, S2_value);
  digitalWrite (S3, S3_value);
  return pulseIn (sensorOut, LOW);
}

//This function finds out what color is the skittle and depending on the color it drops into one of the three containers.
int readColor() {
  int R = frequency(LOW, LOW);
  delay (50);

  int G = frequency(HIGH, HIGH);
  delay (50);

  int B = frequency(LOW, HIGH);
  delay (50);

  // according to some research, MM's is distributed like this:
    //  26% blue. base_color: rgb(47, 159, 215)
    //  22% orange. base_color: rgb(242, 95, 34)
    //  20% green. base_color: rgb(49, 172, 85)
    //  17% yellow. base_color: rgb(255, 242, 0)
    //  8% brown. base_color: rgb(96, 58, 52)
    //  8% red. base_color: rgb(177, 18, 36)


  if(R >= 103 && R <= 160 && G >= 186 && G <= 276 && B >= 150) {
    color = 1; // Blue
  }
  else if(R >= 136 && R <= 180 && G >= 200 && G <= 240 && B >= 162) {
    color = 1; // Red
  }
  else if(R <= 137 && R >= 98 && G <= 169 && G >= 125 && B >= 137) {
    color = 3; // Yellow
  }
  else if(R <= 198 && R >= 153 && G <= 199 && G >= 160 && B >= 160) {
    color = 5; // Green
  }
  else if(R >= 187 && R <= 255 && G <= 335  && G >= 245 && B >= 179) {
    color = 5; // Violet
  }
  return color;
}


void setup() {
  pinMode (S0, OUTPUT);
  pinMode (S1, OUTPUT);
  pinMode (S2, OUTPUT);
  pinMode (S3, OUTPUT);
  pinMode (sensorOut, INPUT);

  digitalWrite (S0, HIGH);
  digitalWrite (S1, LOW);

  bottomServo.attach (8);
  topServo.attach (9);

  Serial.begin (9600);
}

void loop() {
  topServo.write (100);
  delay (500);
////////// this block controls servo speed ////////////////
  for(int i = 100; i > 32; i--) {
    topServo.write (i);
    delay (10);
  }
  delay (500);
////////////////////////////////////////////////////////////

  color = readColor ();
  delay (10);
  // initially there should have been 5 containers but i chose to put red and yellow in the first container and the green and purple ones in the third.
  switch (color) {
    case 1:
      bottomServo.write (45);
      break;
    case 2:
      bottomServo.write (50);
      break;
    case 3:
      bottomServo.write (90);
      break;
    case 4:
      bottomServo.write (100);
      break;
    case 5:
      bottomServo.write (130);
      break;
    case 0:
      break;
  }
  delay (300);

  for(int i = 32; i > 0; i--){
    topServo.write (i);
    delay (25);
  }
  delay (200);

  for(int i = 0; i < 100; i++)
  {
    topServo.write (i);
    delay (10);
  }
  color = 0;
}
