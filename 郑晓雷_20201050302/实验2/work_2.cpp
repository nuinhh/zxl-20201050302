#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);  // 指定清空颜色
    gluOrtho2D (0.0, 400.0, 0.0, 400.0);   //指定二维坐标系中被显示的区域
}

void setPixel(int x,int y){
	glPointSize(1.0f);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}

void lineDDA(int x0,int y0,int xEnd,int yEnd){
    int dx=xEnd-x0, dy=yEnd-y0, steps, k;
    float xIncrement,yIncrement,x=x0,y=y0;
    if(fabs(dx)>fabs(dy))
        steps=fabs(dx);
    else
        steps=fabs(dy);
    xIncrement=float(dx)/float(steps);
    yIncrement=float(dy)/float(steps);
    setPixel(round(x),round(y));
    for(k=0;k<steps;k++){
        x+=xIncrement;
        y+=yIncrement;
        setPixel(round(x),round(y));
    }
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT);// 清空显示窗口
    glColor3f(0.0,0.0,0.0);// 指定绘制颜色为黑色
    lineDDA(0,0,150,100);
    glFlush();// 使绘制立即反映到屏幕上
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);                     // 初始 GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   //设定显示模式
    glutInitWindowPosition (500, 200);   // 设定窗口位置
    glutInitWindowSize (300, 300);      // 设定窗口大小
    glutCreateWindow ("An Example OpenGL Program");
    init( );                       // 进行一些初始化工作
    glutDisplayFunc(&myDisplay);     // 指定绘制的回调函数
    glutMainLoop ( );      
}
