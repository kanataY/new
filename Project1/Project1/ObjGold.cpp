//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjGold.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjGold::CObjGold(float x,float y)
{
	m_px = x;
	m_py = y;

}

//イニシャライズ
void CObjGold::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_gold_vy = 0;
	m_gold_flag = false;
	m_hero_flag = false;

	m_switch_time = 0;
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
void CObjGold::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	CObjswitch* swch = (CObjswitch*)Objs::GetObj(OBJ_SWITCH);
	Hit();
	//金塊が落ちれる時自由落下をつける
	if (m_gold_vy == 0)
		m_vy += 9.8 / (250.0f);
	else
		m_vy = 0.0f;//その場にとどめておく（金塊にかなさる）

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py +32.0f);

	float c = m_px + block->GetScroll();

	block->BlockHit(&c, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type,true, false,0, false,false
	);

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;
}

//ドロー
void CObjGold::Draw()
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
	dst.m_bottom = 32.0f + m_py +32.0f;

	//描画
	Draw::Draw(4, &src, &dst, c, 0.0f);

}

void CObjGold::Hit()
{
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//スイッチの情報取得
	CObjswitch* swch=(CObjswitch*)Objs::GetObj(OBJ_SWITCH);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	if (m_gold_vy == 0 && m_hit_down == false)
	{
		//ヒットボックスに触れている時
		if (hit->CheckObjNameHit(OBJ_GOLD) != nullptr)
		{
			//ゴールドに当たっているなら動きを止める
			m_vy = 0.0f;
			m_gold_vy = 1;
		}
	}
	//金塊の下側にスイッチが当たっている時
	if (hit->CheckObjNameHit(OBJ_SWITCH) != nullptr&& m_hit_down == false)
	{
		//スイッチのフラグをオンにする
		swch->SetSwitchFlag(true);
		m_switch_time++;//当たってからの時間を計る
		
		//計測から5F後に金塊の動きを止める
		if (m_switch_time >=8)
		{
			m_vy = 0.0f;
			m_gold_vy = 1;	
		}
	}
	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		//どの角度で当たっているかを確認
		HIT_DATA** hit_data;                        //当たったときの細やかな情報を入れるための構造体
		hit_data = hit->SearchObjNameHit(OBJ_HERO);  //hit_dataにHitBoxとの情報を入れる

		for (int i = 0; i < hit->GetCount(); i++)
		{
			if (hit_data[i] != NULL)
			{
				float r2 = hit_data[i]->r;

				//主人公が上に乗っかている場合主人公の移動量を0にする。
				if (r2 >= 20&& r2 < 150)
				{
					//上
					//主人公が金塊の左右に当たった時、主人公がブロックを登ろうとしてるときに解除
					if (hero->SetG() == false && hero->Gety() == false)
						hero->SetY(m_py - 30.0f);//主人公を金塊の上に貼り付けにする。
				}
			}
		}
	}
	else
	{
		m_hero_flag = false;
	}
}