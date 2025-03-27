#include "UI.h"
#include "DxLib.h"
#include <cmath>

UI::UI(Player& player) {

    // 使っているフォント
    font = CreateFontToHandle("けいふぉんと", 30, 10, DX_FONTTYPE_ANTIALIASING_EDGE);

    // Playerのhpの表示の画像
    hp1Image = LoadGraph("Images/HP1.png");
    hp2Image = LoadGraph("Images/HP2.png");

    // ゴール、ゲームオーバーのUI
    goalImage = LoadGraph("Images/Goal.png");
    gameOverImage = LoadGraph("Images/GameOver.png");

    titleText = "Enterキーでゲームスタート";
    gameEndText = "Escキーを押して終わる";

    titleTextWidth = GetDrawStringWidthToHandle(titleText, strlen(titleText), font);
    gameEndTextWidth = GetDrawStringWidthToHandle(gameEndText, strlen(gameEndText), font);

    // 各テキストの中心点
    titleTextCenterX = (width - titleTextWidth) / 2;
    titleTextCenterY = 500;
    gameEndTextCenterX = (width - gameEndTextWidth) / 2;
    gameEndTextCenterY = 800;

    // 画面の縦、横のピクセル数
    width = 1920;
    height = 1080;

    // Playerのhp関連
    playerHp = player.GetHitPoint();
    maxPlayerHp = playerHp;

}

void UI::Update() {

}

void UI::Display() {

    // Playerの体力のUI
    float hpRate = 0;

    playerHp = player->GetHitPoint();

    if (playerHp >= 0) {
        hpRate = max(0.0f, (float)playerHp / (float)maxPlayerHp);
    }

    // HPの下地
    DrawGraphF(0, 0, hp2Image, TRUE);

    // HPの緑のところ
    DrawRectGraphF(70, 0, // グラフィックを描画する座標
        70, 0, // 描画するグラフィック上の描画したい矩形の左上座標
        (width - 998) * hpRate, height, // 描画するグラフィックのサイズ
        hp1Image, TRUE, FALSE);



    // ゴール文字表記
    if (player->GetIsGoal()) {
        DrawGraphF(0, 0, goalImage, TRUE);
        DrawStringFToHandle(gameEndTextCenterX, gameEndTextCenterY, gameEndText, GetColor(255, 255, 255), font, GetColor(0, 0, 0));
    }

    // ゲームオーバー文字表記
    if (player->GetIsDead()) {
        DrawGraphF(0, 0, gameOverImage, TRUE);
        DrawStringFToHandle(gameEndTextCenterX, gameEndTextCenterY, gameEndText, GetColor(255, 255, 255), font, GetColor(0, 0, 0));
    }
}