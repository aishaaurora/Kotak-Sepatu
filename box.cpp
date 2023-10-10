/////////////////////////////////          
// box.cpp
//
// This program draws a wire box.
//
// Sumanta Guha.
/////////////////////////////////

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h> 
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


// Drawing routine.

float rotationAngle = 0.0f; // Sudut rotasi awal.
float rotationSpeed = 0.0f; // Kecepatan rotasi.
float _angle = -70.0f;  // Sudut awal rotasi meja

void drawFrameKanan(void)
{
	glColor3f(0.28, 0.16, 0.14);
	glTranslatef(5.1, -60.0, -20.0);
	glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Terapkan rotasi.
	glScalef(0.1, 55.0, 1.0);
	GLfloat material_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
	glutSolidCube(5.0); // Box.
}

void drawFrameKiri(void)
{
	glColor3f(0.28, 0.16, 0.14);
	glTranslatef(-128.0, 0.0, -20.0);
	glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Terapkan rotasi.
	glScalef(1.5, 1.45, 2.0);
	GLfloat material_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
	glutSolidCube(5.0); // Box.
}

void drawFrameBlkg(void)
{
	glColor3f(0.22, 0.16, 0.14);
	glTranslatef(52.0, 0.0, -24.0);
	glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Terapkan rotasi.
	glScalef(30.0, 1.45, 2.0);
	GLfloat material_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
	glutSolidCube(5.0); // Box.
}

void drawTumpukanRak(void)
{
	glColor3f(0.18, 0.16, 0.14);
	// Modeling transformations.
	glTranslatef(0.0, -3.0, -20.0);
	glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Terapkan rotasi.
	glScalef(3.0, 0.05, 1.0);
	GLfloat material_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
	glutSolidCube(5.0); // Box.

	for (int i = 0; i < 3; i++) {
		glTranslatef(0.0, 40.0, 0.0);
		glutSolidCube(5.0); // Kubus tambahan.
	}

}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	GLfloat light_position[] = { 0.0, 10.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glEnable(GL_LIGHT0);


	glLoadIdentity();

	// Perbarui sudut rotasi.
	rotationAngle += rotationSpeed;

	drawTumpukanRak();
	drawFrameKanan();
	drawFrameKiri();
	drawFrameBlkg();

	glDisable(GL_LIGHTING);

	glFlush();
	glutSwapBuffers();

	// Pemicu ulang penggambaran (redisplay) setiap frame.
	glutPostRedisplay();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void update(int value) {
	_angle += 1.5f;  // Tingkat rotasi
	if (_angle > 360) {
		_angle -= 360;  // Reset sudut rotasi setelah melebihi 360 derajat
	}

	glutPostRedisplay();  // Meminta tampilan ulang jendela
	glutTimerFunc(25, update, 0);  // Atur timer untuk memanggil fungsi update lagi
}

// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("rakSepatu.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	update(0);
	glutMainLoop();
}

