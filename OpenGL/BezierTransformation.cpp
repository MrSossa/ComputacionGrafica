#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<unistd.h>
#include <Eigen/Dense>

using Eigen::MatrixXd;

float mix(float a, float b, float t){
    // degree 1
    return a * (1.0f - t) + b*t;
}
float BezierQuadratic(float A, float B, float C, float t){
    // degree 2
    float AB = mix(A, B, t);
    float BC = mix(B, C, t);
    return mix(AB, BC, t);
}
float BezierCubic(float A, float B, float C, float D, float t){
    // degree 3
    float ABC = BezierQuadratic(A, B, C, t);
    float BCD = BezierQuadratic(B, C, D, t);
    return mix(ABC, BCD, t);
}
float BezierQuartic(float A, float B, float C, float D, float E, float t){
    // degree 4
    float ABCD = BezierCubic(A, B, C, D, t);
    float BCDE = BezierCubic(B, C, D, E, t);
    return mix(ABCD, BCDE, t);
}
float BezierQuintic(float A, float B, float C, float D, float E, float F, float t){
    // degree 5
    float ABCDE = BezierQuartic(A, B, C, D, E, t);
    float BCDEF = BezierQuartic(B, C, D, E, F, t);
    return mix(ABCDE, BCDEF, t);
}
 
float BezierSextic(float A, float B, float C, float D, float E, float F, float G, float t){
    // degree 6
    float ABCDEF = BezierQuintic(A, B, C, D, E, F, t);
    float BCDEFG = BezierQuintic(B, C, D, E, F, G, t);
    return mix(ABCDEF, BCDEFG, t);
}

struct SPoint{
    float x;
    float y;
};

void draw(){
	MatrixXd m1(2,2),m2(2,1),m3(2,2);
	float s = 65,r=0.3;
	m1(0,0) = s;
	m1(1,1) = s;
	m3(0,0) = cos(r);
	m3(0,1) = -sin(r);
	m3(1,0) = sin(r);
	m3(1,1) = cos(r);

	SPoint controlPoints[7] ={
        { 0.0f, 0.0f },
        { 2.0f, 8.3f },
        { 0.5f, 6.5f },
        { 5.1f, 4.7f },
        { 3.3f, 3.1f },
        { 1.4f, 7.5f },
        { 2.1f, 0.0f },
    };
    
	int numPoints = 100;
    SPoint bezierPoints[numPoints];
    for (int i = 0; i < 7; ++i){
		m2(0,0) = controlPoints[i].x;
		m2(1,0) = controlPoints[i].y;
		m2 = m1*m2;
		controlPoints[i].x = m2(0,0);
		controlPoints[i].y = m2(1,0);
		
	}

    for (int i = 0; i < numPoints; ++i){
        float t = ((float)i) / (float(numPoints - 1));
        SPoint p;
        p.x = BezierSextic(controlPoints[0].x, controlPoints[1].x, controlPoints[2].x, controlPoints[3].x, controlPoints[4].x, controlPoints[5].x, controlPoints[6].x, t);
        p.y = BezierSextic(controlPoints[0].y, controlPoints[1].y, controlPoints[2].y, controlPoints[3].y, controlPoints[4].y, controlPoints[5].y, controlPoints[6].y, t);
        p.x = p.x;
        p.y = p.y;
        bezierPoints[i] = p;
        //glVertex2f(p.y*30,p.x*30);
		//printf("point at time %0.2f = (%0.2f, %0.2f)n", t, p.x, p.y);
    }
	
    glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_STRIP);
    while(true){
		int t=360;
		glClear(GL_COLOR_BUFFER_BIT);
		
		while (t--){
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i < numPoints; ++i){
				m2(0,0) = bezierPoints[i].x;
				m2(1,0) = bezierPoints[i].y;
				m2 = m3*m2;
				bezierPoints[i].x = m2(0,0);
				bezierPoints[i].y = m2(1,0);
				glVertex2f(m2(1,0),m2(0,0));
			}
			usleep(10000);
			glEnd();
			glFlush();
		}
        usleep(1000000);
	}
	glEnd();
	glFlush();
}
void myInit(){
	glClearColor(1, 1, 1, 1);
	glColor3i(0,1,0);
	glPointSize(5);
	gluOrtho2D(-780, 780, -420, 420);
}
//g++ main.cpp -lGL -lGLU -lglut
int main (int argc, char** argv){
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
