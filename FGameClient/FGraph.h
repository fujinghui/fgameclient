#ifndef _F_GRAPH_H_
#define _F_GRAPH_H_
#define BUFFER_OFFSET(offset) ((GLvoid*)(NULL + offset))
class FGraph {
private :
	//����ģʽ
	static FGraph *instance;
	FGraph();
	FGraph(const FGraph&);
	FGraph& operator=(const FGraph&);

	//��̬����
	//������İ˸���
	GLfloat cube_data[24] = {
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,

		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0
	};
	GLint cube_data2[24] = {
		-1, -1, 1,
		1, -1, 1,
		1, 1, 1,
		-1, 1, 1,

		-1, -1, -1,
		1, -1, -1,
		1, 1, -1,
		-1, 1, -1
	};
	//�����������
	GLbyte cube_indices[24] = {
		0, 1, 2, 3,
		4, 5, 6, 7,
		0, 1, 5, 4,
		2, 3, 7, 6,
		0, 3, 7, 4,
		1, 2, 6, 5
	};
	//˽�й��ܺ���
private:
	void error(char *s);
	void normalize(float v[3]);
	void normcrossprod(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3]);
public:
	static FGraph* getInstance();

	void DrawCircle(GLfloat r);
	void DrawLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void DrawPolygon();
	
	//��������
	void DrawObject(GLint *vertices);
	void DrawObject(GLint *vertices, GLfloat *color);
	void DrawCube(GLfloat r);
	//ͼ��
	void DrawTwelvePloy();
	void DrawTriangle(GLfloat *v1, GLfloat *v2, GLfloat *v3);	//��������
	//ͼ�ι��ܺ���
	void Subdivide(GLfloat *v1, GLfloat *v2, GLfloat *v3, long depth);
	//������ʵ��
	void DrawObjectTest1();
	void DrawObjectTest2();
};

#endif
