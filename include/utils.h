#ifndef UTILS_H
#define UTILS_H
#include "raylib.h"
#include "types.h"
#include "math.h"
  void setRectangleCorners(Rectangle rect, Vector2 position, float rotation, float originX, float originY, Vector2 corners[4]);
  void projectPolygon(Vector2* corners, int count, Vector2 axis, float* min, float* max);
  bool isOverlapping(float min1, float max1, float min2, float max2);
  void setCurrentHurtbox(Boxer* boxer, const FrameBox hurtbox);
  void setCurrentHitbox(Boxer* boxer, const FrameBox hitbox);
#endif
