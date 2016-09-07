#include "GLFW/glfw3.h"
#include "Timer.h"

bool Time::init()
{
	glfwSetTime(0.0f);
	previousTime = 0.0f;
	currentTime = 0.0f;
	deltaTime = 0.0f;
	return true;
}

bool Time::step()
{
	previousTime = currentTime;
	currentTime = getRealTime();
	deltaTime = currentTime - previousTime;
	return false;
}

bool Time::term()
{
	return true;
}

float Time::getDeltaTime() const
{
	return deltaTime;
}

float Time::getTotalTime() const
{
	return currentTime;
}

float Time::getRealTime() const
{
	return glfwGetTime();
}
