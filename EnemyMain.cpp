#include "DxLib.h"
#include "EnemyMain.h"
#include <cmath>

const int FRAME_COUNT_IDLE = 7; // Idol�̃t���[����
const int FRAME_COUNT_WALK = 12; // Walk�̃t���[����
const int FRAME_COUNT_ATTACK = 9; // Attack�̃t���[����
const int FRAME_COUNT_CAUGHT = 6; // Attack�̃t���[����
const float FRAME_TIME_IDLE = 0.2f; // 1�t���[���̕\������
const float FRAME_TIME_WALK = 0.1f; // 1�t���[���̕\������
const float FRAME_TIME_ATTACK = 0.1f; // 1�t���[���̕\������
const float FRAME_TIME_CAUGHT = 0.2f; // 1�t���[���̕\������
const float FRAME_TIME_EXPLOSION = 0.1f;

const float FIRST_TIME_ATTACK = 0.5f; // �U�����肪�o��܂ł̎���

const float BLOW_TIME = 1.0f; // �v���C���[�ɍU�����ꂽ�ۂ̐�����΂���鎞��

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

            // �U�����ꂽ����ɉ�����
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

            // ���K��
            directionX /= length;
            directionX += avoidX;
            // ���x����
            x += directionX * speed * deltaTime;

            //y��
            directionY /= length;
            directionY += avoidY;
            y += directionY * speed * deltaTime;

            // �ړ������ɂ���ăA�j���[�V�����̌�����ύX ������ �ł���ΓG���m���l�܂����Ƃ��̃J�N�J�N�𒼂�����
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

        // ���Z�b�g����
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
                x + 200 - gameManager.GetCameraX() + widthCaught * scale / 2, // ���S��X���W
                y + 50 + heightCaught * scale / 2, // Y���W
                scale, // �g�嗦
                DX_PI_F / 2.0f, // �p�x
                imageCaught, TRUE);
        }
        else if (isExplosion) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaExplosion);
            if (isThrowDirection) {
                DrawRotaGraphF(
                    x - gameManager.GetCameraX() + 80, // ���S��X���W
                    y + 420, // Y���W
                    scaleExplosion, // �g�嗦
                    0, // �p�x
                    imageExplosion, TRUE);
            }
            else {
                DrawRotaGraphF(
                    x - gameManager.GetCameraX() + 550, // ���S��X���W
                    y + 420, // Y���W
                    scaleExplosion, // �g�嗦
                    0, // �p�x
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
                x - gameManager.GetCameraX() + 270, // ���S��X���W
                y + 420, // Y���W
                scaleExplosion / 2, // �g�嗦
                0, // �p�x
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
            DrawFormatString(10, 10, GetColor(255, 225, 255), "�G��idol�������ł�");
        }*/
        /*if (imageWalk == -1) {
            DrawFormatString(10, 30, GetColor(255, 255, 255), "�G��Walk���Ȃ��ł�");
        }*/
    }
}

void Enemy::Collision(Player& player, Enemy enemy[], int enemyCount) {
    if (!isDead) {
        directionX = player.GetX() - x; // �v���C���[�Ƃ�X���W�̍�
        directionY = player.GetY() - y; // �v���C���[�Ƃ�Y���W�̍�
        length = sqrt(directionX * directionX + directionY * directionY); // �v���C���[�Ƃ̋���
        isStop = length < minDistance;
        isAttackLength = length < minDistance;

        float minCatchDistance = 200;  // �v���C���[�ƓG�̍ŏ��������L�^����ϐ�
        Enemy* caughtEnemy = nullptr;     // �L���b�`���ꂽ�G�̃|�C���^

        // �v���C���[����������������Δ�����悤�Ƀx�N�g���𒲐�
        if (!isCaught && !isExplosion && !isSmoke) {
            if (length > 0.0f && length < 100) {
                player.SetIsCollisionEnemy(TRUE);

                // �m�[�}���C�Y
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

        // �U�����ꂽ����
        if (player.GetIsBlow()) {
            if (!isCaught && !isExplosion && !isSmoke) {
                if (length < 200) {  // �v���C���[�Ƃ̋�����200�ȉ��Ȃ�
                    if ((player.GetIsIdleBack() == false && directionX < 50) // �����ĂȂ������������炢�����؂�
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
            if (this == &enemy[i]) continue;  // �����͊܂߂Ȃ�
            if (enemy[i].isDead) continue; // ���񂾓G�͊܂߂Ȃ�
            if (enemy[i].isSmoke) continue; // ���񂾓G�͊܂߂Ȃ�

            // ���̓G�Ƃ̋������v�Z
            float directionToEnemyX = enemy[i].x - this->x;
            float directionToEnemyY = enemy[i].y - this->y;
            float distanceToEnemy = sqrt(directionToEnemyX * directionToEnemyX + directionToEnemyY * directionToEnemyY);


            // Throw�̓����蔻��
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

            // ��������������Δ�����悤�Ƀx�N�g���𒲐�
            if (distanceToEnemy > 0.0f && distanceToEnemy < minDistance) {

                // �m�[�}���C�Y
                float lengthX = directionToEnemyX / distanceToEnemy;
                float lengthY = directionToEnemyY / distanceToEnemy;

                // �ړ��x�N�g���ɉ����A�G����������֐i�܂Ȃ��悤�ɂ���
                this->avoidX -= lengthX;
                this->avoidY -= lengthY;
            }
        }
    }
}