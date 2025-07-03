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

void draw_line(float x1, float y1, float x2, float y2, float w) {
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glLineWidth(w);
  glBegin(GL_LINES);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  glEnd();
  glDisable(GL_LINE_SMOOTH);
}

void write_text_roman_mono(GLfloat x_, GLfloat y_, GLfloat s,
                           const char *text) {
  glPushMatrix();
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glTranslatef(x_, y_, 0);
  glScalef(s, s, s);
  for (size_t i = 0; text[i]; i++)
    glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, text[i]);
  glDisable(GL_LINE_SMOOTH);
  glPopMatrix();
}

void write_text_roman(GLfloat x_, GLfloat y_, GLfloat s, const char *text) {
  glPushMatrix();
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glTranslatef(x_, y_, 0);
  glScalef(s, s, s);
  for (size_t i = 0; text[i]; i++)
    glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
  glDisable(GL_LINE_SMOOTH);
  glPopMatrix();
}
