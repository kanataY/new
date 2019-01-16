#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ゴール
class CObjGoal : public CObj
{
public:
	CObjGoal(float x, float y);
	~CObjGoal() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	void Hit();     //ヒット関連
private:
	float m_px;//位置
	float m_py;

	float  m_hit_draw; //描画の横幅　主人公に当たったら変更
};