#include <iostream>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SOIL.h>
#include <string.h>
#include <stdio.h>
#include <list>
#include <time.h>
#include <map>
#include <algorithm>
#include <ctime>
#include <windows.h>
#define STB_IMAGE_IMPLEMENTATION
using namespace std;

int delta, lastTime;

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


int Engine::zmienna = 0;
Engine* Engine::m_instanceSingleton = NULL;
/*
GLint LoadGLTexture(const char *filename, int width, int height)
{
     GLuint texture;
     unsigned char *data;
     FILE *file;

     // open texture data
     file = fopen(filename, "r");
     if (file == NULL) return 0;

     // allocate buffer
     data = (unsigned char*) malloc(width * height * 4);

     //read texture data
     fread(data, width * height * 4, 1, file);
     fclose(file);


    texture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture
	(
		"face.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);


    // check for an error during the load process
    if(texture == 0)
    {
	    //printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }

    glGenTextures(1, &texture); // allocate a texture name
    glBindTexture(GL_TEXTURE_2D, texture); // select our current texture
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);  // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // when texture area is large, bilinear filter the first mipmap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // texture should tile
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data); // build our texture mipmaps
    free(data);  // free buffer
    return texture;
}
*/
void display() {
        // Menu //
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
     glEnable(GL_TEXTURE_2D) ;
/*
    GLuint texture = LoadGLTexture("tex1.png", 345, 70);

    glBindTexture( GL_TEXTURE_2D, texture );
*/
    glBegin(GL_QUADS);

    glVertex2f(500, 600);
    glVertex2f(900, 600);
    glVertex2f(900, 700);
    glVertex2f(500, 700);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(500, 400);
    glVertex2f(900, 400);
    glVertex2f(900, 450);
    glVertex2f(500, 450);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(500, 300);
    glVertex2f(900, 300);
    glVertex2f(900, 350);
    glVertex2f(500, 350);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(500, 200);
    glVertex2f(900, 200);
    glVertex2f(900, 250);
    glVertex2f(500, 250);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(500, 100);
    glVertex2f(900, 100);
    glVertex2f(900, 150);
    glVertex2f(500, 150);
   // glutSolidCone(30, 50, 2, 2);

    glEnd();
        // END MENU //
    glutSwapBuffers();
    glFlush();
}

void reshape(int Width, int Height) {

    if( Height == 0) {
        Height = 1;
    }
    glViewport(0, 0, Width, Height); // Wyśrodkowanie
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLdouble) Width, 0.0, (GLdouble) Height, 100, -100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0,0,50, 0,0,0, 0,1,0); // Kamera
}

void klawiatura(unsigned char key, int x, int y) {
     switch (key)
     {
         case 27 :
            case 'q':
                exit(0);
          break;
          case 49 :
                glutFullScreen();
          break;
          case 50 :
                glutReshapeWindow(800,600);
                glutInitWindowPosition(100,100);
                cout << "DRUGA OPCJA" << endl;
         break;
     }
}
void mouse(int button, int state, int x, int y) {

    cout << button << endl;
    cout << state << endl;
    cout << x << "," << y << endl;
}

void onIdle() {

    int time;
    time = glutGet(GLUT_ELAPSED_TIME);
    delta = time - lastTime;
    lastTime = time;
    glutPostRedisplay();
}


int main(int argc, char *argv[]) {

    Engine *game;
    game=game->getInstance();
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
        glutInitWindowPosition(100,100);
        glutInitWindowSize(800, 600);
        glutCreateWindow("STATKI 3D");
        glShadeModel(GL_SMOOTH);
        glutDisplayFunc(display);
        glutReshapeFunc(reshape);
        glutKeyboardFunc(klawiatura);
        glutMouseFunc(mouse);
        glutIdleFunc(onIdle);
        gluPerspective(45,1,2,10);
    glutMainLoop();
    return 0;
}
