#include <SoftPWM.h>
#include "Trace.h"
#include "Keypad.h"

static char vk2pin(char vk)
{
  switch(vk)
  {
    case VK_RIGHT:
      return 8;
    case VK_UP:
      return 9;
    case VK_DOWN:
      return 10;
    case VK_LEFT:
      return 11;
    case VK_SEL:
      return 12;
  }
  // for unprocessed keys just use a builtin LED
  return 13;
}

class MyKeypad : public Keypad
{
public:
  MyKeypad(byte bPin) : Keypad(bPin) {}

  /** call backs */
  void onKeyDown(char vk)
  {
    DEBUG_PRINT("MyKeypad::onKeyDown vk="); DEBUG_PRINTDEC(vk); DEBUG_PRINTLN();
    SoftPWMSetPercent(vk2pin(vk), 50);
  }
  void onLongKeyDown(char vk)
  {
    DEBUG_PRINT("MyKeypad::onLongKeyDown vk="); DEBUG_PRINTDEC(vk); DEBUG_PRINTLN();
    SoftPWMSetPercent(vk2pin(vk), 100);
  }
  void onKeyUp(char vk)
  {
    DEBUG_PRINT("MyKeypad::onKeyUp vk="); DEBUG_PRINTDEC(vk); DEBUG_PRINTLN();
    SoftPWMSetPercent(vk2pin(vk), 0);
  }

};

MyKeypad g_kp(A0);


void setup()
{
  Serial.begin(115200);
  
  delay(1000);   
  //while(!Serial)  ; // wait for serial port to connect. Needed for Leonardo only
  DEBUG_PRINTLN("SimpleKeypad test!");

  static char pins[] = {8, 9, 10, 11, 12, 13};
  for(short int i = 0; i < (sizeof(pins)/ sizeof(pins[0])); i++)
  {
    char pin = pins[i];
    SoftPWMSet(pin, 0);
    SoftPWMSetFadeTime(pin, 100, 100);
  }

}

void loop()
{
  unsigned long now = millis();
  g_kp.getAndDispatchKey(now);
  delay(1); 
}



