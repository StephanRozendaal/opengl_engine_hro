/*
 * frame.h
 *
 *  Created on: Apr 12, 2012
 *      Author: stephan
 */

#ifndef FRAME_H_
#define FRAME_H_
#include "global_includes.h"
class Frame {
protected:
	glm::vec3 _origin;
	glm::vec3 _forward;
	glm::vec3 _up;
public:
	Frame() : // standard frame bevindt zich bij het snijpunt tussen de x,y,z axissen, en kijkt naar de positieve Z axis.
			_origin(0.0f, 0.0f, 0.0f), _forward(0.0f, 0.0f, -1.0f), _up(0.0f,
					1.0f, 0.0f) {
	}
	void translate_world(const glm::vec3& vec); // translate the frame in world coordinates
	void translate_local(const glm::vec3& vec); // translate the frame in local coordinates
	void move_forward(float delta); // move along the z-axis
	void move_up(float delta); // move along the y-axis
	void move_right(float delta); // move along the x-axis
	glm::mat4 get_matrix(bool rotation_only);
	glm::mat4 get_camera_matrix(bool rotation_only);
	void rotate_local_x(float angle);
	void rotate_local_y(float angle);
	void rotate_local_z(float angle);
	void normalize();
	void rotate_world(float angle, const glm::vec3& point);
	void set_origin(const glm::vec3& point); // set the origin
	void set_forward_vector(const glm::vec3& fvec); // set the forward vector
	void set_up_vector(const glm::vec3 uvec); // set the up vector
	glm::vec3 get_origin();
	glm::vec3 get_forward_vector();
	glm::vec3 get_up_vector();
	glm::vec3 get_x_axis();
	glm::vec3 get_y_axis();
	glm::vec3 get_z_axis();
};

#endif /* FRAME_H_ */
