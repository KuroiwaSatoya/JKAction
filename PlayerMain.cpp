#include "DxLib.h"
#include "PlayerMain.h"

const int FRAME_COUNT_IDLE = 6; // Idolのフレーム数
const int FRAME_COUNT_WALK = 12; // Walkのフレーム数
const int FRAME_COUNT_ATTACK = 6; // Attackのフレーム数
const int FRAME_COUNT_PROTECTION = 3; // Protectionのフレーム数
const float FRAME_TIME_IDLE = 0.2f; // 1フレームの表示時間
const float FRAME_TIME_WALK = 0.1f; // 1フレームの表示時間
const float FRAME_TIME_ATTACK = 0.1f; // Attackの1フレームの表示時間
const float FRAME_TIME_PROTECTION = 0.3f; // Protectionの1フレームの表示時間

const float FIRST_TIME_ATTACK = 0.4f; // attackの判定が出るまでの時間(blow)

Player::Player()
{
    temp = 0.0f;
    attackSound = LoadSoundMem("Sounds/PlayerAttack.mp3");
    imageIdle = LoadGraph("Images/Player/Idle.png");
    imageWalk = LoadGraph("Images/Player/Walk.png");
    imageAttack = LoadGraph("Images/Player/Attack.png");
    imageProtection = LoadGraph("Images/Player/Protection.png");
    imageDead = LoadGraph("Images/Player/Dead.png");
    hitPoint = 1000;
    GetGraphSize(imageIdle, &widthIdle, &heightIdle);
    GetGraphSize(imageWalk, &widthWalk, &heightWalk);
    GetGraphSize(imageAttack, &widthAttack, &heightAttack);
    GetGraphSize(imageProtection, &widthProtection, &heightProtection);
    GetGraphSize(imageDead, &widthDead, &heightDead);
    firstPositionX = 100.0f;
    firstPositionY = 200.0f;
    x = firstPositionX;
    y = firstPositionY;
    directionX = 0;
    directionY = 0;
    speed = 300.0f;
    scale = 5.0f;
    limitHigh = -70;
    limitLow = 430;
    isStop = false;
    isAttack = false;
    isBlow = false;
    isSlow = false;
    isCatch = false;
    isFirstCatch = false;
    isCatching = false;
    isCatchEnemy = false;
    isThrow = false;
    isRelease = false;
    isCollisionEnemy = false;
    attackCoolTime = 1.0f;
    throwCoolTime = 0.3f;
    isAttackCoolTime = false;
    isThrowCoolTime = false;
    attackTime = 0;
    countFrameIdle = 0;
    countFrameWalk = 0;
    countFrameAttack = 0;
    countFrameProtection = 0;
    animationTimer = 0.0f;
    attackTimer = 0.0f;
    isWalk = false;
    isWalkBack = false;
    isIdleBack = false;
    isDead = false;
    isGoal = false;
}

void Player::Update(float deltaTime) {
    if (!isDead && !isGoal) {
        if (isCollisionEnemy && x > firstPositionX && y > limitHigh && y < limitLow) {
            x += directionX * speed * deltaTime;
            y += directionY * speed * deltaTime;
        }
        else if (!isStop) {
            isWalk = false; // ここで一旦falseにし、入力があった場合にtureにする
            isWalkBack = false;

            if (isSlow) {
                speed /= 10;
            }
            else {
                speed = 300;
            }

            // 入力
            if (CheckHitKey(KEY_INPUT_A)) {
                if (x > firstPositionX) {
                    x -= speed * deltaTime;
                    isWalkBack = true;
                    isIdleBack = true;
                }
            }

            if (CheckHitKey(KEY_INPUT_D)) {
                x += speed * deltaTime;
                isWalk = true;
                isIdleBack = false;
            }

            if (CheckHitKey(KEY_INPUT_W)) {
                if (y > limitHigh) {
                    y -= speed * deltaTime;
                    if (!isIdleBack) {
                        isWalk = true;
                    }
                    else {
                        isWalkBack = true;
                    }
                }
            }

            if (CheckHitKey(KEY_INPUT_S)) {
                if (y < limitLow) {
                    y += speed * deltaTime;
                    if (!isIdleBack) {
                        isWalk = true;
                    }
                    else {
                        isWalkBack = true;
                    }
                }
            }

        }

        if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
            if (isCatch) {
                isCatch = false;
                isThrow = true;
                isCatchEnemy = false;
                isFirstCatch = false;
            }
            else if (!isAttackCoolTime) {
                isAttack = true;
                isStop = true;
            }
        }

        if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0) {
            if (!isThrowCoolTime) {
                isCatch = true;
                if (!isFirstCatch) {
                    isCatching = true;
                    isFirstCatch = true;
                }
                else {
                    isCatching = false;
                }
            }
        }

        if (isAttack) {
            attackTimer += deltaTime;
            if (attackTimer >= FIRST_TIME_ATTACK) {
                isBlow = true;
            }
            if (attackTimer >= FRAME_TIME_ATTACK * FRAME_COUNT_ATTACK) {
                attackTimer = 0.0f;
                isBlow = false;
                isAttack = false;
                isStop = false;
                isAttackCoolTime = true;
            }
        }
        if (isAttackCoolTime) {
            attackTimer += deltaTime;
            if (attackTimer >= attackCoolTime) {
                attackTimer = 0.0f;
                isAttackCoolTime = false;
            }
        }
        if (isCatch) {
            isSlow = true;
        }
        else {
            isSlow = false;
        }
        if (isThrow) {
            attackTimer += deltaTime;
            if (attackTimer >= FIRST_TIME_ATTACK) {
                isRelease = true;
            }
            if (attackTimer >= FRAME_TIME_ATTACK * FRAME_COUNT_ATTACK) {
                attackTimer = 0.0f;
                isRelease = false;
                isThrow = false;
                isSlow = false;
                isThrowCoolTime = true;
            }
        }
        if (isThrowCoolTime) {
            attackTimer += deltaTime;
            if (attackTimer >= attackCoolTime) {
                attackTimer = 0.0f;
                isThrowCoolTime = false;
            }
        }
    }
}

void Player::UpdateAnimation(float deltaTime) {
    animationTimer += deltaTime;

    if (isAttack || isThrow) {
        if (animationTimer >= FRAME_TIME_ATTACK) {
            animationTimer = 0.0f;
            countFrameAttack = (countFrameAttack + 1) % FRAME_COUNT_ATTACK;
        }
    }
    else if (isCatch && countFrameProtection < 2) {
        if (animationTimer >= FRAME_TIME_PROTECTION) {
            animationTimer = 0.0f;
            countFrameProtection = (countFrameProtection + 1) % FRAME_COUNT_PROTECTION;
        }
    }
    else if (isCatch && countFrameProtection > 2) {
        countFrameProtection = 2;
    }
    else if (isWalk || isWalkBack) {
        if (animationTimer >= FRAME_TIME_WALK) {
            animationTimer = 0.0f;
            countFrameWalk = (countFrameWalk + 1) % FRAME_COUNT_WALK;
        }
    }
    else {
        if (animationTimer >= FRAME_TIME_IDLE) {
            animationTimer = 0.0f;
            countFrameIdle = (countFrameIdle + 1) % FRAME_COUNT_IDLE;
        }
    }

    if (!isCatch) {
        countFrameProtection = 0;
    }

}

void Player::Display() {
    if (isDead) {
        DrawRotaGraphF(
            firstPositionX + 100 + widthDead * scale / 2, // 中心のX座標
            y + heightDead * scale / 2, // Y座標
            scale, // 拡大率
            DX_PI_F / 2.0f, // 角度
            imageDead, TRUE);
    }
    else if ((isAttack || isThrow) && isIdleBack) {
        DrawRectExtendGraphF(
            firstPositionX + (widthAttack / FRAME_COUNT_ATTACK) * scale, y,
            firstPositionX, y + heightAttack * scale,
            countFrameAttack * (widthAttack / FRAME_COUNT_ATTACK), 0,
            (widthAttack / FRAME_COUNT_ATTACK), heightAttack,
            imageAttack, TRUE);
        if (CheckSoundMem(attackSound) == FALSE) {
            PlaySoundMem(attackSound, DX_PLAYTYPE_BACK);
        }
    }
    else if (isAttack || isThrow) {
        DrawRectExtendGraphF(
            firstPositionX, y,
            firstPositionX + (widthAttack / FRAME_COUNT_ATTACK) * scale, y + heightAttack * scale,
            countFrameAttack * (widthAttack / FRAME_COUNT_ATTACK), 0,
            (widthAttack / FRAME_COUNT_ATTACK), heightAttack,
            imageAttack, TRUE);
        if (CheckSoundMem(attackSound) == FALSE) {
            PlaySoundMem(attackSound, DX_PLAYTYPE_BACK);
        }
    }
    else if (isCatch && isIdleBack) {
        DrawRectExtendGraphF(
            firstPositionX + (widthProtection / FRAME_COUNT_PROTECTION) * scale, y,
            firstPositionX, y + heightProtection * scale,
            countFrameProtection * (widthProtection / FRAME_COUNT_PROTECTION), 0,
            (widthProtection / FRAME_COUNT_PROTECTION), heightProtection,
            imageProtection, TRUE);
    }
    else if (isCatch) {
        DrawRectExtendGraphF(
            firstPositionX, y,
            firstPositionX + (widthProtection / FRAME_COUNT_PROTECTION) * scale, y + heightProtection * scale,
            countFrameProtection * (widthProtection / FRAME_COUNT_PROTECTION), 0,
            (widthProtection / FRAME_COUNT_PROTECTION), heightProtection,
            imageProtection, TRUE);
    }
    else if (isWalk) {
        DrawRectExtendGraphF(
            firstPositionX, y,
            firstPositionX + (widthWalk / FRAME_COUNT_WALK) * scale, y + heightWalk * scale,
            countFrameWalk * (widthWalk / FRAME_COUNT_WALK), 0,
            (widthWalk / FRAME_COUNT_WALK), heightWalk,
            imageWalk, TRUE);
    }
    else if (isWalkBack) {
        DrawRectExtendGraphF(
            firstPositionX + (widthWalk / FRAME_COUNT_WALK) * scale, y,
            firstPositionX, y + heightWalk * scale,
            countFrameWalk * (widthWalk / FRAME_COUNT_WALK), 0,
            (widthWalk / FRAME_COUNT_WALK), heightWalk,
            imageWalk, TRUE);
    }
    else if (isIdleBack) {
        DrawRectExtendGraphF(
            firstPositionX + (widthIdle / FRAME_COUNT_IDLE) * scale, y,
            firstPositionX, y + heightIdle * scale,
            countFrameIdle * (widthIdle / FRAME_COUNT_IDLE), 0,
            (widthIdle / FRAME_COUNT_IDLE), heightIdle,
            imageIdle, TRUE);
    }
    else {
        DrawRectExtendGraphF(
            firstPositionX, y,
            firstPositionX + (widthIdle / FRAME_COUNT_IDLE) * scale, y + heightIdle * scale,
            countFrameIdle * (widthIdle / FRAME_COUNT_IDLE), 0,
            (widthIdle / FRAME_COUNT_IDLE), heightIdle,
            imageIdle, TRUE);
    }

    /*if (imageIdol == -1) {
        DrawString(10, 10, "読み込めませんでした", GetColor(255, 255, 255));
        char path[260];
        GetCurrentDirectoryA(260, path);
        DrawString(100, 100, path, GetColor(255, 255, 255));
    }*/
}

void Player::Collision() {
    if (!isDead && !isGoal) {
        directionX = 0;
        directionY = 0;
        isCollisionEnemy = false;

        if (hitPoint <= 0) {
            isDead = true;
        }

        if (x >= 9800.0f) {
            isGoal = true;
        }
    }
}
