/*
 * frame.cpp
 *
 *  Created on: Apr 12, 2012
 *      Author: stephan
 */
#include "frame.h"

void Frame::translate_world(const glm::vec3& vec) {
	_origin.x += vec.x;
	_origin.y += vec.y;
	_origin.z += vec.z;
}

void Frame::translate_local(const glm::vec3& vec) {
	move_forward(vec.z);
	move_up(vec.y);
	move_right(vec.x);
}

void Frame::move_forward(float delta) {
	_origin.x += _forward.x * delta;
	_origin.y += _forward.y * delta;
	_origin.z += _forward.z * delta;
}

void Frame::move_up(float delta) {
	_origin.x += _up.x * delta;
	_origin.y += _up.y * delta;
	_origin.z += _up.z * delta;
}

glm::mat4 Frame::get_matrix(bool rotation_only = false) {
	glm::mat4 matrix;
	glm::vec3 xAxis = glm::cross(_up, _forward);
	matrix[0] = glm::vec4(xAxis, 0.0f);
	matrix[1] = glm::vec4(_up, 0.0f);
	matrix[2] = glm::vec4(_forward, 0.0f);
	if (rotation_only)
		matrix[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	else
		matrix[3] = glm::vec4(_origin, 1.0f);
	return matrix;
}

glm::mat4 Frame::get_camera_matrix(bool rotation_only = false) {
	glm::mat4 matrix;
	glm::vec3 x, z;
	z.x = -_forward.x;
	z.y = -_forward.y;
	z.z = -_forward.z;
	x = glm::cross(_up, z);
	matrix[0] = glm::vec4(x, 0.0f);
	matrix[1] = glm::vec4(_up, 0.0f);
	matrix[2] = glm::vec4(z, 0.0f);
	matrix[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::transpose(matrix);
	if (rotation_only)
		return matrix;
	glm::mat4 trans;
	glm::translate(trans, glm::vec3(-_origin.x, -_origin.y, -_origin.z));
	matrix *= trans;
	return matrix;
}

void Frame::rotate_local_y(float angle) {
	glm::rotateY(_forward, angle);
}

void Frame::rotate_local_z(float angle) {
	glm::rotateZ(_up, angle);
}

void Frame::rotate_local_x(float angle) {
	glm::rotateX(_forward, angle);
}

void Frame::normalize() {
	glm::vec3 cross = glm::cross(_up, _forward);
	_forward = glm::cross(cross, _up);
	glm::normalize(_up);
	glm::normalize(_forward);
}

void Frame::rotate_world(float angle, const glm::vec3& point) {
	glm::mat4 rotmatrix = glm::orientation(point, _up);
	glm::vec3 newvec;
	newvec.x = rotmatrix[0][0] * _up.x + rotmatrix[1][0] * _up.y
			+ rotmatrix[2][0] * _up.z;
}
void Frame::move_right(float delta) {
	glm::vec3 cross = glm::cross(_up, _forward);
	_origin.x += cross.x * delta;
	_origin.y += cross.y * delta;
	_origin.z += cross.z * delta;
}
void Frame::set_origin(const glm::vec3& point) {
	_origin = point;
}

void Frame::set_forward_vector(const glm::vec3& fvec) {
	_forward = fvec;
}

void Frame::set_up_vector(const glm::vec3 uvec) {
	_up = uvec;
}

glm::vec3 Frame::get_origin() {
	return _origin;
}

glm::vec3 Frame::get_forward_vector() {
	return _forward;
}

glm::vec3 Frame::get_up_vector() {
	return _up;
}

glm::vec3 Frame::get_x_axis() {
	return _forward;
}
glm::vec3 Frame::get_y_axis() {
	return _up;
}
glm::vec3 Frame::get_z_axis() {
	return glm::cross(_up, _forward);
}

