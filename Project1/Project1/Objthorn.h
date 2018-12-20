#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：針
class CObjthorn : public CObj
{
public:
	CObjthorn(float x, float y);
	~CObjthorn() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
private:
	float m_px;//位置
	float m_py;
	
};