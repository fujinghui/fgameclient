//#include <gl/GL.h>
//#include <gl/GLU.h>
#include <glut.h>
#include <math.h>
#include <cstdlib>
#include "FGraph.h"

#define PI 3.1315926
 
FGraph* FGraph::instance = NULL;
FGraph* FGraph::getInstance() {
	//如果不出意外的话，在多线程模式下是不能够执行的
	if (instance == NULL)
	{
		instance = new FGraph;
	}
	return instance;
}
FGraph::FGraph() {
}
FGraph::FGraph(const FGraph&) {

}	
FGraph& FGraph::operator=(const FGraph&) {
	return *instance;
}

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
//绘制物体
void FGraph::DrawObject(GLint *vertices) {
	//启用定点数组
	glEnableClientState(GL_VERTEX_ARRAY);
	//将顶点放到顶点数组中
	glVertexPointer(3, GL_INT, 0, vertices);
	glBegin(GL_TRIANGLES);
	glArrayElement(0);
	glArrayElement(1);
	glArrayElement(2);
	glEnd();
	//glDisableClientState(GL_VERTEX_ARRAY);
}
//绘制有颜色的物体
void FGraph::DrawObject(GLint *vertices, GLfloat *color) {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	GLint indices[3] = { 0, 1, 2 };

	glVertexPointer(3, GL_INT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, color);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, indices);
	//glBegin(GL_TRIANGLES);
	//glArrayElement(0);
	//g/lArrayElement(1);
	//glArrayElement(2);
	//glEnd();
}
//绘制一个立方体
void FGraph::DrawCube(GLfloat r) {
	GLfloat sdata[] = {
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0 };
	GLbyte indices[] = { 0, 1, 2, 3 };
	GLfloat data[24];
	GLfloat color[24] = { 1.0,1.0,0.0,1.0,1.0,0.0,1.0,1.0,0.0 };
	for (int i = 0; i < 24; i++)
	{
		data[i] = cube_data[i]*r;
		color[i] = (rand() % 100)*1.0 / 100.0;
	} 
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, data);
	glColorPointer(3, GL_FLOAT, 0, color);
	

	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, cube_indices);
	//return;
	//glDrawElements(GL_LINE_STRIP, 4, GL_UNSIGNED_BYTE, cube_indices + 0);
	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, indices);
	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cube_indices + 8);
	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cube_indices + 12);
	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cube_indices + 16);
	//glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, cube_indices + 20);
	/*
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cube_indices);
	for (int i = 0; i < count; i++)
	{
		gl_InstanceID = i;
		glDrawElements(mode, count, type, indicies);
	}
	gl_InstanceID = 0;*/

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDrawElements(GL_LINE_STRIP, 24, GL_UNSIGNED_BYTE, cube_indices);
}

