#include "types.h"
#include "transform.h"
#include "math.h"

void initSpecs(Boxer* newBoxer) {
  SetTextureFilter(newBoxer->specs.texture, TEXTURE_FILTER_POINT);
  newBoxer->specs.position = (Vector2){SCREEN_HALF_W, SCREEN_HALF_H};
  newBoxer->specs.animations.frames = (Vector2){0,0};
  newBoxer->specs.animations.index = 0;
  newBoxer->specs.animations.count = 1;
  newBoxer->specs.animations.speed = 0.1;
  //newBoxer->specs.animations.currentFrameset = {{0,0}};
  newBoxer->specs.size = (Size2){64,64};
  newBoxer->specs.tint = RAYWHITE;
  newBoxer->specs.rotation = 0;
  newBoxer->specs.scale = 1;
}

void initStats(Boxer* newBoxer) {
  #define DEFAULT_VAL 20
  newBoxer->stats.health = 100;
  newBoxer->stats.speed = DEFAULT_VAL;
  newBoxer->stats.strength = DEFAULT_VAL;
}

Boxer initBoxer(const char* imageFile) {
  Boxer newBoxer;
  newBoxer.specs.texture = LoadTexture(imageFile);

  initSpecs(&newBoxer);
  initStats(&newBoxer);

  return newBoxer;
}

void setFacing(Boxer* boxer, Direction dir) {
  switch(dir) {
    case North:
      boxer->specs.rotation = 0;
    break;
    case South:
      boxer->specs.rotation = 180;
    break;
    case West:
      boxer->specs.rotation = -90;
    break;
    case East:
      boxer->specs.rotation = 90;
    break;
  }
}

void setFacingByAngle(Boxer* boxer, float angle) {
  boxer->specs.rotation = angle;
}

void setupRelativePosition(Boxer* blue, Boxer* red) {
  blue->specs.position.y -= 200;
  red->specs.position.y += 200;
}

Vector2 getStepSpeed(Boxer* boxer) {
  float speed = boxer->stats.speed; //test speed
  float rad = boxer->specs.rotation * DEG2RAD;
  float dx = sin(rad);
  float dy = -cos(rad);
  float x = (dx * speed) * GetFrameTime();
  float y = (dy * speed) * GetFrameTime();
  return (Vector2){x, y};
}

void stepForward(Boxer* boxer) {
  Vector2 stepSpeed = getStepSpeed(boxer);
  boxer->specs.position.x += stepSpeed.x;
  boxer->specs.position.y += stepSpeed.y; 
}

void stepBackward(Boxer* boxer) {
  Vector2 stepSpeed = getStepSpeed(boxer);
  boxer->specs.position.x -= stepSpeed.x;
  boxer->specs.position.y -= stepSpeed.y; 
}

void stepLeft(Boxer* boxer) {
  Vector2 v = getStepSpeed(boxer);
  Vector2 left = (Vector2){ -v.y, v.x };
  boxer->specs.position.x += left.x;
  boxer->specs.position.y += left.y;
}

void stepRight(Boxer* boxer) {
  Vector2 v = getStepSpeed(boxer);
  Vector2 right = (Vector2){ v.y, -v.x };
  boxer->specs.position.x += right.x;
  boxer->specs.position.y += right.y;
}
