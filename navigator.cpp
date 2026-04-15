#include <cstdlib>

// mac
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <cmath>

#define SPEED 0.1
#define ANG_SPEED 0.5

// position "virtuelle"
float posX = 0.f, posY = 0.f, posZ = 0.f;
float rotX = 0.f, rotY = 0.f;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // petit pivot au milieu des objets
    glTranslatef(posX, posY, posZ);
    glTranslatef(0.f, 0.f, -3.f);
    glRotatef(rotX, 1.f, 0.f, 0.f);
    glRotatef(rotY, 0.f, 1.f, 0.f);
    glTranslatef(0.f, 0.f, 3.f);

    glPushMatrix();
        glTranslatef(0.f, 0.f, -3.f);
        glColor3f(1.f, 0.f, 0.f);
        glutWireTeapot(1);

        glTranslatef(0.f, 2.f, 0.f);
        glColor3f(0.f, 1.f, 0.f);
        glRotatef(90.f, 1.f, 0.f, 0.f);
        glutWireTeapot(1);
    glPopMatrix();

    glTranslatef(0.f, -2.f, -1.f);
    glColor3f(0.f, 0.f, 1.f);
    glutWireTeapot(1);

    glFlush();
}

void key(unsigned char key, int, int)
{
    switch(key)
    {
        case 27: exit(EXIT_SUCCESS); break;

        // déplacements
        case 'w': posZ += SPEED; break;
        case 's': posZ -= SPEED; break;

        case 'a': posX += SPEED; break;
        case 'd': posX -= SPEED; break;

        case 'q': posY -= SPEED; break;
        case 'z': posY += SPEED; break;

        default: break;
    }

    glutPostRedisplay();
}

void specialKey(int key, int, int)
{
    switch(key)
    {
        // rotation
        case GLUT_KEY_LEFT:  rotY += ANG_SPEED; break;
        case GLUT_KEY_RIGHT: rotY -= ANG_SPEED; break;
        case GLUT_KEY_UP:    rotX += ANG_SPEED; break;
        case GLUT_KEY_DOWN:  rotX -= ANG_SPEED; break;
        default: break;
    }

    glutPostRedisplay();
}

void reshape(int w, int h)
{
    int size = (w < h) ? w : h; // garder carré
    glViewport(w/2 - size/2, h/2 - size/2, size, size);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitWindowSize(500, 500);
    glutInitDisplayMode(GLUT_RGB);

    glutCreateWindow("navigator");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);
    glutReshapeFunc(reshape);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 10);

    glMatrixMode(GL_MODELVIEW);

    glutMainLoop();
}