#include "Scene.h"
#include "DxLib.h"

Scene::Scene() {
    type = SceneType::TITLE;

}

void Scene::Update() override {

    //�G���^�[�L�[����������GAME�V�[���ɂȂ�
    if (type == SceneType::TITLE) {
        if (CheckHitKey(KEY_INPUT_RETURN)) {
            type = SceneType::GAME;
        }
    }
    else if (type == SceneType::GAME) {
        // �Q�[���V�[�����ɃV�[����؂�ւ������ꍇ����������
        // ����������������
    }
}