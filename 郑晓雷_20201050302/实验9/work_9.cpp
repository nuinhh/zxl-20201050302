#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#define  RADDEG  57.29577951f
float XUP[3] = {1,0,0}, XUN[3] = {-1, 0, 0},
      YUP[3] = {0,1,0}, YUN[3] = { 0,-1, 0},
      ZUP[3] = {0,0,1}, ZUN[3] = { 0, 0,-1},
      ORG[3] = {0,0,0};
GLfloat viewangle = 0, tippangle = 0;
GLfloat d[3] = {0.1, 0.1, 0.1};
GLfloat  xAngle = 0.0, yAngle = 0.0, zAngle = 0.0;
void Keyboard (unsigned char key, int x, int y)
{
    switch (key) {
       case 'd' : d[0] += 0.1; std::cout<<"sağ"<<std::endl; break;
       case 'w' : d[1] += 0.1; std::cout<<"yukarı"<<std::endl;  break;
       case 'e' : d[2] += 0.1; std::cout<<"yakınlaş"<<std::endl; break;
       case 's' : d[1] -= 0.1; std::cout<<"aşağı"<<std::endl; break;
       case 'a' : d[0] -= 0.1;  std::cout<<"sol"<<std::endl;break;
       case 'z' : d[2] -= 0.1; std::cout<<"uzaklaş"<<std::endl; break; break;
       case 'k' : xAngle += 5;  std::cout<<"X ekseninde döndür"<<std::endl; break; break;break;
       case 'l' : yAngle += 5; std::cout<<"Y ekseninde döndür"<<std::endl; break; break; break;
       case 'm' : zAngle += 5;  std::cout<<"Z ekseninde döndür"<<std::endl; break; break;break;
    }
    glutPostRedisplay();
}
void Triad (void)
{
    glColor3f (1.0, 1.0, 1.0);

    glBegin (GL_LINES);
       glVertex3fv (ORG); glVertex3fv (XUP);
       glVertex3fv (ORG); glVertex3fv (YUP);
       glVertex3fv (ORG); glVertex3fv (ZUP);
    glEnd ();
}
 void home(void)
 {
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(0.0,0.4,0.2);
		glBegin(GL_POLYGON);
		glVertex3f (0.1, 0.1, 0.0);
        glVertex3f (0.4, 0.1, 0.0);
        glVertex3f (0.4, 0.5, 0.0);
        glVertex3f (0.1, 0.5, 0.0);
    glEnd();
glColor3f(1.0,0.0,0.0);

		glBegin(GL_POLYGON);
		glVertex3f (0.10, 0.5, 0.0);
        glVertex3f (0.4, 0.5, 0.0);
        glVertex3f (0.25, 0.75, 0.0);
       glEnd();
glColor3f(0.0,1.0,0.0);

		glBegin(GL_POLYGON);
		glVertex3f (0.4, 0.1, 0.0);
        glVertex3f (0.8, 0.4, 0.0);
        glVertex3f (0.8, 0.75, 0.0);
        glVertex3f (0.4, 0.5, 0.0);
    glEnd();
glColor3f(0.4,0.0,0.4);

		glBegin(GL_POLYGON);
		glVertex3f (0.4, 0.5, 0.0);
        glVertex3f (0.8, 0.75, 0.0);
        glVertex3f (0.62, 0.93, 0.0);
        glVertex3f (0.25, 0.75, 0.0);
    glEnd();
glFlush();
}


void redraw (void)
{
    int v;

    glClear  (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable (GL_DEPTH_TEST);

    glLoadIdentity ();

    glTranslatef (0, 0, -3);
    glRotatef (tippangle, 1,0,0);
    glRotatef (viewangle, 0,1,0);

    glDisable (GL_LIGHTING);

    Triad ();

    glPushMatrix ();
       glTranslatef (d[0], d[1], d[2]);
       glScalef (0.2, 0.2, 0.2);
       glRotatef (zAngle, 0,0,1);
       glRotatef (yAngle, 0,1,0);
       glRotatef (xAngle, 1,0,0);
       home ();
    glPopMatrix ();

    glutSwapBuffers();
}


int main (int argc, char **argv)
{
    glutInit               (&argc, argv);
    glutInitWindowSize     (900, 600);
    glutInitWindowPosition (300, 300);
    glutInitDisplayMode    (GLUT_DEPTH | GLUT_DOUBLE);

    glutCreateWindow ("Home");
    glutDisplayFunc  (   redraw   );
    glutKeyboardFunc (  Keyboard  );

    glClearColor (0.1, 0.0, 0.1, 1.0);

    glMatrixMode   (GL_PROJECTION);
    gluPerspective (60, 1.5, 1, 10);
    glMatrixMode   (GL_MODELVIEW);
    glutMainLoop   ();

    return 1;
}
