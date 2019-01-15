#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：突進敵
class CObjGolemJudgment : public CObj
{
public:
	CObjGolemJudgment(float x, float y);
	~CObjGolemJudgment() {};
	void Init();	//イニシャライズ
	void Action();
	void Draw();	//ドロー
private:
	float m_px;//位置
	float m_py;
	float m_vy; //移動量
	float m_vx;
};