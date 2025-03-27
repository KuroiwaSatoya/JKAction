#include "DxLib.h"
#include "EnemyMain.h"
#include <cmath>

const int FRAME_COUNT_IDLE = 7; // Idolのフレーム数
const int FRAME_COUNT_WALK = 12; // Walkのフレーム数
const int FRAME_COUNT_ATTACK = 9; // Attackのフレーム数
const int FRAME_COUNT_CAUGHT = 6; // Attackのフレーム数
const float FRAME_TIME_IDLE = 0.2f; // 1フレームの表示時間
const float FRAME_TIME_WALK = 0.1f; // 1フレームの表示時間
const float FRAME_TIME_ATTACK = 0.1f; // 1フレームの表示時間
const float FRAME_TIME_CAUGHT = 0.2f; // 1フレームの表示時間
const float FRAME_TIME_EXPLOSION = 0.1f;

const float FIRST_TIME_ATTACK = 0.5f; // 攻撃判定が出るまでの時間

const float BLOW_TIME = 1.0f; // プレイヤーに攻撃された際の吹き飛ばされる時間

Enemy::Enemy() {
    temp = 0;
    tempBool = false;
    hitPoint = 1000;
    explosionSound = LoadSoundMem("Sounds/EnemyExplosion.mp3");
    attackSound = LoadSoundMem("Sounds/EnemyAttack.mp3");
    imageIdle = LoadGraph("Images/Enemy/Idle.png");
    imageWalk = LoadGraph("Images/Enemy/Walk.png");
    imageAttack = LoadGraph("Images/Enemy/Attack.png");
    imageCaught = LoadGraph("Images/Enemy/Caught.png");
    imageExplosion = LoadGraph("Images/Explosion.png");
    imageSmoke = LoadGraph("Images/Smoke.png");
    GetGraphSize(imageIdle, &widthIdle, &heightIdle);
    GetGraphSize(imageWalk, &widthWalk, &heightWalk);
    GetGraphSize(imageAttack, &widthAttack, &heightAttack);
    GetGraphSize(imageCaught, &widthCaught, &heightCaught);
    GetGraphSize(imageExplosion, &widthExplosion, &heightExplosion);
    GetGraphSize(imageSmoke, &widthSmoke, &heightSmoke);
    firstPositionX = 0;
    firstPositionY = 0;
    x = firstPositionX;
    y = firstPositionY;
    lastPositionX = -100;
    lastPositionY = -100;
    speed = 120.0f;
    throwSpeed = 1000.0f;
    scale = 5.0f;
    scaleExplosion = 0;
    alphaExplosion = 255;
    limitHigh = -180;
    limitLow = 430;
    countFrameIdle = 0;
    countFrameWalk = 0;
    countFrameAttack = 0;
    countFrameCaught = 0;
    animationTimer = 0.0f;
    attackTimer = 0.0f;
    attackCoolTime = 1.0f;
    explosionTimer = 0.0f;
    explosionCoolTime = 1.0f;
    isAttackCoolTime = false;
    directionX = 0;
    directionY = 0;
    totalDirectionX = 0;
    totalDirectionY = 0;
    totalLength = 0;
    length = 0;
    avoidX = 0;
    avoidY = 0;
    minDistance = 200;
    blowTimer = 0.0f;
    isWalk = false;
    isWalkBack = false;
    isIdleBack = false;
    isAttack = false;
    isAttackLength = false;
    isStop = false;
    isExplosion = false;
    isAttacked = false;
    isStopAnimation = false;
    isCollisionPlayer = false;
    isFirstAttacked = false;
    isBlowDirection = false;
    isDecreasedPlayerHP = false;
    isGetDamage = false;
    isDead = false;
    isCaught = false;
    isThrown = false;
    isCaughtCollision = false;
    isFirstCaughtCollision = false;
    isFirstThrow = false;
    isThrowDirection = false;
    isSmoke = false;
}

void Enemy::Update(Player& player, float deltaTime) {
    if (!isDead) {
        if ((!isStop || isStop && isAttacked) && (!isAttackLength || isAttackLength && isAttacked) && !isExplosion && !isSmoke && !isCaught && !isThrown && deltaTime != 0 && length != 0) {

            // 攻撃されたら後ろに下がる
            if (isAttacked) {
                blowTimer += deltaTime;
                if (!isFirstAttacked) {
                    isFirstAttacked = true;
                    isBlowDirection = player.GetIsIdleBack();
                }
                if (isBlowDirection) {
                    directionX -= 1000;
                }
                else {
                    directionX += 1000;
                }
                if (blowTimer >= BLOW_TIME) {
                    blowTimer = 0.0f;
                    isAttacked = false;
                    isFirstAttacked = false;
                }
            }

            // 正規化
            directionX /= length;
            directionX += avoidX;
            // 速度を代入
            x += directionX * speed * deltaTime;

            //yも
            directionY /= length;
            directionY += avoidY;
            y += directionY * speed * deltaTime;

            // 移動方向によってアニメーションの向きを変更 未完成 できれば敵同士が詰まったときのカクカクを直したい
            if (!isAttacked) {
                isIdleBack = player.GetX() - x < 0;
                isWalkBack = player.GetX() - x < 0;

            }
        }
        else if (isExplosion) {
            explosionTimer += deltaTime;
            if (explosionTimer >= explosionCoolTime) {
                explosionTimer = 0.0f;
                isExplosion = false;
                isDead = true;
            }
        }
        else if (isSmoke) {
            explosionTimer += deltaTime;
            if (explosionTimer >= explosionCoolTime) {
                explosionTimer = 0.0f;
                isSmoke = false;
                isDead = true;
            }
        }
        else if (isCaught) {
            x = player.GetX();
            y = player.GetY();
        }
        else if (isThrown) {
            if (!isFirstThrow) {
                isFirstThrow = true;
                isThrowDirection = player.GetIsIdleBack();
            }
            if (isThrowDirection) {
                x -= throwSpeed * deltaTime;
            }
            else {
                x += throwSpeed * deltaTime;
            }
        }
        else if (isAttackLength && !isAttackCoolTime) {
            isIdleBack = player.GetX() - x < 0;
            isWalk = false;
            isWalkBack = false;
            isAttack = true;

            attackTimer += deltaTime;
            if (attackTimer >= FIRST_TIME_ATTACK) {
                if (!isDecreasedPlayerHP) {
                    player.DecreasedHP(10);
                    isDecreasedPlayerHP = true;
                }
            }
            if (attackTimer >= FRAME_TIME_ATTACK * FRAME_COUNT_ATTACK) {
                attackTimer = 0.0f;
                isDecreasedPlayerHP = false;
                isAttack = false;
                isAttackCoolTime = true;
            }
        }
        else if (isAttackCoolTime) {
            attackTimer += deltaTime;
            if (attackTimer >= attackCoolTime) {
                attackTimer = 0.0f;
                isAttackCoolTime = false;
            }
        }
        else if (isStop) {
            isIdleBack = player.GetX() - x < 0;
            isWalk = false;
            isWalkBack = false;
        }

        // リセットする
        avoidX = 0.0f;
        avoidY = 0.0f;

        lastPositionX = x;
        lastPositionY = y;

        totalLength = 0.0f;
    }
}

void Enemy::UpdateAnimation(float deltaTime) {
    if (!isDead) {
        animationTimer += deltaTime;

        if (isExplosion) {
            float alphaExplosionTemp = 1.0f;
            if (animationTimer >= FRAME_TIME_EXPLOSION) {
                animationTimer = 0.0f;
                alphaExplosionTemp *= 30.0f;
                alphaExplosion -= alphaExplosionTemp;
                scaleExplosion += 0.2f;
            }
        }
        else if (isSmoke) {
            float alphaSmokeTemp = 1.0f;
            if (animationTimer >= FRAME_TIME_EXPLOSION) {
                animationTimer = 0.0f;
                alphaSmokeTemp *= 30.0f;
                alphaExplosion -= alphaSmokeTemp;
                scaleExplosion += 0.2f;
            }
        }
        else if (isWalk || isWalkBack) {
            if (animationTimer >= FRAME_TIME_WALK) {
                animationTimer = 0.0f;
                countFrameWalk = (countFrameWalk + 1) % FRAME_COUNT_WALK;
            }
        }
        else if (isAttack) {
            if (animationTimer >= FRAME_TIME_ATTACK) {
                animationTimer = 0.0f;
                countFrameAttack = (countFrameAttack + 1) % FRAME_COUNT_ATTACK;
            }
        }
        else {
            if (animationTimer >= FRAME_TIME_IDLE) {
                animationTimer = 0.0f;
                countFrameIdle = (countFrameIdle + 1) % FRAME_COUNT_IDLE;
            }
        }
    }
}

void Enemy::Display(GameManager& gameManager) {
    if (!isDead) {
        if (isCaught || isThrown) {
            DrawRotaGraphF(
                x + 200 - gameManager.GetCameraX() + widthCaught * scale / 2, // 中心のX座標
                y + 50 + heightCaught * scale / 2, // Y座標
                scale, // 拡大率
                DX_PI_F / 2.0f, // 角度
                imageCaught, TRUE);
        }
        else if (isExplosion) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaExplosion);
            if (isThrowDirection) {
                DrawRotaGraphF(
                    x - gameManager.GetCameraX() + 80, // 中心のX座標
                    y + 420, // Y座標
                    scaleExplosion, // 拡大率
                    0, // 角度
                    imageExplosion, TRUE);
            }
            else {
                DrawRotaGraphF(
                    x - gameManager.GetCameraX() + 550, // 中心のX座標
                    y + 420, // Y座標
                    scaleExplosion, // 拡大率
                    0, // 角度
                    imageExplosion, TRUE);
            }
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            if (CheckSoundMem(explosionSound) == FALSE) {
                PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK);
            }
        }
        else if (isSmoke) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaExplosion);
            DrawRotaGraphF(
                x - gameManager.GetCameraX() + 270, // 中心のX座標
                y + 420, // Y座標
                scaleExplosion / 2, // 拡大率
                0, // 角度
                imageSmoke, TRUE);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        }
        else if (isWalk) {
            DrawRectExtendGraphF(
                x - gameManager.GetCameraX(), y,
                x - gameManager.GetCameraX() + (widthWalk / FRAME_COUNT_WALK) * scale, y + heightWalk * scale,
                countFrameWalk * (widthWalk / FRAME_COUNT_WALK), 0,
                (widthWalk / FRAME_COUNT_WALK), heightWalk,
                imageWalk, TRUE);
        }
        else if (isWalkBack) {
            DrawRectExtendGraphF(
                x - gameManager.GetCameraX() + (widthWalk / FRAME_COUNT_WALK) * scale, y,
                x - gameManager.GetCameraX(), y + heightWalk * scale,
                countFrameWalk * (widthWalk / FRAME_COUNT_WALK), 0,
                (widthWalk / FRAME_COUNT_WALK), heightWalk,
                imageWalk, TRUE);
        }
        else if (isAttack) {
            if (isIdleBack) {
                DrawRectExtendGraphF(
                    x - gameManager.GetCameraX() + (widthAttack / FRAME_COUNT_ATTACK) * scale, y,
                    x - gameManager.GetCameraX(), y + heightAttack * scale,
                    countFrameAttack * (widthAttack / FRAME_COUNT_ATTACK), 0,
                    (widthAttack / FRAME_COUNT_ATTACK), heightAttack,
                    imageAttack, TRUE);
            }
            else {
                DrawRectExtendGraphF(
                    x - gameManager.GetCameraX(), y,
                    x - gameManager.GetCameraX() + (widthAttack / FRAME_COUNT_ATTACK) * scale, y + heightAttack * scale,
                    countFrameAttack * (widthAttack / FRAME_COUNT_ATTACK), 0,
                    (widthAttack / FRAME_COUNT_ATTACK), heightAttack,
                    imageAttack, TRUE);
            }
            if (CheckSoundMem(attackSound) == FALSE) {
                PlaySoundMem(attackSound, DX_PLAYTYPE_BACK);
            }
        }
        else if (isIdleBack) {
            DrawRectExtendGraphF(
                x - gameManager.GetCameraX() + (widthIdle / FRAME_COUNT_IDLE) * scale, y,
                x - gameManager.GetCameraX(), y + heightIdle * scale,
                countFrameIdle * (widthIdle / FRAME_COUNT_IDLE), 0,
                (widthIdle / FRAME_COUNT_IDLE), heightIdle,
                imageIdle, TRUE);
        }
        else {
            DrawRectExtendGraphF(
                x - gameManager.GetCameraX(), y,
                x - gameManager.GetCameraX() + (widthIdle / FRAME_COUNT_IDLE) * scale, y + heightIdle * scale,
                countFrameIdle * (widthIdle / FRAME_COUNT_IDLE), 0,
                (widthIdle / FRAME_COUNT_IDLE), heightIdle,
                imageIdle, TRUE);
        }
        /*if (imageIdol == -1) {
            DrawFormatString(10, 10, GetColor(255, 225, 255), "敵のidolが無いです");
        }*/
        /*if (imageWalk == -1) {
            DrawFormatString(10, 30, GetColor(255, 255, 255), "敵のWalkがないです");
        }*/
    }
}

void Enemy::Collision(Player& player, Enemy enemy[], int enemyCount) {
    if (!isDead) {
        directionX = player.GetX() - x; // プレイヤーとのX座標の差
        directionY = player.GetY() - y; // プレイヤーとのY座標の差
        length = sqrt(directionX * directionX + directionY * directionY); // プレイヤーとの距離
        isStop = length < minDistance;
        isAttackLength = length < minDistance;

        float minCatchDistance = 200;  // プレイヤーと敵の最小距離を記録する変数
        Enemy* caughtEnemy = nullptr;     // キャッチされた敵のポインタ

        // プレイヤーが距離が小さければ避けるようにベクトルを調整
        if (!isCaught && !isExplosion && !isSmoke) {
            if (length > 0.0f && length < 100) {
                player.SetIsCollisionEnemy(TRUE);

                // ノーマライズ
                float lengthX = directionX / length;
                float lengthY = directionY / length;

                totalDirectionX += lengthX;
                totalDirectionY += lengthY;
            }

            totalLength = sqrt(totalDirectionX * totalDirectionX + totalDirectionY * totalDirectionY);

            player.SetDirectionX(totalDirectionX / totalLength);
            player.SetDirectionY(totalDirectionY / totalLength);
        }

        if (totalLength > 0.0f) {
            player.SetDirectionX(totalDirectionX / totalLength);
            player.SetDirectionY(totalDirectionY / totalLength);
        }
        else
        {
            player.SetDirectionX(0.0f);
            player.SetDirectionY(0.0f);
            totalDirectionX = 0;
            totalDirectionY = 0;
            totalLength = 0;
        }

        // 攻撃された判定
        if (player.GetIsBlow()) {
            if (!isCaught && !isExplosion && !isSmoke) {
                if (length < 200) {  // プレイヤーとの距離が200以下なら
                    if ((player.GetIsIdleBack() == false && directionX < 50) // 向いてない方向半分くらい判定を切る
                        || (player.GetIsIdleBack() == true && directionX > 50)) {
                        isAttacked = true;
                        if (!isGetDamage) {
                            hitPoint -= 500;
                            if (hitPoint <= 0) {
                                isSmoke = true;
                            }
                            isGetDamage = true;
                        }
                    }
                }
                else {
                    isGetDamage = false;
                }
            }
        }

        if (player.GetIsCatching()) {
            if (!player.GetIsCatchEnemy()) {
                isCaughtCollision = true;
            }
        }
        else {
            isCaughtCollision = false;
        }

        if (player.GetIsThrow()) {
            if (isCaught) {
                isThrown = true;
                isCaught = false;
            }
        }

        if (isCaughtCollision) {
            if (player.GetIsIdleBack()) {
                if (x < player.GetX() + 82 && x + 247 > player.GetX()
                    && y < player.GetY() + 177 && y + 177 > player.GetY()) {
                    isCaught = true;
                    player.SetIsCatchEnemy(true);
                }
            }
            else {
                if (x < player.GetX() + 247 && x + 82 > player.GetX()
                    && y < player.GetY() + 177 && y + 177 > player.GetY()) {
                    isCaught = true;
                    player.SetIsCatchEnemy(true);
                }
            }
        }

        for (int i = 0; i < enemyCount; i++) {
            if (this == &enemy[i]) continue;  // 自分は含めない
            if (enemy[i].isDead) continue; // 死んだ敵は含めない
            if (enemy[i].isSmoke) continue; // 死んだ敵は含めない

            // 他の敵との距離を計算
            float directionToEnemyX = enemy[i].x - this->x;
            float directionToEnemyY = enemy[i].y - this->y;
            float distanceToEnemy = sqrt(directionToEnemyX * directionToEnemyX + directionToEnemyY * directionToEnemyY);


            // Throwの当たり判定
            if (isThrown && !enemy[i].isThrown && !enemy[i].isCaught) {
                if (x <  enemy[i].x + 165 && x + 355 > enemy[i].x
                    && y < enemy[i].y + 355 && y + 165 > enemy[i].y) {
                    enemy[i].isSmoke = true;
                    isExplosion = true;
                    isThrown = false;
                }
            }
            else if (isExplosion) {
                if (distanceToEnemy < 400) {
                    enemy[i].isSmoke = true;
                }
            }

            // 距離が小さければ避けるようにベクトルを調整
            if (distanceToEnemy > 0.0f && distanceToEnemy < minDistance) {

                // ノーマライズ
                float lengthX = directionToEnemyX / distanceToEnemy;
                float lengthY = directionToEnemyY / distanceToEnemy;

                // 移動ベクトルに加え、敵がいる方向へ進まないようにする
                this->avoidX -= lengthX;
                this->avoidY -= lengthY;
            }
        }
    }
}