#pragma once
#include "globjects.h"

Geometry makeGeometry(const struct Vertex* verts, size_t vsize, const unsigned int *tris, size_t tsize);
void freeGeometry(Geometry& geo);

Shader makeShader(const char* vsource, const char* fsource);
Shader loadShader(const char* vpath, const char* fpath);
void freeShader(Shader& shader);

Geometry loadOBJ(const char* path);
void draw(const Shader& shader, const Geometry& geo);
void draw(const Shader& shader, const Geometry& geo, float time);
void draw(const Shader& shader, const Geometry& geo, const float M[16], const float V[16], const float P[16], float time);