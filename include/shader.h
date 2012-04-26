/*
 * shader.h
 *
 *  Created on: Mar 23, 2012
 *      Author: stephan
 */
#ifndef SHADER_H_
#define SHADER_H_
#include "global_includes.h"
typedef enum {
	VERTEX_SHADER = 0, FRAGMENT_SHADER, GEOMETRY_SHADER
} shader_types;
class Shader {
public:
	Shader() {
	}
	void delete_shader();
	bool loadShaderFromFile(const char*, shader_types); // reads from a filename
	bool loadShaderFromMemory(const char**, shader_types); // reads from a char* array
	bool linkIntoProgram();
	GLuint getProgram();
	void printLogs();
protected:
	GLuint attrib_vertex, attrib_normal, attrib_texcoord0, attrib_texcoord1,
			attrib_texcoord2; // index for attributes bound to shader
	GLuint vertex_shader, fragment_shader, geometry_shader; // shader objects
	GLuint program; // program object
};

class GlobalShaderManager {
private:
	static std::map<std::string, Shader> resource;
	std::map<std::string, Shader>::iterator cur_shader_it;
	static GlobalShaderManager * s_instance;
	static bool instanceflag;
	GlobalShaderManager() {

	}
public:
	~GlobalShaderManager() {
		instanceflag = false;
	}
	Shader get_value();
	void set_next_value();
	Shader get_value(std::string);
	void set_value(std::string, Shader);
	static GlobalShaderManager* instance() {
		if (!instanceflag) {
			s_instance = new GlobalShaderManager;
			instanceflag = true;
			return s_instance;
		} else
			return s_instance;
	}
	void destroy();
};
#endif /* SHADER_H_ */
