/*
  Author - Neevan Redkar
  Subject - Computer Graphics
  Title - DDA

*/

#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void myInit(void){
  glClearColor(1.0,1.0,1.0,1.0);
  glColor3f(0.0f,0.0f,0.0f);
  glPointSize(4.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0.0,640.0,0.0,480.0);
}


int sign(float x){
    if(x<0){
        return -1;
    }
    return 1;

}

int length(float xa,float ya,float xb,float yb){
    if(abs(xb-xa)>=abs(yb-ya)){
        return abs(xb-xa);
    }else{
        return abs(yb-ya);
    }
}


void DDA(){
    cout<<"Enter points in format x1 y1 x2 y2"<<endl;
    float xa,ya,xb,yb;
    cin>>xa>>ya>>xb>>yb;
    int l=length(xa,ya,xb,yb);
   vector <int> points;
   points[0]=int(xa);
   cout<<points[0];
   points[1]=int(xb);
   float dx = (xb-xa)/length(xa,ya,xb,yb);
   float dy = (yb-ya)/length(xa,xb,ya,yb);
   int x,y;
   x=round(xa+0.5*sign(dx));
   y=round(xb+0.5*sign(dy));
   points[2]=x;
   points[3]=y;
   for(int i=1;i<l+1;i++){
    x=round(x+dx);
    points[i+4]=x;
    y=round(y+dx);
    points[i+5]=y;

   }
   for(int x:points){
    cout<<x<<" ";
   }
   //return points;

}

/*void display(void){
    
    vector<int> points = DDA();
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE);
     glVertex2i(points[0],points[1]);
     glVertex2i(points[2],points[3]);
     glEnd();
     glFlush();
     for(int i=0;i<points.size()-1;i=i+2){
        cout<<points[i]<<" "<<points[i+1]<<endl;
     }
}*/





int main(int argc,char** argv){
  /*glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
  glutInitWindowSize(640,480);
  glutInitWindowPosition(100,150);
  glutCreateWindow("Assignment 1");
  glutDisplayFunc(display);
  myInit();
  glutMainLoop();*/
 DDA();
  return 0;


    return 0;
}