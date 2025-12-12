#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include "types.h"
  void setCurrentFrameset(Boxer* boxer, const Vector2* frameset, const int count);
  void animationReset(Boxer* boxer);
  void frameIteration(Boxer* boxer);
  void displayHurtbox(Boxer boxer);
  void displayHitbox(Boxer boxer);
  void enableFrameDisplay(Boxer* boxer);
#endif
