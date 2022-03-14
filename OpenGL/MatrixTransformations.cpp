#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include <iostream>
#include<unistd.h>
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;
struct SPoint{
    float x;
    float y;
};
void draw(){
	
	
	MatrixXd m1(2,2),m2(2,1),m3(2,2);
	float s = 3,r=0.3;
	m1(0,0) = s;
	m1(1,1) = s;
	m3(0,0) = cos(r);
	m3(0,1) = -sin(r);
	m3(1,0) = sin(r);
	m3(1,1) = cos(r);
	SPoint Points[2] ={
        { 0.0f, 0.0f },
        { 0.0f, 100.0f },
    };
	for (int i = 0; i < 2; ++i){
		m2(0,0) = Points[i].x;
		m2(1,0) = Points[i].y;
		m2 = m1*m2;
		Points[i].x = m2(0,0);
		Points[i].y = m2(1,0);
		
	}
	while(true){
		int t=360;
		glClear(GL_COLOR_BUFFER_BIT);
		
		while (t--){
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < 2; ++i){
				m2(0,0) = Points[i].x;
				m2(1,0) = Points[i].y;
				m2 = m3*m2;
				Points[i].x = m2(0,0);
				Points[i].y = m2(1,0);
				glVertex2f(m2(1,0),m2(0,0));
			}
			usleep(1000);
			glEnd();
			glFlush();
		}
	}
}
void myInit(){
	glClearColor(1, 1, 1, 1);
	glColor3i(0,1,0);
	glPointSize(5);
	gluOrtho2D(-780, 780, -420, 420);
}
//g++ -I eigen-3.4.0/ -o m MatrixTransformations.cpp -lGL -lGLU -lglut
int main (int argc, char** argv){
    /*
	MatrixXd m1(2,2),m2(2,1);
	int s = 30;
	m1(0,0) = s;
	m1(1,1) = s;
	cout << m1 << endl << endl;
	cout << m2 << endl << endl;
	m2(0,0) = 2;
	m2(1,0) = 2;
	m2 = m1*m2;
	cout << m2 << endl << endl;
	*/
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE  | GLUT_RGB);
	glutInitWindowSize(900,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Test1");

	myInit();

	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}
