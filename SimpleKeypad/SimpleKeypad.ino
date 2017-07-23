#include "Trace.h"
#include "Keypad.h"

class MyKeypad : public Keypad
{
public:
  MyKeypad(byte bPin) : Keypad(bPin) {}

  /** call backs */
  void onKeyDown(char vk)
  {
    DEBUG_PRINT("MyKeypad::onKeyDown vk="); DEBUG_PRINTDEC(vk); DEBUG_PRINTLN();
  }
  void onLongKeyDown(char vk)
  {
    DEBUG_PRINT("MyKeypad::onLongKeyDown vk="); DEBUG_PRINTDEC(vk); DEBUG_PRINTLN();
  }
  void onKeyUp(char vk)
  {
    DEBUG_PRINT("MyKeypad::onKeyUp vk="); DEBUG_PRINTDEC(vk); DEBUG_PRINTLN();
  }

};

MyKeypad g_kp(A0);


void setup()
{
  Serial.begin(115200);
  
  delay(1000);   
  //while(!Serial)  ; // wait for serial port to connect. Needed for Leonardo only
  DEBUG_PRINTLN("SimpleKeypad test!");

}

void loop()
{
  unsigned long now = millis();
  g_kp.getAndDispatchKey(now);
  delay(1); 
}



