#ifndef CAMERA_H
#define CAMERA_H
#include "global_includes.h"
class Camera {
public:
	Camera(float _fov, glm::ivec2 _view_size, glm::vec2 _near_far);
	~Camera(void);

	void SetOffset(glm::vec3 _offset);
	void SetPosition(glm::vec3 _position);
	void SetOrientation(glm::quat _orientation);
	void SetViewSize(glm::ivec2 _view_size);
	void SetNearFar(glm::vec2 _near_far);
	void SetFOV(float _fov);

	void ComputeViewMatrix(void);
	void ComputeProjectionMatrix(void);
	void Update(void);
	void Move(glm::vec3 movement);
	void Rotate(glm::vec3 angles);
	void RotateByMouse(glm::vec2 mouse_deltas);

	glm::vec3 GetPosition(void);
	glm::vec3 GetOffset(void);
	glm::quat GetOrientation(void);
	glm::ivec2 GetViewSize(void);
	glm::vec2 GetNearFar(void);
	float GetFOV(void);
	glm::mat4 GetViewMatrix(void);
	glm::mat4 GetInverseViewMatrix(void);
	glm::mat4 GetProjectionMatrix(void);
	glm::mat4 GetInverseProjectionMatrix(void);
private:
// View Matrix Stuff
	glm::vec3 offset;
	glm::vec3 position;
	glm::quat orientation;
	glm::mat4 view_matrix;
	glm::mat4 inverse_view_matrix;

// Projection Matrix Stuff
	glm::ivec2 view_size;
	glm::vec2 near_far;
	float fov;
	glm::mat4 projection_matrix;
	glm::mat4 inverse_projection_matrix;

	bool invert_y;
	bool mouse_x_roll;
};
#endif //CAMERA_H
