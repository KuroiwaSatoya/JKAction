#pragma once
#include "BackGround.h"
#include "BGM.h"
#include "Camera.h"
#include "Scene.h"
#include "UI.h"

class GameManager {

public:

	// 仮想関数(純粋仮想関数の方が良かった？)
	virtual void Update() {}
	virtual void Display() {}

private:
	
};

