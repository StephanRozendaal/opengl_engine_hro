#include "camera.h"
Camera::Camera(float _fov, glm::ivec2 _view_size, glm::vec2 _near_far) {
	offset = glm::vec3(0.0f, 0.0f, 0.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	view_matrix = glm::mat4(1.0f);

	fov = _fov;
	view_size = _view_size;
	near_far = _near_far;

	invert_y = false;
	mouse_x_roll = false;
}

Camera::~Camera(void) {
//
}

void Camera::ComputeViewMatrix(void) {
	glm::mat4 rotation_matrix = glm::toMat4(-orientation);
	glm::mat4 offset_matrix = glm::translate(glm::mat4(1.0f), -offset);
	glm::mat4 translation_matrix = glm::translate(glm::mat4(1.0f), -position);
	view_matrix = offset_matrix * rotation_matrix * translation_matrix;
	inverse_view_matrix = glm::inverse(view_matrix);

//view_matrix = glm::gtc::matrix_transform::lookAt(position, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	/*view_matrix = glm::gtx::quaternion::toMat4(glm::gtc::quaternion::normalize(orientation));
	 view_matrix = glm::translate(view_matrix, offset);
	 view_matrix = glm::translate(view_matrix, position);*/

// better!
	/*glm::vec3 direction = glm::normalize(glm::vec3(view_matrix[0][2], view_matrix[1][2], view_matrix[2][2]));
	 glm::vec3 lookat = position + direction;
	 std::cout << position.x << ' ' << position.y << ' ' << position.z << ' ' << direction.x << ' ' << direction.y << ' ' << direction.z << std::endl;
	 view_matrix = glm::gtc::matrix_transform::lookAt(position, lookat, glm::vec3(0.0f, 1.0f, 0.0f));*/

// Very very close!
	/*glm::mat4 translation_matrix = glm::translate(glm::mat4(), position);
	 glm::mat4 rotation_matrix = glm::gtx::quaternion::toMat4(orientation);
	 view_matrix = glm::inverse(translation_matrix * rotation_matrix);*/
}

void Camera::ComputeProjectionMatrix(void) {
	projection_matrix = glm::perspective(fov, view_size.x / float(view_size.y),
			near_far.x, near_far.y);
	inverse_projection_matrix = glm::inverse(projection_matrix);
//projection_matrix = glm::transpose(projection_matrix);
//EG::Math::Utility::PrintMat4(projection_matrix);
}

void Camera::Move(glm::vec3 movement) {
	position += glm::vec3(view_matrix[0][0], view_matrix[1][0],
			view_matrix[2][0]) * movement.x;
	position += glm::vec3(view_matrix[0][1], view_matrix[1][1],
			view_matrix[2][1]) * movement.y;
	position += glm::vec3(view_matrix[0][2], view_matrix[1][2],
			view_matrix[2][2]) * movement.z;
}

void Camera::Rotate(glm::vec3 angles) {
		orientation = glm::quat(angles) * orientation;
		glm::normalize(orientation);
}

void Camera::RotateByMouse(glm::vec2 mouse_deltas) {
	if (!invert_y) {
		mouse_deltas.y = -mouse_deltas.y;
	}
//mouse_deltas.x = -mouse_deltas.x;

	if (mouse_x_roll) {
		Rotate(
				glm::vec3((float) (mouse_deltas.y) / 1000.0f, 0.0f,
						(float) (mouse_deltas.x) / 1000.0f));
	} else {
		Rotate(
				glm::vec3((float) (mouse_deltas.y) / 1000.0f,
						(float) (mouse_deltas.x) / 1000.0f, 0.0f));
	}
}

void Camera::SetOffset(glm::vec3 _offset) {
	offset = _offset;
}

void Camera::SetPosition(glm::vec3 _position) {
	position = _position;
}

void Camera::SetOrientation(glm::quat _orientation) {
	orientation = _orientation;
}

void Camera::SetViewSize(glm::ivec2 _view_size) {
	view_size = _view_size;
}

void Camera::SetNearFar(glm::vec2 _near_far) {
	near_far = _near_far;
}

void Camera::SetFOV(float _fov) {
	fov = _fov;
}

void Camera::Update(void) {
	ComputeViewMatrix();
}

glm::vec3 Camera::GetOffset(void) {
	return offset;
}

glm::vec3 Camera::GetPosition(void) {
	return position;
}

glm::quat Camera::GetOrientation(void) {
	return orientation;
}

glm::ivec2 Camera::GetViewSize(void) {
	return view_size;
}

glm::vec2 Camera::GetNearFar(void) {
	return near_far;
}

float Camera::GetFOV(void) {
	return fov;
}

glm::mat4 Camera::GetViewMatrix(void) {
	return view_matrix;
}

glm::mat4 Camera::GetInverseViewMatrix(void) {
	return inverse_view_matrix;
}

glm::mat4 Camera::GetProjectionMatrix(void) {
	return projection_matrix;
}

glm::mat4 Camera::GetInverseProjectionMatrix(void) {
	return inverse_projection_matrix;
}
