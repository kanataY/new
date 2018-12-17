#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト : 針
class CObjthorn : public CObj
{
public:
	CObjthorn(float x, float y);//コンストラクタ
	~CObjthorn() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー
private:
	float m_px;     //針のX方向の位置用変数
	float m_py;     //針のY方向の位置用変数
};