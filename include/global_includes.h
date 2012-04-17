#ifndef GLOBAL_INCLUDES_H_INCLUDED
#define GLOBAL_INCLUDES_H_INCLUDED
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <exception>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/rotate_vector.hpp"


inline void getGLerror() {
  GLenum errCode = glGetError();
  const GLubyte *errString;
  while((errCode = glGetError()) != GL_NO_ERROR) {
    errString = gluErrorString(errCode);
    std::cout << "OpenGL Error: " << errString << std::endl;
  }
}

#endif // GLOBAL_INCLUDES_H_INCLUDED
