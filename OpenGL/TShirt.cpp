#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include <vector>
#include <tuple>
#include <iostream>
#include<unistd.h>
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXd;
vector<pair<float,float>> Points;

//largo                 = 100
//ancho 2/3 largo       = 2/3 * 100
//mangas 1/3 espalda    = 1/3 * ancho
MatrixXd trans(2,1);
MatrixXd esc(2,2);
MatrixXd rot(2,2);
float pi = 3.141592;
float length = 300;
float tx = -100;//x translation
float ty = -100;//y translation
float s = 1; //scalation
float r = 0; //rotation

void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);
    trans(0,0) = tx;
    trans(1,0) = ty;
    esc(0,0) = s;
	esc(1,1) = s;
    rot(0,0) = cos(r);
	rot(0,1) = -sin(r);
	rot(1,0) = sin(r);
	rot(1,1) = cos(r);
    MatrixXd aux(2,1);
    for (int i = 0; i < Points.size();++i){
        aux(0,0) = Points[i].first;
        aux(1,0) = Points[i].second;
        aux = rot*aux;
        aux = esc*aux;
        aux = aux+trans;
        glVertex2f(aux(0,0),aux(1,0));
        //cout << Points[i].first << " " << Points[i].second << endl;
    }
    glEnd();
	glFlush();
}

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

void generateBasicMetrics(float length){
    float ancho = (float)2/(float)3*length;
    float manga = ancho/(float)3;
    float puntoCuello = ancho/(float)4;

    Points.push_back({0,0});
    Points.push_back({0,length-manga});

    //manga iz
    Points.push_back({-manga/4,length-manga-(manga/2)});
    Points.push_back({-manga,length-manga*1.5});
    int nPoints = 20;
    for (int i = 0; i < nPoints; ++i){
        float t = ((float)i) / (float(nPoints - 1));
        float x = BezierQuadratic(-manga,-manga,puntoCuello,t);
        float y = BezierQuadratic(length-manga*1.5,length,length,t);
        Points.push_back({x,y});
    }    
    //cuello
    for (int i = 0; i < nPoints; ++i){
        float t = ((float)i) / (float(nPoints - 1));
        float x = BezierQuadratic(puntoCuello,ancho/2,ancho-puntoCuello,t);
        float y = BezierQuadratic(length,length-(puntoCuello/2),length,t);
        Points.push_back({x,y});
    }
    for (int i = 0; i < nPoints; ++i){
        float t = ((float)i) / (float(nPoints - 1));
        float x = BezierQuadratic(puntoCuello,ancho/2,ancho-puntoCuello,t);
        float y = BezierQuadratic(length,length-(puntoCuello/3),length,t);
        Points.push_back({x,y});
    }
    for (int i = 0; i < nPoints; ++i){
        float t = ((float)i) / (float(nPoints - 1));
        float x = BezierQuadratic(puntoCuello,ancho/2,ancho-puntoCuello,t);
        float y = BezierQuadratic(length,length+(puntoCuello/10),length,t);
        Points.push_back({x,y});
    }

    //manga der
    for (int i = 0; i < nPoints; ++i){
        float t = ((float)i) / (float(nPoints - 1));
        float x = BezierQuadratic(ancho-puntoCuello,ancho+manga,ancho+manga,t);
        float y = BezierQuadratic(length,length,length-manga*1.5,t);
        Points.push_back({x,y});
    }
    
    Points.push_back({ancho+manga,length-manga*1.5});
    Points.push_back({ancho+manga/4,length-manga-(manga/2)});


    Points.push_back({ancho,length-manga});
    Points.push_back({ancho,0});
    Points.push_back({0,0});
}
void myInit(){
	glClearColor(1, 1, 1, 1);
	glColor3i(0,1,0);
	glPointSize(5);
	gluOrtho2D(-780, 780, -420, 420);
}
//g++ -I eigen-3.4.0/ -o m TShirt.cpp -lGL -lGLU -lglut
int main (int argc, char** argv){
    cout << "Length (default 300): ";
    cin >> length;
    cout << "Translation x (default -100): ";
    cin >> tx;
    cout << "\n";
    cout << "Translation y (default -100): ";
    cin >> ty;
    cout << "\n";
    cout << "Scalation (default 1): ";
    cin >> s;
    cout << "\n";
    cout << "Rotation (default 0): ";
    cin >> r;
    cout << "\n";
    r = r * -pi/180;

    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE  | GLUT_RGB);
	glutInitWindowSize(1280,720);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Test1");

	myInit();

    generateBasicMetrics((float)length);
    
	glutDisplayFunc(draw);
	glutMainLoop();
	return 0;
}
