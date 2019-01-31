//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "Objthorn.h"
#include "GameL\Audio.h"
//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjthorn::CObjthorn(float x, float y)
{
	m_px = x;
	m_py = y;
}
//イニシャライズ
void CObjthorn::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	m_pos = 0.0f;
	m_block_type = 0; //踏んでいるblockの種類を確認用
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_THORN, 1);

}
//アクション
void CObjthorn::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);

	float c = m_px + block->GetScroll();

	block->BlockHit(&c, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type, false, false, 0, false, false
	);

	if (m_hit_up == true)
	{
		m_pos = 1.0f;
	}
	else
	{
		m_pos = 0.0f;
	}
}
//ドロー
void CObjthorn::Draw()
{
	//描画カラー情報　R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 16.0f;
	src.m_bottom = src.m_top + 16.0f;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	if (m_pos == 0.0f)
	{
		//表示位置の設定
		dst.m_top = 0.0f + m_py;
		dst.m_left = 64.0f + m_px + block->GetScroll();
		dst.m_right = 0.0f + m_px + block->GetScroll();
		dst.m_bottom = 64.0f + m_py;
	}
	else
	{
		//表示位置の設定
		dst.m_top = 64.0f + m_py;
		dst.m_left = 64.0f + m_px + block->GetScroll();
		dst.m_right = 0.0f + m_px + block->GetScroll();
		dst.m_bottom = 0.0f + m_py;
	}
	//10番目に登録したグラフィックをsrc・dst・c・の情報を元に描画
	Draw::Draw(10, &src, &dst, c, 0.0);
}