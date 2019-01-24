//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
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
	m_speed = 0.8f;
	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_jump_flag = false;
	m_pos = 1.0f;//左向き
	m_block_type = 0; //踏んでいるblockの種類を確認用

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_JUMP_ENEMY, 1);
}

//アクション
void CObjJumpEnemy::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);

	float c = m_px + block->GetScroll();

	block->BlockHit(&c, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type,false, false,0, false,false
	);

	//左側が壁に当たると反転
	if (m_hit_left == true)
	{
		//右向きに
		m_pos = 1.0f;
	}
	//右側が壁に当たると反転
	if (m_hit_right == true)
	{
		//左向きに
		m_pos = 0.0f;
	}
	//ブロックに触れてない時
	if (m_hit_down == false)
	{
		//ジャンプフラグ::true
		m_jump_flag = true;
	}
	else
	{
		//触れていないときはfalseにしておく
		m_jump_flag = false;
	}
	//ジャンプフラグがtrueの時
	if (m_jump_flag == true)
	{
		//ジャンプ中の時間を計測
		m_jump_time++;
	}
	else
	{
		//飛んでない時は0にしておく
		m_jump_time = 0;
	}
	//敵の向きによって移動方向を変える
	if (m_pos == 0.0f)
	{
		m_vx += m_speed;
		//ジャンプ時間が0より上かつ30より下なら上に飛ぶ
		if (m_jump_time >= 0 && m_jump_time < 40)
			m_vy += -m_speed;
		else
			m_vy -= -m_speed;

	}
	if (m_pos == 1.0f)
	{
		m_vx -= m_speed;
		//ジャンプ時間が0より上かつ30より下なら上に飛ぶ
		if (m_jump_time >= 0 && m_jump_time < 40)
			m_vy += -m_speed;
		else
			m_vy -= -m_speed;

	}
	//自由落下運動
	m_vy += 9.8 / (16.0f);

	//摩擦
	m_vx += -(m_vx * 0.16f);
	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	//削除条件　コインに当たる、下に落ちる
	if(m_py > 1500 || hit->CheckObjNameHit(OBJ_COIN) != nullptr) //下に落ちたら死ぬ
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;//消滅処理は、ここでアクションメゾッドを終了させる
	}
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
	src.m_bottom = 128.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f*m_pos) + m_px + block->GetScroll();
	dst.m_right = (64.0f - 64.0f*m_pos) + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//描画
	Draw::Draw(6, &src, &dst, c, 0.0f);
}