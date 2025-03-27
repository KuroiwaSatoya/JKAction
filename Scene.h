#pragma once
#include "GameManagerMain.h"

class Scene : public GameManager {
public:
	Scene();
	void Update() override ;

	enum class SceneType {
		TITLE,
		GAME
	};

	SceneType GetType() const { return type; }

private:
	SceneType type;
};
