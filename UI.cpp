#include "UI.h"
#include "DxLib.h"
#include <cmath>

UI::UI(Player& player) {

    // �g���Ă���t�H���g
    font = CreateFontToHandle("�����ӂ����", 30, 10, DX_FONTTYPE_ANTIALIASING_EDGE);

    // Player��hp�̕\���̉摜
    hp1Image = LoadGraph("Images/HP1.png");
    hp2Image = LoadGraph("Images/HP2.png");

    // �S�[���A�Q�[���I�[�o�[��UI
    goalImage = LoadGraph("Images/Goal.png");
    gameOverImage = LoadGraph("Images/GameOver.png");

    titleText = "Enter�L�[�ŃQ�[���X�^�[�g";
    gameEndText = "Esc�L�[�������ďI���";

    titleTextWidth = GetDrawStringWidthToHandle(titleText, strlen(titleText), font);
    gameEndTextWidth = GetDrawStringWidthToHandle(gameEndText, strlen(gameEndText), font);

    // �e�e�L�X�g�̒��S�_
    titleTextCenterX = (width - titleTextWidth) / 2;
    titleTextCenterY = 500;
    gameEndTextCenterX = (width - gameEndTextWidth) / 2;
    gameEndTextCenterY = 800;

    // ��ʂ̏c�A���̃s�N�Z����
    width = 1920;
    height = 1080;

    // Player��hp�֘A
    playerHp = player.GetHitPoint();
    maxPlayerHp = playerHp;

}

void UI::Update() {

}

void UI::Display() {

    // Player�̗̑͂�UI
    float hpRate = 0;

    playerHp = player->GetHitPoint();

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
    if (player->GetIsGoal()) {
        DrawGraphF(0, 0, goalImage, TRUE);
        DrawStringFToHandle(gameEndTextCenterX, gameEndTextCenterY, gameEndText, GetColor(255, 255, 255), font, GetColor(0, 0, 0));
    }

    // �Q�[���I�[�o�[�����\�L
    if (player->GetIsDead()) {
        DrawGraphF(0, 0, gameOverImage, TRUE);
        DrawStringFToHandle(gameEndTextCenterX, gameEndTextCenterY, gameEndText, GetColor(255, 255, 255), font, GetColor(0, 0, 0));
    }
}