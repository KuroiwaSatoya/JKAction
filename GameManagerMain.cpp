#include "DxLib.h"
#include "GameManagerMain.h"
#include <cmath>

GameManager::GameManager(Player& player) {
    firstCameraX = player.GetFirstPositionX();
    cameraX = firstCameraX;
    font = CreateFontToHandle("�����ӂ����", 30, 10, DX_FONTTYPE_ANTIALIASING_EDGE);
    titleBgm = LoadSoundMem("Sounds/Title.mp3");
    gameBgm = LoadSoundMem("Sounds/Game.mp3");
    titleImage = LoadGraph("Images/Title.png");
    backGroundImage1 = LoadGraph("Images/BackGround1.png");
    backGroundImage2 = LoadGraph("Images/BackGround2.png");
    backGroundImage3 = LoadGraph("Images/BackGround3.png");
    backGroundImage4 = LoadGraph("Images/BackGround4.png");
    signBoardImage = LoadGraph("Images/signboard.png");
    rightSignBoardImage = LoadGraph("Images/right.png");
    goalImage = LoadGraph("Images/Goal.png");
    gameOverImage = LoadGraph("Images/GameOver.png");
    hp1Image = LoadGraph("Images/HP1.png");
    hp2Image = LoadGraph("Images/HP2.png");
    width = 1920;
    height = 1080;
    GetGraphSize(signBoardImage, &widthBoard, &heightBoard);
    GetGraphSize(rightSignBoardImage, &widthRightSignBoard, &heightRightSignBoard);
    GetGraphSize(goalImage, &widthGoal, &heightGoal);
    GetGraphSize(gameOverImage, &widthGameOver, &heightGameOver);
    boardScale = 2.0f;
    backGroundX = cameraX;
    title = true;
    gameScene = false;
    titleText = "Enter�L�[�ŃQ�[���X�^�[�g";
    gameEndText = "Esc�L�[�������ďI���";
    titleTextWidth = GetDrawStringWidthToHandle(titleText, strlen(titleText), font);
    gameEndTextWidth = GetDrawStringWidthToHandle(gameEndText, strlen(gameEndText), font);
    titleTextCenterX = (width - titleTextWidth) / 2;
    titleTextCenterY = 500;
    gameEndTextCenterX = (width - gameEndTextWidth) / 2;
    gameEndTextCenterY = 800;
    playerHp = player.GetHitPoint();
    maxPlayerHp = playerHp;
    PlaySoundMem(titleBgm, DX_PLAYTYPE_LOOP);
}

void GameManager::DisplayBackGround() {
    if (title) {
        DrawGraphF(0, 0, titleImage, FALSE);
        DrawStringFToHandle(titleTextCenterX, titleTextCenterY, titleText, GetColor(255, 255, 255), font, GetColor(0, 0, 0));
    }
    else if (gameScene) {
        backGroundX = cameraX;

        // �w�i�̕\���ʒu������ (���[�v�p)
        float loopX = fmod(backGroundX, width); // backGroundX % width * scale��float��

        // ��
        DrawGraphF(0, 0, backGroundImage1, FALSE);

        // �R
        float mountainLoopX = fmod(backGroundX / 2, width);
        if (mountainLoopX < 0) mountainLoopX += width;
        DrawGraphF(-mountainLoopX, 0, backGroundImage2, TRUE);
        DrawGraphF(width - mountainLoopX, 0, backGroundImage2, TRUE);

        // ��
        DrawGraphF(-loopX, 0, backGroundImage3, TRUE);
        DrawGraphF(width - loopX, 0, backGroundImage3, TRUE);

        // �n��
        DrawGraphF(-loopX, 0, backGroundImage4, TRUE);
        DrawGraphF(width - loopX, 0, backGroundImage4, TRUE);

        // �S�[���Ŕ�
        DrawExtendGraphF(10000 - cameraX, 330, 10000 - cameraX + widthBoard * boardScale, 330 + heightBoard * boardScale, signBoardImage, TRUE);

        // �X�^�[�g���
        DrawExtendGraphF(1000 - cameraX, 330, 1000 - cameraX + widthRightSignBoard * boardScale, 330 + heightRightSignBoard * boardScale, rightSignBoardImage, TRUE);
    }
}

void GameManager::DisplayGameUI(Player& player) {

    // Player�̗̑͂�UI
    float hpRate = 0;

    playerHp = player.GetHitPoint();

    if (playerHp >= 0) {
        hpRate = max(0.0f, (float)playerHp / (float)maxPlayerHp);
    }

    // HP�̉��n
    DrawGraphF(0, 0, hp2Image, TRUE);

    // HP�̗΂̂Ƃ���
    DrawRectGraphF(70, 0, // �O���t�B�b�N��`�悷����W
        70, 0, // �`�悷��O���t�B�b�N��̕`�悵������`�̍�����W
        (width - 998) * hpRate, height, // �`�悷��O���t�B�b�N�̃T�C�Y
        hp1Image, TRUE, FALSE);



    // �S�[�������\�L
    if (player.GetIsGoal()) {
        DrawGraphF(0, 0, goalImage, TRUE);
        DrawStringFToHandle(gameEndTextCenterX, gameEndTextCenterY, gameEndText, GetColor(255, 255, 255), font, GetColor(0, 0, 0));
    }

    // �Q�[���I�[�o�[�����\�L
    if (player.GetIsDead()) {
        DrawGraphF(0, 0, gameOverImage, TRUE);
        DrawStringFToHandle(gameEndTextCenterX, gameEndTextCenterY, gameEndText, GetColor(255, 255, 255), font, GetColor(0, 0, 0));
    }
}

void GameManager::SceneManager(Player& player) {
    if (title) {
        if (CheckHitKey(KEY_INPUT_RETURN)) {
            if (CheckSoundMem(titleBgm) == FALSE) {
                StopSoundMem(gameBgm);
                PlaySoundMem(titleBgm, DX_PLAYTYPE_LOOP);
            }
            title = false;
            gameScene = true;
        }
    }
    else if (gameScene) {
        if (CheckSoundMem(gameBgm) == FALSE) {
            StopSoundMem(titleBgm);
            PlaySoundMem(gameBgm, DX_PLAYTYPE_LOOP);
        }
        if (player.GetIsGoal()) {

        }
    }
}

void GameManager::Update(Player& player) {
    cameraX = player.GetX() - firstCameraX;
}