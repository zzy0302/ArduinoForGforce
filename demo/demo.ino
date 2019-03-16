#include <gForceAdapter.h>

GForceAdapter gforce = GForceAdapter(&Serial2);
unsigned long gTimestamp = 0;
bool flag = 0;

void digital(int number)
{
  digitalWrite(12, HIGH);
  delay(10);
  byte DIGITAL_DISPLAY[10][8] = { //设置0-9数字所对应数组
    { 1,0,0,0,0,1,0,0 }, // = 0
    { 1,0,0,1,1,1,1,1 }, // = 1
    { 1,1,0,0,1,0,0,0 }, // = 2
    { 1,0,0,0,1,0,1,0 }, // = 3
    { 1,0,0,1,0,0,1,1 }, // = 4
    { 1,0,1,0,0,0,1,0 }, // = 5
    { 1,0,1,0,0,0,0,0 }, // = 6
    { 1,0,0,0,1,1,1,1 }, // = 7
    { 1,0,0,0,0,0,0,0 }, // = 8
    { 1,0,0,0,0,0,1,0 } // = 9
};
  switch (number) {
    case 0:
      digitalWrite(22 + 0, HIGH);
      digitalWrite(24 + 0, HIGH);
      digitalWrite(26 + 0, HIGH);
      digitalWrite(28 + 0, HIGH);
      digitalWrite(30 + 0, HIGH);
      digitalWrite(32 + 0, HIGH);
      digitalWrite(34 + 0, LOW);
      break;
    case 1:
      digitalWrite(22 + 0, LOW);
      digitalWrite(24 + 0, HIGH);
      digitalWrite(26 + 0, HIGH);
      digitalWrite(28 + 0, LOW);
      digitalWrite(30 + 0, LOW);
      digitalWrite(32 + 0, LOW);
      digitalWrite(34 + 0, LOW);
      break;
    case 2:
      digitalWrite(22 + 0, HIGH);
      digitalWrite(24 + 0, HIGH);
      digitalWrite(26 + 0, LOW);
      digitalWrite(28 + 0, HIGH);
      digitalWrite(30 + 0, HIGH);
      digitalWrite(32 + 0, LOW);
      digitalWrite(34 + 0, HIGH);
      break;
    case 3:
      digitalWrite(22 + 0, HIGH);
      digitalWrite(24 + 0, HIGH);
      digitalWrite(26 + 0, HIGH);
      digitalWrite(28 + 0, HIGH);
      digitalWrite(30 + 0, LOW);
      digitalWrite(32 + 0, LOW);
      digitalWrite(34 + 0, HIGH);
      break;
    case 4:
      digitalWrite(22 + 0, LOW);
      digitalWrite(24 + 0, HIGH);
      digitalWrite(26 + 0, HIGH);
      digitalWrite(28 + 0, LOW);
      digitalWrite(30 + 0, LOW);
      digitalWrite(32 + 0, HIGH);
      digitalWrite(34 + 0, HIGH);
      break;
    case 5:
      digitalWrite(22 + 0, HIGH);
      digitalWrite(24 + 0, LOW);
      digitalWrite(26 + 0, HIGH);
      digitalWrite(28 + 0, HIGH);
      digitalWrite(30 + 0, LOW);
      digitalWrite(32 + 0, HIGH);
      digitalWrite(34 + 0, HIGH);
      break;
    case 6:
      digitalWrite(22 + 0, HIGH);
      digitalWrite(24 + 0, LOW);
      digitalWrite(26 + 0, HIGH);
      digitalWrite(28 + 0, HIGH);
      digitalWrite(30 + 0, HIGH);
      digitalWrite(32 + 0, HIGH);
      digitalWrite(34 + 0, HIGH);
      break;
    case 7:
      digitalWrite(22 + 0, HIGH);
      digitalWrite(24 + 0, HIGH);
      digitalWrite(26 + 0, HIGH);
      digitalWrite(28 + 0, LOW);
      digitalWrite(30 + 0, LOW);
      digitalWrite(32 + 0, LOW);
      digitalWrite(34 + 0, LOW);
      break;
    case 8:
      digitalWrite(22 + 0, HIGH);
      digitalWrite(24 + 0, HIGH);
      digitalWrite(26 + 0, HIGH);
      digitalWrite(28 + 0, HIGH);
      digitalWrite(30 + 0, HIGH);
      digitalWrite(32 + 0, HIGH);
      digitalWrite(34 + 0, HIGH);
      break;
    case 9:
      digitalWrite(22 + 0, HIGH);
      digitalWrite(24 + 0, HIGH);
      digitalWrite(26 + 0, HIGH);
      digitalWrite(28 + 0, HIGH);
      digitalWrite(30 + 0, LOW);
      digitalWrite(32 + 0, HIGH);
      digitalWrite(34 + 0, HIGH);
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
  for (i = 0; i < 53; i++)
  {
    pinMode(i, OUTPUT);
    delay(5);
  }
  analogWrite(4,1);
  test_everyone();
  test_number();
  Serial.println("test complete");
  for (i = 0; i < 53; i++)
  {
    digitalWrite(i, LOW);
  }
  Serial.println("all down");
}
void test_everyone() {
  int i;
  for (i = 0; i < 53; i++)
  {
    digitalWrite(i, HIGH);
    delay(10);
    digitalWrite(i, LOW);
  }
  return;
}
void test_number() {
  int i;
  for (i = 0; i < 10; i++)
  {
    digital(i);
    delay(2000);
    Serial.print("test");
    Serial.print(i);
    Serial.println("complete");
  }
  return;
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
