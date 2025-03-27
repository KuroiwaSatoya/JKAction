#pragma once
#include "GameManagerMain.h"
#include "PlayerMain.h"

class UI : public GameManagerMain {
public:
	UI(Player& player);

	void Update() override ;

	void Display() override ;

	void SetPlayer(Player* _player) { player = _player; }

private:

	int font;

	int goalImage, gameOverImage;

	const char* titleText;
	const char* gameEndText;

	int titleTextWidth, gameEndTextWidth;

	int hp1Image, hp2Image;

	int titleTextCenterX, titleTextCenterY, gameEndTextCenterX, gameEndTextCenterY;

	int width, height;

	int playerHp, maxPlayerHp;

	Player* player = nullptr;
};