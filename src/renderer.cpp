#include "renderer.h"

Renderer::Renderer() {
	GlobalShaderManager::instance()->destroy();
}

Renderer::Renderer(int width, int height) {
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		//problem GLEW init, something is seriously wrong
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		throw "error in GLEW";
	}
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearDepth(1.f);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	Shader shader;
	shader.loadShaderFromFile("standard_shader.vert", VERTEX_SHADER);
	shader.loadShaderFromFile("standard_shader.frag", FRAGMENT_SHADER);
	shader.linkIntoProgram();
	GlobalShaderManager::instance()->set_value(std::string("standard_shader"),
			shader);
	objMeshBuilder builder;
	Mesh* msh = builder.makeMesh("/home/stephan/Downloads/obj_files/objects/buddha.obj");
	objects.push_back(msh);
	getGLerror();

}
Renderer::~Renderer() {
}

void Renderer::draw() {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	std::vector<Mesh*>::iterator it;
	Shader shdr = GlobalShaderManager::instance()->get_value(
			std::string("standard_shader"));
	GLuint program = shdr.getProgram();
	glUseProgram(program);
	GLint mvp = glGetUniformLocation(program, "mwvp_matrix");
	setUniformMVP(mvp, glm::vec3(0.0f, 0.0f, -10.0f),
			glm::vec3(0.0f, 0.0f, 0.0f));
	GLint color_loc = glGetUniformLocation(program, "color");
	glUniform4f(color_loc, 1.0f, 0.0f, 0.0f, 1.0f);
	for (it = objects.begin(); it != objects.end(); it++) {
		(*it)->draw();
	}
	shdr.printLogs();
	getGLerror();
}

void Renderer::setUniformMVP(GLint program, glm::vec3 const & translate,
		glm::vec3 const& rotate) {
	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 viewtranslate = glm::translate(glm::mat4(1.0f), translate);
	glm::mat4 viewrotatex = glm::rotate(viewtranslate, rotate.y,
			glm::vec3(-1.0f, 0.0f, 0.0f));
	glm::mat4 view = glm::rotate(viewrotatex, rotate.x,
			glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	glm::mat4 MVP = projection * view * model;
	glUniformMatrix4fv(program, 1, GL_FALSE, glm::value_ptr(MVP));
}
