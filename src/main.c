#include "geometry.h"
#include "window.h"
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define N 100
#define SLEEP_TIME_MS 0
#define DT 0.01f
#define H 500
#define W 500
#define MAX_SPEED 20
#define PROJECT_NAME "OpenGL Template"
WindowDescr w;

struct timespec start, end;
_Bool measure = 1;
float avg = 0;
long count = 0;
float a = 0;

void display(void) {
  a = a > 1 ? 0 : a;
  a += 0.0001;
  glClear(GL_COLOR_BUFFER_BIT);
  glColor4f(a, a, 1, 1);
  draw_circle(100, 100, 100);
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
  printf("\rNeeded time: %f, Avg: %f", time_taken, avg);
  usleep(1000 * SLEEP_TIME_MS);
}

int main(int argc, char **argv) {
  w = *new_window_description(W, H);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

  glutInitWindowSize(W, H);
  glutInitWindowPosition(0, 0);

  glutCreateWindow(PROJECT_NAME);

  initiate_window(&w);

  glutIdleFunc(display);
  glutDisplayFunc(display);
  glutMainLoop();
}
