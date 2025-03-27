#pragma once

class Player {
public:
    Player();
    void Update(float deltaTime);
    void Display();
    void UpdateAnimation(float deltaTime);
    void Collision();

    float GetX() const { return x; }
    float GetY() const { return y; }
    float GetFirstPositionX() const { return firstPositionX; }

    int GetHitPoint() const { return hitPoint; }
    int GetTemp() const { return hitPoint; }

    bool GetIsBlow() const { return isBlow; }
    bool GetIsIdleBack() const { return isIdleBack; }
    bool GetIsCatch() const { return isCatch; }
    bool GetIsThrow() const { return isThrow; }
    bool GetIsDead() const { return isDead; }
    bool GetIsGoal() const { return isGoal; }
    bool GetIsCatching() const { return isCatching; }
    bool GetIsCatchEnemy() const { return isCatchEnemy; }

    void SetDirectionX(float newDirectionX) { directionX = newDirectionX; }
    void SetDirectionY(float newDirectionY) { directionY = newDirectionY; }
    void SetIsCollisionEnemy(bool newIsCollisionEnemy) { isCollisionEnemy = newIsCollisionEnemy; }
    void SetIsCatchEnemy(bool newIsCatchEnemy) { isCatchEnemy = newIsCatchEnemy; }
    void DecreasedHP(int damage) { hitPoint -= damage; }

private:
    float temp;
    int imageIdle, imageWalk, imageAttack, imageProtection, imageDead; // �摜
    int attackSound; // �T�E���h
    int hitPoint;
    float x, y, firstPositionX, firstPositionY; // �ʒu
    float directionX, directionY; // Enemy�̈ʒu�Ƃ͋t�ɓ����x�N�g��
    float speed; // ���x
    float scale; // scale�{�̃T�C�Y�ŕ`��
    int limitHigh, limitLow; // �ړ��̉���
    bool isStop, isAttack, isBlow, isCollisionEnemy, isSlow, isCatch, isCatchEnemy, isCatching, isFirstCatch, isThrow, isRelease, isDead, isGoal; // �����̐���
    float attackCoolTime, throwCoolTime; // �U����CT
    bool isAttackCoolTime, isThrowCoolTime; //CT�̊Ǘ�
    int attackTime; // ���쎞��
    int countFrameIdle, countFrameWalk, countFrameAttack, countFrameProtection; // �A�j���[�V�����̖������J�E���g
    int widthIdle, heightIdle, widthWalk, heightWalk, widthAttack, heightAttack,
        widthProtection, heightProtection, widthDead, heightDead; // �摜�̕��ƍ���
    float animationTimer, attackTimer; // �A�j���[�V�����̎���
    bool isWalk, isWalkBack, isIdleBack; // �A�j���[�V�����̐���
};

