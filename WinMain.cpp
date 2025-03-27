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


// DX���C�u�����̏�����
bool InitDX() {

	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_DEPTH);

	// �E�B���h�E���[�h�̐ݒ�
	//ChangeWindowMode(TRUE);

	// ��ʔ䗦��ς����邩�ǂ���
	SetWindowSizeChangeEnableFlag(TRUE);

	// DX���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	// �`���𗠉�ʂɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	return true;
}

// enemy�̏����ʒu
void InitEnemySpawn(Enemy enemy[], int& enemyIndex) {
	// �G�̏����ʒu�������_���ɐݒ�
	for (int i = 0; i < FIRST_ENEMY_INDEX; i++) {

		// x = 300�`1920�܂Ń����_��
		float enemyX = (rand() % (FIRST_ENEMY_X_MAX - FIRST_ENEMY_X_MIN)) + FIRST_ENEMY_X_MIN;

		// y = -70�`430�܂Ń����_��
		float enemyY = (rand() % (FIRST_ENEMY_Y_MAX - FIRST_ENEMY_Y_MIN)) + FIRST_ENEMY_Y_MIN;

		// ���߂����W��enemy�ɓn��
		enemy[enemyIndex].SetX(enemyX);
		enemy[enemyIndex].SetY(enemyY);

		// ���̔z���
		enemyIndex++;
	}
}

// �G�l�~�[�̃X�|�[������
void EnemySpawn(Enemy enemy[], float playerX, float cameraX, float lastSpawnDistance, int& enemyIndex) {

	// 500�s�N�Z���ړ����閈�ɐV�����X�|�[��������
	if (playerX - lastSpawnDistance >= ENEMY_SPAWN_DISTANCE) {
		lastSpawnDistance = playerX;  // �Ō�ɃX�|�[�������������X�V

		// �S�[���t�߂ł̓X�|�[�������Ȃ�
		if (playerX < ENEMY_DOESNT_SPAWN_DISTANCE) {

			// �V�����G�������_���ɃX�|�[��
			// MAX_ENEMY_INDEX�𒴂��ĂȂ�������
			if (enemyIndex < MAX_ENEMY_INDEX) {

				// �G�l�~�[��5�̐���
				for (int i = 0; i < ADDITIONAL_ENEMIES; i++) {

					// x = +1920�`2920�܂�(�v���C���[�̈ʒu���猩��)
					float enemyX = (rand() % (ENEMY_X_MAX - ENEMY_X_MIN)) + ENEMY_X_MIN + cameraX;

					// y = 70�`430�܂�
					float enemyY = (rand() % (ENEMY_Y_MAX - ENEMY_Y_MIN)) + ENEMY_Y_MIN;

					// �ݒ肵�����W��enemy�ɑ��
					enemy[enemyIndex].SetX(enemyX);
					enemy[enemyIndex].SetY(enemyY);

					// �C���f�b�N�X��1����
					enemyIndex++;
				}
			}
		}
	}
}

// ����
void Collision(Player& player, Enemy enemy[], bool title, int enemyIndex) {

	// �Q�[���V�[���̂ݔ�����s��
	if (!title) {
		// �v���C���[�̔���
		player.Collision();

		// �G�l�~�[�̔���
		for (int i = 0; i < enemyIndex; i++) {
			enemy[i].Collision(player, enemy, enemyIndex);
		}
	}
}

// �s���ƃA�j���[�V����
void Update(Player& player, Enemy enemy[], GameManager& gameManager, float deltaTime, int enemyIndex) {

	if (!gameManager.GetTitle()) {
		// �v���C���[
		player.Update(deltaTime);

		// �A�j���[�V�����𐧌�
		player.UpdateAnimation(deltaTime);

		// �G�l�~�[
		for (int i = 0; i < enemyIndex; i++) {

			enemy[i].Update(player, deltaTime);

			// �A�j���[�V�����𐧌�
			enemy[i].UpdateAnimation(deltaTime);

		}

		// �J�������X�V
		gameManager.Update(player);
	}

}

// �`��
void Display(Player& player, Enemy enemy[], GameManager& gameManager, int enemyIndex) {

	// �w�i����
	gameManager.Display();

	// �Q�[���V�[���Ȃ�
	if (!gameManager.GetTitle()) {

		// �v���C���[�̍��W����ɂ���G�l�~�[���ɕ`��
		for (int i = 0; i < enemyIndex; i++) {
			if (enemy[i].GetY() < player.GetY()) {
				enemy[i].Display(gameManager);
			}
			else {

				// �v���C���[�ɕ߂܂�Ă���ꍇ����ɕ`��
				if (enemy[i].GetIsCaught()) {
					enemy[i].Display(gameManager);
				}
			}
		}

		// �v���C���[��`��
		player.Display();

		// �v���C���[�̍��W��艺�ɂ���ꍇ�ɂ̓v���C���[����ɕ`��
		for (int i = 0; i < enemyIndex; i++) {
			if (enemy[i].GetY() >= player.GetY()) {
				if (!enemy[i].GetIsCaught()) {
					enemy[i].Display(gameManager);
				}
			}
		}

		// UI��`��
		gameManager.DisplayGameUI(player);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand((unsigned int)(time(NULL)));

	float oldTime = GetNowCount();
	float nowTime = 0;
	float deltaTime = 0; // �f���^�^�C�����Ǘ����遪

	int enemyIndex = 0; // �G�̐�

	int lastSpawnDistance = 0; // �Ō�ɓG���X�|�[�������v���C���[�̈ʒu

	Player player;
	Enemy enemy[MAX_ENEMY_INDEX];
	GameManager gameManager(player);

	EnemySpawn(enemy, player.GetX(), gameManager.GetCameraX(), lastSpawnDistance, enemyIndex);

	// update�݂����Ȃ���
	while (TRUE) {
		// deltaTime���쐬
		nowTime = GetNowCount();

		// deltaTime��0�ɂȂ�Ȃ��悤��max�Ő���
		// nowTime, oldTime���ɒP�ʂ��~���b�̂��߁A1000�Ŋ���
		deltaTime = max((nowTime - oldTime) / 1000.0f, 0.01f);

		// ���̃t���[���̂��߂�oldTime��nowTime����
		oldTime = nowTime;

		// �X�N���[���ɉf���Ă���̂�����
		ClearDrawScreen();

		// �V�[���𔻒�
		gameManager.SceneManager(player);

		// ����
		Collision(player, enemy, gameManager.GetTitle(), enemyIndex);

		// �s��
		Update(player, enemy, gameManager, deltaTime, enemyIndex);

		// �G���X�|�[�����邩����
		EnemySpawn(enemy, player.GetX(), gameManager.GetCameraX(), lastSpawnDistance, enemyIndex);

		// �`��
		Display(player, enemy, gameManager, enemyIndex);

		// ESC�L�[�������ꂽ�烋�[�v���甲����(�Q�[�����I��)
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		// Windows �V�X�e�����炭�������������
		if (ProcessMessage() == -1) break;

		// ����ʂɕ`�悵�����̂��f��
		ScreenFlip();
	}

	// DX���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I�� 
	return 0;
}

/* void DisplayGameManager(GameManager& gameManager){ gameManager->Display() }
������Ăяo���Ɓ� DisplayGameManager(&Camera) �����z�֐��Ȃ̂ł���ŃJ������Display���N������
(���z�֐��łȂ��ꍇ�͐e�N���X(GameManager��Display���N������))*/