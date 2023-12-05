//Adyatma Dyma
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
    glRotatef(rotationAngle, 1.0, 1.0, 1.0); // Terapkan rotasi.
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

    glTranslatef(0.0f, 0.0f, 0.0f);
    glRotatef(rotationAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotationAngleZ, 0.0f, 0.0f, 1.0f);

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
    switch (key) {
    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            prevX = x;
            prevY = y;
            mouseRotate = true;
        }
        else if (state == GLUT_UP) {
            mouseRotate = false;
        }
    }
}

void motion(int x, int y) {
    if (mouseRotate) {
        int deltaX = x - prevX;
        int deltaY = y - prevY;

        rotationAngle += deltaX;
        rotationAngle += deltaY;
        
        rotationAngleX = fmod(rotationAngleX, 360.0f);
        rotationAngleY = fmod(rotationAngleY, 360.0f);

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
