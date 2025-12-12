#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "raylib.h"
#include "types.h"
  void initSpecs(Boxer* newBoxer);
  void initStats(Boxer* newBoxer);
  Boxer initBoxer(const char* imageFile);
  void setFacing(Boxer* boxer, Direction dir);
  void setFacingByAngle(Boxer* boxer, float angle);
  void setupRelativePosition(Boxer* blue, Boxer* red);
  Vector2 getStepSpeed(Boxer* boxer);
  void stepForward(Boxer* boxer);
  void stepBackward(Boxer* boxer);
  void stepRight(Boxer* boxer);
  void stepLeft(Boxer* boxer);
#endif
