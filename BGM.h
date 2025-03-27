#pragma once
#include "GameManagerMain.h"
#include "Scene.h"

class BGM : public GameManagerMain {
public:
	BGM();

	void Update() override;

	void Display() override;

	void SetScene(Scene* _scene) { scene = _scene; }

private:
	int titleBgm, gameBgm;

	Scene* scene = nullptr; // Scene‚Ì•Û
};