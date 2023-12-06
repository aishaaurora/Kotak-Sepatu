//Ahamd Adyatma Akbar
//Aisha Aurora 

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

// Drawing routine.

float rotationAngleX = 0.0f, rotationAngleY = 0.0f, rotationAngleZ = 0.0f;
float rotationAngle = 0.0f;
float rotationSpeed = 0.0f;
int prevX = 0, prevY = 0;
bool mouseRotate = false;
bool rotateXAxis = true;
bool rotateYAxis = false;
bool rotateZAxis = false;  // Flag to indicate Z-axis rotation

void drawFrameKanan(void)
{
    glPushMatrix();
    glColor3f(0.28, 0.16, 0.14);
    glTranslatef(2.5, -70.0, 0.0);
    //glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Terapkan rotasi.
    glScalef(0.025, 30.0, 1.0);
    GLfloat material_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    glutSolidCube(5.0); // Box.
    glPopMatrix();
}

void drawFrameKiri(void)
{
    glPushMatrix();
    glColor3f(0.28, 0.16, 0.14);
    glTranslatef(-2.5, -70.0, 0.0);
    //glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Terapkan rotasi.
    glScalef(0.025, 30.0, 1.0);
    GLfloat material_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    glutSolidCube(5.0); // Box.
    glPopMatrix();
}

void drawFrameBlkg(void)
{
    glPushMatrix();
    glColor3f(0.22, 0.16, 0.14);
    glTranslatef(0.0, -70.0, -2.5);
    //glRotatef(rotationAngle, 0.0, 1.0, 0.0); // Terapkan rotasi.
    glScalef(1.0, 30.0, 0.01);
    GLfloat material_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    glutSolidCube(5.0); // Box.
    glPopMatrix();
}

void drawTumpukanRak(void)
{
    glColor3f(0.18, 0.16, 0.14);

    // Modeling transformations.
	glTranslatef(0.0, -3.0, -20.0);
	glRotatef(rotationAngleX, 1.0, 0.0, 0.0);  // Rotate around X-axis.
	glRotatef(rotationAngleY, 0.0, 1.0, 0.0);  // Rotate around Y-axis.
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

	gluLookAt(rotationAngleX, rotationAngleY, rotationAngleZ,  // eye position
		0.0, 0.0, 0.0,  // look at position
		0.0, 1.0, 0.0);  // up vector

    // Set up the light and enable lighting
   // glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);

    // Set the position of the light based on the camera view
    GLfloat light_position[] = { 0.0, 0.0, 5.0, 1.0 }; // Adjust as needed
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    // Set the direction of the light based on the camera view
    GLfloat light_direction[] = { 0.0, 0.0, -1.0 }; // Adjust as needed
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);

    // Set the spotlight cutoff angle and exponent if using a spotlight
    GLfloat spot_cutoff = 45.0; // Adjust as needed
    GLfloat spot_exponent = 2.0; // Adjust as needed
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);

    // Set the diffuse color of the light
    GLfloat light_diffuse[] = { 0.3, 0.0, 0.0, 0.0 }; // Adjust as needed
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    GLfloat ambient_light[] = { 0.8, 0.2, 0.2, 3.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);


    // Set up the material properties of the object
    GLfloat material_diffuse[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat material_specular[] = { 1.0, 0.0, 0.0, 0.0 };  // Adjust these values for shininess
    GLfloat material_shininess = 10.0;  // Adjust this value for shininess level

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_shininess);

    // Enable the light
    glEnable(GL_LIGHT0);

    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, 0.0f);
   // glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
    //glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
    //glRotatef(rotationAngleZ, 0.0f, 0.0f, 1.0f);

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
void keyInput(unsigned char key, int x, int y) {
    switch (key) {
    case 27:  // Escape key to exit
        exit(0);
        break;
    case ' ':  // Space key to reset rotation
        rotationAngleX = 0.0f;
        rotationAngleY = 0.0f;
        rotationAngleZ = 0.0f;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}


void mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        prevX = x;
        prevY = y;

        // Check if both left and right mouse buttons are held down
        if (button == GLUT_LEFT_BUTTON && glutGetModifiers() == (GLUT_ACTIVE_SHIFT | GLUT_ACTIVE_CTRL)) {
            rotateZAxis = true;  // Rotate around Z-axis
        }
        else if (button == GLUT_LEFT_BUTTON) {
            mouseRotate = true;
            rotateYAxis = true;  // Rotate around X-axis
        }
        else if (button == GLUT_RIGHT_BUTTON) {
            mouseRotate = true;
            rotateXAxis = true;  // Rotate around Y-axis
        }
    }
    else if (state == GLUT_UP) {
        mouseRotate = false;
        rotateXAxis = false;
        rotateYAxis = false;
        rotateZAxis = false;
    }
}

void motion(int x, int y) {
    if (mouseRotate) {
        int deltaX = x - prevX;
        int deltaY = y - prevY;

        if (rotateXAxis) {
            rotationAngleX += deltaY;
            rotationAngleX = fmod(rotationAngleX, 360.0f);
        }
        else if (rotateYAxis) {
            rotationAngleY += deltaX;
            rotationAngleY = fmod(rotationAngleY, 360.0f);
        }
        else if (rotateZAxis) {
            rotationAngleZ += deltaX + deltaY;
            rotationAngleZ = fmod(rotationAngleZ, 360.0f);
        }

        prevX = x;
        prevY = y;

        glutPostRedisplay();
    }
}


// Main routine.
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("rakSepatu.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    glutMainLoop();

    return 0;
}
