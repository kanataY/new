#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//オブジェクト：ランナー
class CObjHero : public CObj
{
public:
	CObjHero();
	~CObjHero() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	void HitBox();  //当たり判定関連
	float GetX() { return m_px; }						//m_px,m_pyの値を渡す
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }						//m_vx,m_vyの値を渡す
	float GetVX() { return m_vx; }
	void  SetX(float x) { m_px = x; }					//m_px,m_pyの値をほかのcppでもいじれるようにする
	void  SetY(float y) { m_py = y; }
	void  SetVX(float x) { m_vx = x; }					//m_vx,m_vyの値をほかのcppでもいじれるようにする
	void  SetVY(float y) { m_vy = y; }
private:
	float m_px;			//位置
	float m_py;
	float m_vx;			//移動ベクトル
	float m_vy;
	float m_speed;      //主人公の移動量のスピード管理

	//制御系---------
	bool m_gold_flag;  //金塊を出しすぎないようにするため
	bool m_gold_spawn; //金塊を出せる位置を決める

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