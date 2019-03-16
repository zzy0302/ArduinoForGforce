#include <gForceAdapter.h>

GForceAdapter gforce = GForceAdapter(&Serial2);
unsigned long gTimestamp = 0;
bool flag = 0;
void pwmmode(int pin,int level)
{
  switch(level){
    case 0:
      analogWrite(pin, 0);
      break;
    case 1:
      analogWrite(pin, 64);
      break;
    case 2:
      analogWrite(pin, 128);
      break;
    case 3:
      analogWrite(pin, 192);
      break;
    case 4:
      analogWrite(pin, 255);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("setup");
  gforce.Init();
  gTimestamp = millis();
  int i;
  for (i = 0; i < 53; i++)
  {
    pinMode(i, OUTPUT);
    delay(5);
  }
  Serial.println("test complete");
}

void loop() {
  GF_Data gForceData;
  if (!flag) {
    delay(100);
    Serial.println("connecting...");
  }
  if (OK == gforce.GetGForceData(&gForceData)) {
    if (!flag)
      Serial.println("connected");
    flag = 1;
  }
  digitalWrite(11, HIGH);
  if (OK == gforce.GetGForceData(&gForceData)) {
    digitalWrite(13, HIGH);
    GF_Gesture gesture;
    switch (gForceData.type) {
      case GF_Data::QUATERNION:
        if (millis() - gTimestamp > 5000) {
          gTimestamp = millis();
          digital(0);
          Serial.println("Receive quaternion,Communication normal");
        }
        digitalWrite(11, LOW);
        break;
      case GF_Data::GESTURE:
        digitalWrite(13, LOW);
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
        gesture = gForceData.value.gesture;
        if (gesture == GF_FIST) {
          digital(1);
          Serial.println("Fist");
        } else if (gesture == GF_SPREAD) {
          digital(2);
          Serial.println("Spread");
        } else if (gesture == GF_WAVEIN) {
          digital(3);
          Serial.println("WaveIn");
        } else if (gesture == GF_WAVEOUT) {
          digital(4);
          Serial.println("WaveOut");
        } else if (gesture == GF_PINCH) {
          digital(5);
          Serial.println("Pinch");
        } else if (gesture == GF_SHOOT) {
          digital(6);
          Serial.println("Shoot");
        } else if (gesture == GF_RELEASE) {
          digital(7);
          Serial.println("Release");
        } else if (gesture == GF_UNKNOWN) {
          digital(8);
          Serial.println("Unknown");
        }
        digitalWrite(12, LOW);
        break;
      default:
        digital(0);
        break;
    }
  }
}
