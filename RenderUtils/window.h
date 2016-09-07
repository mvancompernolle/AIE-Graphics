#pragma once

class Window {
private:
	friend class Input;

	int width, height;
	char title[64];
	struct GLFWwindow* winHandle = nullptr;
	bool isInitialized = false;

public:
	bool init(int a_width = 800, int a_height = 600, char* a_title = "Window");
	bool step();
	bool term();
};