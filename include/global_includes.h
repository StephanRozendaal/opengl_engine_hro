#ifndef GLOBAL_INCLUDES_H_INCLUDED
#define GLOBAL_INCLUDES_H_INCLUDED
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <exception>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstdio>

inline void getGLerror() {
  GLenum errCode = glGetError();
  const GLubyte *errString;
  while((errCode = glGetError()) != GL_NO_ERROR) {
    errString = gluErrorString(errCode);
    std::cout << "OpenGL Error: " << errString << std::endl;
  }
}

#endif // GLOBAL_INCLUDES_H_INCLUDED
