#pragma once
#include "Scene.h"

class BGM {
public:
	BGM();
	void Update(Scene& scene);

private:
	int titleBgm, gameBgm;
};