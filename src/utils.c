#include "raylib.h"
#include "types.h"
#include "math.h"

void setRectangleCorners(Rectangle rect, Vector2 position, float rotation, 
                        float originX, float originY, Vector2 corners[4]) {
  float localX = rect.x - originX;
  float localY = rect.y - originY;
 
  float rad = rotation * (PI / 180.0f);
  float cosA = cosf(rad);
  float sinA = sinf(rad);

  float xs[4] = {localX, localX + rect.width, localX + rect.width, localX};
  float ys[4] = {localY, localY, localY + rect.height, localY + rect.height};

  for (int i = 0; i < 4; i++) {
    corners[i].x = position.x + (xs[i] * cosA - ys[i] * sinA);
    corners[i].y = position.y + (xs[i] * sinA + ys[i] * cosA);
  }
}
