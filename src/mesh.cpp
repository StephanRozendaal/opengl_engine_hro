#include "mesh.h"

Mesh::~Mesh() {
	if (vbo_buffer != 0)
		glDeleteBuffers(1, &vbo_buffer);
	if (ibo_buffer != 0)
		glDeleteBuffers(1, &ibo_buffer);
	if (vao != 0)
		glDeleteVertexArrays(1, &vao);
	if (elements != 0)
		delete elements;
	if (vertices != 0)
		delete vertices;
	if (ranges != 0)
		delete ranges;
}

void Mesh::upload(int no_vertices, int no_elements) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	Shader shader = GlobalShaderManager::instance()->get_value(
			std::string("phong_shader"));
	GLuint program = shader.getProgram();
	GLint buffer_size = 0;
	glGenBuffers(1, &vbo_buffer); // VBO BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, vbo_buffer);
	glBufferData(GL_ARRAY_BUFFER, no_vertices * sizeof(MyVertex),
			&vertices[0].x, GL_STATIC_DRAW);
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size);
	std::cout << "array buffer size in bytes: " << buffer_size
			<< " myvertex size in bytes: " << sizeof(MyVertex) << std::endl;
	glGenBuffers(1, &ibo_buffer); // IBO BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, no_elements * sizeof(GLuint),
			&elements[0], GL_STATIC_DRAW);
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE,
			&buffer_size);
	std::cout << "element buffer size in bytes: " << buffer_size
			<< " GLuint size in bytes: " << sizeof(GLuint) << std::endl;
	if (vertices[0].x && vertices[0].y != 0) { // ATTRIB VERTEX
		attrib_vertex = glGetAttribLocation(program, "attrib_vertex");
		glEnableVertexAttribArray(attrib_vertex);
		glVertexAttribPointer(attrib_vertex, 3, GL_FLOAT, GL_FALSE,
				sizeof(MyVertex), BUFFER_OFFSET(0));
	}
	if (vertices[0].nx > 0 || vertices[0].ny > 0 || vertices[0].nz) { // ATTRIB NORMALS
		attrib_normals = glGetAttribLocation(program, "attrib_normal");
		glEnableVertexAttribArray(attrib_normals);
		glVertexAttribPointer(attrib_normals, 3, GL_FLOAT, GL_FALSE,
				sizeof(MyVertex), BUFFER_OFFSET(3));
	}
	if (vertices[0].s0 && vertices[0].t0 != 0) { // ATTRIB TEXCOORDS0
		attrib_texcoords0 = glGetAttribLocation(program, "attrib_texcoord0");
		glEnableVertexAttribArray(attrib_texcoords0);
		glVertexAttribPointer(attrib_texcoords0, 2, GL_FLOAT, GL_FALSE,
				sizeof(MyVertex), BUFFER_OFFSET(6));
	}
	if (vertices[0].s1 && vertices[0].t1 != 0) { // ATTRIB TEXCOORDS1
		attrib_texcoords1 = glGetAttribLocation(program, "attrib_texcoord1");
		glEnableVertexAttribArray(attrib_texcoords1);
		glVertexAttribPointer(attrib_texcoords1, 2, GL_FLOAT, GL_FALSE,
				sizeof(MyVertex), BUFFER_OFFSET(8));
	}
	if (vertices[0].s2 && vertices[0].t2 != 0) { // ATTRIB_TEXCOORDS2
		attrib_texcoords2 = glGetAttribLocation(program, "attrib_texcoord2");
		glEnableVertexAttribArray(attrib_texcoords2);
		glVertexAttribPointer(attrib_texcoords2, 2, GL_FLOAT, GL_FALSE,
				sizeof(MyVertex), BUFFER_OFFSET(10));
	}
	glBindVertexArray(0);
}
void Mesh::setMaterials(const std::string& name) {
	Shader shdr = GlobalShaderManager::instance()->get_value();
	GLuint program = shdr.getProgram();
	GLint ambient_color = glGetUniformLocation(program, "ambient_color");
	GLint diffuse_color = glGetUniformLocation(program, "diffuse_color");
	GLint specular_color = glGetUniformLocation(program, "specular_color");
	std::vector<MyMaterial>::iterator matit;
	for (matit = materials->begin(); matit != materials->end(); matit++) {
		if (name == matit->material_name) {
			glUniform4f(ambient_color, matit->col_amb_r, matit->col_amb_g, matit->col_amb_b, 1.0f);
			glUniform4f(diffuse_color, matit->col_dif_r, matit->col_dif_g, matit->col_dif_b, 1.0f);
			glUniform4f(specular_color, matit->col_spe_r, matit->col_spe_g, matit->col_spe_b, 1.0f);
			break;
		}
	}
}
void Mesh::draw() {
	glBindVertexArray(vao);
	if (ibo_buffer != 0) {
		int buffer_size = 0;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_buffer);
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE,
				&buffer_size);
		if (ranges->size() > 0) {
			std::vector<MyRanges>::iterator elemit;
			for (elemit = ranges->begin(); elemit != ranges->end(); elemit++) {
				setMaterials(elemit->name);
				glDrawRangeElements(GL_TRIANGLES, elemit->start, elemit->end,
						elemit->count, GL_UNSIGNED_INT, NULL);
			}
		} else
			glDrawElements(GL_LINES, buffer_size / sizeof(GLuint),
					GL_UNSIGNED_INT, 0);
	} else {
		int buffer_size = 0;
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size);
		glDrawArrays(GL_LINES, 0, buffer_size / 4);
	}
	glBindVertexArray(0);
}
