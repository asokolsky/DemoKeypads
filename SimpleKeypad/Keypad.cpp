#include "Keypad.h"
#include "Trace.h"

/**
 * get one of VK_xxx
 */
byte Keypad::getKey()
{
  int adc_key_in = analogRead(m_bPin);      // read the value from the sensor 
  // buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // we add approx 50 to those values and check to see if we are close

  // 1st option for speed reasons since it will be the most likely result
  if (adc_key_in > 850) return VK_NONE; 
  // For V1.1
  if (adc_key_in < 50)   return VK_RIGHT;  
//  if (adc_key_in < 250)  return VK_UP; 
  if (adc_key_in < 250)  return VK_DOWN;
  //if (adc_key_in < 450)  return VK_DOWN; 
  if (adc_key_in < 450)  return VK_UP;
  if (adc_key_in < 650)  return VK_LEFT;
  //if (adc_key_in < 850)  
    return VK_SEL;
  //return VK_NONE;
}

boolean Keypad::getAndDispatchKey(unsigned long ulNow)
{
  byte vk = getKey();
  if(vk == m_cOldKey) { 
    if(vk == VK_NONE)
      return false;
    // fire long key logic here  
    if((m_ulToFireLongKey == 0) || (ulNow < m_ulToFireLongKey))
      return false;
    m_ulToFireLongKey = 0;
    onLongKeyDown(vk);
    return true;
  }
  // vk != m_cOldKey
  if(m_cOldKey == VK_NONE) 
  {
    m_ulToFireLongKey = ulNow + s_iLongKeyDelay;
    onKeyDown(vk);
  } 
  else if(vk != VK_NONE)
  {
    // ignore transients!
    return false;
  } else {
    m_ulToFireLongKey = 0l;
    onKeyUp(m_cOldKey);
  }
  m_cOldKey = vk;
  return true;
}


