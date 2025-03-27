#pragma once
#include "GameManagerMain.h"
#include "Camera.h"
#include "Scene.h"

class BackGround : public GameManagerMain {
public:
	BackGround();

	// �w�i�̐���
	void Update() override ;

	// �w�i�̕`��
	void Display() override ;

	void SetCamera(Camera* _camera) { camera = _camera; }

	void SetScene(Scene* _scene) { scene = _scene; }

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

	Camera* camera = nullptr;		// Camera��ێ�
	Scene* scene = nullptr;			// Scene��ێ�

};