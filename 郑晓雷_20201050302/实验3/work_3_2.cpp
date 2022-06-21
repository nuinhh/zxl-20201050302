#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void setPixel(int x, int y)
{
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void init(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //设置显示窗口颜色为白色
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0f, 200.0f, 0.0f, 150.0f); //设置规划参数
}
void proBresenhamLine(int x0, int y0, int x1, int y1)
{
    int dx, dy, e, x, y;
    dx = x1 - x0;
    dy = y1 - y0;
    e = -dx;
    x = x0;
    y = y0;
    while (x <= x1)
    {
        setPixel(x, y);
        x++;
        e = e + 2 * dy;
        if (e > 0)
        {
            y++;
            e = e - 2 * dx;
        }
    }
}

void myDisplay()
{
    int x0, y0, xEnd, yEnd;
    //s输入起点中点位置
    scanf_s("%d %d %d %d", &x0, &y0, &xEnd, &yEnd);
    proBresenhamLine(x0, y0, xEnd, yEnd);
}

void main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //初始化显示模式
    glutInitWindowSize(600, 600);       //设置窗口尺寸
    glutInitWindowPosition(200, 100);     //设置窗口位置
    glutCreateWindow("Bresenham算法");  //创建窗口
    glutDisplayFunc(&myDisplay);         //注册显示函数
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);    //设置背景颜色
    glColor3f(1.0f, 0.0f, 0.0f);           //设置绘制颜色
    glMatrixMode(GL_PROJECTION);   
    gluOrtho2D(0.0, 600, 0.0, 600);       //设置投影区域
    glutMainLoop();                   //进入程序循环
}
