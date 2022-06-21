#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdlib.h>
const double TWO_PI = 6.28318;

/*Initial display-window size*/
GLsizei winWidth = 400,winHeight = 400;
GLuint regHex;

class screenPT{
 private:
      GLint x,y;
 public:
     screenPT(){
     x=y=0;
     }
     void setCoords(GLint xCoord,GLint yCoord){
         x = xCoord;
         y = yCoord;
     }

     GLint getx() const {
        return x;
     }

     GLint gety() const {
        return y;
     }

};
  static void init (void)
  {

      screenPT hexVertex, circCtr;
      GLdouble theta;
      GLint k;

      /*set circle center coordinates*/
      circCtr.setCoords(winWidth/2,winHeight/2);

      glClearColor(1.0,1.0,1.0,0.0);//display-window color=white
      regHex = glGenLists(1);
      glNewList(regHex,GL_COMPILE);
      glColor3f(1.0,0.0,0.0);
      glBegin(GL_POLYGON);
      theta=TWO_PI/6.0;
      hexVertex.setCoords(circCtr.getx()+100*cos(theta*2),circCtr.gety()+150*sin(theta*2));
      glVertex2i(hexVertex.getx(),hexVertex.gety());
      hexVertex.setCoords(circCtr.getx()+140*cos(theta*2),circCtr.gety()+160*sin(theta*2));
      glVertex2i(hexVertex.getx(),hexVertex.gety());
      hexVertex.setCoords(circCtr.getx()+160*cos(theta*4),circCtr.gety()+170*sin(theta*3));
      glVertex2i(hexVertex.getx(),hexVertex.gety());
      hexVertex.setCoords(circCtr.getx()+180*cos(theta*4),circCtr.gety()+180*sin(theta*3));
      glVertex2i(hexVertex.getx(),hexVertex.gety());
      hexVertex.setCoords(circCtr.getx()+200*cos(theta*5),circCtr.gety()+190*sin(theta*4));
      glVertex2i(hexVertex.getx(),hexVertex.gety());
      hexVertex.setCoords(circCtr.getx()+250*cos(theta*5),circCtr.gety()+200*sin(theta*4));
      glVertex2i(hexVertex.getx(),hexVertex.gety());
       glEnd();
    glEndList();
  }
  void regHexagen(void)
  {
   glClear(GL_COLOR_BUFFER_BIT);

   glCallList(regHex);

   glFlush();
  }
  void winReshapeFcn(int newWidth,int newHeight)
  {
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0.0, (GLdouble)newWidth,0.0,(GLdouble)newHeight);

      glClear(GL_COLOR_BUFFER_BIT);
  }

  int main(int argc,char** argv)
  {
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
      glutInitWindowPosition(100,100);
      glutInitWindowSize(winWidth,winHeight);
      glutCreateWindow("Reshape-Function & Display-List Example");

      init();
      glutDisplayFunc(regHexagen);
      glutReshapeFunc(winReshapeFcn);

      glutMainLoop();
      return 0;
  }
