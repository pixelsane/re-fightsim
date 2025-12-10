#ifndef ANIMATIONFRAMES_H
#define ANIMATIONFRAMES_H
#include "types.h"
  static const Vector2 IDLE_FRAMES[] = {{0,0}};
  static const int IDLE_FRAMES_COUNT = 1;

  static const Vector2 JAB_FRAMES[] = {{0,0}, {1,0}, {2,0}};
  static const int JAB_FRAMES_COUNT = 3;

  FrameBox DEFAULT_HURTBOX = {
    shape: {{10,19,44,42}},
    isAlwaysActive: true
  };
  FrameBox JAB_HITBOX =  {
    shape: {{0,0,0,0}, {37,0,14,12}, {38,7,14,12}},
    isAlwaysActive: false,
  };
#endif
