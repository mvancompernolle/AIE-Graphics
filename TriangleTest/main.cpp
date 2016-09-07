#include "crenderutils.h"
#include "window.h"
#include "Gallery.h"

int main()
{ 
	Window window;
	Gallery gallery;

	window.init(960, 960);
	gallery.init();

	Vertex verts[] = { { 1,1,0,1 },{ 1,-1,0,1 },{ -1,-1,0,1 },{ -1,1,0,1 } };

	unsigned tris[] = { 0,1,2, 2,3,0 };
	gallery.loadShader("SIMPLE", "../res/shaders/simpleVert.txt", "../res/shaders/simpleFrag.txt");
	gallery.makeObject("quad", verts, 4, tris, 6);
	gallery.loadObjectOBJ("sphere", "../res/models/sphere.obj");

	float time = 0.0f;

	while (window.step()) {
		time += 0.0016667f;
		draw(gallery.getShader("SIMPLE"), gallery.getObject("sphere"), time);
	}

	gallery.term();
	window.term();
	return 0;
}