#include "geometry.h"
#include <GL/gl.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#define PI 3.1415926535f

void draw_circle(float cx, float cy, float r) {
  glBegin(GL_POLYGON);
  size_t n = 2 * PI * r + 1;
  for (size_t i = 0; i <= n; i += 4) {
    glVertex2f(cx + (r * cos(i * (2.0f * PI) / n)),
               cy + (r * sin(i * (2.0f * PI) / n)));
  }
  glEnd();
}

float fast_sqrt(float x) {
  union {
    float f;
    uint32_t i;
  } conv = {.f = x};
  conv.i = 0x5f3759df - (conv.i >> 1);
  // conv.f *= 1.5F - (x * 0.5F * conv.f * conv.f);
  return 1 / conv.f;
}

float dist(float x1, float y1, float x2, float y2) {
  float x_diff = x1 - x2;
  float y_diff = y1 - y2;
  return fast_sqrt(x_diff * x_diff + y_diff * y_diff);
}

void draw_polygon(float *x, float *y, size_t n) {
  glBegin(GL_POLYGON);
  for (size_t i = 0; i < n; ++i) {
    glVertex2f(x[i], y[i]);
  }
  glEnd();
}

void draw_plot_segment(float x1, float y1, float x2, float y2, float w) {
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glLineWidth(w);
  glBegin(GL_LINES);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glEnd();
  glDisable(GL_LINE_SMOOTH);
}

void render_bitmap_string(float x, float y, void *font, const char *string) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();   // save
  glLoadIdentity(); // and clear
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST); // also disable the depth test so renders on top

  glRasterPos2f(x, y); // center of screen. (-1,0) is center left.
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  do
    glutBitmapCharacter(font, *string);
  while (*(++string));

  glEnable(GL_DEPTH_TEST); // Turn depth testing back on

  glMatrixMode(GL_PROJECTION);
  glPopMatrix(); // revert back to the matrix I had before.
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}
