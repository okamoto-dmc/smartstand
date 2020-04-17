#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;
// set port number of buzzer
int SpeakerPin = 9;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  sensor.startContinuous();
  pinMode(SpeakerPin, OUTPUT);

}

void sound() {
  unsigned int i;
  for (i = 0; i < 250; i++) {
    digitalWrite(SpeakerPin, HIGH);
    delayMicroseconds(253);
    digitalWrite(SpeakerPin, LOW);
    delayMicroseconds(253);
  }
  for (i = 0; i < 500; i++) {
    digitalWrite(SpeakerPin, HIGH);
    delayMicroseconds(189);
    digitalWrite(SpeakerPin, LOW);
    delayMicroseconds(189);
  }
  delay(50);
}


void loop()
{
  unsigned int t_dist;

  t_dist = sensor.readRangeContinuousMillimeters();
  Serial.print(t_dist);
  if (sensor.timeoutOccurred()) {
    Serial.print(" TIMEOUT");
  }
  Serial.println();

  if (t_dist < 400)
  {
    if (t_dist < 200)
    {
        sound();
    }
    else
    {
      sound();
      delay(300);
    }
  } else
  {
    digitalWrite(SpeakerPin, LOW);
  }
  delay(200);
}
