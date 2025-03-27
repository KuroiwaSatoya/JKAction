#pragma once
#include "GameManagerMain.h"
#include "Camera.h"

class BackGround : public GameManager {
public:
	BackGround();

	// �w�i�̐���
	void Update(Camera& camera);

	// �w�i�̕`��
	void Display(Camera& camera, bool title, bool gameScene);

private:

	// �摜
	int imageTitle,					// �^�C�g����ʂ̉摜
		imageBackGroundSky,			// �w�i�̋�̉摜
		imageBackGroundMountain,	// �w�i�̎R�̉摜
		imageBackGroundTree,		// �w�i�̖؂̉摜
		imageBackGroundGround,		// �w�i�̒n�ʂ̉摜
		imageGoalSignBoard,			// �S�[���̊Ŕ�
		imageStartRightSignBoard;	// �X�^�[�g�n�_�̉E���Ŕ�

	// �摜�̏c��
	int widthBackGround,			// �w�i�̉摜�̕�
		heightBackGround,			// �w�i�̉摜�̍���
		widthGoalSignBoard,			// �S�[���̊Ŕ̕�
		heightGoalSignBoard,		// �S�[���̊Ŕ̍���
		widthRightSignBoard,		// �X�^�[�g�̊Ŕ̕�
		heightRightSignBoard;		// �X�^�[�g�̊Ŕ̍���

	// �g�嗦
	float signBoardScale;			// �Ŕ̊g�嗦

	// �w�i�̈ړ�
	float backGroundX,				// �w�i�̈ړ���
		loopX,						// ���[�v�p
		mountainLoopX;				// �R��1/2�̑��x�Ń��[�v���邽�ߎR�p�̃��[�v�ϐ���p��

};