#include <algorithm>
#include <cstdlib>

// for mac osx
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
// only for windows
#ifdef _WIN32
#include <windows.h>
#endif
// for windows and linux
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif
bool wire_indicator = true;

// function called everytime the windows is refreshed
void display()
{
    // clear window
    glClear(GL_COLOR_BUFFER_BIT);

    // draw scene
    if (wire_indicator)
    {
        glutWireTeapot(0.5);
    }else{
        glutSolidTeapot(0.5);
    }

    // flush drawing routines to the window
    glFlush();
}

// Function called everytime a key is pressed
void key(unsigned char key, int, int)
{
    switch(key)
    {
        // the 'esc' key
        case 27:
        // the 'q' key
        case 'q': exit(EXIT_SUCCESS); break;
        case 'w': wire_indicator = !wire_indicator; break;
        default: break;
    }
    glutPostRedisplay();
}

// Function called every time the main window is resized
void reshape(int width, int height)
{
    // define the viewport transformation;
    //def box pour garder l'aspect ratio
    int length_box = width;
    if (width > height)
    {
        length_box = height;
    }
    glViewport(width/2 - length_box/2, height/2 - length_box/2, length_box, length_box);
}

// Main routine
int main(int argc, char* argv[])
{
    // initialize GLUT, using any commandline parameters passed to the
    //   program
    glutInit(&argc, argv);

    // setup the size, position, and display mode for new windows
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutInitDisplayMode(GLUT_RGB);

    // create and set up a window
    glutCreateWindow("Hello, teapot!");

    // Set up the callback functions:
    // for display
    glutDisplayFunc(display);
    // for the keyboard
    glutKeyboardFunc(key);
    // for reshaping
    glutReshapeFunc(reshape);
    // define the projection transformation
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,1,10);
    // define the viewing transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // position a
    //gluLookAt(0.0,2.0,0.0,0.0,0.0,0.0,1.0,0.0,0);
    //position b
    //gluLookAt(0.0,.0,-2,0.0,0.0,0,1.0,1.0,0);
    gluLookAt(0.0,2.0,0.0,0.0,0.0,0.0,0.0,0.0,1);
    // tell GLUT to wait for events
    glutMainLoop();
}
