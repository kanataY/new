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
	float m_vx;//移動
	float m_vy;
	//当たり判定
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
	//どっちの向きに当たってるかの確認
	float m_pos;
	//ブロックのタイプ確認
	int m_block_type;
	
};