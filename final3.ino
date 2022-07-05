// C++ code//
#include
int sensread_i = 0;

int sensread_f = 0;

int sound_int = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

int counter;

void setup()
{
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  Serial.begin(9600);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop()
{
  sensread_i = 0.01723 * readUltrasonicDistance(12, 11);
  delay(100); // Wait for 100 millisecond(s)
  sensread_f = 0.01723 * readUltrasonicDistance(12, 11);
  sound_int = digitalRead(7);
  Serial.println(sound_int);
  Serial.println(sensread_f - sensread_i);
  if (sensread_f - sensread_i > 20 || sensread_f - sensread_i < -20) {
    if (sound_int == HIGH) {
      Serial.println("PARTY");
      for (counter = 0; counter < 10; ++counter) {
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        delay(100); // Wait for 100 millisecond(s)
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        delay(100); // Wait for 100 millisecond(s)
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        delay(100); // Wait for 100 millisecond(s)
      }
    }
  } else {
    if (sensread_f - sensread_i > 5 || sensread_f - sensread_i < -5) {
      if (sound_int == HIGH) {
        Serial.println("SPEECH");
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        delay(3000); // Wait for 30000 millisecond(s)
      } else {
        Serial.println("WORKING");
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        delay(3000); // Wait for 30000 millisecond(s)
      }
    } else {
      if (sensread_f - sensread_i > 0 || sensread_f - sensread_i < 0) {
        if (sound_int == LOW) {
          Serial.println("MEETING");
          digitalWrite(4, HIGH);
          digitalWrite(5, LOW);
          digitalWrite(6, LOW);
          delay(3000); // Wait for 30000 millisecond(s)
        }
      } else {
        if (sensread_i == sensread_f && sound_int == LOW) {
          Serial.println("NO ACTIVITY");
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
          digitalWrite(6, LOW);
          delay(3000); // Wait for 30000 millisecond(s)
        }
      }
    }
  }
}
