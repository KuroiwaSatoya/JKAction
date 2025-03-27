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
    int imageIdle, imageWalk, imageAttack, imageProtection, imageDead; // 画像
    int attackSound; // サウンド
    int hitPoint;
    float x, y, firstPositionX, firstPositionY; // 位置
    float directionX, directionY; // Enemyの位置とは逆に働くベクトル
    float speed; // 速度
    float scale; // scale倍のサイズで描画
    int limitHigh, limitLow; // 移動の下限
    bool isStop, isAttack, isBlow, isCollisionEnemy, isSlow, isCatch, isCatchEnemy, isCatching, isFirstCatch, isThrow, isRelease, isDead, isGoal; // 動きの制御
    float attackCoolTime, throwCoolTime; // 攻撃のCT
    bool isAttackCoolTime, isThrowCoolTime; //CTの管理
    int attackTime; // 動作時間
    int countFrameIdle, countFrameWalk, countFrameAttack, countFrameProtection; // アニメーションの枚数をカウント
    int widthIdle, heightIdle, widthWalk, heightWalk, widthAttack, heightAttack,
        widthProtection, heightProtection, widthDead, heightDead; // 画像の幅と高さ
    float animationTimer, attackTimer; // アニメーションの時間
    bool isWalk, isWalkBack, isIdleBack; // アニメーションの制御
};

