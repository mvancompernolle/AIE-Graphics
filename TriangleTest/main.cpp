#include "window.h"

// this is in the dev branch

int main() {
	Window window;
	window.init();

	while (window.step()) {

	}

	window.term();

	return 0;
}