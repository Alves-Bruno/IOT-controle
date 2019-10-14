// Variaveis do Serial
String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

// Variaveis do Joystick
int outputValueX = 0;
int outputValueY = 0;
int buttonState = 0;

const int analogInPinX = 1; // A1
const int analogInPinY = 2; // A2
const int digitalJoystick = 2; // D2

void setup()
{
  pinMode(buttonState, INPUT);
  Serial.begin(115200);
  inputString.reserve(200);
}

void loop() {
  buttonState = digitalRead(digitalJoystick);
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
