//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjRushEnemy.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjRushEnemy::CObjRushEnemy(float x, float y)
{
	m_px = x;
	m_py = y;

}

//イニシャライズ
void CObjRushEnemy::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_speed = 1.0f;
	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
	m_ani_max_time = 12; //アニメーション間隔幅

	m_move = true;
	m_pos = 1.0f;//左向き
	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //踏んでいるblockの種類を確認用

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 64, 32, ELEMENT_ENEMY, OBJ_RUSH_ENEMY, 1);
}

//アクション
void CObjRushEnemy::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	//アニメーションーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	m_ani_time++;//フレーム動作感覚タイムを進める
	if (m_ani_time > m_ani_max_time)//フレーム動作感覚タイムが最大まで行ったら
	{
		m_ani_frame++;//フレームを進める
		m_ani_time = 0;
	}
	if (m_ani_frame == 2)//フレームが最後まで進んだら戻す
	{
		m_ani_frame = 0;
	}
	//アニメーション終了－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

	

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py+32);

	float c = m_px + block->GetScroll();

	block->BlockHit(&c, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type,false, false,0, false,false
	);

	Hit(); //当たり判定

	//左側が壁に当たると反転
	if (m_hit_left == true)
	{
		m_move = true;
	}
	//右側が壁に当たると反転
	if (m_hit_right == true)
	{
		m_move = false;
	}

	//移動方向
	if (m_move == true)
	{
		m_vx -= m_speed;
		m_pos = 1.0f;
	}
	if (m_move == false)
	{
		m_vx += m_speed;
		m_pos = 0.0f;
	}

	
	if (hit->CheckElementHit(ELEMENT_NULL)==false)
	{
		//自由落下運動
		m_vy += 9.8 / (16.0f);
	}
	m_vx += -(m_vx * 0.16f);
	//位置の更新
	m_px += m_vx;
	m_py += m_vy;
}

//ドロー
void CObjRushEnemy::Draw()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

				//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + m_ani_frame * 64;
	src.m_right = 64.0f + m_ani_frame * 64;
	src.m_bottom =128.0f;

	//表示位置の設定
	dst.m_top = -20.0f + m_py;
	dst.m_left = (64.0f*m_pos) + m_px + block->GetScroll();
	dst.m_right = (64.0f-64.0f*m_pos) + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//描画
	Draw::Draw(5, &src, &dst, c, 0.0f);

}

//当たり判定
void CObjRushEnemy::Hit()
{
	//HitBox情報取得
	CHitBox* hit = Hits::GetHitBox(this);
	//スイッチの情報取得
	CObjswitch* swch = (CObjswitch*)Objs::GetObj(OBJ_SWITCH);
	//スイッチを踏んでいる時の処理--------------------------------------------------------------------------------
	if (hit->CheckObjNameHit(OBJ_SWITCH) != nullptr)
	{
		//スイッチのフラグをオンにする
		swch->SetSwitchFlag(true);
	}
	else
	{//スイッチのフラグをオフにする
		swch->SetSwitchFlag(false);
	}
	//---------------------------------------------------------------------------------------------------------------

	//金塊に当たっている時
	if (hit->CheckObjNameHit(OBJ_GOLD) != nullptr)
	{
		//どの角度で当たっているかを確認
		HIT_DATA** hit_data;                        //当たったときの細やかな情報を入れるための構造体
		hit_data = hit->SearchObjNameHit(OBJ_GOLD);  //hit_dataにHitBoxとの情報を入れる

		for (int i = 0; i < hit->GetCount(); i++)
		{
			if (hit_data[i] != NULL)
			{

				float r2 = hit_data[i]->r;

				//上に乗れるようにする
				if (r2 >= 210 && r2 < 340)
				{
					//また、地面に当たっている判定にする
					m_vy = 0.0f;
					m_hit_down = true;
				}
				if (r2 > 160 && r2 < 200)
				{
					//左
					m_hit_right = true;

				}

				if (r2 <= 45 && r2>=0 || r2 > 330)
				{
					//右
					m_hit_left = true;
				}
			}
		}
	}
}