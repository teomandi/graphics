#include "visuals.h"  
#include "gl/glut.h"   

using namespace std;

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	begin();

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Solar System");

	Setup();

	glutSpecialFunc(Keyboard_angle);
	glutDisplayFunc(Render);
	glutReshapeFunc(Resize);
	glutIdleFunc(Idle);

	glutMainLoop();
	return 0;
}