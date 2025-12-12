#include "raylib.h"
#include "types.h"
#include "math.h"

Vector2 getNormal(Vector2 polygon1, Vector2 polygon2) {
  Vector2 edge = {polygon2.x - polygon1.x, polygon2.y - polygon1.y};
  Vector2 normal = {-edge.y, edge.x};
  float length = sqrtf(normal.x * normal.x + normal.y * normal.y);
  normal.x /= length;
  normal.y /= length;
  return normal;
}

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

void projectPolygon(Vector2* corners, int count, Vector2 axis, float* min, float* max) {
  float dotProduct = corners[0].x * axis.x + corners[0].y * axis.y;
  *min = *max = dotProduct;
  
  for (int i = 1; i < count; i++) {
    dotProduct = corners[i].x * axis.x + corners[i].y * axis.y;
    if (dotProduct < *min) *min = dotProduct;
    if (dotProduct > *max) *max = dotProduct;
  }
}

bool isOverlapping(float min1, float max1, float min2, float max2) {
    return !(max1 < min2 || max2 < min1);
}

bool isColliding(Vector2* corners1, Vector2* corners2) {
  Vector2 axes[4];
  axes[0] = getNormal(corners1[0], corners1[1]);
  axes[1] = getNormal(corners1[1], corners1[2]);
  axes[2] = getNormal(corners2[0], corners2[1]);
  axes[3] = getNormal(corners2[1], corners2[2]);
  
  for (int i = 0; i < 4; i++) {
    float min1, max1, min2, max2;
    projectPolygon(corners1, 4, axes[i], &min1, &max1);
    projectPolygon(corners2, 4, axes[i], &min2, &max2);
    
    if (!isOverlapping(min1, max1, min2, max2)) {
      return false; 
    }
  }
  
  return true;
}

void setCurrentHurtbox(Boxer* boxer, const FrameBox hurtbox) {
  Animations* animations = &boxer->specs.animations;
  animations->hurtbox = hurtbox;
}

void setCurrentHitbox(Boxer* boxer, const FrameBox hitbox) {
  Animations* animations = &boxer->specs.animations;
  animations->hitbox = hitbox;
}
