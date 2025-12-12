#include "animations.h"
#include "types.h"
#include "math.h"
#include "utils.h"

void setCurrentFrameset(Boxer* boxer, const Vector2* frameset, const int count) {
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

void displayHitbox(Boxer boxer) {
  Animations anims = boxer.specs.animations;
  Vector2 pos = boxer.specs.position;

  if (!anims.shouldDisplayHitbox) return;
  int idx = anims.index;
  if (idx < 0) idx = 0;
  if (idx >= anims.hitbox.shapeCount) {
    if (anims.hitbox.isAlwaysActive && anims.hitbox.shapeCount > 0) {
      idx = 0;
    } else {
      return;
    }
  }

  Rectangle hb = anims.hitbox.shape[idx];
  float originX = boxer.specs.size.width * 0.5f;
  float originY = boxer.specs.size.height * 0.5f;

  Vector2 corners[4];
  setRectangleCorners(hb, pos, boxer.specs.rotation, originX, originY, corners);

  DrawLineV(corners[0], corners[1], YELLOW);
  DrawLineV(corners[1], corners[2], YELLOW);
  DrawLineV(corners[2], corners[3], YELLOW);
  DrawLineV(corners[3], corners[0], YELLOW);
}

void displayHurtbox(Boxer boxer) {
  Animations anims = boxer.specs.animations;
  Vector2 pos = boxer.specs.position;

  if (!anims.shouldDisplayHurtbox) return;
  int idx = anims.index;
  if (idx < 0) idx = 0;
  if (idx >= anims.hurtbox.shapeCount) {
    if (anims.hurtbox.isAlwaysActive && anims.hurtbox.shapeCount > 0) {
      idx = 0;
    } else {
      return;
    }
  }
  Rectangle hb = anims.hurtbox.shape[idx];
  float originX = boxer.specs.size.width * 0.5f;
  float originY = boxer.specs.size.height * 0.5f;

  Vector2 corners[4];
  setRectangleCorners(hb, pos, boxer.specs.rotation, originX, originY, corners);

  DrawLineV(corners[0], corners[1], RED);
  DrawLineV(corners[1], corners[2], RED);
  DrawLineV(corners[2], corners[3], RED);
  DrawLineV(corners[3], corners[0], RED);
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
