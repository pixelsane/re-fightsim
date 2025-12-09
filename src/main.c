#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "types.h"
#include "animations.h"
#include "transform.h"
#include "rendering.h"

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

void draw() {
  ClearBackground(GRAY);
  animateBoxer(testBoxer);
  animateBoxer(testBoxer2);
  displayTestHealth(testBoxer, 0);
  displayTestHealth(testBoxer2, 830);
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
