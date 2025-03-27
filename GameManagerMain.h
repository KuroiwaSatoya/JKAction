#pragma once
#include "PlayerMain.h"

class GameManager {

public:
	GameManager(Player& player);
	void DisplayBackGround();
	void DisplayGameUI(Player& player);
	void SceneManager(Player& player);
	void Update(Player& player);

	float GetCameraX() const { return cameraX; };

	bool GetTitle() const { return title; }

private:
	float cameraX, firstCameraX;
	int font; // フォント
	int titleBgm, gameBgm; // BGM
	int titleImage, backGroundImage1, backGroundImage2, backGroundImage3, backGroundImage4, signBoardImage,
		goalImage, gameOverImage, rightSignBoardImage, hp1Image, hp2Image;
	int width, height, widthBoard, heightBoard, widthRightSignBoard, heightRightSignBoard,
		widthGoal, heightGoal, widthGameOver, heightGameOver;
	float boardScale; // 看板の拡大率
	float backGroundX; // cameraのX座標
	bool title, gameScene; // シーンの選別
	int titleTextWidth, gameEndTextWidth;
	int titleTextCenterX, titleTextCenterY, gameEndTextCenterX, gameEndTextCenterY;
	const char* titleText;
	const char* gameEndText; // テキスト
	int playerHp, maxPlayerHp;
};

