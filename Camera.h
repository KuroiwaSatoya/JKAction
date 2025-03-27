#pragma once
#include "GameManagerMain.h"
#include "PlayerMain.h"

class Camera : public GameManager {
public:
	Camera();

	void Update() override;

	void Display() override;

	void SetPlayer(Player* _player) { player = _player; }

	float GetCameraX() const { return cameraX; };

private:
	float cameraX, firstCameraX;

	Player* player = nullptr; // player‚Ì•Û
};
