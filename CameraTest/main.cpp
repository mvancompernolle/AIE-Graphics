

#include "crenderutils.h"
#include "window.h"
#include "Input.h"

#include "GLM\glm.hpp"
#include "GLM\ext.hpp"

int main()
{
	Window	window;
	Input input;
	window.init(1280, 720);
	input.init(window);

	glm::mat4 view = glm::lookAt(glm::vec3(0.f, 1.5f, 3.f),  // eye
		glm::vec3(0.f, 1.5f, 0.f),  // center
		glm::vec3(0.f, 1.f, 0.f)); // up

	glm::mat4 proj = glm::perspective(45.f, 16 / 9.f, 1.f, 100.f);
	glm::mat4 modelC, modelS;

	Geometry soulspear = loadOBJ("../res/models/soulspear.obj");
	Shader   shader = loadShader("../res/shaders/phongVert.glsl",
		"../res/shaders/phongFrag.glsl");

	Texture tarray[] = { loadTexture("../res/textures/soulspear_diffuse.tga"),
		loadTexture("../res/textures/soulspear_specular.tga"),
		loadTexture("../res/textures/soulspear_normal.tga") };

	float time = 0;
	while (window.step())
	{
		input.step();

		time += 0.016f;


		modelC = glm::rotate(time, glm::normalize(glm::vec3(0, 1, 0)));

		drawPhong(shader, soulspear, glm::value_ptr(modelC),
			glm::value_ptr(view),
			glm::value_ptr(proj),
			tarray, 3);
	}

	window.term();
	return 0;
}