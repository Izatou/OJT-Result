
HardwareSerial mySerial(USART3);
const int voltageSensor = PA0;
const int red = PB4;                // choose the pin for the LED
const int green = PB5;
int count = 0;

float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;

int inputPin = PC15;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status


void setup()
{
  pinMode(red, OUTPUT);      // declare LED as output
  pinMode(green, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input

  mySerial.begin(9600);

  digitalWrite(red, LOW);
  mySerial.print("exit");
  delay(2000);
}

void loop()
{
  val = digitalRead(inputPin);
  if (val == HIGH) {
    if (pirState == LOW) {

      count ++;
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH) {
      pirState = LOW;
    }
  }
  value = analogRead(voltageSensor);
  vOUT = (value * 5.0) / 1024.0;
  //vIN = vOUT / (R2 / (R1 + R2));
  vIN = value/70.0;
  if ((int)vIN > 5) {
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  }
  else {
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
  }
  mySerial.print(vIN);
  mySerial.print(":");
  mySerial.print(count);
  mySerial.print(":");
  mySerial.println(val);
  delay(1000);
}
