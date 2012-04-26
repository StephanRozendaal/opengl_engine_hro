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
const boost::regex materiallibexp("^mtllib [aA-zZ]*.mtl");
const boost::regex materialfilenexp("[aA-zZ]*.mtl");
const boost::regex namedobjexp("^o [a-z]*");
const boost::regex polygongroupexp("^g [a-z]*");
const boost::regex polygongroupnameexp("((?!^g))[aA-zZ_0-9]*$");
const boost::regex usematerialexp("^usemtl [aA-zZ_0-9]*");
const boost::regex usematerialgetnameexp("((?!usemtl))[aA-zZ_0-9]*$"); // to get material name

/*regex gebruikt in .mtl files. */
const boost::regex materialdefexp("^newmtl [aA-zZ_0-9]*");
const boost::regex mtlfnameexp("[aA-zZ_]*.mtl");
const boost::regex mtlnameexp("((?!newmtl))[aA-zZ_0-9]*$"); // the materialname without newmtl
const boost::regex mtlkaexp("^Ka [0-9. ]*");
const boost::regex mtlkdexp("^Kd [0-9. ]*");
const boost::regex mtlksexp("^Ks [0-9. ]*");
const boost::regex mtlkscoeffexp("^Ns [0-9. ]*");

/*regex gebruikt om datatypes te vinden. */
const boost::regex floatexp("[-]?[0-9]*[\\.][0-9]*");
//const boost::regex floatexp("[-+]?[0-9]*\.?[0-9]+");
const boost::regex decimalexp("[-]?[0-9]+");

objMeshBuilder::objMeshBuilder() {

}

Mesh* objMeshBuilder::makeMesh(const std::string& fname) {
	std::ifstream infile;
	std::string str;
	infile.open(fname, std::ifstream::in);
	bool b_use_material = false;
	bool b_polygon_group = false;
	std::string polygon_group_name;
	std::vector<MyRanges> * ranges = 0;
	MyRanges* range = 0;
	GLsizei face_count = 0;
	std::vector<element_data>::iterator it_vec_start; // houdt de range bij van vectoren.
	material_data = new std::vector<MyMaterial>;
	elements_data.reserve(1000000);
	array_data.reserve(1000000);
	while (infile) { // start checking OBJ file line-by-line
		getline(infile, str);
		if (str[str.size() - 1] == '\r')
			str.resize(str.size() - 1);
		if (boost::regex_match(str, faceexp)) { //is a face definition
			face_count += 3;
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
		}
		if (boost::regex_match(str, vertexexp)) { // is a vertex definition
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
			std::vector<std::string> vec;
			iterate_line<std::string>(str, mtlfnameexp, vec);
			boost::filesystem3::path cur_path(
					"/home/stephan/Downloads/obj_files/objects/");
			boost::filesystem3::path path_found;
			find_file(cur_path, vec[0], path_found);
			std::cout << "material path: " << path_found.c_str() << std::endl;
			processMaterialFile(std::string(path_found.c_str()));
		}
		if (boost::regex_match(str, namedobjexp)) { // is a named object definition

		}
		if (boost::regex_match(str, polygongroupexp)) { // is a polygon group definition
			std::vector<std::string> vec;
			iterate_line<std::string>(str, polygongroupnameexp, vec); // get the polygon group name
			polygon_group_name = vec[0];
			b_polygon_group = true;
		}
		if (boost::regex_match(str, usematerialexp)) { // is a material usage definition
			std::vector<std::string> vec;
			iterate_line<std::string>(str, usematerialgetnameexp, vec); // get the polygon group name
			std::string material_name = vec[0];

			if (it_vec_start != elements_data.begin())
				it_vec_start = elements_data.begin();
			if (range != 0) {
				const std::pair<std::vector<element_data>::const_iterator,
						std::vector<element_data>::const_iterator> temp_elm =
						std::minmax_element(
								(it_vec_start + 1),
								elements_data.end(),
								[](const element_data& rhs, const element_data& lhs) {
									return rhs.v_elm > lhs.v_elm;
								});
				range->start = temp_elm.first->v_elm;
				range->end = temp_elm.second->v_elm;
				range->count = face_count;
				if (ranges == 0)
					ranges = new std::vector<MyRanges>;
				ranges->push_back(
						MyRanges(range->name, range->start, range->end,
								range->count));
			} else
				range = new MyRanges { material_name, 0, 0, 0 };
			b_use_material = true;
			it_vec_start = elements_data.end();
		}
	}

	if (b_use_material) {
		if (it_vec_start != elements_data.begin())
			it_vec_start = elements_data.begin();
		const std::pair<std::vector<element_data>::const_iterator,
				std::vector<element_data>::const_iterator> temp_elm =
				std::minmax_element(
						(it_vec_start + 1),
						elements_data.end(),
						[](const element_data& rhs, const element_data& lhs) {
							return rhs.v_elm < lhs.v_elm;
						});
		range->start = temp_elm.first->v_elm;
		range->end = temp_elm.second->v_elm;
		range->count = face_count;
		ranges = new std::vector<MyRanges>;
		ranges->push_back(
				MyRanges(range->name, range->start, range->end, range->count));
	}
	infile.close();
	std::cout << " size of vertex elements: " << elements_data.size()
			<< " size of vertices: " << array_data.size()
			<< " size of normals: " << normals_data.size()
			<< " size of texcoords: " << texcoords_data.size() << std::endl;
	Mesh* mesh = new Mesh();
	if (ranges > 0)
		mesh->ranges = ranges;
	mesh->vertices = new MyVertex[elements_data.size()]();
	mesh->elements = new GLuint[elements_data.size()];
	for (int i = 0; i < elements_data.size(); i++) {
		mesh->elements[i] = elements_data[i].v_elm;
		mesh->vertices[elements_data[i].v_elm].x =
				array_data[elements_data[i].v_elm].x;
		mesh->vertices[elements_data[i].v_elm].y =
				array_data[elements_data[i].v_elm].y;
		mesh->vertices[elements_data[i].v_elm].z =
				array_data[elements_data[i].v_elm].z;
		if (!normals_data.empty()) {
			mesh->vertices[elements_data[i].n_elm].nx =
					normals_data[elements_data[i].n_elm].x;
			mesh->vertices[elements_data[i].n_elm].ny =
					normals_data[elements_data[i].n_elm].y;
			mesh->vertices[elements_data[i].n_elm].nz =
					normals_data[elements_data[i].n_elm].z;
		}
		if (!texcoords_data.empty()) {
			mesh->vertices[elements_data[i].n_elm].s0 =
					texcoords_data[elements_data[i].t_elm].s;
			mesh->vertices[elements_data[i].n_elm].t0 =
					texcoords_data[elements_data[i].t_elm].t;
		}
	}
	mesh->materials = material_data;
	std::cout << "number of materials: " << mesh->materials->size()
			<< std::endl;
	mesh->upload(array_data.size(), elements_data.size());
	return mesh;
}

void objMeshBuilder::processMaterialFile(const std::string& fname) { // process the material template library files
	std::ifstream infile;
	std::string str;
	infile.open(fname, std::ifstream::in);
	MyMaterial temp;
	bool first_material = true;
	while (infile) {
		getline(infile, str);
		if (str[str.size() - 1] == '\r')
			str.resize(str.size() - 1);
		if (boost::regex_match(str, materialdefexp)) { // material name match
			if (first_material)
				first_material = false;
			else
				material_data->push_back(temp);
			std::vector<std::string> vec;
			iterate_line<std::string>(str, mtlnameexp, vec);
			temp.material_name = vec[0];
		}
		if (boost::regex_match(str, mtlkaexp)) { // ambient color match
			std::vector<float> vec;
			iterate_line<float>(str, floatexp, vec);
			temp.col_amb_r = vec[0];
			temp.col_amb_g = vec[1];
			temp.col_amb_b = vec[2];
		}
		if (boost::regex_match(str, mtlkdexp)) { //diffuse color match
			std::vector<GLfloat> vec;
			iterate_line<GLfloat>(str, floatexp, vec);
			temp.col_dif_r = vec[0];
			temp.col_dif_g = vec[1];
			temp.col_dif_b = vec[2];
		}
		if (boost::regex_match(str, mtlksexp)) { // specular color match
			std::vector<GLfloat> vec;
			iterate_line<GLfloat>(str, floatexp, vec);
			temp.col_spe_r = vec[0];
			temp.col_spe_g = vec[1];
			temp.col_spe_b = vec[2];
		}
		if (boost::regex_match(str, mtlkscoeffexp)) { //specular coefficient match
			std::vector<GLfloat> vec;
			iterate_line<GLfloat>(str, floatexp, vec);
			temp.spec_coeff = vec[0];
		}
	}
	material_data->push_back(temp);
}

bool objMeshBuilder::find_file(const boost::filesystem3::path& dir_path,
		const std::string& file_name, boost::filesystem3::path& path_found) {
	if (!boost::filesystem3::exists(dir_path)
			|| !boost::filesystem3::is_directory(dir_path))
		return false;
	boost::filesystem3::directory_iterator end_iter;
	for (boost::filesystem3::directory_iterator dir_itr(dir_path);
			dir_itr != end_iter; ++dir_itr) {
		if (dir_itr->path().filename() == file_name) {
			path_found = dir_itr->path();
			//std::cout << "path found! " << std::endl;
			return true;
		}
	}
	return false;
}

bool objMeshBuilder::compare_elements(element_data& rhs, element_data& lhs) {
	return (rhs.v_elm < lhs.v_elm);
}
