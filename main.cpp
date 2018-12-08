#include <iostream>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glpng.h>
#include <string.h>
#include <stdio.h>
#include <list>
#include <time.h>
#include <map>
#include <algorithm>
#include <ctime>
#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
using namespace std;

class Engine
{
private:
    Engine()
    {

    }
    ~Engine()
    {

    }
    Engine(const Engine&);
    Engine& operator=(const Engine&);
    static Engine *m_instanceSingleton;

public:
    // ZMIENNE
    static int zmienna;

    // END ZMIENNNE

    static Engine & getSingleton()
    {
        static Engine singleton;
        return singleton;
    }

    static Engine* getInstance()
    {
        return (!m_instanceSingleton) ?
        m_instanceSingleton = new Engine :
        m_instanceSingleton;
    }

    // Metody

};

        void display()
    {
        // Menu //
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glBegin(GL_QUADS);
    glEnable(GL_TEXTURE_2D) ;

    glVertex2f(525, 700);
    glVertex2f(925, 700);
    glVertex2f(925, 800);
    glVertex2f(525, 800);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(525, 500);
    glVertex2f(925, 500);
    glVertex2f(925, 550);
    glVertex2f(525, 550);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(525, 400);
    glVertex2f(925, 400);
    glVertex2f(925, 450);
    glVertex2f(525, 450);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(525, 300);
    glVertex2f(925, 300);
    glVertex2f(925, 350);
    glVertex2f(525, 350);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(525, 200);
    glVertex2f(925, 200);
    glVertex2f(925, 250);
    glVertex2f(525, 250);
    glEnd();
        // END MENU //
    glutSwapBuffers();

    }
void reshape(int Width, int Height) {
    glViewport(10, 0, Width, Height); // Wyśrodkowanie
    //glViewport(0, 0, (GLsizei) Width, (GLsizei) Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();                                // Reset The Projection Matrix
    //gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
    gluOrtho2D(45.0f, (GLdouble) Width, 0.0, (GLdouble) Height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0,0,50, 0,0,0, 0,1,0); // Kamera
}

    void klawiatura(unsigned char key, int x, int y)
{
     switch (key)
     {
     case 27 :
     case 'q':
     exit(0);
     break;
     }
}


int Engine::zmienna = 0;
Engine* Engine::m_instanceSingleton = NULL;

int main(int argc, char *argv[]) {

    Engine *game;
    game=game->getInstance();
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
        glutCreateWindow(argv[0]);
        glutFullScreen();
        glShadeModel(GL_SMOOTH);
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(klawiatura);
    glutMainLoop();
    return 0;
}
