#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "types.h"
#include "animations.h"
#include "transform.h"

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

void updateBoxer(Boxer* boxer) {
  frameIteration(boxer);
  animationReset(boxer);
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
