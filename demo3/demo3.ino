#include <gForceDataTypes.h>
#include <gForceAdapterC.h>
#include <Arduino.h>
#define Timeout 10000
#define gforceSerial Serial2
#define MAX 188
#define MIN 188
int i = 0;
float temp_pitch = 0, temp_yaw = 0, temp_roll = 0;
bool flag=0;
//min 138 mid 188 max 238
//pitch +-90 yaw +-180 roll +-180
/* returns char count */
// pitch +-60 yaw +-75

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
  analogWrite(3, 188);
  analogWrite(4, 188);
  analogWrite(5, 188);
  // set pin mode to output
  for (i = 0; i < 54; i++)
    digitalWrite(i, LOW);
  // default set output low
  Serial.begin(115200);
  gforceSerial.begin(115200);
}

int get_pitch(int pitch) {
  float i = 0.8333333 * pitch + 188;
  if (i > 238)
    i = MAX;
  if (i < 138)
    i = MIN;
  int p = int(i);
  return p;
}
int get_yaw(int yaw) {

  float i = 0.833333 * yaw + 188;
  if (i > 238)
    i = MAX;
  if (i < 138)
    i = MIN;
  int p = int(i);
  return p;
}
int get_roll(int roll) {
  float i = 0.8333333 * roll + 188;
  if (i > 238)
    i = MAX;
  if (i < 138)
    i = MIN;
  int p = int(i);
  return p;
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
        //        Serial.print("pitch: "); Serial.print(Euler.pitch);
        //        Serial.print(", yaw: "); Serial.print(Euler.yaw);
        //        Serial.print(", roll: "); Serial.print(Euler.roll);
        //        Serial.println();
        //        Serial.println(get_pitch(Euler.pitch - temp_pitch));
        analogWrite(3, get_pitch(Euler.pitch));
        analogWrite(5, get_yaw(Euler.yaw));
        analogWrite(6, get_roll(Euler.roll));
        break;
      case GF_Data::GESTURE:
        gesture = gForceData.value.gesture;
        //          Serial.print("gesture: ");
        //          Serial.println(gesture);

        if (gesture == GF_FIST)
        {
          Serial.println("Fist");
          analogWrite(10, 138+100*flag);
          flag=flag? 0:1;
        }
//        else if (gesture == GF_SPREAD)
//        {
//          Serial.println("Spread");
//        }
//        else if (gesture == GF_WAVEIN)
//        {
//          Serial.println("WaveIn");
//        }
//        else if (gesture == GF_WAVEOUT)
//        {
//          Serial.println("WaveOut");
//        }
//        else if (gesture == GF_PINCH)
//        {
//          Serial.println("Pinch");
//        }
//        else if (gesture == GF_SHOOT)
//        {
//          Serial.println("Shoot");
//        }
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
