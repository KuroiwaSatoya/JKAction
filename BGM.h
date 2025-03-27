#pragma once
#include "Scene.h"

class BGM : public GameManager {
public:
	BGM();

	void Update() override;

	void Display() override;

	//void Update(Scene& scene);

private:
	int titleBgm, gameBgm;
};