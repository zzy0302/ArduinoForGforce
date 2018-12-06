#include <gForceAdapter.h>

GForceAdapter gforce = GForceAdapter(&Serial2);
unsigned long gTimestamp = 0;
bool flag = 0;
void digital(int number)
{
  digitalWrite(12, HIGH);
  delay(1000);

  switch (number) {
    case 0:
      digitalWrite(2 + 0, HIGH);
      digitalWrite(3 + 0, HIGH);
      digitalWrite(4 + 0, HIGH);
      digitalWrite(5 + 0, HIGH);
      digitalWrite(6 + 0, HIGH);
      digitalWrite(7 + 0, HIGH);
      digitalWrite(8 + 0, LOW);
      break;
    case 1:
      digitalWrite(2 + 0, LOW);
      digitalWrite(3 + 0, HIGH);
      digitalWrite(4 + 0, HIGH);
      digitalWrite(5 + 0, LOW);
      digitalWrite(6 + 0, LOW);
      digitalWrite(7 + 0, LOW);
      digitalWrite(8 + 0, LOW);
      break;
    case 2:
      digitalWrite(2 + 0, HIGH);
      digitalWrite(3 + 0, HIGH);
      digitalWrite(4 + 0, LOW);
      digitalWrite(5 + 0, HIGH);
      digitalWrite(6 + 0, HIGH);
      digitalWrite(7 + 0, LOW);
      digitalWrite(8 + 0, HIGH);
      break;
    case 3:
      digitalWrite(2 + 0, HIGH);
      digitalWrite(3 + 0, HIGH);
      digitalWrite(4 + 0, HIGH);
      digitalWrite(5 + 0, HIGH);
      digitalWrite(6 + 0, LOW);
      digitalWrite(7 + 0, LOW);
      digitalWrite(8 + 0, HIGH);
      break;
    case 4:
      digitalWrite(2 + 0, LOW);
      digitalWrite(3 + 0, HIGH);
      digitalWrite(4 + 0, HIGH);
      digitalWrite(5 + 0, LOW);
      digitalWrite(6 + 0, LOW);
      digitalWrite(7 + 0, HIGH);
      digitalWrite(8 + 0, HIGH);
      break;
    case 5:
      digitalWrite(2 + 0, HIGH);
      digitalWrite(3 + 0, LOW);
      digitalWrite(4 + 0, HIGH);
      digitalWrite(5 + 0, HIGH);
      digitalWrite(6 + 0, LOW);
      digitalWrite(7 + 0, HIGH);
      digitalWrite(8 + 0, HIGH);
      break;
    case 6:
      digitalWrite(2 + 0, HIGH);
      digitalWrite(3 + 0, LOW);
      digitalWrite(4 + 0, HIGH);
      digitalWrite(5 + 0, HIGH);
      digitalWrite(6 + 0, HIGH);
      digitalWrite(7 + 0, HIGH);
      digitalWrite(8 + 0, HIGH);
      break;
    case 7:
      digitalWrite(2 + 0, HIGH);
      digitalWrite(3 + 0, HIGH);
      digitalWrite(4 + 0, HIGH);
      digitalWrite(5 + 0, LOW);
      digitalWrite(6 + 0, LOW);
      digitalWrite(7 + 0, LOW);
      digitalWrite(8 + 0, LOW);
      break;
    case 8:
      digitalWrite(2 + 0, HIGH);
      digitalWrite(3 + 0, HIGH);
      digitalWrite(4 + 0, HIGH);
      digitalWrite(5 + 0, HIGH);
      digitalWrite(6 + 0, HIGH);
      digitalWrite(7 + 0, HIGH);
      digitalWrite(8 + 0, HIGH);
      break;
    case 9:
      digitalWrite(2 + 0, HIGH);
      digitalWrite(3 + 0, HIGH);
      digitalWrite(4 + 0, HIGH);
      digitalWrite(5 + 0, HIGH);
      digitalWrite(6 + 0, LOW);
      digitalWrite(7 + 0, HIGH);
      digitalWrite(8 + 0, HIGH);
      break;
    default:
      digitalWrite(12, LOW);
      break;
      digitalWrite(12, LOW);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("setup");
  gforce.Init();
  gTimestamp = millis();
  int i;
  for (i = 0; i < 14; i++)
  {
    pinMode(i, OUTPUT);
    delay(10);
  }
  test_everyone();
  test_number();
  Serial.println("test complete");
  for (i = 0; i < 14; i++)
  {
    digitalWrite(i, LOW);
  }
  Serial.println("all down");
}
void test_everyone() {
  int i;
  for (i = 0; i < 14; i++)
  {
    digitalWrite(i, HIGH);
    delay(500);
    digitalWrite(i, LOW);
  }
  return;
}
void test_number() {
  int i;
  for (i = 0; i < 10; i++)
  {
    digital(i);
    delay(500);
    Serial.print("test");
    Serial.print(i);
    Serial.println("complete");
  }
  return;
}


void loop() {
  GF_Data gForceData;
  if (!flag)
    Serial.println("connecting...");
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
