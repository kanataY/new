//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjGolem.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjGolem::CObjGolem(float x, float y)
{
	m_px = x;
	m_py = y;

}

//イニシャライズ
void CObjGolem::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_speed = 0.5f;
	m_audio_flag = false;
	m_audio_footsteps_flag = false;

	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
	m_ani_max_time = 15; //アニメーション間隔幅

	m_ani_time_del = 0;
	m_ani_frame_del = 0;  //静止フレームを初期にする
	m_ani_max_time_del = 10; //アニメーション間隔幅

	m_move = true;
	m_pos = 0.0f;//左向き
				 //blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //踏んでいるblockの種類を確認用

	m_del = false;//死ぬときのフラグ
	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 40, 64, ELEMENT_ENEMY, OBJ_GOLEM, 1);
}

//アクション
void CObjGolem::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//主人公の情報を持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//アニメーションーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	m_ani_time++;//フレーム動作感覚タイムを進める
	if (m_ani_time > m_ani_max_time)//フレーム動作感覚タイムが最大まで行ったら
	{
		m_ani_frame++;//フレームを進める
		m_ani_time = 0;
	}
	if (m_ani_frame == 8)//フレームが最後まで進んだら戻す
	{
		m_ani_frame = 0;
	}

	//砂煙がでるアニメーション時に足音を出す
	if ((m_ani_frame == 3 && m_audio_footsteps_flag == false) || (m_ani_frame == 7 && m_audio_footsteps_flag == false))
	{
		Audio::Start(8);
		m_audio_footsteps_flag = true;	//一回のみ鳴らす
	}

	if(m_ani_frame == 4 || m_ani_frame == 1)//フレームが進んだらもう一度鳴らせるように戻す
	{
		m_audio_footsteps_flag = false;
	}

	//アニメーション終了－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	if (m_pos == 1.0)
	hit->SetPos(m_px+15 + block->GetScroll(), m_py);
	else
		hit->SetPos(m_px+10 + block->GetScroll(), m_py);
	float c = m_px + block->GetScroll();

	block->BlockHit(&c, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type, false,false,0,false,false
	);

	Hit(); //当たり判定

    //左側が壁に当たると反転
	if (m_hit_left == true || hit->CheckObjNameHit(OBJ_HERO) != nullptr && hero->GetHitLeft() == true)
	{
		m_move = true;
	}
	//右側が壁に当たると反転
	if (m_hit_right == true || hit->CheckObjNameHit(OBJ_HERO) != nullptr && hero->GetHitRight() == true)
	{
		m_move = false;
	}

	//移動方向
	if (m_move == false&&m_del==false)
	{
		m_vx += m_speed;
		m_pos = 1.0f;
	}
	if (m_move == true && m_del == false)
	{
		m_vx -= m_speed;
		m_pos = 0.0f;
	}
	
	//自由落下運動
	m_vy += 9.8 / (16.0f);
	
	m_vx += -(m_vx * 0.16f);

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

	//落ちているとき
	if (m_py > 600.0f)
		Audio::Stop(8);    //足音を消す

	//死んだとき音を出す
	if (m_del == true && m_audio_flag == false)
	{
		Audio::Start(7); //崩れる音
		m_audio_flag = true;
	}

	//死亡処理
	if (m_ani_frame_del > 2)
	{
		m_ani_max_time_del = 15;
	}
	if (m_del == true &&m_ani_frame_del<6 )
	{
		m_ani_time_del++;
	}
	if (m_ani_time_del > m_ani_max_time_del)//フレーム動作感覚タイムが最大まで行ったら
	{
		m_ani_frame_del++;//フレームを進める
		m_ani_time_del = 0;
	}
	if (m_ani_frame_del == 5)//フレームが最後まで進んだら戻す
	{
		//ドロップアイテム召喚
		CObjDropGold* drop = new CObjDropGold(m_px, m_py+40);
		Objs::InsertObj(drop, OBJ_DROP_GOLD, 16);

		Audio::Stop(7);//崩れる音を止める
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;//消滅処理は、ここでアクションメゾッドを終了させる
	}
}

//ドロー
void CObjGolem::Draw()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	if (m_del == false)
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame * 64;
		src.m_right = 64.0f + m_ani_frame * 64;
		src.m_bottom = 512.0f;

		//表示位置の設定
		dst.m_top = 0.0f + m_py;
		dst.m_left = (64.0f*m_pos) + m_px + block->GetScroll();
		dst.m_right = (64.0f - 64.0f*m_pos) + m_px + block->GetScroll();
		dst.m_bottom = 64.0f + m_py;

		Draw::Draw(11, &src, &dst, c, 0.0f);
	}
	//描画
	if (m_del == true)
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame_del * 64;
		src.m_right = 64.0f + m_ani_frame_del * 64;
		src.m_bottom = 384.0f;

		//表示位置の設定
		dst.m_top = 0.0f + m_py;
		dst.m_left = (64.0f*m_pos) + m_px + block->GetScroll();
		dst.m_right = (64.0f - 64.0f*m_pos) + m_px + block->GetScroll();
		dst.m_bottom = 64.0f + m_py;
		Draw::Draw(12, &src, &dst, c, 0.0f);
	}
		


}

//当たり判定
void CObjGolem::Hit()
{
	//HitBox情報取得
	CHitBox* hit = Hits::GetHitBox(this);
	
	//金塊に当たっている時
	if (hit->CheckObjNameHit(OBJ_GOLD) != nullptr)
	{
		//どの角度で当たっているかを確認
		HIT_DATA** hit_data;                        //当たったときの細やかな情報を入れるための構造体
		hit_data = hit->SearchObjNameHit(OBJ_GOLD); //hit_dataにHitBoxとの情報を入れる

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

				if (r2 < 45 && r2>0 || r2 > 330)
				{
					//右
					m_hit_left = true;
				}
			}
		}
	}
}