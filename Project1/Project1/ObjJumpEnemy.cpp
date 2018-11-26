//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjJumpEnemy.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjJumpEnemy::CObjJumpEnemy(float x, float y)
{
	m_px = x;
	m_py = y;

}

//イニシャライズ
void CObjJumpEnemy::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //踏んでいるblockの種類を確認用

					  //HitBox
	Hits::SetHitBox(this, m_px, m_py, 64, 32, ELEMENT_NULL, OBJ_GOLD, 1);
}

//アクション
void CObjJumpEnemy::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//自由落下運動
	m_vy += 9.8 / (16.0f);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py + 32.0f);

	float c = m_px + block->GetScroll();

	block->BlockHit(&c, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type,false
	);

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;
}

//ドロー
void CObjJumpEnemy::Draw()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

				//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py + 32.0f;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 32.0f + m_py + 32.0f;

	//描画
	Draw::Draw(4, &src, &dst, c, 0.0f);

}