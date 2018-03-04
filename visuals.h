#include <iostream>
#include <stdio.h>     
#include <cstdlib>
#include <ctime>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>

#define STARCOUNT 3000
#define MIN_DISTANCE 50

void Render();
void Resize(int w, int h);
void Setup();
void Idle();

struct point {
	float x;
	float y;
	float z;
};

struct face {
	int vtx[3];
};

struct model {
	point *obj_points;
	face *obj_faces;
	int vertices;
	int faces;
};

void begin();
void Keyboard_angle(int key, int x, int y);
void ReadFile(model *md);
void DisplayModel(model md);