#include "raylib.h"

#ifndef TYPES_H
#define TYPES_H

#define TITLE "PunchProto"
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define SCREEN_HALF_W SCREEN_WIDTH/2
#define SCREEN_HALF_H SCREEN_HEIGHT/2

// Test Macros
#define FLIPPED 180
#define BOUNDS 0.5
#define FRAME_LIMIT 16

typedef enum {
  North,
  South,
  West,
  East
} Direction;

typedef struct {
  float width;
  float height;
} Size2;

typedef struct {
  int column;
  int row;
} Table2;

typedef struct {
  float speed;
  float strength;
  float health;
} BoxerStats;

typedef enum {
  Idle,
  Walk,
  Jab
} AnimationState;

typedef struct {
  Vector2 frames;
  Vector2 currentFrameset[FRAME_LIMIT];
  int index;
  int count;
  bool shouldLoop;
  float speed; // Put this to the actual frameset struct later, in milliseconds
  float currentAnimationTime;
} Animations;

typedef struct {
  Rectangle collisionBox;
  Texture2D texture;
  Vector2 position;
  Animations animations;
  Size2 size;
  Color tint;
  float rotation;
  float scale;
} BoxerSpecs;

typedef struct {
  BoxerSpecs specs;
  BoxerStats stats;
} Boxer;

#endif
