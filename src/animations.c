#include "animations.h"
#include "types.h"

void setCurrentFrameset(Boxer* boxer, const Vector2* frameset, const int count) {
  boxer->specs.animations.count = count;
  for (int i = 0; i < count; i++) {
      boxer->specs.animations.currentFrameset[i] = frameset[i];
  }
}

void setCurrentHurtbox(Boxer* boxer, const FrameBox hurtbox) {
  Animations* animations = &boxer->specs.animations;
  animations->hurtbox = hurtbox;
}

void setCurrentHitbox(Boxer* boxer, const FrameBox hitbox) {
  Animations* animations = &boxer->specs.animations;
  animations->hitbox = hitbox;
}

void animationReset(Boxer* boxer) {
  Animations* anims = &boxer->specs.animations;
  if(anims->currentAnimationTime >= anims->speed) {
    anims->currentAnimationTime = 0;
  } else {
    anims->currentAnimationTime += GetFrameTime();
  }
}

void displayHurtbox(Boxer boxer) {
  Animations anims = boxer.specs.animations;
  Vector2 pos = boxer.specs.position;
  if(!anims.shouldDisplayHurtbox) return;
  Rectangle hb = anims.hitbox.shape[anims.index];
  float x = hb.x + pos.x;
  float y = hb.y + pos.y;
  float width = hb.width;
  float height = hb.height;
  DrawRectangle(x, y, width, height, RED);
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

void enableFrameDisplay(Boxer* boxer) {
  Animations* anims = &boxer->specs.animations;
  anims->shouldDisplayHurtbox = true;
  anims->shouldDisplayHitbox = true;
}
