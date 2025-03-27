#include "Camera.h"

Camera::Camera(Player& player) {

	firstCameraX = player.GetFirstPositionX(); // カメラのX座標
	cameraX = firstCameraX;

	/*カメラと言っても画面が移動しているわけではなく
	プレイヤーの動きに合わせて他のオブジェクトが
	プレイヤーの動きとは反対に動いているだけ*/
}

void Camera::Update(Player& player) {

	// プレイヤーの移動量に合わせてカメラを動かす
	cameraX = player.GetX() - firstCameraX;

}