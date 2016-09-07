#pragma once

class Time {
private:
	float currentTime;
	float previousTime;
	float deltaTime;

public:
	bool init();
	bool step();
	bool term();

	float getDeltaTime() const;
	float getTotalTime() const;
	float getRealTime() const;
};