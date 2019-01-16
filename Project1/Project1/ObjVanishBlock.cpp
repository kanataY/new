//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"

#include "ObjVanishBlock.h"
#include "GameL\Audio.h"
//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjVanishBlock::CObjVanishBlock(float x, float y)
{
	m_px = x;
	m_py = y;
}
//イニシャライズ
void CObjVanishBlock::Init()
{
	m_hit_draw = 64.0f;
	m_swich_flag = false;

	//当たり判定用HitBoxを作成
	//Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_GOAL, 1);
}
//アクション
void CObjVanishBlock::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	//CHitBox* hit = Hits::GetHitBox(this);
	//hit->SetPos(m_px + block->GetScroll(), m_py);

	Hit();
}
//ドロー
void CObjVanishBlock::Draw()
{
	//描画カラー情報　R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.f;
	src.m_left = 0.0f;
	src.m_right = m_hit_draw;
	src.m_bottom = m_hit_draw;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//8番目に登録したグラフィックをsrc・dst・c・の情報を元に描画
	if (m_swich_flag == false)
	Draw::Draw(1, &src, &dst, c, 0.0);
}

//ヒット関連
void CObjVanishBlock::Hit()
{
	//スイッチの情報を持ってくる
	CObjswitch* swi = (CObjswitch*)Objs::GetObj(OBJ_SWITCH);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	if (swi->GetSwitchFlag() == true) //スイッチが押されていた場合
	{
		if(block->GetSwichTime() > 160000)//スイッチが押されてからしばらくしたら描画を消す
		m_swich_flag = true;
	}
	else
	{
		m_swich_flag = false;//押されていない場合は描画を消さないようにする
	}
}