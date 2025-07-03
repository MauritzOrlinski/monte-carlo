#include "geometry.h"
#include "window.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <endian.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? -(a) : (a))

#define N 100
#define SLEEP_TIME_MS 0
#define DT 0.01f
#define H 800
#define W 1000
#define MAX_SPEED 20
#define PROJECT_NAME "Monte Carlo integration"
#define SCALE 50
WindowDescr w;

struct timespec start, end;
_Bool measure = 1;
float avg = 0;
double area = 0;
unsigned long count = 0;
double x;
double y;

double max_x;
double min_x;

inline double get_randomf(void) {
  return ((rand() / (double)(RAND_MAX)) - 0.5) * 2;
}

inline double f(double t) {
  if (t * t > 10000) {
    return 0;
  }

  return 2 * sqrt(10000 - t * t); // function to plot
}
void draw_coordinate_system(void) {
  write_text_roman_mono(-W / 2.0f, H / 2.0f - 20, 0.1, PROJECT_NAME);

  glColor4f(1, 1, 1, 1);
  draw_line(-W / 2.0, 0, W / 2.0, 0, 1);
  draw_line(0, -H / 2.0, 0, H / 2.0, 1);
  for (int i = 1; i * SCALE < W / 2.0f; i++) {
    char str[12];
    sprintf(str, "%d", i * SCALE);
    write_text_roman_mono(i * SCALE, -10, 0.08, str);
    sprintf(str, "%d", -i * SCALE);
    write_text_roman_mono(-i * SCALE, -10, 0.08, str);
  }

  for (int i = 1; i * SCALE < H / 2.0f; i++) {
    char str[12];
    sprintf(str, "%d", i * SCALE);
    write_text_roman_mono(5, i * SCALE, 0.08, str);
    sprintf(str, "%d", -i * SCALE);
    write_text_roman_mono(5, -i * SCALE, 0.08, str);
  }
  glFlush();
}

void draw_function(size_t n, double x1, double x2) {

  double dx = (x2 - x1) / n;
  double cx = x1;
  double cy = f(cx);

  glColor4f(1, 0, 0, 1);
  for (size_t i = 0; i < n; i++) {
    draw_line((float)cx, (float)cy, (float)cx + dx, (float)f(cx + dx), 2);
    cx += dx;
    cy = f(cx);
    glFlush();
  }
}

void display(void) {
  glColor4f(0.5, 0, 0.5, 1);
  x = get_randomf() * W / 2;
  y = f(x);
  draw_line(x, 0, x, y, 1);
  // moving avg
  count++;
  area -= area / count;
  area += y / count;

  draw_coordinate_system();
  glFlush();
}

void display_measure(void) {
  clock_gettime(CLOCK_MONOTONIC, &start);
  display();
  clock_gettime(CLOCK_MONOTONIC, &end);
  double time_taken;
  time_taken = (end.tv_sec - start.tv_sec) * 1e9;
  time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
  avg += (time_taken - avg) / (++count);
  printf("\rNeeded time: %f, Avg time: %f, area approx: %f", time_taken, avg,
         area);
  usleep(1000 * SLEEP_TIME_MS);
}
int main(int argc, char **argv) {

  srand(time(NULL));
  w = *new_window_description(W, H);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowSize(W, H);
  glutInitWindowPosition(0, 0);

  glutCreateWindow(PROJECT_NAME);

  initiate_window(&w);
  draw_coordinate_system();
  draw_function(N, -W / 2.0, W / 2.0);
  glutIdleFunc(display_measure);
  glutDisplayFunc(display_measure);
  glutMainLoop();
}
