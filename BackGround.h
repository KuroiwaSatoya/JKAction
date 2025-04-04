#pragma once
#include "GameManagerMain.h"
#include "Camera.h"
#include "Scene.h"

class BackGround : public GameManagerMain {
public:
	BackGround();

	// wiÌ§ä
	void Update() override ;

	// wiÌ`æ
	void Display() override ;

	void SetCamera(Camera* _camera) { camera = _camera; }

	void SetScene(Scene* _scene) { scene = _scene; }

private:

	// æ
	int imageTitle,					// ^CgæÊÌæ
		imageBackGroundSky,			// wiÌóÌæ
		imageBackGroundMountain,	// wiÌRÌæ
		imageBackGroundTree,		// wiÌØÌæ
		imageBackGroundGround,		// wiÌnÊÌæ
		imageGoalSignBoard,			// S[ÌÅÂ
		imageStartRightSignBoard;	// X^[gn_ÌEîóÅÂ

	// æÌc¡
	int widthBackGround,			// wiÌæÌ
		heightBackGround,			// wiÌæÌ³
		widthGoalSignBoard,			// S[ÌÅÂÌ
		heightGoalSignBoard,		// S[ÌÅÂÌ³
		widthRightSignBoard,		// X^[gÌÅÂÌ
		heightRightSignBoard;		// X^[gÌÅÂÌ³

	// gå¦
	float signBoardScale;			// ÅÂÌgå¦

	// wiÌÚ®
	float backGroundX,				// wiÌÚ®Ê
		loopX,						// [vp
		mountainLoopX;				// RÍ1/2Ì¬xÅ[v·é½ßRpÌ[vÏðpÓ

	Camera* camera = nullptr;		// CameraðÛ
	Scene* scene = nullptr;			// SceneðÛ

};