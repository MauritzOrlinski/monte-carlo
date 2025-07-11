#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "GL/glut.h"
#include <bits/types/siginfo_t.h>
#include <stdint.h>
#include <sys/types.h>

void draw_circle(float, float, float);
float dist(float, float, float, float);
void draw_polygon(float *, float *, size_t);
void draw_line(float x1, float y1, float x2, float y2, float w);
void write_text_roman(GLfloat x_, GLfloat y_, GLfloat s, const char *text);
void write_text_roman_mono(GLfloat x_, GLfloat y_, GLfloat s, const char *text);
#endif // !GEOMETRY_H
