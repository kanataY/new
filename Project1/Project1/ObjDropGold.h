#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：針
class CObjDropGold : public CObj
{
public:
	CObjDropGold(float x, float y);
	~CObjDropGold() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	float m_px;//位置
	float m_py;

};