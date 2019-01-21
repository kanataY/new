#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：ゴール
class CObjVanishBlock : public CObj
{
public:
	CObjVanishBlock(float x, float y);
	~CObjVanishBlock() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	void Hit();     //ヒット関連
private:
	float m_px;//位置
	float m_py;

	float  m_hit_draw; //描画の横幅　主人公に当たったら変更
	float  m_draw_right;    //横の描画
	float  m_draw_bottom;	//縦の描画
	bool   m_swich_flag;     //スイッチが押されているかどうかを入れる変数
};
