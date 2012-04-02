#include "objMeshBuilder.h"

/*regex gebruikt in .obj files. */
const boost::regex vertexexp("^v ([-]?[0-9]*[\\.][0-9]*[ ]?){3,3}");
const boost::regex faceexp("^f [0-9/ ]*");

const boost::regex facevertexp("^f[ ]+([0-9]*[ ]?){3,}");
const boost::regex faceverttexexp("^f[ ]+([0-9]+/[0-9]+[ ]?){3,}");
const boost::regex faceverttexnormexp("^f[ ]+([0-9]+/[0-9]+/[0-9]+[ ]?){3,}");
const boost::regex facevertnormexp("^f[ ]+([0-9]+//[0-9]+[ ]?){3,}");

const boost::regex textureexp("^vt ([-]?[0-9]*[\\.][0-9]*[ ]?){2,3}");
const boost::regex normalexp("^vn ([-]?[0-9]*[\\.][0-9]*[ ]?){3,3}");
const boost::regex materiallibexp("^mtllib [a-z]*.mtl");
const boost::regex namedobjexp("^o [a-z]*");
const boost::regex polygongroupexp("^g [a-z]*");
const boost::regex usematerialexp("^usemtl [a-z]*");

/*regex gebruikt in .mtl files. */
const boost::regex materialdefexp("^newmtl [a-z]*");

/*regex gebruikt om datatypes te vinden. */
const boost::regex floatexp("[-]?[0-9]*[\\.][0-9]*");
const boost::regex decimalexp("[-]?[0-9]+");

objMeshBuilder::objMeshBuilder() {

}

Mesh* objMeshBuilder::makeMesh(const std::string& fname) {
	std::ifstream infile;
	std::string str;
	infile.open(fname, std::ifstream::in);
	bool in_face_value = false;
	bool in_vertex_value = true;
	std::vector<MyRanges> * ranges = 0;
	MyRanges* range = 0;
	GLuint face_count = 0;
	while (infile) { // start checking OBJ file line-by-line
		getline(infile, str);
		if (str[str.size() - 1] == '\r')
			str.resize(str.size() - 1);
		if (boost::regex_match(str, faceexp)) { //is a face definition

			if (!in_face_value) {
				in_vertex_value = false;
				if (range == 0) {
					range = new MyRanges { 0, 0, 0 };
					range->start = face_count;
				}
				range->count += 3;
			}
			if (boost::regex_match(str, facevertexp)) { // face definition for vertexes
				std::vector<GLuint> vec;
				iterate_line<GLuint>(str, decimalexp, vec);
				elements_data.push_back(element_data(vec[0] - 1)); // vertex element value 1
				elements_data.push_back(element_data(vec[1] - 1)); // vertex element value 2
				elements_data.push_back(element_data(vec[2] - 1)); // vertex element value 3
			} else if (boost::regex_match(str, faceverttexexp)) { // face definition for vertex/texturecoords
				std::vector<GLuint> vec;
				iterate_line<GLuint>(str, decimalexp, vec);
				elements_data.push_back(
						element_data(vec[0] - 1, 0, vec[1] - 1)); // vertex element value 1
				elements_data.push_back(
						element_data(vec[2] - 1, 0, vec[3] - 1)); // vertex element value 2
				elements_data.push_back(
						element_data(vec[4] - 1, 0, vec[5] - 1)); // vertex element value 3
			} else if (boost::regex_match(str, facevertnormexp)) { // face definition for vertex/normals
				std::vector<GLuint> vec;
				iterate_line<GLuint>(str, decimalexp, vec);
				elements_data.push_back(element_data(vec[0] - 1, vec[1] - 1)); // vertex element value 1
				elements_data.push_back(element_data(vec[2] - 1, vec[3] - 1)); // vertex element value 2
				elements_data.push_back(element_data(vec[4] - 1, vec[5] - 1)); // vertex element value 3
			} else if (boost::regex_match(str, faceverttexnormexp)) { // face definition for vertex/texture/normals
				std::vector<GLuint> vec;
				iterate_line<GLuint>(str, decimalexp, vec);
				elements_data.push_back(
						element_data(vec[0] - 1, vec[1] - 1, vec[2] - 1)); // vertex element value 1
				elements_data.push_back(
						element_data(vec[3] - 1, vec[4] - 1, vec[5] - 1)); // vertex element value 2
				elements_data.push_back(
						element_data(vec[6] - 1, vec[7] - 1, vec[8] - 1)); // vertex element value 3
			} else { //error: unknown face definition

			}
			face_count++;
		}
		if (boost::regex_match(str, vertexexp)) { // is a vertex definition
			if (!in_vertex_value) {
				in_face_value = false;
				range->end = face_count + range->count;
				if (ranges == 0)
					ranges = new std::vector<MyRanges>;
				ranges->push_back(
						MyRanges(range->start, range->end, range->count));
				range = 0;
				in_vertex_value = true;
			}
			std::vector<GLfloat> vec;
			iterate_line<GLfloat>(str, floatexp, vec);
			glm::vec4 vert(vec[0], vec[1], vec[2], 1.0);
			array_data.push_back(vert);
		}
		if (boost::regex_match(str, textureexp)) { // is a texture coordinate definition
			std::vector<GLfloat> vec;
			iterate_line<GLfloat>(str, floatexp, vec);
			glm::vec3 vert(vec[0], vec[1], vec[2]);
			texcoords_data.push_back(vert);
		}
		if (boost::regex_match(str, normalexp)) { // is a normal definition
			std::vector<GLfloat> vec;
			iterate_line<GLfloat>(str, floatexp, vec);
			glm::vec3 vert(vec[0], vec[1], vec[2]);
			normals_data.push_back(vert);
		}
		if (boost::regex_match(str, materiallibexp)) { // is a material reference file definition

		}
		if (boost::regex_match(str, namedobjexp)) { // is a named object definition

		}
		if (boost::regex_match(str, polygongroupexp)) { // is a polygon group definition

		}
		if (boost::regex_match(str, usematerialexp)) { // is a material usage definition

		}
	}
	infile.close();
	std::cout << " size of vertex elements: " << elements_data.size()
			<< " size of vertices: " << array_data.size()
			<< " size of normals: " << normals_data.size()
			<< " size of texcoords: " << texcoords_data.size() << std::endl;
	Mesh* mesh = new Mesh();
	if (ranges > 0)
		mesh->ranges = ranges;
	mesh->vertices = (MyVertex*) malloc(sizeof(MyVertex) * array_data.size());
	mesh->elements = new GLuint[elements_data.size()];
	for (int i = 0; i < array_data.size(); i++) {
		mesh->vertices[i].x = array_data[i].x;
		mesh->vertices[i].y = array_data[i].y;
		mesh->vertices[i].z = array_data[i].z;
	}
	for (int i = 0; i < elements_data.size(); i++) {
		mesh->elements[i] = elements_data[i].v_elm;
		if (!normals_data.empty()) {
			mesh->vertices[elements_data[i].n_elm].nx =
					normals_data[elements_data[i].n_elm].x;
			mesh->vertices[elements_data[i].n_elm].ny =
					normals_data[elements_data[i].n_elm].y;
			mesh->vertices[elements_data[i].n_elm].nz =
					normals_data[elements_data[i].n_elm].z;
		}
	}
	mesh->upload(array_data.size(), elements_data.size());
	return mesh;
}

void objMeshBuilder::processMaterialFile(const std::string& fname) { // process the material template library files
	std::ifstream infile;
	std::string str;
	infile.open(fname, std::ifstream::in);
	while (infile) {
		getline(infile, str);
		if (boost::regex_match(str, materialdefexp)) {

		}
	}
}
