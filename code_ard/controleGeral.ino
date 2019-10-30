//Written by Ahmet Burkay KIRNIK
//TR_CapaFenLisesi
//Measure Angle with a MPU-6050(GY-521)

/* Volante */

#include<Wire.h>

const int MPU_addr=0x68;
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

double x;
double y;
double z;

/**/

/* Joystick */

// Variaveis do Serial
String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
bool controller = false; // true = volante; false = joystick

// Variaveis do Joystick
int outputValueX = 0;
int outputValueY = 0;
int buttonState = 0;

const int analogInPinX = 1; // A1
const int analogInPinY = 2; // A2
const int digitalJoystick = 2; // D2

/**/

void setup()
{
  /* Joystick */
  pinMode(buttonState, INPUT);
  //Serial.begin(115200);
  inputString.reserve(200);
  /**/
  /* Volante */
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(9600);
}

void loop() {
  // Lê o estado do botão e muda o dispositivo controlador, se necessário
  buttonState = digitalRead(digitalJoystick);
    if (!buttonState) {
      controller = !controller;
      while (!digitalRead(digitalJoystick)) {}
      delay(50);
    }
    if (controller) {
      Serial.println("VOLANTE");
    } else {
      Serial.println("JOYSTICK");
    }
  // Usa o volante como dispositivo controlador
  if (controller) {
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr,14,true);
    AcX=Wire.read()<<8|Wire.read();
    AcY=Wire.read()<<8|Wire.read();
    AcZ=Wire.read()<<8|Wire.read();
      int xAng = map(AcX,minVal,maxVal,-90,90);
      int yAng = map(AcY,minVal,maxVal,-90,90);
      int zAng = map(AcZ,minVal,maxVal,-90,90);
  
         x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
         y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
         z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
  
       Serial.print("X=");
       Serial.println(x);
  
  //     Serial.print("AngleY= ");
  //     Serial.println(y);
  
  
       Serial.print("Y=");
       Serial.println(y);
  
       Serial.print("Z=");
       Serial.println(z);
  //     Serial.println("-----------------------------------------");
       delay(100);
  } 
  // Usa o joystick como dispositivo controlador
  else {
    outputValueX = analogRead(analogInPinX);
    outputValueY = analogRead(analogInPinY);
    Serial.print("X = ");
    Serial.print(outputValueX);
    Serial.print(";");
    Serial.print("Y = ");
    Serial.println(outputValueY);
    Serial.print("BOTÃO: ");
    Serial.println(!buttonState);
  }
  
}
