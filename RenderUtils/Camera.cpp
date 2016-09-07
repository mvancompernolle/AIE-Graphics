#include "Camera.h"
#include "Timer.h"
#include "input.h"

void FlyCamera::update(const Input & input, const Time & time)
{
	yaw -= input.getMouseAxisHorizontal() / 200.0f;
	pitch -= input.getMouseAxisVertical() / 200.0f;
	pitch = glm::clamp<float>(pitch, -glm::pi<float>() / 2.0f + 0.0001f, glm::pi<float>() / 2.0f - 0.0001f);
	printf("pitch: %f offset: %f\n", pitch, input.getMouseAxisHorizontal());

	glm::mat4& view = transform;
	view = glm::rotate(yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	view = glm::rotate(pitch, glm::vec3(view[0])) * view;
	view = glm::rotate(roll, glm::vec3(view[2])) * view;

	view = glm::eulerAngleYXZ(yaw, pitch, roll);
	view = glm::translate(-position) * view;

	glm::vec3 moveDir = glm::vec3(0.0f, 0.0f, 0.0f);
	if (input.getKeyState('W') == Input::DOWN) moveDir += glm::vec3(view[2]);
	if (input.getKeyState('S') == Input::DOWN) moveDir -= glm::vec3(view[2]);
	if (input.getKeyState('A') == Input::DOWN) moveDir += glm::vec3(view[0]);
	if (input.getKeyState('D') == Input::DOWN) moveDir -= glm::vec3(view[0]);
	if (input.getKeyState('E') == Input::DOWN) moveDir -= glm::vec3(view[1]);
	if (input.getKeyState('Q') == Input::DOWN) moveDir += glm::vec3(view[1]);

	if (glm::length(moveDir) >= 0.7f) {
		moveDir = glm::normalize(moveDir);
		position += moveDir * time.getDeltaTime() * speed;
	}
}

void FlyCamera::lookAt(const glm::vec3 & target)
{
	direction = normalize(target - position);
}
