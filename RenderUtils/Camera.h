#pragma once

#define GLM_SWIZZLE
#include "GLM/glm.hpp"
#include "GLM/ext.hpp"

class FlyCamera {
public:
	glm::vec3 position;
	glm::vec3 direction;
	glm::mat4 transform;

	float pitch, yaw, roll;
	float aspect, fov, near, far;
	float speed;

public:
	FlyCamera(float a_aspect = 16.0f / 9.0f, float a_fov = 45.0f, float a_near = 1.0f, float a_far = 100.0f) :
		aspect(a_aspect), fov(a_fov), near(a_near), far(a_far), position{}, direction(0.0f, 0.0f, 1.0f), speed(20.0f), pitch(0.0f), yaw(0.0f), roll(0.0f) {}

	void update(const class Input& input, const class Time& time);
	void lookAt(const glm::vec3& target);

	void jumpTo(const glm::vec3& location) {
		position = location;
	}

	glm::mat4 getView() const {
		return glm::inverse(transform);
	}

	glm::mat4 getProjection() const {
		return glm::perspective(fov, aspect, near, far);
	}
};