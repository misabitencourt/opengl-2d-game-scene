#include <GL/glut.h>
#include <GL/glext.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <png.h>
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
        glTranslatef(0.0, 0.0, -3.6);
        glRotatef(0, 0,1,0);
        glRotatef(0, 1,0,0);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        // glColor3f(0.0, 1.0, 0.0);        

        glEnable(GL_TEXTURE_2D);

        // for (i=0; i<sizeof(sprites); i++) {
        //         if (sprites[i].loaded == 1) {    
        //                 printf("width: %d\r\n", sprites[i].width);
        //                 printf("height: %d\r\n", sprites[i].height);
        //                 printf("data: %d\r\n", sprites[i].image);
        //                 glGenTextures(1, &sprites[i].texture);
        //                 glBindTexture(GL_TEXTURE_2D, sprites[i].texture);
        //                 glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        //                 glTexImage2D(GL_TEXTURE_2D, 0, 4, sprites[i].width,
        //                                 sprites[i].height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
        //                                 sprites[i].image);
        //                 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_LINEAR
        //                 glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);                        
        //                 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        //                 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        //                 float color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
        //                 glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
        //         }
        // } 

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, 4, sprites[1].frame_width,
                        sprites[1].height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                        get_frame_image(sprites[1]));
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_LINEAR
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);                        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); 
        
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0); glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0, 0.0); glVertex2f(sprites[1].frame_width / 100.0f, 0.0f);
        glTexCoord2f(1.0, 1.0); glVertex2f(sprites[1].frame_width / 100.0f, sprites[1].height / 100.0f);
        glTexCoord2f(0.0, 1.0); glVertex2f(0.0f, sprites[1].height / 100.0f);
        glEnd();


        glDisable(GL_TEXTURE_2D);

        if (doubleBuffer) {
                glutSwapBuffers();
        } else {
                glFlush();
        }
}

void myReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0 * (GLfloat) w / (GLfloat) h, 1.0, 30.0);
    glMatrixMode(GL_MODELVIEW);
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

        glutReshapeFunc(myReshape);
        glutDisplayFunc(Draw); 
        glutMainLoop();

        return 0; 
}