#include "BGM.h"
#include "DxLib.h"

BGM::BGM() {

    //BGMのファイル
    titleBgm = LoadSoundMem("Sounds/Title.mp3");
    gameBgm = LoadSoundMem("Sounds/Game.mp3");
}

void BGM::Update(Scene& scene) {

    // タイトルシーンだったら
    if (scene.GetType() == Scene::SceneType::TITLE) {
        if (CheckHitKey(KEY_INPUT_RETURN)) { // ←これシーンが切り替わったらにできるんじゃ？
            if (CheckSoundMem(titleBgm) == FALSE) {
                StopSoundMem(gameBgm);
                PlaySoundMem(titleBgm, DX_PLAYTYPE_LOOP);
            }
        }
    }
    // ゲームシーンだったら
    else if (scene.GetType() == Scene::SceneType::GAME) {
        if (CheckSoundMem(gameBgm) == FALSE) {
            StopSoundMem(titleBgm);
            PlaySoundMem(gameBgm, DX_PLAYTYPE_LOOP);
        }
    }
}