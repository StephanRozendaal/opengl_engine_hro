#include "renderer.h"

Renderer::Renderer() {

}

Renderer::Renderer(int width, int height) {
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		//problem GLEW init, something is seriously wrong
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		throw "error in GLEW";
	}
	glClearColor(0.0, 0.004, 0.2, 1.0);
	glClearDepth(1.f);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glEnable(GL_POLYGON_SMOOTH);
	init_shaders();
	init_meshes();
	_mat_projection = glm::perspective(45.0f, (float)width / height, 0.1f, 2000.f);
	_light_position = glm::vec4(0.0, 800.0f, 0.0f, 1.0f);
}
Renderer::~Renderer() {
	GlobalShaderManager::instance()->destroy();
}

void Renderer::draw(Camera& camera, Frame& frame) {
	if(_light_angle >= 360.0) _light_angle = 0.0;
	_light_angle += 0.002;
	_light_position = glm::rotateX(_light_position, _light_angle);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	std::vector<Mesh*>::iterator it;
	Shader shdr = GlobalShaderManager::instance()->get_value();
	GLuint program = shdr.getProgram();
	glUseProgram(program);
	GLint cam_position = glGetUniformLocation(program, "camera_position");
	GLint projection = glGetUniformLocation(program, "projection_matrix");
	GLint model = glGetUniformLocation(program, "model_matrix");
	GLint view = glGetUniformLocation(program, "view_matrix");
	GLint normal_matrix = glGetUniformLocation(program, "normal_matrix");
	GLint light_pos = glGetUniformLocation(program, "light_position");

	glm::mat4 m_view = camera.GetViewMatrix();
	glm::mat4 m_model = glm::scale(frame.get_matrix(false),glm::vec3(0.02, 0.02, 0.02));
	glm::mat3 m_normal_matrix = glm::inverseTranspose(glm::mat3(m_view * m_model));
	glm::vec3 m_camera_position = camera.GetPosition();

	glUniform3fv(cam_position, 1, glm::value_ptr(m_camera_position));
	glUniform4fv(light_pos, 1, glm::value_ptr(_light_position));
	glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(_mat_projection));
	glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(m_view));
	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(m_model));
	glUniformMatrix3fv(normal_matrix, 1, GL_FALSE, glm::value_ptr(m_normal_matrix));

	for (it = objects.begin(); it != objects.end(); it++) {
		(*it)->draw();
	}
	//shdr.printLogs();
}

void Renderer::init_shaders() {
	Shader shader1;
	shader1.loadShaderFromFile("phong_shader.vert", VERTEX_SHADER);
	shader1.loadShaderFromFile("phong_shader.frag", FRAGMENT_SHADER);
	shader1.linkIntoProgram();
	GlobalShaderManager::instance()->set_value(std::string("phong_shader"),
			shader1);
	Shader shader2;
	shader2.loadShaderFromFile("gouraud_shader.vert", VERTEX_SHADER);
	shader2.loadShaderFromFile("gouraud_shader.frag", FRAGMENT_SHADER);
	shader2.linkIntoProgram();
	GlobalShaderManager::instance()->set_value(std::string("gouraud_shader"),
			shader2);
	Shader shader3;
	shader3.loadShaderFromFile("toon_shader.vert", VERTEX_SHADER);
	shader3.loadShaderFromFile("toon_shader.frag", FRAGMENT_SHADER);
	shader3.linkIntoProgram();
	GlobalShaderManager::instance()->set_value(std::string("toon_shader"),
			shader3);
}

void Renderer::init_meshes() {
	objMeshBuilder builder;
	Mesh* msh = builder.makeMesh(
			"/home/stephan/Downloads/obj_files/objects/queen.obj");
	objects.push_back(msh);
}

