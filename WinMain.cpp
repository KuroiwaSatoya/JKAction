#include <windows.h>
#include "DxLib.h"
#include "PlayerMain.h"
#include "EnemyMain.h"
#include "GameManagerMain.h"
#include <ctime>
#include <cstdlib>

using namespace std;

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int COLOR_DEPTH = 16;
const int FIRST_ENEMY_INDEX = 5;
const int MAX_ENEMY_INDEX = 100;
const int ENEMY_SPAWN_DISTANCE = 500;
const int ENEMY_DOESNT_SPAWN_DISTANCE = 8500;
const int ENEMY_X_MIN = 1920;
const int ENEMY_X_MAX = 2920;
const int ENEMY_Y_MIN = -70;
const int ENEMY_Y_MAX = 430;
const int FIRST_ENEMY_X_MIN = 300;
const int FIRST_ENEMY_X_MAX = 1920;
const int FIRST_ENEMY_Y_MIN = -70;
const int FIRST_ENEMY_Y_MAX = 430;
const int ADDITIONAL_ENEMIES = 5;


// DXライブラリの初期化
bool InitDX() {

	// 画面モードの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_DEPTH);

	// ウィンドウモードの設定
	//ChangeWindowMode(TRUE);

	// 画面比率を変えられるかどうか
	SetWindowSizeChangeEnableFlag(TRUE);

	// DXライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// 描画先を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}

// enemyの初期位置
void InitEnemySpawn(Enemy enemy[], int& enemyIndex) {
	// 敵の初期位置をランダムに設定
	for (int i = 0; i < FIRST_ENEMY_INDEX; i++) {

		// x = 300～1920までランダム
		float enemyX = (rand() % (FIRST_ENEMY_X_MAX - FIRST_ENEMY_X_MIN)) + FIRST_ENEMY_X_MIN;

		// y = -70～430までランダム
		float enemyY = (rand() % (FIRST_ENEMY_Y_MAX - FIRST_ENEMY_Y_MIN)) + FIRST_ENEMY_Y_MIN;

		// 決めた座標をenemyに渡す
		enemy[enemyIndex].SetX(enemyX);
		enemy[enemyIndex].SetY(enemyY);

		// 次の配列へ
		enemyIndex++;
	}
}

// エネミーのスポーン判定
void EnemySpawn(Enemy enemy[], float playerX, float cameraX, float lastSpawnDistance, int& enemyIndex) {

	// 500ピクセル移動する毎に新しくスポーンさせる
	if (playerX - lastSpawnDistance >= ENEMY_SPAWN_DISTANCE) {
		lastSpawnDistance = playerX;  // 最後にスポーンした距離を更新

		// ゴール付近ではスポーンさせない
		if (playerX < ENEMY_DOESNT_SPAWN_DISTANCE) {

			// 新しい敵をランダムにスポーン
			// MAX_ENEMY_INDEXを超えてないか判定
			if (enemyIndex < MAX_ENEMY_INDEX) {

				// エネミーを5体生成
				for (int i = 0; i < ADDITIONAL_ENEMIES; i++) {

					// x = +1920～2920まで(プレイヤーの位置から見て)
					float enemyX = (rand() % (ENEMY_X_MAX - ENEMY_X_MIN)) + ENEMY_X_MIN + cameraX;

					// y = 70～430まで
					float enemyY = (rand() % (ENEMY_Y_MAX - ENEMY_Y_MIN)) + ENEMY_Y_MIN;

					// 設定した座標をenemyに代入
					enemy[enemyIndex].SetX(enemyX);
					enemy[enemyIndex].SetY(enemyY);

					// インデックスを1足す
					enemyIndex++;
				}
			}
		}
	}
}

// 判定
void Collision(Player& player, Enemy enemy[], bool title, int enemyIndex) {

	// ゲームシーンのみ判定を行う
	if (!title) {
		// プレイヤーの判定
		player.Collision();

		// エネミーの判定
		for (int i = 0; i < enemyIndex; i++) {
			enemy[i].Collision(player, enemy, enemyIndex);
		}
	}
}

// 行動とアニメーション
void Update(Player& player, Enemy enemy[], GameManager& gameManager, float deltaTime, int enemyIndex) {

	if (!gameManager.GetTitle()) {
		// プレイヤー
		player.Update(deltaTime);

		// アニメーションを制御
		player.UpdateAnimation(deltaTime);

		// エネミー
		for (int i = 0; i < enemyIndex; i++) {

			enemy[i].Update(player, deltaTime);

			// アニメーションを制御
			enemy[i].UpdateAnimation(deltaTime);

		}

		// カメラを更新
		gameManager.Update(player);
	}

}

// 描画
void Display(Player& player, Enemy enemy[], GameManager& gameManager, int enemyIndex) {

	// 背景から
	gameManager.Display();

	// ゲームシーンなら
	if (!gameManager.GetTitle()) {

		// プレイヤーの座標より上にいるエネミーを先に描画
		for (int i = 0; i < enemyIndex; i++) {
			if (enemy[i].GetY() < player.GetY()) {
				enemy[i].Display(gameManager);
			}
			else {

				// プレイヤーに捕まれている場合も先に描画
				if (enemy[i].GetIsCaught()) {
					enemy[i].Display(gameManager);
				}
			}
		}

		// プレイヤーを描画
		player.Display();

		// プレイヤーの座標より下にいる場合にはプレイヤーより後に描画
		for (int i = 0; i < enemyIndex; i++) {
			if (enemy[i].GetY() >= player.GetY()) {
				if (!enemy[i].GetIsCaught()) {
					enemy[i].Display(gameManager);
				}
			}
		}

		// UIを描画
		gameManager.DisplayGameUI(player);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)(time(NULL)));

	float oldTime = GetNowCount();
	float nowTime = 0;
	float deltaTime = 0; // デルタタイムを管理する↑

	int enemyIndex = 0; // 敵の数

	int lastSpawnDistance = 0; // 最後に敵がスポーンしたプレイヤーの位置

	Player player;
	Enemy enemy[MAX_ENEMY_INDEX];
	GameManager gameManager(player);

	EnemySpawn(enemy, player.GetX(), gameManager.GetCameraX(), lastSpawnDistance, enemyIndex);

	// updateみたいなもの
	while (TRUE) {
		// deltaTimeを作成
		nowTime = GetNowCount();

		// deltaTimeが0にならないようにmaxで制御
		// nowTime, oldTime共に単位がミリ秒のため、1000で割る
		deltaTime = max((nowTime - oldTime) / 1000.0f, 0.01f);

		// 次のフレームのためにoldTimeにnowTimeを代入
		oldTime = nowTime;

		// スクリーンに映ってるものを消す
		ClearDrawScreen();

		// シーンを判定
		gameManager.SceneManager(player);

		// 判定
		Collision(player, enemy, gameManager.GetTitle(), enemyIndex);

		// 行動
		Update(player, enemy, gameManager, deltaTime, enemyIndex);

		// 敵がスポーンするか判定
		EnemySpawn(enemy, player.GetX(), gameManager.GetCameraX(), lastSpawnDistance, enemyIndex);

		// 描画
		Display(player, enemy, gameManager, enemyIndex);

		// ESCキーが押されたらループから抜ける(ゲームを終了)
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// Windows システムからくる情報を処理する
		if (ProcessMessage() == -1) break;

		// 裏画面に描画したものを映す
		ScreenFlip();
	}

	// DXライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了 
	return 0;
}

/* void DisplayGameManager(GameManager& gameManager){ gameManager->Display() }
これを呼び出すと→ DisplayGameManager(&Camera) →仮想関数なのでこれでカメラのDisplayが起動する
(仮想関数でない場合は親クラス(GameManagerのDisplayが起動する))*/