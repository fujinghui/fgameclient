// FGameClient.cpp: 定义控制台应用程序的入口点。
//
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glut.h>
#include <math.h>
#include "FGraph.h"

#define PI 3.1315926
static GLfloat spin = 0.0;
FGraph graph;
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	graph.DrawCircle(1.0);
	graph.DrawLine(0, 0, 1.0, 1.1);
	graph.DrawPolygon();
	glEnd();


	//glBegin(GL_TRIANGLES);
	//glVertex3f(-0.5, -0.5, 1.0);
	//glVertex3f(0.5, 0.0, 1.0);
	//glVertex3f(0.0, 0.5, 1.0);


	//glEnd();
	
	//glColor3f(1.0, 1.0, 0.0);

	glPopMatrix();
	glutSwapBuffers();
}
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(spin, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 1.0);
	glRectf(-25.0, -25.0, 25.0, 25.0);

	glLineWidth(10.0f);


	glPopMatrix();
	glutSwapBuffers();
}
void spinDisplay(void) {
	spin = spin + 2.0;
	if (spin > 360.0)
		spin = spin - 360.0;
	glutPostRedisplay();			//重绘窗口
}
//重绘窗口调用的函数
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-500.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	gluOrtho2D(-100.0, 100.0, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}
int main(int argc, char **argv)
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("hello opengl");
	init();
	glutDisplayFunc(renderScene);
	//glutReshapeFunc(reshape);
	//glutMouseFunc(mouse);
	glutMainLoop();
    return 0;
}

