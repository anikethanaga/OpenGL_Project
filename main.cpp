#include<windows.h>
#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<lab.h>

using namespace std;

double R,XC,YC;

int roundpt(double x)
{
    return floor(x+0.5);
}

void Init()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0,0.0,0.0,1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100,100,-100,100);
}

void drawpt(double X,double Y)
{
    glBegin(GL_POINTS);
    glVertex2i(roundpt(XC+X),roundpt(YC+Y));
    //printf("The point is : %ld %ld \n",(XC+X),(YC+Y));
    glVertex2i(roundpt(XC-X),roundpt(YC+Y));
    //printf("The point is : %ld %ld \n",(XC-X),(YC+Y));
    glVertex2i(roundpt(XC+X),roundpt(YC-Y));
    //printf("The point is : %ld %ld \n",(XC+X),(YC-Y));
    glVertex2i(roundpt(XC-X),roundpt(YC-Y));
    //printf("The point is : %ld %ld \n",(XC-X),(YC-Y));
    glVertex2i(roundpt(XC+Y),roundpt(YC+X));
    //printf("The point is : %ld %ld \n",(XC+Y),(YC+X));
    glVertex2i(roundpt(XC-Y),roundpt(YC+X));
    //printf("The point is : %ld %ld \n",(XC-Y),(YC+X));
    glVertex2i(roundpt(XC+Y),roundpt(YC-X));
    //printf("The point is : %ld %ld \n",(XC+Y),(YC-X));
    glVertex2i(roundpt(XC-Y),roundpt(YC-X));
    //printf("The point is : %ld %ld \n",(XC-Y),(YC-X));
    glEnd();
    //printf("\n********\n");
}

void drawQuadr()
{
    double p = 5/4 - R;
    double xincr = 1,yincr = -1;
    double X = 0,Y = R;
    while(X<=Y)
    {
        drawpt(X,Y);
        if(p<0)
        {
            p += 2*X + 2;
        }
        else
        {
            p += 2*X + 1 - 2*(Y - 1);
            Y += yincr;
        }
        X += xincr;
    }
    glFlush();
}

int main(int argc,char **argv)
{
    printf("Enter the center and the radius\n*****\n");
    scanf("%lf%lf%lf",&XC,&YC,&R);
    //printf("The centre and radius is : %lf %lf %lf\n",XC,YC,R);
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGBA);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(400,400);
    glutCreateWindow("Circle");
    Init();
    glutDisplayFunc(drawQuadr);
    glutMainLoop();
    return 0;
}


