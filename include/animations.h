#include "types.h"
#ifndef ANIMATIONS_H
#define ANIMATIONS_H
  void setCurrentFrameset(Boxer* boxer, Vector2* frameset, int count);
  void animationReset(Boxer* boxer);
  void frameIteration(Boxer* boxer);
#endif
