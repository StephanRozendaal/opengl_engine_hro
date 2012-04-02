#ifndef RENDERER_H
#define RENDERER_H
#include "global_includes.h"
#include "mesh.h"
#include "objMeshBuilder.h"
#include "shader.h"

class Renderer {
public:
	Renderer();
	Renderer(int, int);
	~Renderer();
	void draw();
	void setUniformMVP(GLint, glm::vec3 const&, glm::vec3 const&);
private:
	std::vector<Mesh*> objects;
};
#endif //RENDERER_H
