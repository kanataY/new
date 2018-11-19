#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ジャンプ敵
class CObjJumpEnemy : public CObj
{
public:
	CObjJumpEnemy(float x, float y);
	~CObjJumpEnemy() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	float GetX() { return m_px; }						//m_px,m_pyの値を渡す
	float GetY() { return m_py; }

private:
	float m_px;//位置
	float m_py;
	float m_vy; //移動量
	float m_vx;

	//-アニメーション
	int m_ani_time; //アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値
	int m_ani_change; //アニメーション変更変数

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//踏んでいるblockの種類を確認用
	int m_block_type;
};