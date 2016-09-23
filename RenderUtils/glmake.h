#pragma once
#include "globjs.h"

Geometry makeGeometry(const struct Vertex* verts, size_t vsize, const unsigned int *tris, size_t tsize);
void freeGeometry(Geometry& geo);

Shader makeShader(const char* vsource, const char* fsource, bool depth = true, bool add = false, bool face = true);
void freeShader(Shader& shader);

Texture makeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char *pixels);
Texture makeTextureF(unsigned square, const float *pixels);
void freeTexture(Texture& texture);

Framebuffer makeFramebuffer(unsigned width, unsigned height, unsigned numColors);
void freeFramebuffer(Framebuffer& fbo);
