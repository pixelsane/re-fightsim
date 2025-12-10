#ifndef ANIMATIONS_H
#define ANIMATIONS_H
#include "types.h"
#include "animationFrames.h"
  void setCurrentFrameset(Boxer* boxer, Vector2* frameset, int count);
  void animationReset(Boxer* boxer);
  void frameIteration(Boxer* boxer);
#endif
