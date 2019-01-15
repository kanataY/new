#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：主人公のヒットボックスのみ
class CObjhero_hitbox : public CObj
{
public:
	CObjhero_hitbox();
	~CObjhero_hitbox() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	bool HitCheck() { return hit_check; } //金塊の上にヒットしているかどうかを渡す
	float GetY() { return m_py; }			//ヒットボックスのY位置を渡す。

private:
	float m_px;//位置
	float m_py;

	bool hit_check;  //金塊に当たっていたらture:
};