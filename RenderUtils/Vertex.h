#pragma once

struct Vertex {
	float position[4];
	float color[4];

	enum
	{
		POSITION = 0,
		COLOR = 16
	};
};