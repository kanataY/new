#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：突進敵
class CObjGolem : public CObj
{
public:
	CObjGolem(float x, float y);
	~CObjGolem() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	void Hit();     //当たり判定
	float GetX() { return m_px; }						//m_px,m_pyの値を渡す
	float GetY() { return m_py; }
	float GetPos() { return m_pos; }//向きを渡す
	void  SetDelFlag(bool del) { m_del = del; }
private:
	float m_px;//位置
	float m_py;
	float m_vy; //移動量
	float m_vx;
	float m_speed;

	bool  m_audio_flag;  //音楽を止めるよう
	bool  m_audio_footsteps_flag;  //音楽を止めるよう足音要

	//-アニメーション
	int m_ani_time;//アニメーションフレーム動作感覚
	int m_ani_frame;//描画フレーム
	float m_ani_max_time;   //アニメーション動作間隔最大値

	int m_ani_time_del; //死亡アニメーションフレーム動作感覚
	int m_ani_frame_del;//死亡描画フレーム
	float m_ani_max_time_del;   //死亡アニメーション動作間隔最大値

    //blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//向き
	bool m_move;//移動方向
	float  m_pos;//向いてる方向

	//踏んでいるblockの種類を確認用
	int m_block_type;

	//削除チェック
	bool m_del;    
};