#include <stdio.h>
#include "rendering.h"
#include "types.h"
#include "raylib.h"

void displayTestHealth(Boxer boxer, float x) {
  char buffer[32];
  sprintf(buffer, "Health: %f", boxer.stats.health);
  DrawText(buffer, x, 0, 24, RAYWHITE);
}

void renderBoxer(Boxer boxer) {
  Vector2 frames = boxer.specs.animations.frames;
  int frameX = frames.x * boxer.specs.size.width;
  int frameY = frames.y * boxer.specs.size.height;
  Rectangle source = {frameX, frameY, boxer.specs.size.width, boxer.specs.size.height};
  Rectangle dest = {boxer.specs.position.x, boxer.specs.position.y, boxer.specs.size.width, boxer.specs.size.height};
  Vector2 origin = {dest.width/2, dest.height/2};

  DrawTexturePro(boxer.specs.texture, source, dest, origin, boxer.specs.rotation, boxer.specs.tint);
}
