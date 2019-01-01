#include <GL/glut.h>
#include <GL/glext.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <png.h>
#include "maps.h"
#include "state.h"
#include "sprites.h"
#include "sprites.c"

Scene scene;
GLenum doubleBuffer;
double size = (double)600/1034;

static void
Draw(void)
{
        int i;
        glLoadIdentity();
        glTranslatef(-0.5, -0.5, -1.0);
        glRotatef(0, 0,1,0);
        glRotatef(0, 1,0,0);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_TEXTURE_2D);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        GLubyte * scene = mount_scene();
        glTexImage2D(GL_TEXTURE_2D, 0, 4, SCREEN_WIDTH,
                        SCREEN_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                        scene);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_LINEAR
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);                        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); 
        
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0, 0.0); glVertex2f(1.0f, 0.0f);
        glTexCoord2f(1.0, 1.0); glVertex2f(1.0f, 1.0f);
        glTexCoord2f(0.0, 1.0); glVertex2f(0.0f, 1.0f);
        glEnd();


        glDisable(GL_TEXTURE_2D);
        glutSwapBuffers();
        glFlush();
        free(scene);
}

void myReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0 * (GLfloat) w / (GLfloat) h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyUp(unsigned char key, int x, int y)
{
    State current_state;
    current_state.up = 0;
    current_state.down = 0;
    current_state.left = 0;
    current_state.right = 0;
    game_state = current_state;
}

void keyPressed (unsigned char key, int x, int y) 
{  
    State current_state;
    current_state.up = 0;
    current_state.down = 0;
    current_state.left = 0;
    current_state.right = 0;

    if (key == 'w') {
        current_state.up = 1;
    }
    if (key == 's') {
        current_state.down = 1;
    }
    if (key == 'a') {
        current_state.left = 1;
    }
    if (key == 'd') {
        current_state.right = 1;
    }

    game_state = current_state;
}

int
main(int argc, char **argv)
{
        load_sprites();
        glutInit(&argc, argv); 
        glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

        glutInitWindowPosition(100,100); 
        glutInitWindowSize(800, 600); 
        glutCreateWindow("square");

        glMatrixMode(GL_PROJECTION);
        // glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 1.0);

        glutKeyboardFunc(keyPressed);
        glutKeyboardUpFunc(keyUp); 
        glutReshapeFunc(myReshape);
        glutDisplayFunc(Draw); 
        glutIdleFunc(Draw);
        glutMainLoop();

        return 0; 
}