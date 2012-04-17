/*
 * shader.cpp
 *
 *  Created on: Mar 23, 2012
 *      Author: stephan
 */
#include "shader.h"

void Shader::delete_shader() {
	if (vertex_shader > 0)
		glDeleteShader(vertex_shader);
	if (fragment_shader > 0)
		glDeleteShader(fragment_shader);
	if (geometry_shader > 0)
		glDeleteShader(geometry_shader);
	if (program > 0)
		glDeleteProgram(program);
}

bool Shader::loadShaderFromFile(const char* fname, shader_types stype) {
	std::ifstream file;
	file.open(fname, std::ios::in);
	if (file.is_open()) { // the file is open
		char** shader_source = new char*[2000];
		int* filelen = new int[2000];
		int linecount;
		for (linecount = 0; file.good(); linecount++) {
			shader_source[linecount] = new char[2560];
			file.getline(shader_source[linecount], 2560, '\0');
			filelen[linecount] = file.gcount();
		}
		file.close();
		GLint compile_result = 0;
		switch (stype) {
		case VERTEX_SHADER: {
			vertex_shader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertex_shader, linecount,
					(const char**) shader_source, filelen);
			glCompileShader(vertex_shader);
			glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_result);
			getGLerror();
			break;
		}
		case FRAGMENT_SHADER: {
			fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragment_shader, linecount,
					(const char**) shader_source, filelen);
			glCompileShader(fragment_shader);
			glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_result);
			getGLerror();
			break;
		}
		case GEOMETRY_SHADER: {
			geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry_shader, linecount,
					(const char**) shader_source, filelen);
			glCompileShader(geometry_shader);
			glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &compile_result);
			getGLerror();
			break;
		}
		}
		if (compile_result != GL_TRUE) {
			std::cout << "compile failed" << std::endl;
			switch (stype) {
			case VERTEX_SHADER: {
				GLchar* info_log = new GLchar[1000];
				glGetShaderInfoLog(vertex_shader, 1000, NULL, info_log);
				std::cout << "compile log: " << info_log;
				delete[] info_log;
				break;
			}
			case FRAGMENT_SHADER: {
				GLchar* info_log = new GLchar[1000];
				glGetShaderInfoLog(fragment_shader, 1000, NULL, info_log);
				std::cout << "compile log: " << info_log;
				delete[] info_log;
				break;
			}
			case GEOMETRY_SHADER: {
				GLchar* info_log = new GLchar[1000];
				glGetShaderInfoLog(fragment_shader, 1000, NULL, info_log);
				std::cout << "compile log" << info_log;
				delete[] info_log;
				break;
			}
			}
		} else
			std::cout << "compile succeeded of file: " << fname << std::endl;
		for (int i = 0; i < linecount; i++) {
			delete shader_source[i];
		}
		delete[] shader_source;
		delete filelen;
		return true;
	} else {
		std::cout << "shader file not found" << std::endl;
		return false;
	}
}

bool Shader::loadShaderFromMemory(const char** shader_source,
		shader_types stype) {
	int* filelen = new int[200];
	int linecount = 0;
	for (int linecount = 0; shader_source[linecount] != NULL; linecount++) {
		filelen[linecount] = sizeof(shader_source[linecount]) / sizeof(char);
	}
	GLint compile_result = 0;
	switch (stype) {
	case VERTEX_SHADER: {
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, linecount, shader_source, filelen);
		glCompileShader(vertex_shader);
		glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_result);
		getGLerror();
		break;
	}
	case FRAGMENT_SHADER: {
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, linecount, shader_source, filelen);
		glCompileShader(fragment_shader);
		glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_result);
		getGLerror();
		break;
	}
	case GEOMETRY_SHADER: {
		geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry_shader, linecount, shader_source, filelen);
		glCompileShader(geometry_shader);
		glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &compile_result);
		getGLerror();
		break;
	}
	}
	if (compile_result != GL_TRUE) {
		std::cout << "compile failed" << std::endl;
		switch (stype) {
		case VERTEX_SHADER: {
			GLchar* info_log = new GLchar[1000];
			glGetShaderInfoLog(vertex_shader, 1000, NULL, info_log);
			std::cout << "compile log: " << info_log;
			delete[] info_log;
			break;
		}
		case FRAGMENT_SHADER: {
			GLchar* info_log = new GLchar[1000];
			glGetShaderInfoLog(fragment_shader, 1000, NULL, info_log);
			std::cout << "compile log: " << info_log;
			delete[] info_log;
			break;
		}
		case GEOMETRY_SHADER: {
			GLchar* info_log = new GLchar[1000];
			glGetShaderInfoLog(fragment_shader, 1000, NULL, info_log);
			std::cout << "compile log" << info_log;
			delete[] info_log;
			break;
		}
		}
		return false;
	} else
		std::cout << "compile succeeded of file: from memory" << std::endl;
	return true;
}

bool Shader::linkIntoProgram() {
	/*create program and attach shaders */
	program = glCreateProgram();
	if (vertex_shader > 0)
		glAttachShader(program, vertex_shader);
	if (fragment_shader > 0)
		glAttachShader(program, fragment_shader);
	//if (geometry_shader > 0)
	//	glAttachShader(program, geometry_shader);

	glBindAttribLocation(program, 0, "attrib_vertex");
	glBindAttribLocation(program, 1, "attrib_normal");
	glBindAttribLocation(program, 2, "attrib_texcoord0");
	glBindAttribLocation(program, 3, "attrib_texcoord1");
	glBindAttribLocation(program, 4, "attrib_texcoord2");
	/*link the shaders into the program */glLinkProgram(program);
	/*check for errors */glValidateProgram(program);
	GLint status = 0;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
	if (status != GL_TRUE) {
		std::cout << "program not validated" << std::endl;
		return false;
	} else
		std::cout << "program is validated" << std::endl;
	getGLerror();
	return true;
}

GLuint Shader::getProgram() {
	return program;
}

void Shader::printLogs() {
	GLint info_log_length = 0;
	GLint attached_shaders = 0;
	GLint active_attributes = 0;
	GLint active_uniforms = 0;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
	glGetProgramiv(program, GL_ATTACHED_SHADERS, &attached_shaders);
	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &active_attributes);
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &active_uniforms);
	GLchar* info_log = new GLchar[info_log_length];
	glGetProgramInfoLog(program, 1000, &info_log_length, info_log);
	std::cout << "program info log: " << info_log << std::endl;
	std::cout << "number of attached shaders: " << attached_shaders
			<< std::endl;
	std::cout << "number of active attributes: " << active_attributes
			<< std::endl;
	std::cout << "number of active uniforms: " << active_uniforms << std::endl;
	GLint vertex_attribs = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, & vertex_attribs);
	std::cout << "max number of vertex attributes: " << vertex_attribs << std::endl;
	delete info_log;
}

/*************************************************************
 * Singleton globalshadermanager memberfunctions declarations.
 *************************************************************/

GlobalShaderManager* GlobalShaderManager::s_instance = NULL;
bool GlobalShaderManager::instanceflag = false;
std::map<std::string, Shader> GlobalShaderManager::resource;

Shader GlobalShaderManager::get_value(std::string val) {
	return resource[val];
}

void GlobalShaderManager::set_value(std::string key, Shader val) {
	resource.insert(std::pair<std::string, Shader>(key, val));
}

void GlobalShaderManager::destroy() {
	std::map<std::string, Shader>::iterator it;
	for (it = resource.begin(); it != resource.end(); it++)
		it->second.delete_shader();
	delete s_instance;
}
