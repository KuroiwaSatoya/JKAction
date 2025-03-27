#pragma once
#include "PlayerMain.h"

class Camera {
public:
	Camera(Player& player);

	void Update(Player& player);

	float GetCameraX() const { return cameraX; };

private:
	float cameraX, firstCameraX;
};
