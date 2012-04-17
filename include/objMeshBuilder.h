#ifndef OBJMESHBUILDER_H
#define OBJMESHBUILDER_H
#include "baseMeshBuilder.h"
#include "mesh.h"
#include "global_includes.h"

class objMeshBuilder : public baseMeshBuilder, protected commonMesh {
 public:
  objMeshBuilder();
  virtual  ~objMeshBuilder() {};
  Mesh* makeMesh(const std::string&);
 private:
  void processMaterialFile(const std::string&);
  bool find_file(const boost::filesystem3::path&, const std::string&, boost::filesystem3::path&);
  template <typename T>
    void iterate_line(const std::string&, const boost::regex&, std::vector<T>&);
};

template <typename T>
void objMeshBuilder::iterate_line(const std::string& line, const boost::regex& expression, std::vector<T>& vec)
{
  boost::sregex_token_iterator it(line.begin(), line.end(), expression);
  boost::sregex_token_iterator j;
  while(it != j) {
    T temp = boost::lexical_cast<T>(*it++);
    vec.push_back(temp);
  }
}

#endif // OBJMESHBUILDER_H
