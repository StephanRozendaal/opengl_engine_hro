#ifndef BASEMESHBUILDER_H
#define BASEMESHBUILDER_H
#include "global_includes.h"
#include "mesh.h"
class baseMeshBuilder {
public:
	virtual Mesh* makeMesh(const std::string&) = 0;
};

struct commonMesh {
	struct element_data {
		GLuint v_elm;
		GLuint n_elm;
		GLuint t_elm;
		element_data(GLuint v, GLuint n = 0, GLuint t = 0) {
			v_elm = v;
			n_elm = n;
			t_elm = t;
		}
	};
	std::vector<glm::vec4> array_data; // 4-floatingpoint type [x,y,z,(w)]
	std::vector<glm::vec3> texcoords_data; // 3-floatingpoint type [u,v,(w)]
	std::vector<glm::vec3> normals_data; // 3-floatingpoint type [x,y,z]
	std::vector<element_data> elements_data; // unsigned shorts
	std::vector<MyMaterial> * material_data;
};
#endif // BASEMESHBUILDER_H
