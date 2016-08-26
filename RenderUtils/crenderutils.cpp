#include "gldecs.h"

#include "Vertex.h"
#include "crenderutils.h"

#include <cstdio>

Geometry makeGeometry(const Vertex* verts, size_t vsize, const unsigned int* tris, size_t tsize)
{
	Geometry geo;
	geo.size = tsize;

	// define the variables
	glGenBuffers(1, &geo.vbo);
	glGenBuffers(1, &geo.ibo);
	glGenVertexArrays(1, &geo.vao);
	// scope the variables
	glBindVertexArray(geo.vao);
	glBindBuffer(GL_ARRAY_BUFFER, geo.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geo.ibo);
	// init the variables
	glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(Vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris, GL_STATIC_DRAW);

	// attributes
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::COLOR);

	// unscope the variables
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return geo;
}

void freeGeometry(Geometry& geo) {
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);
	geo = { 0, 0, 0, 0 };
}

Shader makeShader(const char * vsource, const char * fsource)
{
	Shader shader;
	shader.handle = glCreateProgram();
	// creater shader variables
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);
	// init variables
	glShaderSource(vs, 1, &vsource, NULL);
	glShaderSource(fs, 1, &fsource, NULL);
	// compile shaders
	glCompileShader(vs);
	glCompileShader(fs);
	// link shaders into a single program
	glAttachShader(shader.handle, vs);
	glAttachShader(shader.handle, fs);
	glLinkProgram(shader.handle);
	// no longer need these, functionality is in the program
	glDeleteShader(vs);
	glDeleteShader(fs);

	return shader;
}

void freeShader(Shader& shader)
{
	glDeleteProgram(shader.handle);
	shader.handle = 0;
}

void draw(const Shader& shader, const Geometry& geo)
{
	glUseProgram(shader.handle);

	// binding the VAO also binds the IBO and VBO
	glBindVertexArray(geo.vao);
	// Draw elements will draw the vertices that are currently bound usign an array of indices
	// IF AN IBO IS BOUND, we don't kneed to provide any indices
	glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, 0);
}
