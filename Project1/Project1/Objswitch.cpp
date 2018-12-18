//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "Objthorn.h"
#include "GameL\Audio.h"
//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjswitch::CObjswitch(float x, float y)
{
	m_px = x;
	m_py = y;
	
}
//イニシャライズ
void CObjswitch::Init()
{
	switch_on_flag = false;
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 25, ELEMENT_ENEMY, OBJ_SWITCH, 1);
}
//アクション
void CObjswitch::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	if (switch_on_flag == false)
	{
		hit->SetPos(m_px + block->GetScroll(), m_py + 9.0f);
	}
	else
	{
		hit->SetPos(m_px + block->GetScroll(), m_py + 18.0f);
	}
}
//ドロー
void CObjswitch::Draw()
{
	//描画カラー情報　R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

    //切り取り位置の設定
	src.m_top = 0.0f;
	src.m_bottom = 128.0f;
	if (switch_on_flag == false)
	{
		src.m_left = 0.0f;
		src.m_right = 64.0f;
	}
	else
	{
		src.m_left = 64.0f;
		src.m_right = 128.0f;
	}
	

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = -32.0f + m_py;
	dst.m_left = 64.0f + m_px + block->GetScroll();
	dst.m_right = 0.0f + m_px + block->GetScroll();
	dst.m_bottom = 32.0f + m_py;

	//9番目に登録したグラフィックをsrc・dst・c・の情報を元に描画
	Draw::Draw(9, &src, &dst, c, 0.0);
}