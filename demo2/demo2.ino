#include <gForceAdapterC.h>
#define gforceSerial Serial2

#define Timeout 1000
//min 138 mid 188 max 238

unsigned long gTimestamp = 0;
bool flag = 0;

void pwmmode(int pin,int level)
{
  switch(level){
    case 0:
      analogWrite(pin, 138);
      break;
    case 1:
      analogWrite(pin, 163);
      break;
    case 2:
      analogWrite(pin, 188);
      break;
    case 3:
      analogWrite(pin, 213);
      break;
    case 4:
      analogWrite(pin, 238);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  gforceSerial.begin(115200);
  Serial.println("setup");
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
  delay(500);
   struct GF_Data gForceData;
  struct GF_Euler Euler;
  GF_Ret ret = GFC_GetgForcedata((&gForceData), Timeout);
  if (OK == ret)
  {
    GF_Gesture gesture;

    switch (gForceData.type)
    {
    case GF_Data::QUATERNION:
      GFC_QuaternionToEuler(&(gForceData.value.quaternion), &Euler);
      // Serial.print("pitch: "); Serial.print(Euler.pitch);
      // Serial.print(", yaw: "); Serial.print(Euler.yaw);
      // Serial.print(", roll: "); Serial.print(Euler.roll);
      // Serial.println();
      break;

    case GF_Data::GESTURE:
      gesture = gForceData.value.gesture;
      Serial.print("gesture: ");
      Serial.println(gesture);

      if (gesture == GF_FIST)
      {
        Serial.println("Fist");
      }
      else if (gesture == GF_SPREAD)
      {
        Serial.println("Spread");
      }
      else if (gesture == GF_WAVEIN)
      {
        Serial.println("WaveIn");
      }
      else if (gesture == GF_WAVEOUT)
      {
        Serial.println("WaveOut");
      }
      else if (gesture == GF_PINCH)
      {
        Serial.println("Pinch");
      }
      else if (gesture == GF_SHOOT)
      {
        Serial.println("Shoot");
      }
      else if (gesture == GF_RELEASE)
      {
        Serial.println("Release");
      }
      else if (gesture == GF_UNKNOWN)
      {
        Serial.println("Unknown");
      }

      break;

    default:
      break;
    }
  }
  else
  {
    Serial.print("GFC_GetgForcedata() returned: ");
    Serial.println(ret);
  }
}
//  
//  if (!flag) {
//    delay(100);
//    Serial.println("connecting...");
//  }
//  if (OK == gforce.GetGForceData(&gForceData)) {
//    if (!flag)
//      Serial.println("connected");
//    flag = 1;
//  }
//  digitalWrite(11, HIGH);
//  if (OK == gforce.GetGForceData(&gForceData)) {
//    digitalWrite(13, HIGH);
//    GF_Gesture gesture;
//    switch (gForceData.type) {
//      case GF_Data::QUATERNION:
//        if (millis() - gTimestamp > 5000) {
//          gTimestamp = millis();
//          digital(0);
//          Serial.println("Receive quaternion,Communication normal");
//        }
//        digitalWrite(11, LOW);
//        break;
//      case GF_Data::GESTURE:
//        digitalWrite(13, LOW);
//        digitalWrite(11, LOW);
//        digitalWrite(12, HIGH);
//        gesture = gForceData.value.gesture;
//        if (gesture == GF_FIST) {
//          
//          Serial.println("Fist");
//        } else if (gesture == GF_SPREAD) {
//          
//          Serial.println("Spread");
//        } else if (gesture == GF_WAVEIN) {
//          
//          Serial.println("WaveIn");
//        } else if (gesture == GF_WAVEOUT) {
//         
//          Serial.println("WaveOut");
//        } else if (gesture == GF_PINCH) {
//          
//          Serial.println("Pinch");
//        } else if (gesture == GF_SHOOT) {
//          
//          Serial.println("Shoot");
//        } else if (gesture == GF_RELEASE) {
//         
//          Serial.println("Release");
//        } else if (gesture == GF_UNKNOWN) {
//         
//          Serial.println("Unknown");
//        }
//        digitalWrite(12, LOW);
//        break;
//      default:
//        
//        break;
//    }
//  }
//}
