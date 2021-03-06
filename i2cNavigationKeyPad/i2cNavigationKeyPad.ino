#include <Arduino.h>
#include <SoftPWM.h>
#include <avr/io.h>
#include "Trace.h"
#include "i2cNavigationKeyPad.h"

const byte MyNavKeyPadAddress = 0x27;

static uint8_t vk2pin(uint8_t vk)
{
  switch(vk)
  {
    case VK_SOFTA:
      return 6;
    case VK_SOFTB:
      return 7;
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


class MyKeypad: public i2cNavigationKeyPad
{
public:  
  MyKeypad() : i2cNavigationKeyPad(MyNavKeyPadAddress)
  {
    
  }
/*  
  bool onUserInActivity(unsigned long ulNow)
  {
    DEBUG_PRINT("MyKeypad::onUserInActivity ulNow="); DEBUG_PRINTDEC(ulNow); DEBUG_PRINTLN("");
    return false; 
  }
  
  bool onKeyAutoRepeat(uint8_t vks)
  {
    DEBUG_PRINT("MyKeypad::onKeyAutoRepeat vks="); DEBUG_PRINTLN(getKeyNames(vks));
    return false; 
  }
  */
  bool onKeyDown(uint8_t vks)
  {
    DEBUG_PRINT("MyKeypad::onKeyDown vks="); DEBUG_PRINTLN(getKeyNames(vks));
    SoftPWMSetPercent(vks, 50);
    return false; 
  }
  bool onLongKeyDown(uint8_t vks)
  {
    DEBUG_PRINT("MyKeypad::onLongKeyDown vks="); DEBUG_PRINTLN(getKeyNames(vks));
    SoftPWMSetPercent(vks, 100);
    return false; 
  }
  bool onKeyUp(uint8_t vks)
  {
    DEBUG_PRINT("MyKeypad::onKeyUp vks="); DEBUG_PRINTLN(getKeyNames(vks));
    SoftPWMSetPercent(vks, 0);
    return false; 
  }
private:
  void SoftPWMSetPercent(uint8_t vks, uint8_t pcent)
  {
    if(vks & VK_UP)
      ::SoftPWMSetPercent(vk2pin(VK_UP), pcent);
    if(vks & VK_DOWN)
      ::SoftPWMSetPercent(vk2pin(VK_DOWN), pcent);
    if(vks & VK_LEFT)
      ::SoftPWMSetPercent(vk2pin(VK_LEFT), pcent);
    if(vks & VK_RIGHT)
      ::SoftPWMSetPercent(vk2pin(VK_RIGHT), pcent);
    if(vks & VK_SEL)
      ::SoftPWMSetPercent(vk2pin(VK_SEL), pcent);
    if(vks & VK_SOFTA)
      ::SoftPWMSetPercent(vk2pin(VK_SOFTA), pcent);
    if(vks & VK_SOFTB)
      ::SoftPWMSetPercent(vk2pin(VK_SOFTB), pcent);
  }
  
};

MyKeypad g_kp;


void setup()
{  
  Serial.begin(115200);
  
  delay(1000);   
  //while(!Serial)  ; // wait for serial port to connect. Needed for Leonardo only
  DEBUG_PRINTLN("i2cNavigationKeyPad (polling) test!");
  
  static char pins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  for(short int i = 0; i < (sizeof(pins)/ sizeof(pins[0])); i++)
  {
    char pin = pins[i];
    SoftPWMSet(pin, 0);
    SoftPWMSetFadeTime(pin, 100, 100);
  }

  g_kp.setup();  
}

void loop()
{
  unsigned long ulNow = millis();
  g_kp.getAndDispatchKey(ulNow);
  delay(1); 
}

