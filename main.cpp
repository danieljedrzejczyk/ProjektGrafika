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
GLuint texture[1];
int flaga_menu = 0;
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
    // Ładowanie tekstur
    int LoadGLTextures()
    {
        texture[0] = SOIL_load_OGL_texture
                     (
                         "menu.jpg",
                         SOIL_LOAD_AUTO,
                         SOIL_CREATE_NEW_ID,
                         SOIL_FLAG_INVERT_Y
                     );

        if(texture[0] == 0)
            return false;


        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

        return true;
    }

};


int Engine::zmienna = 0;
Engine* Engine::m_instanceSingleton = NULL;



void main_menu()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    main_menu(); // TEXTURA Z MENU GŁÓWNYM
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    float ratio = 1.0f * width/height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,width,height);
    gluPerspective(45,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,6.0,0.0,0.0,0.0,0.0f,1.0f,0.0f);
}

void klawiatura(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void onIdle();
void new_game_texture();
void info_game_texture();
int main(int argc, char *argv[])
{

    Engine *game;
    game=game->getInstance();
    flaga_menu = 1;
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
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    game->LoadGLTextures(); //<-- added this
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glutMainLoop();

    return 0;
}

void klawiatura(unsigned char key, int x, int y)
{
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

void mouse(int button, int state, int x, int y)
{
    cout << x << "," << y << endl;
    // FULL SCR :
    // if(x >= 460 && x <= 872 && y >= 250 && y <= 296 && flaga_menu == 1)
    // if(x >= 544 && x <= 761 && y >= 370 && y <= 416 && flaga_menu == 1)
    // if(x >= 520 && x <= 790 && y >= 482 && y <= 531 && flaga_menu == 1)
    // if(x >= 523 && x <= 781 && y >= 597 && y <= 648 && flaga_menu == 1)
    // END
    // Znalezc funkcje, ktora zwraca status okna!
    if(x >= 271 && x <= 503 && y >= 194 && y <= 233 && flaga_menu == 1)
    {
        cout << "NOWA GRA" << endl;
        if(flaga_menu == 1)
        {
            flaga_menu = 0;
            new_game_texture();
        }
    }
    if(x >= 317 && x <= 450 && y >= 286 && y <= 325 && flaga_menu == 1)
    {
        cout << "OPCJE" << endl;
    }
    if(x >= 305 && x <= 463 && y >= 375 && y <= 413 && flaga_menu == 1)
    {
        cout << "O GRZE" << endl;
        if(flaga_menu == 1)
        {
            info_game_texture();
        }
    }
    if(x >= 305 && x <= 460 && y >= 460 && y <= 506 && flaga_menu == 1)
    {
        cout << "Wyjdz" << endl;
        exit(0);
    }

}

void onIdle()
{

    int time;
    time = glutGet(GLUT_ELAPSED_TIME);
    delta = time - lastTime;
    lastTime = time;
    glutPostRedisplay();
}
// Texture in New Game
void new_game_texture()
{

    glDeleteTextures(1,texture);
    texture[0] = SOIL_load_OGL_texture
                 (
                     "nowagra.jpg",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y
                 );
}
// Texture in Info Game
void info_game_texture()
{

    glDeleteTextures(1,texture);
    texture[0] = SOIL_load_OGL_texture
                 (
                     "ogrze.jpg",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y
                 );
}
