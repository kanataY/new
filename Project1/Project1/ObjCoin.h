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
	float m_px;     //弾丸のX方向の位置用変数
	float m_py;     //弾丸のY方向の位置用変数
	float m_vx;    //弾丸のX方向の速度用変数
	float m_vy;//弾丸のY方向の速度用変数
	int   m_hero_pos;//主人公の向き保存用
	bool   m_del;     //削除チェック

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
	//踏んでいるblockの種類を確認用
	int m_block_type;
};