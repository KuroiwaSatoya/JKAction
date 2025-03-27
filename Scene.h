#pragma once
#include "GameManagerMain.h"

class Scene : public GameManagerMain {
public:
	Scene();

	void Update() override;

	void Display() override;

	enum class SceneType {
		TITLE,
		GAME
	};

	SceneType GetType() const { return type; }

private:
	SceneType type;
};
