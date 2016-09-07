#include "gldecs.h"
#include "Vertex.h"
#include "crenderutils.h"
#include <cstdio>

Geometry makeGeometry(const Vertex       * verts, size_t vsize,
					  const unsigned int * tris , size_t tsize)
{
	Geometry retval;

	// Define the variables
	glGenBuffers(1, &retval.vbo);	   // Store vertices
	glGenBuffers(1, &retval.ibo);	   // Store indices
	glGenVertexArrays(1, &retval.vao); // Store attribute information

	// Scope the variables
	glBindVertexArray(retval.vao);
	glBindBuffer(GL_ARRAY_BUFFER        , retval.vbo); // scope our vertices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, retval.ibo); // triangle is scoped

	// Initialize the variables
	glBufferData(GL_ARRAY_BUFFER        , vsize * sizeof(Vertex)  , verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tsize * sizeof(unsigned), tris , GL_STATIC_DRAW);

	// Attributes let us tell openGL how the memory is laid out
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// index of the attribute, number of elements, type, normalized?, size of vertex, offset
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::POSITION);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)Vertex::COLOR);

	// unscope the variables
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER		, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	retval.size = tsize;
	return retval;
}

void freeGeometry(Geometry &geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);
	geo = {0,0,0,0};
}

Shader makeShader(const char * vsource, const char * fsource)
{
	Shader retval;
	 // create our variables
	retval.handle = glCreateProgram();
	unsigned vs = glCreateShader(GL_VERTEX_SHADER);
	unsigned fs = glCreateShader(GL_FRAGMENT_SHADER);
	// initialize our variables
	glShaderSource(vs, 1, &vsource, 0);
	glShaderSource(fs, 1, &fsource, 0);
	// compile the shaders
	glCompileShader(vs);
	glCompileShader(fs);
	// link the shaders into a single program
	glAttachShader(retval.handle, vs);
	glAttachShader(retval.handle, fs);
	glLinkProgram(retval.handle);
	// no longer need these! Their functionality has been eaten by the program.
	glDeleteShader(vs);
	glDeleteShader(fs);

	return retval;
}

void freeShader(Shader &shader)
{
	glDeleteProgram(shader.handle);
	shader.handle = 0;
}



// not quite working!
long copyFileToArray(char *dest, size_t dlen, const char *path)
{
	FILE *fp;
	fopen_s(&fp,path, "r");	// open file	
	if (!fp) return 0;

	fseek(fp, 0L, SEEK_END);		// jump to end of file
	long size = ftell(fp);			// determine how many chars we passed
	rewind(fp);						// go back to beginning
		
	long lastIndex =  fread_s(dest, dlen, 1, size, fp);

	dest[lastIndex] = 0;

	fclose(fp);
	return size;
}

Shader loadShader(const char *vpath, const char *fpath)
{
	// not likely to exceed this.
	char vsource[4096];
	char fsource[4096];	

	// if the retval is 0 or > 4096, it's an error.
	copyFileToArray(vsource, 4096, vpath);
	copyFileToArray(fsource, 4096, fpath);

	
	return makeShader(vsource, fsource);
}



#include <fstream>
#include <istream>
#include <string>

std::string stdStyleFileToString(const char *path)
{
	std::ifstream infile{ path };
	std::string file_contents{ std::istreambuf_iterator<char>(infile),
		std::istreambuf_iterator<char>() };
	return file_contents;
}

Shader loadShaderSTDStyle(const char *vpath, const char *fpath)
{
	std::string vs = stdStyleFileToString(vpath);
	std::string fs = stdStyleFileToString(fpath);

	return makeShader(vs.c_str(), fs.c_str());
}


#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "OBJ\tiny_obj_loader.h"
#include <random>

Geometry loadOBJ(const char *path)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	Vertex   *verts = new Vertex[attrib.vertices.size()/3];
	unsigned * tris = new unsigned[shapes[0].mesh.indices.size()];

	for (int i = 0; i < attrib.vertices.size()/3; ++i)
	{
		verts[i] = { attrib.vertices[i*3],
					 attrib.vertices[i*3+1],
					 attrib.vertices[i*3+2], 1};

		verts[i].color[0] = rand() * 1.0f / RAND_MAX;
		verts[i].color[1] = rand() * 1.0f / RAND_MAX;
		verts[i].color[2] = rand() * 1.0f / RAND_MAX;
		verts[i].color[3] = 1;
	}

	for (int i = 0; i < shapes[0].mesh.indices.size(); ++i)
		tris[i] = shapes[0].mesh.indices[i].vertex_index;

	Geometry retval = makeGeometry(verts, attrib.vertices.size() / 3,
								    tris, shapes[0].mesh.indices.size());

	delete[] verts;
	delete[] tris;
	// then we can call makeGeometry as per normal.
	return retval;
}


void draw(const Shader &shader, const Geometry &geometry)
{
	glUseProgram(shader.handle);

	// binding the VAO also binds the IBO (tri) and VBO (verts)
	glBindVertexArray(geometry.vao);

	// Draw elements will draw the vertices that are currently bound
	// using an array of indices.
	// IF AN IBO IS BOUND, we don't need to provide any indices.
	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}

void draw(const Shader &shader, const Geometry &geometry, float time)
{
	glUseProgram(shader.handle);
	glBindVertexArray(geometry.vao);

	int loc = glGetUniformLocation(shader.handle, "time");
	glUniform1f(loc, time);

	glDrawElements(GL_TRIANGLES, geometry.size, GL_UNSIGNED_INT, 0);
}


void draw(const Shader &s, const Geometry &g,
					const float M[16], const float V[16], const float P[16], float time)
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(s.handle);
	glBindVertexArray(g.vao);
	

	glUniformMatrix4fv(0, 1, GL_FALSE, P);
	glUniformMatrix4fv(1, 1, GL_FALSE, V);
	glUniformMatrix4fv(2, 1, GL_FALSE, M);

	glUniform1f(3, time);

	glDrawElements(GL_TRIANGLES, g.size, GL_UNSIGNED_INT, 0);
}