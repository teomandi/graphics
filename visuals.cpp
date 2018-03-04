#include "visuals.h"  
#include "gl/glut.h"   
#include "time.h"
#include <cmath>


#include <conio.h>
#include <windows.h>

using namespace std;

model md;
static float ray = 1.0;
static float transparency = 0.0;
bool flag1 = true, animate=true;

static float star_coordinates[STARCOUNT][3];
static float rotx = 0.0, roty = 0.0, turnx=0.0;

void begin() {
	srand(time(NULL));
	for (int i = 0; i < STARCOUNT; i++) {
		star_coordinates[i][0] = (static_cast<double>(std::rand()) / RAND_MAX * 1100 + 1) - 500;
		star_coordinates[i][1] = (static_cast<double>(std::rand()) / RAND_MAX * 900 + 1) - 300;
		star_coordinates[i][2] = (static_cast<double>(std::rand()) / RAND_MAX * 1100 + 1) - 500;

	}
	
}

void Render(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
														 // and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	
	//sun
	glPushMatrix();
	glTranslatef(0, 0, -300);
	glRotatef(rotx, 1, 0, 00); //gia th peristrofh ths cameras..
	glRotatef(roty, 0, 1, 00);
	glColor3f(1.0, 0.2, 0.0);							   
	glutSolidSphere(30.0,80,55);		
	//glutSolidTeapot(20.0);
	
	//sun brightness
	glPushMatrix();
	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);
	glColor4f(3, 1.2, 0.0,transparency);
	glutSolidSphere(ray*30, 80, 55);
	glPopMatrix();
	glPopMatrix();
	//end of sun




	//planet
	glPushMatrix();
	glTranslatef(0, 0, -300); // to shmeio apto opoio tha peristrefetai...o hlios
	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);
	glRotatef(6 * turnx, 0, 1, 0);//gurw apton hlio
	glTranslatef(0,0,150); //h aktina
	glRotatef(turnx, 0,1.0, 0); //gurw apton eauto tou
	glColor3f(0, 0, 1);
	glScalef(0.07, 0.07, 0.07);
	DisplayModel(md);
	//glutSolidTeapot(15.0);
	

	//moon
	glPushMatrix();
	glRotatef(rotx, 1, 0, 0); /// <<<<<------
	glRotatef(roty, 0, 1, 0);
	glTranslatef(0,0,0); //shmeio peristrofhs
	glRotatef(15*turnx, 0.0, 1.0, 0.0);
	glTranslatef(900, 0.0, 0.0); //aktina
	glColor3f(1, 0,0);
	//glutSolidTeapot(50.0);
	glScalef(0.3, 0.3, 0.3);
	DisplayModel(md);
	glPopMatrix();
	glPopMatrix();
	



	

		

	//stars
	glPushMatrix();
	glRotatef(rotx, 1, 0, -300);
	glRotatef(roty, 0, 1, -300);
	glTranslatef(0, 0, 0);
	glTranslatef(0, 0, 0);
	for (int i = 0; i < STARCOUNT; i++) {
		glPushMatrix();
		glColor3f(1, 1, 1);		
		glTranslatef(star_coordinates[i][0], star_coordinates[i][1], star_coordinates[i][2]);
		glutSolidSphere(0.1, 30, 24);


		glPushMatrix();
		glColor4f(0.8, 0.8, 0.8, transparency);
		glutSolidSphere(ray * 1, 22, 24);
		glPopMatrix();
		glPopMatrix();
	}
	glPopMatrix();
	
	

	glutSwapBuffers(); 												   
	
}

//gia sugkrish twn float
bool AlmostEqualRelative(float A, float B, float maxRelativeError)
{
	if (A == B)
		return true;
	float relativeError = fabs((A - B) / B);
	if (relativeError <= maxRelativeError)
		return true;
	return false;
}




void Idle() {
	if (animate) {
		if (AlmostEqualRelative(ray, 1.0, 0.001))flag1 = true;
		if (AlmostEqualRelative(ray, 1.5, 0.001)) flag1 = false;
		if (flag1) {
			ray += 0.05;
			transparency += 0.05;
		}
		else {

			ray -= 0.05;
			transparency -= 0.05;
		}

		turnx += 1.0f;
		glutPostRedisplay();
	}
		
}





void Keyboard_angle(int key, int x, int y){		
	switch (key)
	{
	case GLUT_KEY_END: exit(0);
		break;
	case GLUT_KEY_UP: rotx -= 4.0f;
		break;
	case GLUT_KEY_DOWN: rotx += 4.0f;
		break;
	case GLUT_KEY_LEFT: roty -= 4.0f;
		break;
	case GLUT_KEY_RIGHT: roty += 4.0f;
		break;
	case GLUT_KEY_HOME: animate = !animate;
		break;
	default: break;
	}
	glutPostRedisplay();
	
}											

void Resize(int w, int h) {
	if (h == 0) h = 1;
	glViewport(0,0,w,h);

	// Setup viewing volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);

}



void Setup(){
	ReadFile(&md);

	//Parameter handling
	glShadeModel(GL_SMOOTH);

	//(02)
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);

	// (06) // polygon rendering mode
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//Set up light source
	

	GLfloat light_position[] = { 0, 20.0, 0	, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	//gia thn diafania antikeimenwn..
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


}




void ReadFile(model *md) {		// synarthsh gia read tou planet
	char buffer[1024];
	int v_count = 0;
	int f_count = 0;
	int trash;
	ifstream obj_file("planet.obj");
	if (obj_file.fail()) exit(1);
	md->obj_points = (point*)malloc(sizeof(point) * 9122);
	md->obj_faces = (face*)malloc(sizeof(face) * 18240);
	while (obj_file.good()) {
		memset(buffer, '\0', 1024);
		obj_file >> buffer;
		if (buffer[0] == 'v' && buffer[1] == '\0') {
			obj_file >> md->obj_points[v_count].x;
			obj_file >> md->obj_points[v_count].y;
			obj_file >> md->obj_points[v_count].z;
			v_count++;
		}
		else if (buffer[0] == 'f' && buffer[1] == '\0') {
			for (int counter = 0; counter < 3; counter++) {
				obj_file >> md->obj_faces[f_count].vtx[counter];
				if (obj_file.peek() == '/') {
					obj_file.ignore(2);
					obj_file >> trash;
				}
			}
			f_count++;
		}
	}
	md->faces = f_count;
	md->vertices = v_count;
	obj_file.close();
}





void DisplayModel(model md) {		// synarthsh gia display tou planet
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < md.faces; i++) {
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[0] - 1].x, md.obj_points[md.obj_faces[i].vtx[0] - 1].y, md.obj_points[md.obj_faces[i].vtx[0] - 1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[1] - 1].x, md.obj_points[md.obj_faces[i].vtx[1] - 1].y, md.obj_points[md.obj_faces[i].vtx[1] - 1].z);
		glVertex3f(md.obj_points[md.obj_faces[i].vtx[2] - 1].x, md.obj_points[md.obj_faces[i].vtx[2] - 1].y, md.obj_points[md.obj_faces[i].vtx[2] - 1].z);
	}
	glEnd();
	glPopMatrix();
}