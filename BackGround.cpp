#include "BackGround.h"
#include "DxLib.h"
#include <cmath>

const float SLOW_DOWM_MOUNTAIN = 2.0f;
const float GOAL_SIGN_BOARD_X = 10000.0f;
const float GOAL_SIGN_BOARD_Y = 330.0f;
const float START_RIGHT_SIGN_BOARD_X = 1000.0f;
const float START_RIGHT_SIGN_BOARD_Y = 330.0f;
const float SCREEN_ORIGIN_X = 0.0f;
const float SCREEN_ORIGIN_Y = 0.0f;


BackGround::BackGround() {
	imageTitle = LoadGraph("Images/Title.png");
	imageBackGroundSky = LoadGraph("Images/BackGround1.png");
	imageBackGroundMountain = LoadGraph("Images/BackGround2.png");
	imageBackGroundTree = LoadGraph("Images/BackGround3.png");
	imageBackGroundGround = LoadGraph("Images/BackGround4.png");
	imageGoalSignBoard = LoadGraph("Images/signboard.png");
	imageStartRightSignBoard = LoadGraph("Images/right.png");

	widthBackGround = 1920;
	heightBackGround = 1080;
	GetGraphSize(imageGoalSignBoard, &widthGoalSignBoard, &heightGoalSignBoard);
	GetGraphSize(imageStartRightSignBoard, &widthRightSignBoard, &heightRightSignBoard);

    signBoardScale = 2.0f;

    backGroundX = 0.0f;
    loopX = 0.0f;
    mountainLoopX = 0.0f;
}

void BackGround::Update(Camera& camera) {

    backGroundX = camera.GetCameraX();

    // 背景の表示位置を決定 (ループ用)
    loopX = fmod(backGroundX, widthBackGround); // backGroundX % widthBackGround→floatに

    // 山は1/2の速度で流れるため、他の背景とは別にループ周期を設定
    mountainLoopX = fmod(backGroundX / SLOW_DOWM_MOUNTAIN, widthBackGround);
    if (mountainLoopX < SCREEN_ORIGIN_X) mountainLoopX += widthBackGround;

}

void BackGround::Display(Camera& camera, bool title, bool gameScene) {

    // タイトル画面なら
    if (title) {
        // タイトル画面の描画
        DrawGraphF(
            SCREEN_ORIGIN_X,    // 描画する画像の左上のX座標
            SCREEN_ORIGIN_Y,    // 描画する画像の左上のY座標
            imageTitle,         // 描画する画像のハンドル
            FALSE);             // 透過するかどうか
    }
    //ゲーム画面なら
    else if (gameScene) {

        // 空の描画
        DrawGraphF(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, imageBackGroundSky, FALSE);

        // 山の描画
        DrawGraphF(-mountainLoopX, SCREEN_ORIGIN_Y, imageBackGroundMountain, TRUE);
        // ループさせるために2枚描画している
        DrawGraphF(widthBackGround - mountainLoopX, SCREEN_ORIGIN_Y, imageBackGroundMountain, TRUE);

        // 木の描画
        DrawGraphF(-loopX, SCREEN_ORIGIN_Y, imageBackGroundTree, TRUE);
        // ループ用
        DrawGraphF(widthBackGround - loopX, SCREEN_ORIGIN_Y, imageBackGroundTree, TRUE);

        // 地面の描画
        DrawGraphF(-loopX, 0, imageBackGroundGround, TRUE);
        // ループ用
        DrawGraphF(widthBackGround - loopX, SCREEN_ORIGIN_Y, imageBackGroundGround, TRUE);

        // ゴール看板
        DrawExtendGraphF(GOAL_SIGN_BOARD_X - backGroundX, GOAL_SIGN_BOARD_Y,
            GOAL_SIGN_BOARD_X - backGroundX + widthGoalSignBoard * signBoardScale,
            GOAL_SIGN_BOARD_Y + heightGoalSignBoard * signBoardScale,
            imageGoalSignBoard, TRUE);

        // スタート矢印看板
        DrawExtendGraphF(START_RIGHT_SIGN_BOARD_X - backGroundX, START_RIGHT_SIGN_BOARD_Y,
            START_RIGHT_SIGN_BOARD_X - backGroundX + widthRightSignBoard * signBoardScale,
            START_RIGHT_SIGN_BOARD_Y + heightRightSignBoard * signBoardScale,
            imageStartRightSignBoard, TRUE);
    }
}