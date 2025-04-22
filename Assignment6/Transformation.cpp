/*
 *
 * Author : Neevan Redkar
 * Title : 2D Transformations
 * Date : 24|02|2025 
 * 
 *
*/

#include <GL/glut.h>;
#include <stdio.h>;
#include <cmath>;
static int flag;
int length, xi, yi, choice;
double angle, ET[3][3], ETResult[3][3];
double Rh[4][4], RhResult[4][4];

}

DRAW

void drawET(double ET[3][3]){

int i;

glBegin(GL_LINE_LOOP);
for(i=0;i<3;i++)

glVertex2i(ET[i][0],ET[i][1]);
}
glEnd();

void drawR(double Rh[4][4]){

int i;

glBegin(GL_LINE_LOOP);
for(i=0;i<4;i++){

glVertex2i(Rh[i][0],Rh[i][1]);
}
glEnd();
}

void Display(){

glClearColor(0,0,0,0);
glClear(GL_COLOR_BUFFER_BIT);

glLoadIdentity();
gluOrtho2D(-320,320,-240,240);//note

glColor3f(1,1,1);
glBegin(GL_LINES);
glVertex2d(-320,0);
glVertex2d(320,0);
glVertex2d(0,-240);
glVertex2d(0,240);
glEnd();

glColor3f(1,0,0);
if(flag == 0)
drawET(ET);
else if(flag == 1)
drawR(Rh);
glFlush();
}

void mult3X3(double ET[3][3],double temp[3][3])
{
double sum;
int i,j,k;
for(i=0;i&lt;3;i++)
{
for(j=0;j&lt;3;j++)
{
sum=0;
for(k=0;k&lt;3;k++)
{
sum=sum+ET[i][k]*temp[k][j];
}
ETResult[i][j]=sum;
}
}
}
void mult4X4(double Rh[4][4],double temp[4][4])
{
double sum;
int i,j,k;
for(i=0;i&lt;4;i++)
{
for(j=0;j&lt;4;j++)
{
sum=0;
for(k=0;k&lt;4;k++)
{
sum=sum+Rh[i][k]*temp[k][j];
}
RhResult[i][j]=sum;
}
}
}

// Translation //
void translationET()
{
double tx,ty,temp[3][3];
printf(&quot;\nTranslating Equilateral triangle&quot;);
printf(&quot;\nEnter Tx: &quot;);
scanf(&quot;%lf&quot;,&amp;tx);
printf(&quot;\nEnter Ty: &quot;);
scanf(&quot;%lf&quot;,&amp;ty);
temp[3][3]={0};
temp[0][0]=1;
temp[1][1]=1;
temp[2][2]=1;
temp[2][0]=tx;
temp[2][1]=ty;
mult3X3(ET,temp);
glColor3f(0.0,1.0,0.0);
drawET(ETResult);
}

void translationRh()
{
double tx,ty,temp[4][4];
printf(&quot;\nTranslating Rhombus&quot;);
printf(&quot;\nEnter Tx: &quot;);
scanf(&quot;%lf&quot;,&amp;tx);
printf(&quot;\nEnter Ty: &quot;);
scanf(&quot;%lf&quot;,&amp;ty);
temp[4][4]={0};
temp[0][0]=1;
temp[1][1]=1;
temp[2][2]=1;
temp[3][3]=1;
temp[3][0]=tx;
temp[3][1]=ty;
mult4X4(Rh,temp);
glColor3f(0.0,1.0,0.0);
drawR(RhResult);
}