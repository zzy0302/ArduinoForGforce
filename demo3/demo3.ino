#include <gForceDataTypes.h>
#include <gForceAdapterC.h>
#include <Arduino.h>
#define Timeout 10000
#define gforceSerial Serial2
int i = 0;
float temp_pitch = 0, temp_yaw = 0, temp_roll = 0;
//min 138 mid 188 max 238
//pitch +-90 yaw +-180 woll +-180
/* returns char count */
int getChar(unsigned char *data)
{
  int ret = gforceSerial.read();

  if (ret == -1)
    return 0;

  *data = (unsigned char)ret;

  return 1;
}


/* returns System time */
unsigned long HAL_GetTick(void)
{
  return millis();
}


void setup()
{
  for (i = 0; i < 45; i++)
    pinMode(i, OUTPUT);
  pinMode(47, INPUT);
  pinMode(48, INPUT);
  // set pin mode to output
  for (i = 0; i < 54; i++)
    digitalWrite(i, LOW);
  // default set output low
  Serial.begin(115200);
  gforceSerial.begin(115200);
}

int get_pitch(int pitch) {
  return 0.5555 * pitch + 188;
}
int get_pitch(int raw) {
  return 0.5555 * (raw / 2) + 188;
}
int get_pitch(int roll) {
  return 0.5555 * (roll / 2) + 188;
}

void loop()
{
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
        if (digitalRead(47)) {
          temp_pitch = Euler.pitch;
          temp_yaw = Euler.yaw;
          temp_roll = Euler.roll;
        }
        Serial.print("pitch: "); Serial.print(Euler.pitch - temp_pitch);
        Serial.print(", yaw: "); Serial.print(Euler.yaw - temp_yaw);
        Serial.print(", roll: "); Serial.print(Euler.roll - temp_roll);
        Serial.println();
        //        Serial.println(get_pitch(Euler.pitch - temp_pitch));
        analogWrite(3, get_pitch(Euler.pitch - temp_pitch));
        analogWrite(4, get_pitch(Euler.yaw - temp_yaw));
        analogWrite(5, get_pitch(Euler.roll - temp_roll));
        break;
        //    case GF_Data::GESTURE:
        //      gesture = gForceData.value.gesture;
        //      Serial.print("gesture: ");
        //      Serial.println(gesture);
        //
        //      if (gesture == GF_FIST)
        //      {
        //        Serial.println("Fist");
        //      }
        //      else if (gesture == GF_SPREAD)
        //      {
        //        Serial.println("Spread");
        //      }
        //      else if (gesture == GF_WAVEIN)
        //      {
        //        Serial.println("WaveIn");
        //      }
        //      else if (gesture == GF_WAVEOUT)
        //      {
        //        Serial.println("WaveOut");
        //      }
        //      else if (gesture == GF_PINCH)
        //      {
        //        Serial.println("Pinch");
        //      }
        //      else if (gesture == GF_SHOOT)
        //      {
        //        Serial.println("Shoot");
        //      }
        //      else if (gesture == GF_RELEASE)
        //      {
        //        Serial.println("Release");
        //      }
        //      else if (gesture == GF_UNKNOWN)
        //      {
        //        Serial.println("Unknown");
        //      }
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
