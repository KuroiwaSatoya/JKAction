#pragma once
#include "PlayerMain.h"
#include "GameManagerMain.h"

class Enemy {
public:
	Enemy();
	void Update(Player& player, float deltaTime);
	void Display(GameManager& gameManager);
	void UpdateAnimation(float deltaTime);
	void Collision(Player& player, Enemy enemy[], int enemyCount);

	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetLastX() const { return lastPositionX; }
	float GetLastY() const { return lastPositionY; }

	bool GetTemp() const { return isCaughtCollision; }

	bool GetIsCaught() const { return isCaught; }

	void SetX(float newX) { x = newX; }
	void SetY(float newY) { y = newY; }

private:
	int imageIdle, imageWalk, imageAttack, imageCaught, imageExplosion, imageSmoke; // 画像

	int explosionSound, attackSound; // サウンド

	float temp; // デバッグ用
	bool tempBool;

	int hitPoint;

	float x, y, firstPositionX, firstPositionY, lastPositionX, lastPositionY; // 位置
	float speed, throwSpeed; // 速度
	int limitHigh, limitLow; // 移動の下限

	float scale, scaleExplosion, alphaExplosion; // scale倍のサイズで描画

	int countFrameIdle, countFrameWalk, countFrameAttack, countFrameCaught; // アニメーションの枚数をカウント
	int widthIdle, heightIdle, widthWalk, heightWalk, widthAttack, heightAttack,
		widthCaught, heightCaught, widthExplosion, heightExplosion, widthSmoke, heightSmoke; // 画像の幅と高さ
	float animationTimer; // アニメーションの時間
	bool isWalk, isWalkBack, isIdleBack, isStopAnimation, isAttack, isAttackLength, isExplosion; // アニメーションの制御
	bool isStop, isAttacked, isDecreasedPlayerHP, isGetDamage,
		isCollisionPlayer, isFirstAttacked, isBlowDirection, isDead, isCaught, isThrown,
		isCaughtCollision, isFirstCaughtCollision, isThrowDirection, isFirstThrow, isSmoke; // 行動の制御
	float attackTimer, attackCoolTime, explosionTimer, explosionCoolTime; // CTの管理 
	bool isAttackCoolTime; // CTの管理

	float directionX, directionY, length, avoidX, avoidY, totalDirectionX, totalDirectionY, totalLength; // プレイヤーとの距離
	float minDistance; // キャラクターが当たらない範囲
	float blowTimer; // 吹き飛ばされる際のタイマー
};
