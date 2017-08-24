//#include <gl/GL.h>
//#include <gl/GLU.h>
#include <glut.h>
#include <math.h>
#include "FGraph.h"

#define PI 3.1315926

void FGraph::DrawCircle(GLfloat r) {
	int n = 10;
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);
	//glBegin(GL_LINE_STRIP);
	for (int i = 0; i < 10; i++)
	{
		double angle = 2 * PI / 10 * i;
		GLfloat x = cos(angle) * r;
		GLfloat y = sin(angle) * r;
		glVertex3f(x, y, 0);
	}
	glEnd();
}
void FGraph::DrawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(1, 0xAAAA);
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}
void FGraph::DrawPolygon() {
	GLubyte fly[] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0xff, 0x00, 0xf0, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00,
	};
	glFrontFace(GL_CCW);		//指定逆时针为正面
	glCullFace(GL_FRONT_AND_BACK);
	glRectf(-0.5, -0.5, 0.5, 0.5);

	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(fly);
	glRectf(0.5, 0.5, 1.0, 1.0);
	glDisable(GL_POLYGON_STIPPLE);
}
