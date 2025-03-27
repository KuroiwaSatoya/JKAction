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
	int imageIdle, imageWalk, imageAttack, imageCaught, imageExplosion, imageSmoke; // �摜

	int explosionSound, attackSound; // �T�E���h

	float temp; // �f�o�b�O�p
	bool tempBool;

	int hitPoint;

	float x, y, firstPositionX, firstPositionY, lastPositionX, lastPositionY; // �ʒu
	float speed, throwSpeed; // ���x
	int limitHigh, limitLow; // �ړ��̉���

	float scale, scaleExplosion, alphaExplosion; // scale�{�̃T�C�Y�ŕ`��

	int countFrameIdle, countFrameWalk, countFrameAttack, countFrameCaught; // �A�j���[�V�����̖������J�E���g
	int widthIdle, heightIdle, widthWalk, heightWalk, widthAttack, heightAttack,
		widthCaught, heightCaught, widthExplosion, heightExplosion, widthSmoke, heightSmoke; // �摜�̕��ƍ���
	float animationTimer; // �A�j���[�V�����̎���
	bool isWalk, isWalkBack, isIdleBack, isStopAnimation, isAttack, isAttackLength, isExplosion; // �A�j���[�V�����̐���
	bool isStop, isAttacked, isDecreasedPlayerHP, isGetDamage,
		isCollisionPlayer, isFirstAttacked, isBlowDirection, isDead, isCaught, isThrown,
		isCaughtCollision, isFirstCaughtCollision, isThrowDirection, isFirstThrow, isSmoke; // �s���̐���
	float attackTimer, attackCoolTime, explosionTimer, explosionCoolTime; // CT�̊Ǘ� 
	bool isAttackCoolTime; // CT�̊Ǘ�

	float directionX, directionY, length, avoidX, avoidY, totalDirectionX, totalDirectionY, totalLength; // �v���C���[�Ƃ̋���
	float minDistance; // �L�����N�^�[��������Ȃ��͈�
	float blowTimer; // ������΂����ۂ̃^�C�}�[
};
