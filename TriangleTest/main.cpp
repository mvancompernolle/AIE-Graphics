
#include "crenderutils.h"

#include "GLM\ext.hpp"

void main()
{
	Window context;
	context.init(1280, 720);

	Framebuffer screen = { 0,1280,720 };
	Framebuffer frame = makeFramebuffer(1280, 720, 4);

	Geometry quad = makeGeometry(quad_verts, 4,
		quad_tris, 6);

	Shader gpass = loadShader("../res/shaders/gpass.vert",
		"../res/shaders/gpass.frag");

	Shader post = loadShader("../res/shaders/quad.vert",
		"../res/shaders/quad.frag");

	Geometry spear = loadOBJ("../res/models/soulspear.obj");

	Texture spear_normal = loadTexture("../res/textures/soulspear_normal.tga");
	Texture spear_diffuse = loadTexture("../res/textures/soulspear_diffuse.tga");
	Texture spear_specular = loadTexture("../res/textures/soulspear_specular.tga");

	glm::mat4 model, view, proj;

	model = glm::translate(glm::vec3(0, -1, 0));
	view = glm::lookAt(glm::vec3(0, 0, 4), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	proj = glm::perspective(45.f, 1280.f / 720, 1.f, 100.f);

	float time = 0;
	while (context.step())
	{
		time += 0.016f;
		clearFramebuffer(frame);

		tdraw(gpass, spear, frame, model, view, proj,
			spear_diffuse, spear_normal, spear_specular);

		// 0-4
		// 0: -1,-1
		// 1:  1,-1
		// 2:  1,1
		// 3: -1,1
		for (int i = 0; i < 4; ++i)
		{
			glm::mat4 mod =
				glm::translate(glm::vec3(-.75f + .5*i, 0.75f, 0)) *
				glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
			tdraw(post, quad, screen, frame.colors[i], mod);
		}

		glm::mat4 mod =
			glm::translate(glm::vec3(-.75f, 0.25f, 0)) *
			glm::scale(glm::vec3(0.25f, 0.25f, 1.f));
		tdraw(post, quad, screen, frame.depth, mod);
	}

	context.term();
}