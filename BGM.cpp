#include "BGM.h"
#include "DxLib.h"

BGM::BGM() {

    //BGM�̃t�@�C��
    titleBgm = LoadSoundMem("Sounds/Title.mp3");
    gameBgm = LoadSoundMem("Sounds/Game.mp3");
}

void BGM::Update(Scene& scene) {

    // �^�C�g���V�[����������
    if (scene.GetType() == Scene::SceneType::TITLE) {
        if (CheckHitKey(KEY_INPUT_RETURN)) { // ������V�[�����؂�ւ������ɂł���񂶂�H
            if (CheckSoundMem(titleBgm) == FALSE) {
                StopSoundMem(gameBgm);
                PlaySoundMem(titleBgm, DX_PLAYTYPE_LOOP);
            }
        }
    }
    // �Q�[���V�[����������
    else if (scene.GetType() == Scene::SceneType::GAME) {
        if (CheckSoundMem(gameBgm) == FALSE) {
            StopSoundMem(titleBgm);
            PlaySoundMem(gameBgm, DX_PLAYTYPE_LOOP);
        }
    }
}