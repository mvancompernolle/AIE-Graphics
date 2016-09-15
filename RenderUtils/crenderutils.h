#pragma once
#include "globjects.h"

Geometry makeGeometry(const struct Vertex* verts, size_t vsize, const unsigned int *tris, size_t tsize);
void freeGeometry(Geometry& geo);

Shader makeShader(const char* vsource, const char* fsource);
Shader loadShader(const char* vpath, const char* fpath);
void freeShader(Shader& shader);

Texture makeTexture(unsigned width, unsigned height, unsigned format, const unsigned char *pixels);
Texture makeTextureF(unsigned square, const float *pixels);
Texture loadTexture(const char *path);
void freeTexture(Texture& texture);

Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned numColors);
void freeFramebuffer(Framebuffer& fbo);
void clearFramebuffer(const Framebuffer& fbo);

Geometry loadOBJ(const char* path);
void draw(const Shader& shader, const Geometry& geo);
void draw(const Shader& shader, const Geometry& geo, float time);
void draw(const Shader& shader, const Geometry& geo, const float M[16], const float V[16], const float P[16], float time);
void draw(const Shader& shader, const Geometry& geo, const Texture& tex, const float M[16], const float V[16], const float P[16], float time);
void drawPhong(const Shader &s, const Geometry &g,
	const float M[16], const float V[16], const float P[16]);

void drawPhong(const Shader &s, const Geometry &g,
	const float M[16], const float V[16], const float P[16],
	const Texture *T, unsigned t_count);

void drawFB(const Shader &s, const Geometry &g, const Framebuffer& fbo,
	const float M[16], const float V[16], const float P[16],
	const Texture *T, unsigned t_count);