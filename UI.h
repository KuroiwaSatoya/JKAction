#pragma once
#include "PlayerMain.h"

class UI {
public:
	UI(Player& player);
	void DisplayGameUI(Player& player);

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
};
#pragma once
