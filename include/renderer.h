#ifndef RENDERER_H
#define RENDERER_H
#include "global_includes.h"
#include "mesh.h"
#include "objMeshBuilder.h"
#include "shader.h"
#include "camera.h"
#include "frame.h"

class Renderer {
public:
	Renderer();
	Renderer(int, int);
	~Renderer();
	void draw(Camera&, Frame&);
	void init_shaders();
	void init_meshes();
	void setUniformMVP(GLuint, glm::vec3 const&, glm::vec3 const&);
private:
	std::vector<Mesh*> objects;
	glm::mat4 _mat_projection;
};
#endif //RENDERER_H
