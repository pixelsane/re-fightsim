#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "uthash.h"
#include "raylib.h"
#include "types.h"
#include "animations.h"

void initSpecs(Boxer* newBoxer) {
  SetTextureFilter(newBoxer->specs.texture, TEXTURE_FILTER_POINT);
  newBoxer->specs.position = (Vector2){SCREEN_HALF_W, SCREEN_HALF_H};
  newBoxer->specs.animations.frames = (Vector2){0,0};
  newBoxer->specs.animations.index = 0;
  newBoxer->specs.animations.count = 1;
  newBoxer->specs.animations.speed = 0.5;
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

void drawBoxer(Boxer boxer) {
  // setup the animation on source later
  Vector2 frames = boxer.specs.animations.frames;
  int frameX = frames.x * boxer.specs.size.width;
  int frameY = frames.y * boxer.specs.size.height;
  Rectangle source = {frameX, frameY, boxer.specs.size.width, boxer.specs.size.height};
  Rectangle dest = {boxer.specs.position.x, boxer.specs.position.y, boxer.specs.size.width, boxer.specs.size.height};
  Vector2 origin = {dest.width/2, dest.height/2};

  DrawTexturePro(boxer.specs.texture, source, dest, origin, boxer.specs.rotation, boxer.specs.tint);
}

void updateBoxer(Boxer* boxer) {
  frameIteration(boxer);
  animationReset(boxer);
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

Boxer testBoxer;
Boxer testBoxer2;

void init() {
  testBoxer = initBoxer("assets/tdchartemp.png");
  testBoxer2 = initBoxer("assets/tdchartemp.png");
  setupRelativePosition(&testBoxer2, &testBoxer);

  setFacing(&testBoxer, North);
  setFacing(&testBoxer2, South);

  Vector2 testIdleFrames[] = {{0,0}};
  Vector2 testJabFrames[] = {{0,0}, {1,0}, {0,0}};
  setCurrentFrameset(&testBoxer2, testIdleFrames, 1);
  setCurrentFrameset(&testBoxer, testJabFrames, 3);
}

void cleanup() {

}

void update() {
  //stepForward(&testBoxer);
  //stepForward(&testBoxer2);
  updateBoxer(&testBoxer);
}

void drawTestHealth(Boxer boxer, float x) {
  char buffer[32];
  sprintf(buffer, "Health: %f", boxer.stats.health);
  DrawText(buffer, x, 0, 24, RAYWHITE);
}

void draw() {
  ClearBackground(GRAY);
  drawBoxer(testBoxer);
  drawBoxer(testBoxer2);
  drawTestHealth(testBoxer, 0);
  drawTestHealth(testBoxer2, 830);
}

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, TITLE);
  SetTargetFPS(60);
  init();

  while(!WindowShouldClose()) {
    update();

    BeginDrawing();
    draw();
    EndDrawing();
  }

  cleanup();

  return 0;
}
