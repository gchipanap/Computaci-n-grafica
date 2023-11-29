#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void display();
void specialKeys();

double rotate_y = 0; 
double rotate_x = 0;
double rotate_z = 0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);

    //Frontal
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 1.0f, 0.0f, 0.0f);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    //TRASERO
    glBegin(GL_POLYGON);
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glEnd();

    //DERECHO
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, -0.5, 0.5);
    glEnd();

    //IZQUIERDO
    glBegin(GL_POLYGON);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, 0.5, 0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    //SUPERIOR
    glBegin(GL_POLYGON);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.5, 0.5, 0.5);
        glVertex3f(0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, -0.5);
        glVertex3f(-0.5, 0.5, 0.5);
    glEnd();

    //INFERIOR
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.5, -0.5, -0.5);
        glVertex3f(0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, 0.5);
        glVertex3f(-0.5, -0.5, -0.5);
    glEnd();

    glFlush();
    glutSwapBuffers();

}

void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    else if (key == GLUT_KEY_F2)
        rotate_z -= 5;
    else if (key == GLUT_KEY_F1)
        rotate_z += 5;

    glutPostRedisplay();

}

int main(int argc, char* argv[])
{

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutCreateWindow("Tutorial 09");
  glEnable(GL_DEPTH_TEST);

  glutDisplayFunc(display);
  glutSpecialFunc(specialKeys);

  glutMainLoop();

  return 0;
 
}

