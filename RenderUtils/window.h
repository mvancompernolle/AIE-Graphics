#pragma once

class Window {
private:
	int width, height;
	char title[64];
	class GLFWwindow* winHandle = nullptr;
	bool isInitialized = false;

public:
	bool init(int a_width = 800, int a_height = 600, char* a_title = "Window");
	bool step();
	bool term();
};