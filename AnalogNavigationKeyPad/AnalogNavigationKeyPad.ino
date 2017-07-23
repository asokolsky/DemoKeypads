#include "Trace.h"
#include "AnalogNavigationKeyPad.h"

class MyKeypad : public AnalogNavigationKeypad
{
public:
  MyKeypad(uint8_t bPin1, uint8_t bPin2) : AnalogNavigationKeypad(bPin1, bPin2) {}

  /** call backs */
  bool onKeyDown(uint8_t vks)
  {
    DEBUG_PRINT("MyKeypad::onKeyDown vks="); DEBUG_PRINTLN(getKeyNames(vks));
    return false; 
  }
  bool onLongKeyDown(uint8_t vks)
  {
    DEBUG_PRINT("MyKeypad::onLongKeyDown vks="); DEBUG_PRINTLN(getKeyNames(vks));
    return false; 
  }
  bool onKeyUp(uint8_t vks)
  {
    DEBUG_PRINT("MyKeypad::onKeyUp vks="); DEBUG_PRINTLN(getKeyNames(vks));
    return false; 
  }

};

MyKeypad g_kp(A0, A1);


void setup()
{
  Serial.begin(115200);
  
  delay(1000);   
  //while(!Serial)  ; // wait for serial port to connect. Needed for Leonardo only
  DEBUG_PRINTLN("AnalogNavigationKeypad test!");
}

void loop()
{
  unsigned long now = millis();
  g_kp.getAndDispatchKey(now);
  delay(1); 
}

