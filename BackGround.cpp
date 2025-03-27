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

    // �w�i�̕\���ʒu������ (���[�v�p)
    loopX = fmod(backGroundX, widthBackGround); // backGroundX % widthBackGround��float��

    // �R��1/2�̑��x�ŗ���邽�߁A���̔w�i�Ƃ͕ʂɃ��[�v������ݒ�
    mountainLoopX = fmod(backGroundX / SLOW_DOWM_MOUNTAIN, widthBackGround);
    if (mountainLoopX < SCREEN_ORIGIN_X) mountainLoopX += widthBackGround;

}

void BackGround::Display(Camera& camera, bool title, bool gameScene) {

    // �^�C�g����ʂȂ�
    if (title) {
        // �^�C�g����ʂ̕`��
        DrawGraphF(
            SCREEN_ORIGIN_X,    // �`�悷��摜�̍����X���W
            SCREEN_ORIGIN_Y,    // �`�悷��摜�̍����Y���W
            imageTitle,         // �`�悷��摜�̃n���h��
            FALSE);             // ���߂��邩�ǂ���
    }
    //�Q�[����ʂȂ�
    else if (gameScene) {

        // ��̕`��
        DrawGraphF(SCREEN_ORIGIN_X, SCREEN_ORIGIN_Y, imageBackGroundSky, FALSE);

        // �R�̕`��
        DrawGraphF(-mountainLoopX, SCREEN_ORIGIN_Y, imageBackGroundMountain, TRUE);
        // ���[�v�����邽�߂�2���`�悵�Ă���
        DrawGraphF(widthBackGround - mountainLoopX, SCREEN_ORIGIN_Y, imageBackGroundMountain, TRUE);

        // �؂̕`��
        DrawGraphF(-loopX, SCREEN_ORIGIN_Y, imageBackGroundTree, TRUE);
        // ���[�v�p
        DrawGraphF(widthBackGround - loopX, SCREEN_ORIGIN_Y, imageBackGroundTree, TRUE);

        // �n�ʂ̕`��
        DrawGraphF(-loopX, 0, imageBackGroundGround, TRUE);
        // ���[�v�p
        DrawGraphF(widthBackGround - loopX, SCREEN_ORIGIN_Y, imageBackGroundGround, TRUE);

        // �S�[���Ŕ�
        DrawExtendGraphF(GOAL_SIGN_BOARD_X - backGroundX, GOAL_SIGN_BOARD_Y,
            GOAL_SIGN_BOARD_X - backGroundX + widthGoalSignBoard * signBoardScale,
            GOAL_SIGN_BOARD_Y + heightGoalSignBoard * signBoardScale,
            imageGoalSignBoard, TRUE);

        // �X�^�[�g���Ŕ�
        DrawExtendGraphF(START_RIGHT_SIGN_BOARD_X - backGroundX, START_RIGHT_SIGN_BOARD_Y,
            START_RIGHT_SIGN_BOARD_X - backGroundX + widthRightSignBoard * signBoardScale,
            START_RIGHT_SIGN_BOARD_Y + heightRightSignBoard * signBoardScale,
            imageStartRightSignBoard, TRUE);
    }
}