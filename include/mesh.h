#ifndef MESH_H
#define MESH_H
#include "global_includes.h"
#include "shader.h"
#include "camera.h"

struct MyVertex { // per-vertice data struct
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

struct MyMaterial { // per-material properties struct
	std::string material_name;
	float col_amb_r, col_amb_g, col_amb_b; // ambient color ranged between 0-1
	float col_dif_r, col_dif_g, col_dif_b; // diffuse color ranged between 0-1
	float col_spe_r, col_spe_g, col_spe_b; // specular color ranged between 0-1
	float spec_coeff; // specular coefficient ranged between 0-1000
	float transparency; // transparency or dissolved value
	MyMaterial() {
		material_name = "";
		col_amb_r = 0, col_amb_g = 0, col_amb_b = 0;
		col_dif_r = 0, col_dif_g = 0, col_dif_b = 0;
		col_spe_r = 0, col_spe_g = 0, col_spe_b = 0;
		spec_coeff = 0;
		transparency = 0;
	}
	MyMaterial(const MyMaterial& rhs) {
		material_name = rhs.material_name;
		col_amb_r = rhs.col_amb_r, col_amb_g = rhs.col_amb_g, col_amb_b =
				rhs.col_amb_g;
		col_dif_r = rhs.col_dif_r, col_dif_g = rhs.col_dif_g, col_dif_b =
				rhs.col_dif_b;
		col_spe_r = rhs.col_spe_r, col_spe_g = rhs.col_spe_g, col_spe_b =
				rhs.col_spe_b;
		spec_coeff = rhs.spec_coeff;
		transparency = rhs.transparency;
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
	std::vector<MyMaterial> * materials;
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
