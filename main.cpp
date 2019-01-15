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

int flaga_new_game = 0;
int flaga_options = 0;
int flaga_info_game = 0;
int flaga_exit = 0;
int flag_fullscr = 0;
int flaga_back_to_menu = 0;
int obiekt = 0;

double  kamerax=0.0,
        kameray=0.0,
        kameraz= 0.0;

double WiezcholekX1 = -0.765;
double Bok_LeftX1 = -0.788;
double Bok_RightX1 = -0.740;
double Komin_WiezcholekX1 = -0.773;
double Komin_Bok_LeftX1 = -0.755;

double WierzcholekY1 = 0.25;
double BokY1 = 0.30;
double Wierzcholek_Dla_ZY1 = 0.20;
double Komin_1_Y = 0.40;
double Komin_2_Y = 0.35;

double Dlugosc_statku = 0.3;
double Komin_1_tyl = 0.17;
double Komin_1_prz = 0.15;
double Komin_2_tyl = 0.22;
double Komin_2_prz = 0.20;
double Komin_3_tyl = 0.12;
double Komin_3_prz = 0.10;

GLfloat rtrx, zrot;

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
    // gluLookAt(0.0+kamerax,0.0+kameray,0.1,0.0,0.0,0.0, 0.0,0.6,0.0);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0f,  1.0f, 1.0f);
    glEnd();
//glMatrixMode(GL_MODELVIEW);
    //  glLoadIdentity();
}
void Oswietlenie()
{
    GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat specular[] = { 0.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPos[] = { 0.0f, 150.0f, 150.0f, 1.0f };
    GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glFrontFace(GL_CCW);
    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
    glMateriali(GL_FRONT,GL_SHININESS,128);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
}
void statek_gracza_1()
{
    Oswietlenie();
     //glTranslatef(0.0f,0.2f,0.0f);
     glRotatef(rtrx,1.0f,0.0f,0.0f);
    glPushMatrix();

    glTranslatef(0.0,-0.3,0.0);
    glBegin(GL_TRIANGLES);
    // Kadłub
    glVertex3f( WiezcholekX1, WierzcholekY1, 0.0);        // Góra trójkąta (Przednia)
    glVertex3f(Bok_LeftX1,BokY1, 0.0);         // Lewy punkt trójkąta (Przednia)
    glVertex3f( Bok_RightX1,BokY1, 0.0);       // Prawy punkt trójkąta (Przednia)
    // LEWY BOK STATKU
    glVertex3f( WiezcholekX1,WierzcholekY1, 0.0);         // Góra trójkąta (Przednia)
    glVertex3f(Bok_LeftX1,BokY1, 0.0);          // Lewy punkt trójkąta (Przednia)
    glVertex3f(WiezcholekX1,Wierzcholek_Dla_ZY1, Dlugosc_statku);         // Prawy punkt trójkąta (Glebia)

    glVertex3f( Bok_LeftX1,BokY1, 0.0);
    glVertex3f( Bok_LeftX1,BokY1, Dlugosc_statku);
    glVertex3f( WiezcholekX1,Wierzcholek_Dla_ZY1, Dlugosc_statku);
    // PRAWY BOK STATKU
    glVertex3f( WiezcholekX1,WierzcholekY1, 0.0);         // Góra trójkąta (Przednia)
    glVertex3f( Bok_RightX1,BokY1, 0.0);         // Prawy punkt trójkąta (Przednia)
    glVertex3f(WiezcholekX1,Wierzcholek_Dla_ZY1, Dlugosc_statku);         // Góra trójkąta (Glebia)

    glVertex3f( Bok_RightX1,BokY1, 0.0);        // Prawy punkt trójkąta (Przod)
    glVertex3f( Bok_RightX1,BokY1, Dlugosc_statku);       // Prawy punkt trójkąta (Glebia)
    glVertex3f( WiezcholekX1,Wierzcholek_Dla_ZY1, Dlugosc_statku);      // Góra trójkąta (Glebia)

    // POKŁAD
    glVertex3f(Bok_LeftX1,BokY1, 0.0);            // Lewy punkt trójkąta (Przednia)
    glVertex3f(Bok_LeftX1,BokY1, Dlugosc_statku);           // Lewy punkt trójkąta (Przednia)
    glVertex3f( Bok_RightX1,BokY1, Dlugosc_statku);         // Prawy punkt trójkąta (Głebia)

    glVertex3f( Bok_RightX1,BokY1, 0.0);           // Prawy punkt trójkąta (Przednia)
    glVertex3f(Bok_LeftX1,BokY1, 0.0);           // Lewy punkt trójkąta (Przednia)
    glVertex3f( Bok_RightX1,BokY1, Dlugosc_statku);         // Lewy punkt trójkąta (Glebia)

    // Kadłub TYL
    glVertex3f( WiezcholekX1,WierzcholekY1, Dlugosc_statku);         // Góra trójkąta (Glebia)
    glVertex3f(Bok_LeftX1,BokY1, Dlugosc_statku);         // Lewy punkt trójkąta (Glebia)
    glVertex3f( Bok_RightX1,BokY1, Dlugosc_statku);       // Prawy punkt trójkąta (Glebia)
    // Komin STATKU 1
    glVertex3f( Komin_WiezcholekX1, Komin_1_Y, Komin_1_prz);         // Góra trójkąta (Glebia)
    glVertex3f(Komin_Bok_LeftX1,BokY1, Komin_1_prz);         // Lewy punkt trójkąta (Glebia)
    glVertex3f( Komin_WiezcholekX1,BokY1, Komin_1_prz);       // Prawy punkt trójkąta (Glebia)

    glVertex3f( Komin_WiezcholekX1, Komin_1_Y, Komin_1_prz);         // Góra trójkąta (Glebia)
    glVertex3f(Komin_Bok_LeftX1,Komin_1_Y, Komin_1_prz);         // Lewy punkt trójkąta (Glebia)
    glVertex3f( Komin_Bok_LeftX1,BokY1, Komin_1_prz);       // Prawy punkt trójkąta (Glebia)
    // Tył komina
    glVertex3f( Komin_WiezcholekX1, Komin_1_Y, Komin_1_tyl);         // Góra trójkąta (Glebia)
    glVertex3f(Komin_Bok_LeftX1,BokY1, Komin_1_tyl);         // Lewy punkt trójkąta (Glebia)
    glVertex3f( Komin_WiezcholekX1,BokY1, Komin_1_tyl);       // Prawy punkt trójkąta (Glebia)
    glVertex3f( Komin_WiezcholekX1, Komin_1_Y, Komin_1_tyl);         // Góra trójkąta (Glebia)
    glVertex3f(Komin_Bok_LeftX1,Komin_1_Y, Komin_1_tyl);         // Lewy punkt trójkąta (Glebia)
    glVertex3f( Komin_Bok_LeftX1,BokY1, Komin_1_tyl);       // Prawy punkt trójkąta (Glebia)
    // boczna sciana
    glVertex3f( Komin_WiezcholekX1, Komin_1_Y, Komin_1_tyl);
    glVertex3f( Komin_WiezcholekX1, BokY1, Komin_1_tyl);
    glVertex3f( Komin_WiezcholekX1,BokY1, Komin_1_prz);
    glVertex3f( Komin_WiezcholekX1, BokY1, Komin_1_prz);
    glVertex3f( Komin_WiezcholekX1,Komin_1_Y, Komin_1_prz);
    glVertex3f( Komin_WiezcholekX1, Komin_1_Y, Komin_1_tyl);
    //boczna sciana
    glVertex3f( Komin_Bok_LeftX1, Komin_1_Y, Komin_1_tyl);
    glVertex3f( Komin_Bok_LeftX1,BokY1, Komin_1_tyl);
    glVertex3f( Komin_Bok_LeftX1, BokY1, Komin_1_prz);
    glVertex3f( Komin_Bok_LeftX1, BokY1, Komin_1_prz);
    glVertex3f( Komin_Bok_LeftX1,Komin_1_Y, Komin_1_prz);
    glVertex3f( Komin_Bok_LeftX1, Komin_1_Y, Komin_1_tyl);
    // Komin STATKU 2
    glVertex3f( Komin_WiezcholekX1, Komin_2_Y, Komin_2_prz);         // Góra trójkąta (Glebia)
    glVertex3f(Komin_Bok_LeftX1,BokY1, Komin_2_prz);         // Lewy punkt trójkąta (Glebia)
    glVertex3f( Komin_WiezcholekX1,BokY1, Komin_2_prz);       // Prawy punkt trójkąta (Glebia)

    glVertex3f( Komin_WiezcholekX1, Komin_2_Y, Komin_2_prz);         // Góra trójkąta (Glebia)
    glVertex3f(Komin_Bok_LeftX1,Komin_2_Y, Komin_2_prz);         // Lewy punkt trójkąta (Glebia)
    glVertex3f( Komin_Bok_LeftX1,BokY1, Komin_2_prz);       // Prawy punkt trójkąta (Glebia)

    // Tył komina
    glVertex3f( Komin_WiezcholekX1, Komin_2_Y, Komin_2_tyl);         // Góra trójkąta (Glebia)
    glVertex3f(Komin_Bok_LeftX1,BokY1, Komin_2_tyl);         // Lewy punkt trójkąta (Glebia)
    glVertex3f( Komin_WiezcholekX1,BokY1, Komin_2_tyl);       // Prawy punkt trójkąta (Glebia)
    glVertex3f( Komin_WiezcholekX1, Komin_2_Y, Komin_2_tyl);         // Góra trójkąta (Glebia)
    glVertex3f(Komin_Bok_LeftX1,Komin_2_Y, Komin_2_tyl);         // Lewy punkt trójkąta (Glebia)
    glVertex3f( Komin_Bok_LeftX1,BokY1, Komin_2_tyl);       // Prawy punkt trójkąta (Glebia)
    // boczna sciana
    glVertex3f( Komin_WiezcholekX1, Komin_2_Y, Komin_2_tyl);
    glVertex3f( Komin_WiezcholekX1, BokY1, Komin_2_tyl);
    glVertex3f( Komin_WiezcholekX1,BokY1, Komin_2_prz);
    glVertex3f( Komin_WiezcholekX1, BokY1, Komin_2_prz);
    glVertex3f( Komin_WiezcholekX1,Komin_2_Y, Komin_2_prz);
    glVertex3f( Komin_WiezcholekX1, Komin_2_Y, Komin_2_tyl);
    //boczna sciana
    glVertex3f( Komin_Bok_LeftX1, Komin_2_Y, Komin_2_tyl);
    glVertex3f( Komin_Bok_LeftX1,BokY1, Komin_2_tyl);
    glVertex3f( Komin_Bok_LeftX1, BokY1, Komin_2_prz);
    glVertex3f( Komin_Bok_LeftX1, BokY1, Komin_2_prz);
    glVertex3f( Komin_Bok_LeftX1,Komin_2_Y, Komin_2_prz);
    glVertex3f( Komin_Bok_LeftX1, Komin_2_Y, Komin_2_tyl);

    // Komin STATKU 3
    glVertex3f( Komin_WiezcholekX1, Komin_2_Y, Komin_3_prz);         // Góra trójkąta (Glebia)
    glVertex3f(Komin_Bok_LeftX1,BokY1, Komin_3_prz);         // Lewy punkt trójkąta (Glebia)
    glVertex3f( Komin_WiezcholekX1,BokY1, Komin_3_prz);       // Prawy punkt trójkąta (Glebia)

    glVertex3f( Komin_WiezcholekX1, Komin_2_Y, Komin_3_prz);         // Góra trójkąta (Glebia)
    glVertex3f(Komin_Bok_LeftX1,Komin_2_Y, Komin_3_prz);         // Lewy punkt trójkąta (Glebia)
    glVertex3f( Komin_Bok_LeftX1,BokY1, Komin_3_prz);       // Prawy punkt trójkąta (Glebia)

    // Tył komina
    glVertex3f( Komin_WiezcholekX1, Komin_2_Y, Komin_3_tyl);         // Góra trójkąta (Glebia)
    glVertex3f(Komin_Bok_LeftX1,BokY1, Komin_3_tyl);         // Lewy punkt trójkąta (Glebia)
    glVertex3f( Komin_WiezcholekX1,BokY1, Komin_3_tyl);       // Prawy punkt trójkąta (Glebia)
    glVertex3f( Komin_WiezcholekX1, Komin_2_Y, Komin_3_tyl);         // Góra trójkąta (Glebia)
    glVertex3f(Komin_Bok_LeftX1,Komin_2_Y, Komin_3_tyl);         // Lewy punkt trójkąta (Glebia)
    glVertex3f( Komin_Bok_LeftX1,BokY1, Komin_3_tyl);       // Prawy punkt trójkąta (Glebia)
    // boczna sciana
    glVertex3f( Komin_WiezcholekX1, Komin_2_Y, Komin_3_tyl);
    glVertex3f( Komin_WiezcholekX1, BokY1, Komin_3_tyl);
    glVertex3f( Komin_WiezcholekX1,BokY1, Komin_3_prz);
    glVertex3f( Komin_WiezcholekX1, BokY1, Komin_3_prz);
    glVertex3f( Komin_WiezcholekX1,Komin_2_Y, Komin_3_prz);
    glVertex3f( Komin_WiezcholekX1, Komin_2_Y, Komin_3_tyl);
    //boczna sciana
    glVertex3f( Komin_Bok_LeftX1, Komin_2_Y, Komin_3_tyl);
    glVertex3f( Komin_Bok_LeftX1,BokY1, Komin_3_tyl);
    glVertex3f( Komin_Bok_LeftX1, BokY1, Komin_3_prz);
    glVertex3f( Komin_Bok_LeftX1, BokY1, Komin_3_prz);
    glVertex3f( Komin_Bok_LeftX1,Komin_2_Y, Komin_3_prz);
    glVertex3f( Komin_Bok_LeftX1, Komin_2_Y, Komin_3_tyl);
    glEnd();

    glPopMatrix();
    rtrx+=0.2f;
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    main_menu(); // TEXTURA Z MENU GŁÓWNYM
    if(obiekt == 1)
    {
        GLuint tex;
        glGenTextures( 1, &tex);
        glBindTexture( GL_TEXTURE_2D, tex);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        float pixels[] =
        {
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 0.0f, 0.0f
        };
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
        statek_gracza_1();
        // STATKI MODELE DO PREZENTACJI
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0+kamerax,0.0+kameray,0.1+kameraz,0.0,0.0,0.0, 0.0,0.6,0.0);
        glRotatef(zrot,0.0,1.0f,0.0f);
        glTranslatef(0.0, 0.0, 0.0);

        glBegin(GL_TRIANGLES);
        // Kadłub
        glVertex3f( 0.0, 0.25, 0.0);        // Góra trójkąta (Przednia)
        glVertex3f(-0.028,0.30, 0.0);         // Lewy punkt trójkąta (Przednia)
        glVertex3f( 0.020,0.30, 0.0);       // Prawy punkt trójkąta (Przednia)
        // LEWY BOK STATKU
        glVertex3f( 0.0, 0.25, 0.0);         // Góra trójkąta (Przednia)
        glVertex3f(-0.028,0.30, 0.0);          // Lewy punkt trójkąta (Przednia)
        glVertex3f(0.0,0.25, 0.2);         // Prawy punkt trójkąta (Glebia)   (Na 0.20)

        glVertex3f( -0.028,0.30, 0.0);
        glVertex3f( -0.028,0.30, 0.2);
        glVertex3f( 0.0,0.25, 0.2);        // (Na 0.20)
        // PRAWY BOK STATKU
        glVertex3f( 0.0, 0.25, 0.0);         // Góra trójkąta (Przednia)
        glVertex3f( 0.020,0.30, 0.0);         // Prawy punkt trójkąta (Przednia)
        glVertex3f(0.0,0.25, 0.2);         // Góra trójkąta (Glebia) (Na 0.20)

        glVertex3f( 0.020,0.30, 0.0);        // Prawy punkt trójkąta (Przod)
        glVertex3f( 0.020,0.30, 0.2);       // Prawy punkt trójkąta (Glebia)
        glVertex3f( 0.0,0.25, 0.2);      // Góra trójkąta (Glebia) (Na 0.20)

        // POKŁAD
        glVertex3f(-0.028,0.30, 0.0);            // Lewy punkt trójkąta (Przednia)
        glVertex3f(-0.028,0.30, 0.2);           // Lewy punkt trójkąta (Przednia)
        glVertex3f( -0.020,0.30, 0.2);         // Prawy punkt trójkąta (Głebia)

        glVertex3f( 0.020,0.30, 0.0);           // Prawy punkt trójkąta (Przednia)
        glVertex3f(-0.028,0.30, 0.0);           // Lewy punkt trójkąta (Przednia)
        glVertex3f( 0.020,0.30, 0.2);         // Lewy punkt trójkąta (Glebia)


        // Kadłub TYL
        glVertex3f( 0.0, 0.25, 0.2);         // Góra trójkąta (Glebia)
        glVertex3f(-0.028,0.30, 0.2);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( 0.020,0.30, 0.2);       // Prawy punkt trójkąta (Glebia)

        // Komin STATKU 1
        glVertex3f( 0.005, 0.40, 0.15);         // Góra trójkąta (Glebia)
        glVertex3f(-0.013,0.30, 0.15);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( 0.005,0.30, 0.15);       // Prawy punkt trójkąta (Glebia)

        glVertex3f( 0.005, 0.40, 0.15);         // Góra trójkąta (Glebia)
        glVertex3f(-0.013,0.40, 0.15);         // Lewy punkt trójkąta (Glebia)
        glVertex3f(-0.013,0.30, 0.15);       // Prawy punkt trójkąta (Glebia)
        // Tył komina
        glVertex3f( 0.005, 0.40, 0.17);         // Góra trójkąta (Glebia)
        glVertex3f(0.005,0.30, 0.17);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.013,0.30, 0.17);       // Prawy punkt trójkąta (Glebia)
        glVertex3f( -0.013, 0.40, 0.17);         // Góra trójkąta (Glebia)
        glVertex3f(0.005,0.40, 0.17);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.013,0.30, 0.17);       // Prawy punkt trójkąta (Glebia)
        // boczna sciana
        glVertex3f( 0.005, 0.40, 0.17);
        glVertex3f( 0.005, 0.30, 0.17);
        glVertex3f( 0.005,0.30, 0.15);
        glVertex3f( 0.005, 0.30, 0.15);
        glVertex3f( 0.005,0.40, 0.15);
        glVertex3f( 0.005, 0.40, 0.17);
        //boczna sciana
        glVertex3f( -0.013, 0.40, 0.17);
        glVertex3f( -0.013,0.30, 0.17);
        glVertex3f( -0.013, 0.30, 0.15);
        glVertex3f( -0.013, 0.30, 0.15);
        glVertex3f( -0.013,0.40, 0.15);
        glVertex3f( -0.013, 0.40, 0.17);

        // Komin STATKU 2
        glVertex3f( 0.005, 0.35, 0.10);         // Góra trójkąta (Glebia)
        glVertex3f(-0.013,0.30, 0.10);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( 0.005,0.30, 0.10);       // Prawy punkt trójkąta (Glebia)

        glVertex3f( 0.005, 0.35, 0.10);         // Góra trójkąta (Glebia)
        glVertex3f(-0.013,0.35, 0.10);         // Lewy punkt trójkąta (Glebia)
        glVertex3f(-0.013,0.30, 0.10);       // Prawy punkt trójkąta (Glebia)
        // Tył komina
        glVertex3f( 0.005, 0.35, 0.12);         // Góra trójkąta (Glebia)
        glVertex3f(0.005,0.30, 0.12);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.013,0.30, 0.12);       // Prawy punkt trójkąta (Glebia)
        glVertex3f( -0.013, 0.35, 0.12);         // Góra trójkąta (Glebia)
        glVertex3f(0.005,0.35, 0.12);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.013,0.30, 0.12);       // Prawy punkt trójkąta (Glebia)
        // boczna sciana
        glVertex3f( 0.005, 0.35, 0.12);
        glVertex3f( 0.005, 0.30, 0.12);
        glVertex3f( 0.005,0.30, 0.10);
        glVertex3f( 0.005, 0.30, 0.10);
        glVertex3f( 0.005,0.35, 0.10);
        glVertex3f( 0.005, 0.40, 0.10);
        //boczna sciana
        glVertex3f( -0.013, 0.35, 0.12);
        glVertex3f( -0.013,0.30, 0.12);
        glVertex3f( -0.013, 0.30, 0.10);
        glVertex3f( -0.013, 0.30, 0.10);
        glVertex3f( -0.013,0.35, 0.10);
        glVertex3f( -0.013, 0.35, 0.12);
        glEnd();
        // STATEK 3 KOMINY POKAZ
        glBegin(GL_TRIANGLES);
        // Kadłub
        glVertex3f( 0.0, 0.00, 0.0);        // Góra trójkąta (Przednia)
        glVertex3f(-0.028,0.05, 0.0);         // Lewy punkt trójkąta (Przednia)
        glVertex3f( 0.020,0.05, 0.0);       // Prawy punkt trójkąta (Przednia)
        // LEWY BOK STATKU
        glVertex3f( 0.0, 0.00, 0.0);         // Góra trójkąta (Przednia)
        glVertex3f(-0.028,0.05, 0.0);          // Lewy punkt trójkąta (Przednia)
        glVertex3f(0.0,0.00, 0.26);         // Prawy punkt trójkąta (Glebia)

        glVertex3f( -0.028,0.05, 0.0);
        glVertex3f( -0.028,0.05, 0.26);
        glVertex3f( 0.0,0.00, 0.26);
        // PRAWY BOK STATKU
        glVertex3f( 0.0, 0.00, 0.0);         // Góra trójkąta (Przednia)
        glVertex3f( 0.020,0.05, 0.0);         // Prawy punkt trójkąta (Przednia)
        glVertex3f(0.0,0.00, 0.26);         // Góra trójkąta (Glebia)

        glVertex3f( 0.020,0.05, 0.0);        // Prawy punkt trójkąta (Przod)
        glVertex3f( 0.020,0.05, 0.26);       // Prawy punkt trójkąta (Glebia)
        glVertex3f( 0.0,0.00, 0.26);      // Góra trójkąta (Glebia)

        // POKŁAD
        glVertex3f(-0.028,0.05, 0.0);            // Lewy punkt trójkąta (Przednia)
        glVertex3f(-0.028,0.05, 0.26);           // Lewy punkt trójkąta (Przednia)
        glVertex3f( -0.020,0.05, 0.26);         // Prawy punkt trójkąta (Głebia)

        glVertex3f( 0.020,0.05, 0.0);           // Prawy punkt trójkąta (Przednia)
        glVertex3f(-0.028,0.05, 0.0);           // Lewy punkt trójkąta (Przednia)
        glVertex3f( 0.020,0.05, 0.26);         // Lewy punkt trójkąta (Glebia)


        // Kadłub TYL
        glVertex3f( 0.0, 0.00, 0.26);         // Góra trójkąta (Glebia)
        glVertex3f(-0.028,0.05, 0.26);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( 0.020,0.05, 0.26);       // Prawy punkt trójkąta (Glebia)

        // Komin STATKU 1
        glVertex3f( 0.005, 0.15, 0.15);         // Góra trójkąta (Glebia)
        glVertex3f(-0.013,0.05, 0.15);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( 0.005,0.05, 0.15);       // Prawy punkt trójkąta (Glebia)

        glVertex3f( 0.005, 0.15, 0.15);         // Góra trójkąta (Glebia)
        glVertex3f(-0.013,0.15, 0.15);         // Lewy punkt trójkąta (Glebia)
        glVertex3f(-0.013,0.05, 0.15);       // Prawy punkt trójkąta (Glebia)
        // Tył komina
        glVertex3f( 0.005, 0.15, 0.17);         // Góra trójkąta (Glebia)
        glVertex3f(0.005,0.05, 0.17);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.013,0.05, 0.17);       // Prawy punkt trójkąta (Glebia)
        glVertex3f( -0.013, 0.15, 0.17);         // Góra trójkąta (Glebia)
        glVertex3f(0.005,0.15, 0.17);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.013,0.05, 0.17);       // Prawy punkt trójkąta (Glebia)
        // boczna sciana
        glVertex3f( 0.005, 0.15, 0.17);
        glVertex3f( 0.005, 0.05, 0.17);
        glVertex3f( 0.005,0.05, 0.15);
        glVertex3f( 0.005, 0.05, 0.15);
        glVertex3f( 0.005,0.15, 0.15);
        glVertex3f( 0.005, 0.15, 0.17);
        //boczna sciana
        glVertex3f( -0.013, 0.15, 0.17);
        glVertex3f( -0.013,0.05, 0.17);
        glVertex3f( -0.013, 0.05, 0.15);
        glVertex3f( -0.013, 0.05, 0.15);
        glVertex3f( -0.013,0.15, 0.15);
        glVertex3f( -0.013, 0.15, 0.17);
        // Komin STATKU 2
        glVertex3f( 0.005, 0.10, 0.10);         // Góra trójkąta (Glebia)
        glVertex3f(-0.013,0.05, 0.10);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( 0.005,0.05, 0.10);       // Prawy punkt trójkąta (Glebia)

        glVertex3f( 0.005, 0.10, 0.10);         // Góra trójkąta (Glebia)
        glVertex3f(-0.013,0.10, 0.10);         // Lewy punkt trójkąta (Glebia)
        glVertex3f(-0.013,0.05, 0.10);       // Prawy punkt trójkąta (Glebia)
        // Tył komina
        glVertex3f( 0.005, 0.10, 0.12);         // Góra trójkąta (Glebia)
        glVertex3f(0.005,0.05, 0.12);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.013,0.05, 0.12);       // Prawy punkt trójkąta (Glebia)
        glVertex3f( -0.013, 0.10, 0.12);         // Góra trójkąta (Glebia)
        glVertex3f(0.005,0.10, 0.12);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.013,0.05, 0.12);       // Prawy punkt trójkąta (Glebia)
        // boczna sciana
        glVertex3f( 0.005, 0.10, 0.12);
        glVertex3f( 0.005, 0.05, 0.12);
        glVertex3f( 0.005,0.05, 0.10);
        glVertex3f( 0.005, 0.05, 0.10);
        glVertex3f( 0.005,0.10, 0.10);
        glVertex3f( 0.005, 0.15, 0.10);
        //boczna sciana
        glVertex3f( -0.013, 0.10, 0.12);
        glVertex3f( -0.013,0.05, 0.12);
        glVertex3f( -0.013, 0.05, 0.10);
        glVertex3f( -0.013, 0.05, 0.10);
        glVertex3f( -0.013,0.10, 0.10);
        glVertex3f( -0.013, 0.10, 0.12);

        // Komin STATKU 3
        glVertex3f( 0.005, 0.10, 0.20);         // Góra trójkąta (Glebia)
        glVertex3f(-0.013,0.05, 0.20);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( 0.005,0.05, 0.20);       // Prawy punkt trójkąta (Glebia)

        glVertex3f( 0.005, 0.10, 0.20);         // Góra trójkąta (Glebia)
        glVertex3f(-0.013,0.10, 0.20);         // Lewy punkt trójkąta (Glebia)
        glVertex3f(-0.013,0.05, 0.20);       // Prawy punkt trójkąta (Glebia)
        // Tył komina
        glVertex3f( 0.005, 0.10, 0.22);         // Góra trójkąta (Glebia)
        glVertex3f(0.005,0.05, 0.22);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.013,0.05, 0.22);       // Prawy punkt trójkąta (Glebia)
        glVertex3f( -0.013, 0.10, 0.22);         // Góra trójkąta (Glebia)
        glVertex3f(0.005,0.10, 0.22);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.013,0.05, 0.22);       // Prawy punkt trójkąta (Glebia)
        // boczna sciana
        glVertex3f( 0.005, 0.10, 0.22);
        glVertex3f( 0.005, 0.05, 0.22);
        glVertex3f( 0.005,0.05, 0.20);
        glVertex3f( 0.005, 0.05, 0.20);
        glVertex3f( 0.005,0.10, 0.20);
        glVertex3f( 0.005, 0.15, 0.20);
        //boczna sciana
        glVertex3f( -0.013, 0.10, 0.22);
        glVertex3f( -0.013,0.05, 0.22);
        glVertex3f( -0.013, 0.05, 0.20);
        glVertex3f( -0.013, 0.05, 0.20);
        glVertex3f( -0.013,0.10, 0.20);
        glVertex3f( -0.013, 0.10, 0.22);
        glEnd();
        zrot+=0.2f;         // Obrót na osi Z
    }
    glutSwapBuffers();

}

void reshape(int width, int height)
{
    float ratio = 1.0f * width/height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,ratio,1,1000);
    glViewport(0,0,width,height);
    //glOrtho(0.0, (GLdouble) width, 0.0, (GLdouble) height, 100, -100);
}

void klawiatura(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void onIdle();
void new_game_texture();
void info_game_texture();
void main_menu_texture();
void options_texture();

int main(int argc, char *argv[])
{
    Engine *game;
    game=game->getInstance();
    flaga_new_game = 1;
    flaga_exit = 1;
    flaga_info_game = 1;
    flaga_options = 1;
    flaga_back_to_menu = 1;
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
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Obniza szybkosc dzialania programu, ale ładniej wygląda
    game->LoadGLTextures(); //<-- added this
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
    case 'f' :
        glutFullScreen();
        flag_fullscr = 1;
        break;
    case 'o' :
        glutReshapeWindow(800,600);
        glutInitWindowPosition(100,100);
        flag_fullscr = 0;
        cout << "DRUGA OPCJA" << endl;
        break;
    case 49 :
        Dlugosc_statku = 0.10;
        Komin_1_tyl = 0.07;
        Komin_1_prz = 0.05;
        Komin_2_tyl = 0.07;
        Komin_2_prz = 0.05;
        Komin_3_tyl = 0.07;
        Komin_3_prz = 0.05;
        break;  //W - 119 , S - 115, A - 97, D - 100
    case 50 :
        Dlugosc_statku = 0.2;
        Komin_1_tyl = 0.17;
        Komin_1_prz = 0.15;
        Komin_2_tyl = 0.12;
        Komin_2_prz = 0.10;
        Komin_3_tyl = 0.12;
        Komin_3_prz = 0.10;
        break;
    case 51 :
        Dlugosc_statku = 0.3;
        Komin_1_tyl = 0.17;
        Komin_1_prz = 0.15;
        Komin_2_tyl = 0.22;
        Komin_2_prz = 0.20;
        Komin_3_tyl = 0.12;
        Komin_3_prz = 0.10;
        break;
    case 52 :
         kameray+=0.05;
        break;
    case 53 :
        kameray-=0.05;
        break;
    case 54 :
        kamerax+=0.05;
        break;
    case 55 :
        kamerax-=0.05;
        break;
    //W - 119 , S - 115, A - 97, D - 100
    case 100 :
        WiezcholekX1 += 0.057;
        Bok_LeftX1 += 0.057;
        Bok_RightX1 += 0.057;
        Komin_WiezcholekX1 += 0.057;
        Komin_Bok_LeftX1 += 0.057;
        break;
    case 97 :
        WiezcholekX1 -= 0.057;
        Bok_LeftX1 -= 0.057;
        Bok_RightX1 -= 0.057;
        Komin_WiezcholekX1 -= 0.057;
        Komin_Bok_LeftX1 -= 0.057;
        break;
    }
}

void mouse(int button, int state, int x, int y)
{
    cout << x << "," << y << endl;
    if(flag_fullscr == 1)
    {
        // FULL SCR :
        if(x >= 460 && x <= 872 && y >= 250 && y <= 296 && flaga_new_game == 1 && obiekt == 0)
        {
            cout << "NOWA GRA" << endl;
            flaga_new_game = 0;
            obiekt = 1;
            flaga_info_game = 0;
            flaga_options = 0;
            flaga_exit = 0;
            flaga_back_to_menu = 1;
            new_game_texture();
        }
        if(x >= 544 && x <= 761 && y >= 370 && y <= 416 && flaga_options == 1)
        {
            cout << "OPCJE" << endl;
            flaga_new_game = 0;
            flaga_info_game = 0;
            flaga_options = 0;
            flaga_exit = 0;
            flaga_back_to_menu = 1;
            options_texture();
        }
        if(x >= 520 && x <= 790 && y >= 482 && y <= 531 && flaga_info_game == 1)
        {
            cout << "O GRZE" << endl;
            flaga_new_game = 0;
            flaga_info_game = 0;
            flaga_options = 0;
            flaga_exit = 0;
            flaga_back_to_menu = 1;
            info_game_texture();

        }
        if(x >= 523 && x <= 781 && y >= 597 && y <= 648 && flaga_exit == 1)
        {
            cout << "Wyjdz" << endl;
            exit(0);
        }
        if(x >= 523 && x <= 781 && y >= 597 && y <= 648 && flaga_back_to_menu == 1)
        {

            cout << "Powrot" << endl;
            flaga_new_game = 1;
            flaga_info_game = 1;
            flaga_options = 1;
            obiekt = 0;
            flaga_back_to_menu = 0;
            main_menu_texture();
        }

    }
    else
    {
        if(x >= 271 && x <= 503 && y >= 194 && y <= 233 && flaga_new_game == 1 && obiekt == 0)
        {
            cout << "NOWA GRA" << endl;
            flaga_new_game = 0;
            flaga_info_game = 0;
            flaga_options = 0;
            flaga_exit = 0;
            obiekt = 1;
            flaga_back_to_menu = 1;
            new_game_texture();
        }

        if(x >= 317 && x <= 450 && y >= 286 && y <= 325 && flaga_options == 1)
        {
            cout << "OPCJE" << endl;
            flaga_new_game = 0;
            flaga_info_game = 0;
            flaga_options = 0;
            flaga_exit = 0;
            flaga_back_to_menu = 1;
            options_texture();
        }
        if(x >= 305 && x <= 463 && y >= 375 && y <= 413 && flaga_info_game == 1)
        {
            cout << "O GRZE" << endl;
            flaga_new_game = 0;
            flaga_info_game = 0;
            flaga_options = 0;
            flaga_exit = 0;
            flaga_back_to_menu = 1;

            info_game_texture();

        }
        if(x >= 305 && x <= 460 && y >= 460 && y <= 506 && flaga_exit == 1)
        {

            cout << "Wyjdz" << endl;
            exit(0);
        }
        if(x >= 305 && x <= 460 && y >= 460 && y <= 506 && flaga_back_to_menu == 1)
        {

            cout << "Powrot" << endl;
            flaga_new_game = 1;
            flaga_info_game = 1;
            flaga_options = 1;
            obiekt = 0;
            flaga_back_to_menu = 0;
            main_menu_texture();
        }

    }
}

void onIdle()
{

    int time;
    time = glutGet(GLUT_ELAPSED_TIME);
    delta = time - lastTime;
    lastTime = time;
    glutPostRedisplay();
    //cout << time << endl;
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
//Texture in menu
void main_menu_texture()
{

    glDeleteTextures(1,texture);
    texture[0] = SOIL_load_OGL_texture
                 (
                     "menu.jpg",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y
                 );
}
//Texture in options
void options_texture()
{

    glDeleteTextures(1,texture);
    texture[0] = SOIL_load_OGL_texture
                 (
                     "opcje.jpg",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y
                 );

}
