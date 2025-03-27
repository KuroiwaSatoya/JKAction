#include "Scene.h"
#include "DxLib.h"

Scene::Scene() {
    type = SceneType::TITLE;

}

void Scene::Update() override {

    //エンターキーを押したらGAMEシーンになる
    if (type == SceneType::TITLE) {
        if (CheckHitKey(KEY_INPUT_RETURN)) {
            type = SceneType::GAME;
        }
    }
    else if (type == SceneType::GAME) {
        // ゲームシーン中にシーンを切り替えたい場合があったら
        // ここを書き換える
    }
}