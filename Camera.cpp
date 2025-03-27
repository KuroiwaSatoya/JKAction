#include "Camera.h"

Camera::Camera(Player& player) {

	firstCameraX = player.GetFirstPositionX(); // �J������X���W
	cameraX = firstCameraX;

	/*�J�����ƌ����Ă���ʂ��ړ����Ă���킯�ł͂Ȃ�
	�v���C���[�̓����ɍ��킹�đ��̃I�u�W�F�N�g��
	�v���C���[�̓����Ƃ͔��΂ɓ����Ă��邾��*/
}

void Camera::Update(Player& player) {

	// �v���C���[�̈ړ��ʂɍ��킹�ăJ�����𓮂���
	cameraX = player.GetX() - firstCameraX;

}