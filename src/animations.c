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

  if (!anims.shouldDisplayHurtbox) return;
  int idx = anims.index;
  if (idx < 0) idx = 0;
  if (idx >= anims.hurtbox.shapeCount) {
    // If hurtbox is marked always active and has at least one shape, fall back to frame 0
    if (anims.hurtbox.isAlwaysActive && anims.hurtbox.shapeCount > 0) {
      idx = 0;
    } else {
      return;
    }
  }
  Rectangle hb = anims.hurtbox.shape[idx];
  float originX = boxer.specs.size.width * 0.5f;
  float originY = boxer.specs.size.height * 0.5f;

  float x = pos.x - originX + hb.x;
  float y = pos.y - originY + hb.y;
  float width = hb.width;
  float height = hb.height;

  DrawRectangleLines((int)x, (int)y, (int)width, (int)height, RED);
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
