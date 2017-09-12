//#include <gl/GL.h>
//#include <gl/GLU.h>
#define GLEW_STATIC 0
#include <GL/glew.h>
#include <glut.h>
#include <math.h>
#include <cstdlib>

#include "FGraph.h"
#include <stdio.h>
#include <math.h>

#pragma comment(lib, "glew32s.lib")
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


//私有函数实现
void FGraph::error(char *s) {
	printf("%s\n", s);
}
void FGraph::normalize(float v[3]) {
	GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (fabs(d) <= 0.000000001)
	{
		error("zero length vector");
		return;
	}
	v[0] /= d;
	v[1] /= d;
	v[2] /= d;
}
void FGraph::normcrossprod(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3]) {
	//向量积
	v3[0] = v1[1] * v2[2] - v1[2] * v2[1];
	v3[1] = v1[2] * v2[0] - v1[0] * v2[2];
	v3[2] = v1[0] * v2[1] - v1[1] * v2[0];
	//归一化
	normalize(v3);
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

	glVertexPointer(3, GL_INT, 6 * sizeof(GLint), vertices);
	glColorPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), color);
	//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, indices);
	//glBegin(GL_TRIANGLES);
	//glArrayElement(0);
	//g/lArrayElement(1);
	//glArrayElement(2);
	//glEnd();
}
//绘制一个立方体
void FGraph::DrawCube(GLfloat r) {
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
	
	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cube_indices);
	/*
	for (int i = 0; i < count; i++)
	{
		gl_InstanceID = i;
		glDrawElements(mode, count, type, indicies);
	}
	gl_InstanceID = 0;
	*/
	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cube_indices);
	
	//glDrawArrays(GL_LINE_STRIP, 0, 24);
	//glDrawElementsInstanced(GL_LINE_STRIP, 24, GL_UNSIGNED_BYTE, cube_indices);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

//缓冲区实验
void FGraph::DrawObjectTest1() {
	int const VERTICES = 0;
	int const INDICES = 1;
	int const NUM_BUFFERS = 2;
	GLuint buffers[NUM_BUFFERS];
	GLfloat vertices[][3] = {
		{-1.0, -1.0, -1.0},
		{1.0, -1.0, -1.0},
		{1.0, 1.0, -1.0},
		{-1.0, 1.0, -1.0},

		{-1.0, -1.0, 1.0},
		{1.0, -1.0, 1.0},
		{1.0, 1.0, 1.0},
		{-1.0, 1.0, 1.0}
	};
	GLubyte indices[][4] = {
		{0, 1, 2, 3},
		{ 4, 5, 6, 7 },
		{ 0, 4, 5, 1 },
		{ 3, 2, 6, 7 },
		{ 0, 3, 7, 4 },
		{ 1, 5, 6, 2 }
	}; 

	//创建缓冲区对象
	glGenBuffers(NUM_BUFFERS, buffers); //创建两个缓冲区，标记在buffers中
	printf("create buffer indexs:");
	for (int i = 0; i < NUM_BUFFERS; i++)
	{
		printf("%d ", buffers[i]);
	}
	printf("\n");
										//绑定缓冲区
	glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTICES]);
	//将数据放到GPU中
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
	glEnableClientState(GL_VERTEX_ARRAY);
	//绑定缓冲区
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDICES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices, GL_STATIC_DRAW);
	
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
	glDeleteBuffers(NUM_BUFFERS, buffers);
}

void FGraph::DrawObjectTest2() {

}
void FGraph::DrawTwelvePloy() {
	GLdouble const X = 0.525731112119133606;
	GLdouble const Z = 0.850650808352039932;
	GLfloat vdata[12][3] = {
		{-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
		{0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
		{Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
	};
	static GLuint tindices[20][3] = {
		{1, 4, 0}, {4, 9, 0}, {4, 5, 9}, {8, 5, 4}, {1, 8, 4},
		{1, 10, 8}, {10, 3, 8}, {8, 3, 5}, {3, 2, 5}, {3, 7, 2},
		{3, 10, 7}, {10, 6, 7}, {6, 11, 7}, {6, 0, 11}, {6, 1, 0},
		{10, 1, 6}, {11, 0, 9}, {2, 11, 9}, {5, 2, 9}, {11, 2, 7}
	};
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vdata[i][j] *= 1;
		}
	}
	int i;
	glBegin(GL_TRIANGLES);
	for (i = 0; i < 20; i++)
	{
		//glVertex3fv(&vdata[tindices[i][0]][0]);
		//glVertex3fv(&vdata[tindices[i][1]][0]);
		//glVertex3fv(&vdata[tindices[i][2]][0]);
		Subdivide(
			&vdata[tindices[i][0]][0],
			&vdata[tindices[i][1]][0],
			&vdata[tindices[i][2]][0],
			1);
	}
	glEnd();
}
void FGraph::DrawTriangle(GLfloat *v1, GLfloat *v2, GLfloat *v3) {
	glBegin(GL_TRIANGLES);
	glNormal3fv(v1);
	glVertex3fv(v1);
	glNormal3fv(v2);
	glVertex3fv(v2);
	glNormal3fv(v3);
	glVertex3fv(v3);
	glEnd();
}
void FGraph::Subdivide(GLfloat *v1, GLfloat *v2, GLfloat *v3, long depth) {
	if (depth == 0)
	{
		DrawTriangle(v1, v2, v3);
		return;
	}
	
	GLfloat v12[3], v31[3], v23[3];
	GLint i;
	for (i = 0; i < 3; i++)
	{
		v12[i] = (v1[i] + v2[i]) / 2.0;
		v31[i] = (v1[i] + v3[i]) / 2.0;
		v23[i] = (v2[i] + v3[i]) / 2.0;
	}
	normalize(v12); normalize(v23); normalize(v31);
	//DrawTriangle(v1, v12, v31);
	//DrawTriangle(v2, v23, v12);
	//DrawTriangle(v3, v31, v23);
	//DrawTriangle(v12, v23, v31);
	Subdivide(v1, v12, v31, depth - 1);
	Subdivide(v2, v23, v12, depth - 1);
	Subdivide(v3, v31, v23, depth - 1);
	Subdivide(v12, v23, v31, depth - 1);
}