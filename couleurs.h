#ifndef COULEURS_H
#define COULEURS_H

#include <ChainableLED.h>

#define NUM_LEDS  1

ChainableLED leds(7, 8, NUM_LEDS);


void blue(){
  for (byte i=0; i<NUM_LEDS; i++)
  {
    if (i%2 == 0)
      leds.setColorRGB(i, 0, 0, 255);
  }
}
void green(){
  for (byte i=0; i<NUM_LEDS; i++)
  {
    if (i%2 == 0)
      leds.setColorRGB(i, 0, 255, 0);
  }
}
void yellow(){
  for (byte i=0; i<NUM_LEDS; i++)
  {
    if (i%2 == 0)
      leds.setColorRGB(i, 255, 155, 0);
  }
}
void orange(){
  for (byte i=0; i<NUM_LEDS; i++)
  {
    if (i%2 == 0)
      leds.setColorRGB(i, 255, 50, 0);
  }
}
void red(){
  for (byte i=0; i<NUM_LEDS; i++)
  {
    if (i%2 == 0)
      leds.setColorRGB(i, 255, 0, 0);
  }
}
void white(){
  for (byte i=0; i<NUM_LEDS; i++)
  {
    if (i%2 == 0)
      leds.setColorRGB(i, 255, 255, 255);
  }
}

#endif