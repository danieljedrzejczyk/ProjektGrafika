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
GLfloat rtri;         // Kąt obrotu trójkąta ( NOWE )
GLfloat rquad;         // Kąt obroty czworokąta ( NOWE )
GLfloat zrot;         // Obrót na osi Z ( NOWE )

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
    // Problem z narysowaniem dowolnej figury przed texturą

    // Wielokąt na textury
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
}
void statek_gracza() {
     glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glRotatef(rtri,1.0f,0.0,0.0f);
    //  glRotatef(zrot,0.0,1.0f,0.0f);
        glTranslatef(0.0, 0.0, 0.0);
        glBegin(GL_TRIANGLES);
            // Kadłub
        glVertex3f( -0.765, 0.25, 0.0);        // Góra trójkąta (Przednia)
        glVertex3f(-0.788,0.30, 0.0);         // Lewy punkt trójkąta (Przednia)
        glVertex3f( -0.740,0.30, 0.0);       // Prawy punkt trójkąta (Przednia)
            // LEWY BOK STATKU
        glVertex3f( -0.765, 0.25, 0.0);         // Góra trójkąta (Przednia)
        glVertex3f(-0.788,0.30, 0.0);          // Lewy punkt trójkąta (Przednia)
        glVertex3f(-0.765,0.20, 0.3);         // Prawy punkt trójkąta (Glebia)

        glVertex3f( -0.788,0.30, 0.0);
        glVertex3f( -0.788,0.30, 0.3);
        glVertex3f( -0.765,0.20, 0.3);
            // PRAWY BOK STATKU
        glVertex3f( -0.765, 0.25, 0.0);         // Góra trójkąta (Przednia)
        glVertex3f( -0.740,0.30, 0.0);         // Prawy punkt trójkąta (Przednia)
        glVertex3f(-0.765,0.20, 0.3);         // Góra trójkąta (Glebia)

        glVertex3f( -0.740,0.30, 0.0);        // Prawy punkt trójkąta (Przod)
        glVertex3f( -0.740,0.30, 0.3);       // Prawy punkt trójkąta (Glebia)
        glVertex3f( -0.765,0.20, 0.3);      // Góra trójkąta (Glebia)

            // POKŁAD
        glVertex3f(-0.788,0.30, 0.0);            // Lewy punkt trójkąta (Przednia)
        glVertex3f(-0.788,0.30, 0.3);           // Lewy punkt trójkąta (Przednia)
        glVertex3f( -0.740,0.30, 0.3);         // Prawy punkt trójkąta (Głebia)

        glVertex3f( -0.740,0.30, 0.0);           // Prawy punkt trójkąta (Przednia)
        glVertex3f(-0.788,0.30, 0.0);           // Lewy punkt trójkąta (Przednia)
        glVertex3f( -0.740,0.30, 0.3);         // Lewy punkt trójkąta (Glebia)


                    // Kadłub TYL
        glVertex3f( -0.765, 0.25, 0.3);         // Góra trójkąta (Glebia)
        glVertex3f(-0.788,0.30, 0.3);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.740,0.30, 0.3);       // Prawy punkt trójkąta (Glebia)
                    // Komin STATKU 1
        glVertex3f( -0.773, 0.40, 0.15);         // Góra trójkąta (Glebia)
        glVertex3f(-0.755,0.30, 0.15);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.773,0.30, 0.15);       // Prawy punkt trójkąta (Glebia)

        glVertex3f( -0.773, 0.40, 0.15);         // Góra trójkąta (Glebia)
        glVertex3f(-0.755,0.40, 0.15);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.755,0.30, 0.15);       // Prawy punkt trójkąta (Glebia)
                        // Tył komina
            glVertex3f( -0.773, 0.40, 0.17);         // Góra trójkąta (Glebia)
            glVertex3f(-0.755,0.30, 0.17);         // Lewy punkt trójkąta (Glebia)
            glVertex3f( -0.773,0.30, 0.17);       // Prawy punkt trójkąta (Glebia)
            glVertex3f( -0.773, 0.40, 0.17);         // Góra trójkąta (Glebia)
            glVertex3f(-0.755,0.40, 0.17);         // Lewy punkt trójkąta (Glebia)
            glVertex3f( -0.755,0.30, 0.17);       // Prawy punkt trójkąta (Glebia)
                        // boczna sciana
        glVertex3f( -0.773, 0.40, 0.17);
        glVertex3f( -0.773, 0.30, 0.17);
        glVertex3f( -0.773,0.30, 0.15);
        glVertex3f( -0.773, 0.30, 0.15);
        glVertex3f( -0.773,0.40, 0.15);
        glVertex3f( -0.773, 0.40, 0.17);
                        //boczna sciana
        glVertex3f( -0.755, 0.40, 0.17);
        glVertex3f( -0.755,0.30, 0.17);
        glVertex3f( -0.755, 0.30, 0.15);
        glVertex3f( -0.755, 0.30, 0.15);
        glVertex3f( -0.755,0.40, 0.15);
        glVertex3f( -0.755, 0.40, 0.17);
                    // Komin STATKU 2
        glVertex3f( -0.773, 0.35, 0.20);         // Góra trójkąta (Glebia)
        glVertex3f(-0.755,0.30, 0.20);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.773,0.30, 0.20);       // Prawy punkt trójkąta (Glebia)

        glVertex3f( -0.773, 0.35, 0.20);         // Góra trójkąta (Glebia)
        glVertex3f(-0.755,0.35, 0.20);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.755,0.30, 0.20);       // Prawy punkt trójkąta (Glebia)

                         // Tył komina
            glVertex3f( -0.773, 0.35, 0.22);         // Góra trójkąta (Glebia)
            glVertex3f(-0.755,0.30, 0.22);         // Lewy punkt trójkąta (Glebia)
            glVertex3f( -0.773,0.30, 0.22);       // Prawy punkt trójkąta (Glebia)
            glVertex3f( -0.773, 0.35, 0.22);         // Góra trójkąta (Glebia)
            glVertex3f(-0.755,0.35, 0.22);         // Lewy punkt trójkąta (Glebia)
            glVertex3f( -0.755,0.30, 0.22);       // Prawy punkt trójkąta (Glebia)
                                // boczna sciana
                glVertex3f( -0.773, 0.35, 0.22);
                glVertex3f( -0.773, 0.30, 0.22);
                glVertex3f( -0.773,0.30, 0.20);
                glVertex3f( -0.773, 0.30, 0.20);
                glVertex3f( -0.773,0.35, 0.20);
                glVertex3f( -0.773, 0.35, 0.22);
                                //boczna sciana
                glVertex3f( -0.755, 0.35, 0.22);
                glVertex3f( -0.755,0.30, 0.22);
                glVertex3f( -0.755, 0.30, 0.20);
                glVertex3f( -0.755, 0.30, 0.20);
                glVertex3f( -0.755,0.35, 0.20);
                glVertex3f( -0.755, 0.35, 0.22);
                            // Komin STATKU 3
        glVertex3f( -0.773, 0.35, 0.10);         // Góra trójkąta (Glebia)
        glVertex3f(-0.755,0.30, 0.10);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.773,0.30, 0.10);       // Prawy punkt trójkąta (Glebia)

        glVertex3f( -0.773, 0.35, 0.10);         // Góra trójkąta (Glebia)
        glVertex3f(-0.755,0.35, 0.10);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.755,0.30, 0.10);       // Prawy punkt trójkąta (Glebia)

                             // Tył komina
            glVertex3f( -0.773, 0.35, 0.12);         // Góra trójkąta (Glebia)
            glVertex3f(-0.755,0.30, 0.12);         // Lewy punkt trójkąta (Glebia)
            glVertex3f( -0.773,0.30, 0.12);       // Prawy punkt trójkąta (Glebia)
            glVertex3f( -0.773, 0.35, 0.12);         // Góra trójkąta (Glebia)
            glVertex3f(-0.755,0.35, 0.12);         // Lewy punkt trójkąta (Glebia)
            glVertex3f( -0.755,0.30, 0.12);       // Prawy punkt trójkąta (Glebia)
                            // boczna sciana
            glVertex3f( -0.773, 0.35, 0.12);
            glVertex3f( -0.773, 0.30, 0.12);
            glVertex3f( -0.773,0.30, 0.10);
            glVertex3f( -0.773, 0.30, 0.10);
            glVertex3f( -0.773,0.35, 0.10);
            glVertex3f( -0.773, 0.35, 0.12);
                            //boczna sciana
            glVertex3f( -0.755, 0.35, 0.12);
            glVertex3f( -0.755,0.30, 0.12);
            glVertex3f( -0.755, 0.30, 0.10);
            glVertex3f( -0.755, 0.30, 0.10);
            glVertex3f( -0.755,0.35, 0.10);
            glVertex3f( -0.755, 0.35, 0.12);
        glEnd();

        glBegin(GL_TRIANGLES);
            // Kadłub
        glVertex3f( -0.365, 0.25, 0.0);        // Góra trójkąta (Przednia)
        glVertex3f(-0.388,0.30, 0.0);         // Lewy punkt trójkąta (Przednia)
        glVertex3f( -0.340,0.30, 0.0);       // Prawy punkt trójkąta (Przednia)
            // LEWY BOK STATKU
        glVertex3f( -0.365, 0.25, 0.0);         // Góra trójkąta (Przednia)
        glVertex3f(-0.388,0.30, 0.0);          // Lewy punkt trójkąta (Przednia)
        glVertex3f(-0.365,0.20, 0.2);         // Prawy punkt trójkąta (Glebia)

        glVertex3f( -0.388,0.30, 0.0);
        glVertex3f( -0.388,0.30, 0.2);
        glVertex3f( -0.365,0.20, 0.2);
            // PRAWY BOK STATKU
        glVertex3f( -0.365, 0.25, 0.0);         // Góra trójkąta (Przednia)
        glVertex3f( -0.340,0.30, 0.0);         // Prawy punkt trójkąta (Przednia)
        glVertex3f(-0.365,0.20, 0.2);         // Góra trójkąta (Glebia)

        glVertex3f( -0.340,0.30, 0.0);        // Prawy punkt trójkąta (Przod)
        glVertex3f( -0.340,0.30, 0.2);       // Prawy punkt trójkąta (Glebia)
        glVertex3f( -0.365,0.20, 0.2);      // Góra trójkąta (Glebia)

            // POKŁAD
        glVertex3f(-0.388,0.30, 0.0);            // Lewy punkt trójkąta (Przednia)
        glVertex3f(-0.388,0.30, 0.2);           // Lewy punkt trójkąta (Przednia)
        glVertex3f( -0.340,0.30, 0.2);         // Prawy punkt trójkąta (Głebia)

        glVertex3f( -0.340,0.30, 0.0);           // Prawy punkt trójkąta (Przednia)
        glVertex3f(-0.388,0.30, 0.0);           // Lewy punkt trójkąta (Przednia)
        glVertex3f( -0.340,0.30, 0.2);         // Lewy punkt trójkąta (Glebia)


                    // Kadłub TYL
        glVertex3f( -0.365, 0.25, 0.2);         // Góra trójkąta (Glebia)
        glVertex3f(-0.388,0.30, 0.2);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.340,0.30, 0.2);       // Prawy punkt trójkąta (Glebia)
                    // Komin STATKU 1
        glVertex3f( -0.373, 0.40, 0.15);         // Góra trójkąta (Glebia)
        glVertex3f(-0.355,0.30, 0.15);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.373,0.30, 0.15);       // Prawy punkt trójkąta (Glebia)

        glVertex3f( -0.373, 0.40, 0.15);         // Góra trójkąta (Glebia)
        glVertex3f(-0.355,0.40, 0.15);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.355,0.30, 0.15);       // Prawy punkt trójkąta (Glebia)
                        // Tył komina
            glVertex3f( -0.373, 0.40, 0.17);         // Góra trójkąta (Glebia)
            glVertex3f(-0.355,0.30, 0.17);         // Lewy punkt trójkąta (Glebia)
            glVertex3f( -0.373,0.30, 0.17);       // Prawy punkt trójkąta (Glebia)
            glVertex3f( -0.373, 0.40, 0.17);         // Góra trójkąta (Glebia)
            glVertex3f(-0.355,0.40, 0.17);         // Lewy punkt trójkąta (Glebia)
            glVertex3f( -0.355,0.30, 0.17);       // Prawy punkt trójkąta (Glebia)
                        // boczna sciana
        glVertex3f( -0.373, 0.40, 0.17);
        glVertex3f( -0.373, 0.30, 0.17);
        glVertex3f( -0.373,0.30, 0.15);
        glVertex3f( -0.373, 0.30, 0.15);
        glVertex3f( -0.373,0.40, 0.15);
        glVertex3f( -0.373, 0.40, 0.17);
                        //boczna sciana
        glVertex3f( -0.355, 0.40, 0.17);
        glVertex3f( -0.355,0.30, 0.17);
        glVertex3f( -0.355, 0.30, 0.15);
        glVertex3f( -0.355, 0.30, 0.15);
        glVertex3f( -0.355,0.40, 0.15);
        glVertex3f( -0.355, 0.40, 0.17);

                            // Komin STATKU 2
        glVertex3f( -0.373, 0.35, 0.10);         // Góra trójkąta (Glebia)
        glVertex3f(-0.355,0.30, 0.10);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.373,0.30, 0.10);       // Prawy punkt trójkąta (Glebia)

        glVertex3f( -0.373, 0.35, 0.10);         // Góra trójkąta (Glebia)
        glVertex3f(-0.355,0.35, 0.10);         // Lewy punkt trójkąta (Glebia)
        glVertex3f( -0.355,0.30, 0.10);       // Prawy punkt trójkąta (Glebia)

                             // Tył komina
            glVertex3f( -0.373, 0.35, 0.12);         // Góra trójkąta (Glebia)
            glVertex3f(-0.355,0.30, 0.12);         // Lewy punkt trójkąta (Glebia)
            glVertex3f( -0.373,0.30, 0.12);       // Prawy punkt trójkąta (Glebia)
            glVertex3f( -0.373, 0.35, 0.12);         // Góra trójkąta (Glebia)
            glVertex3f(-0.355,0.35, 0.12);         // Lewy punkt trójkąta (Glebia)
            glVertex3f( -0.355,0.30, 0.12);       // Prawy punkt trójkąta (Glebia)
                            // boczna sciana
            glVertex3f( -0.373, 0.35, 0.12);
            glVertex3f( -0.373, 0.30, 0.12);
            glVertex3f( -0.373,0.30, 0.10);
            glVertex3f( -0.373, 0.30, 0.10);
            glVertex3f( -0.373,0.35, 0.10);
            glVertex3f( -0.373, 0.35, 0.12);
                            //boczna sciana
            glVertex3f( -0.355, 0.35, 0.12);
            glVertex3f( -0.355,0.30, 0.12);
            glVertex3f( -0.355, 0.30, 0.10);
            glVertex3f( -0.355, 0.30, 0.10);
            glVertex3f( -0.355,0.35, 0.10);
            glVertex3f( -0.355, 0.35, 0.12);
        glEnd();
        rtri+=0.3f;         // Zwiększ kąt obrotu trójkąta ( NOWE )
        zrot+=0.3f;         // Obrót na osi Z
        glPopMatrix();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    main_menu(); // TEXTURA Z MENU GŁÓWNYM
    if(flaga_new_game==0 && flaga_info_game == 1 && flaga_options == 1)
    {
       statek_gracza();
        // STATKI MODELE DO PREZENTACJI
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

        zrot+=0.3f;         // Obrót na osi Z
    }
    glutSwapBuffers();

}

void reshape(int width, int height)
{
    float ratio = 1.0f * width/height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0,width,height);
    // Rzuty BEGIN
    gluPerspective(45,ratio,1,1000);
    //glOrtho(0.0, (GLdouble) width, 0.0, (GLdouble) height, 100, -100);
    // Rzuty END;
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(0.0,0.0,6.0,0.0,0.0,0.0,0.0f,1.0f,0.0f);

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
    case 49 :
        glutFullScreen();
        flag_fullscr = 1;
        break;
    case 50 :
        glutReshapeWindow(800,600);
        glutInitWindowPosition(100,100);
        flag_fullscr = 0;
        cout << "DRUGA OPCJA" << endl;
        break;
    }
}

void mouse(int button, int state, int x, int y)
{
    cout << x << "," << y << endl;
    if(flag_fullscr == 1)
    {
        // FULL SCR :
        if(x >= 460 && x <= 872 && y >= 250 && y <= 296 && flaga_new_game == 1)
        {
            cout << "NOWA GRA" << endl;
                flaga_new_game = 0;
                //flaga_info_game = 0;
                //flaga_options = 0;
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

                 flaga_back_to_menu = 0;
                 main_menu_texture();
        }

    }
    else
    {
        if(x >= 271 && x <= 503 && y >= 194 && y <= 233 && flaga_new_game == 1)
        {
            cout << "NOWA GRA" << endl;
                flaga_new_game = 0;
                //flaga_info_game = 0;
                //flaga_options = 0;
                flaga_exit = 0;
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
void options_texture() {

    glDeleteTextures(1,texture);
    texture[0] = SOIL_load_OGL_texture
                 (
                     "opcje.jpg",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y
                 );

}
