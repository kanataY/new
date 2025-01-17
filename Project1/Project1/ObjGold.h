#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：金塊
class CObjGold : public CObj
{
public:
	CObjGold(float x,float y);
	~CObjGold() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	float GetX() { return m_px; }						//m_px,m_pyの値を渡す
	float GetY() { return m_py; }
	bool  GetD() { return m_hit_down; }
	bool  GetGoldFlag() { return m_gold_flag; }         //
	bool GetGoldHero() { return m_hero_flag; }
	bool  GetGoldSwitch() { return m_switch_gold_flag; } //ゴールドがスイッチを踏んだかどうかを渡す
	void  Hit();

private:
	float m_px;//位置
	float m_py;
	float m_vy; //移動量
	float m_vx;
	int   m_gold_vy;   //金塊が落ちれるかどうか
	int  m_switch_time;//金塊がスイッチをつぶすのを防ぐためのやつ

	bool  m_gold_flag; //フラグ
	bool  m_hero_flag;
	bool  m_switch_gold_flag; //ゴールドがスイッチ押したときに使う変数
	bool  m_audio;     //音を一回だけ鳴らす

	//blockとの衝突状態確認用
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//踏んでいるblockの種類を確認用
	int m_block_type;
};