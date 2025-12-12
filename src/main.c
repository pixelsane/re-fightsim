#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "types.h"
#include "animations.h"
#include "animationFrames.h"
#include "transform.h"
#include "rendering.h"
#include "utils.h"

Boxer testBoxer;
Boxer testBoxer2;

void init() {
  testBoxer = initBoxer("assets/tdchartemp.png");
  testBoxer2 = initBoxer("assets/tdchartemp.png");
  setupRelativePosition(&testBoxer2, &testBoxer);

  setFacing(&testBoxer, North);
  setFacing(&testBoxer2, South);

  setCurrentFrameset(&testBoxer2, IDLE_FRAMES, IDLE_FRAMES_COUNT);
  setCurrentHurtbox(&testBoxer2, DEFAULT_HURTBOX);

  setCurrentFrameset(&testBoxer, JAB_FRAMES, JAB_FRAMES_COUNT);
  setCurrentHurtbox(&testBoxer, JAB_HURTBOX);
  setCurrentHitbox(&testBoxer, JAB_HITBOX);

  enableFrameDisplay(&testBoxer);
  enableFrameDisplay(&testBoxer2);
}

void cleanup() {

}

void updateBoxer(Boxer* boxer) {
  frameIteration(boxer);
  animationReset(boxer);
}
void update() {
  stepForward(&testBoxer);
  stepForward(&testBoxer2);
  stepLeft(&testBoxer2);
  faceBoxer(&testBoxer, testBoxer2);
  faceBoxer(&testBoxer2, testBoxer);
  updateBoxer(&testBoxer);
  updateBoxer(&testBoxer2);
}

void draw() {
  ClearBackground(GRAY);
  renderBoxer(testBoxer);
  renderBoxer(testBoxer2);
  displayTestHealth(testBoxer, 0);
  displayTestHealth(testBoxer2, 830);
  displayHurtbox(testBoxer);
  displayHitbox(testBoxer);
  displayHurtbox(testBoxer2);
  displayHitbox(testBoxer2);
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
