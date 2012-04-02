#ifndef MESH_H
#define MESH_H
#include "global_includes.h"
#include "shader.h"
struct MyVertex {
	float x, y, z; //Vertex
	float nx, ny, nz; //Normal
	float s0, t0; //Texcoord0
	float s1, t1; //Texcoord1
	float s2, t2; //Texcoord2
	float padding[4];
	MyVertex() :
			x(0), y(0), z(0), nx(0), ny(0), nz(0), s0(0), t0(0), s1(0), t1(0), s2(
					0), t2(0) {
	}
};

struct MyRanges {
	GLuint start, end;
	GLsizei count;
	MyRanges(GLuint start, GLuint end, GLsizei count) :
			start(start), end(end), count(count) {
	}
};

#define BUFFER_OFFSET(i)((GLfloat *) NULL + (i))

class Mesh {
private:
	GLuint ibo_buffer, vbo_buffer, vao;
	GLuint attrib_vertex, attrib_normals, attrib_texcoords0, attrib_texcoords1,
			attrib_texcoords2;
public:
	MyVertex* vertices;
	GLuint* elements;
	std::vector<MyRanges> * ranges;
	glm::mat4 object2world;
	Mesh() :
			vertices(0), elements(0), ranges(0) {
	}
	;
	~Mesh();
	void upload(int, int);
	void draw();
};
#endif //MESH_H
