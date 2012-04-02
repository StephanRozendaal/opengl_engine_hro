#ifndef CAMERA_H
#define CAMERA_H
#include "global_includes.h"

typedef enum {CAM_UP = 0, CAM_DOWN, CAM_RIGHT, CAM_LEFT}cam_vector;

class Camera {
 public:
  Camera(float, float, float);
  virtual ~Camera();
  void translate(cam_vector);
  void rotate();
  glm::mat4x4 get_camera_matrix();
 private:
  glm::mat4x4 cam_matrix;
};

#endif //CAMERA_H
