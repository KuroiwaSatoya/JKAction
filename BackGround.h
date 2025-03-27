#pragma once
#include "GameManagerMain.h"
#include "Camera.h"
#include "Scene.h"

class BackGround : public GameManagerMain {
public:
	BackGround();

	// 背景の制御
	void Update() override ;

	// 背景の描画
	void Display() override ;

	void SetCamera(Camera* _camera) { camera = _camera; }

	void SetScene(Scene* _scene) { scene = _scene; }

private:

	// 画像
	int imageTitle,					// タイトル画面の画像
		imageBackGroundSky,			// 背景の空の画像
		imageBackGroundMountain,	// 背景の山の画像
		imageBackGroundTree,		// 背景の木の画像
		imageBackGroundGround,		// 背景の地面の画像
		imageGoalSignBoard,			// ゴールの看板
		imageStartRightSignBoard;	// スタート地点の右矢印看板

	// 画像の縦横
	int widthBackGround,			// 背景の画像の幅
		heightBackGround,			// 背景の画像の高さ
		widthGoalSignBoard,			// ゴールの看板の幅
		heightGoalSignBoard,		// ゴールの看板の高さ
		widthRightSignBoard,		// スタートの看板の幅
		heightRightSignBoard;		// スタートの看板の高さ

	// 拡大率
	float signBoardScale;			// 看板の拡大率

	// 背景の移動
	float backGroundX,				// 背景の移動量
		loopX,						// ループ用
		mountainLoopX;				// 山は1/2の速度でループするため山用のループ変数を用意

	Camera* camera = nullptr;		// Cameraを保持
	Scene* scene = nullptr;			// Sceneを保持

};