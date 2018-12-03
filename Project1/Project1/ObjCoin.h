#pragma once
//使用するヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト : 弾丸
class CObjCoin : public CObj
{
public:
	CObjCoin(float x, float y);//コンストラクタ
	~CObjCoin() {};
	void Init();   //イニシャライズ
	void Action(); //アクション
	void Draw();   //ドロー
private:
	float m_x;     //弾丸のX方向の位置用変数
	float m_y;     //弾丸のY方向の位置用変数
	float m_vx;    //弾丸のX方向の速度用変数
	int    m_ani;     //着弾アニメーション用
	int    m_ani_time;//着弾アニメーション削除
	bool   m_del;     //削除チェック
};