#include "animations.h"
#include "types.h"

void setCurrentFrameset(Boxer* boxer, Vector2* frameset, int count) {
  boxer->specs.animations.count = count;
  for (int i = 0; i < count; i++) {
      boxer->specs.animations.currentFrameset[i] = frameset[i];
  }
}

void animationReset(Boxer* boxer) {
  Animations* anims = &boxer->specs.animations;
  if(anims->currentAnimationTime >= anims->speed) {
    anims->currentAnimationTime = 0;
  } else {
    anims->currentAnimationTime += GetFrameTime();
  }
}

void frameIteration(Boxer* boxer) {
  Animations* anims = &boxer->specs.animations;
  anims->frames = anims->currentFrameset[anims->index];

  if(anims->currentAnimationTime >= anims->speed) {
    anims->index++;
    if(anims->index >= anims->count) {
      anims->index = 0;
    }
  }
}
