//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjHero.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjHero::CObjHero()
{

}

//イニシャライズ
void CObjHero::Init()
{
	m_px = 250.0f;
	m_py = 200.0f;	//位置
	m_vx = 0.0f;
	m_vy = 0.0f;	//移動ベクトル
	
	m_speed = 0.8f;
	m_pos = 0.0f;//右向き
	m_gold_flag = false;
	m_gold_spawn = false;

	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期にする
	m_ani_max_time = 8; //アニメーション間隔幅

	m_ani_change = 2;//アニメーションを2に

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //踏んでいるblockの種類を確認用


	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 60, 64, ELEMENT_HERO, OBJ_HERO, 1);
}

//アクション
void CObjHero::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//補正の情報を持ってくる
	//CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);


	//アニメーションーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	
	if (m_ani_time > m_ani_max_time)//フレーム動作感覚タイムが最大まで行ったら
	{
		m_ani_frame++;//フレームを進める
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)//フレームが最後まで進んだら戻す
	{
		m_ani_frame = 0;
	}
	//アニメーション終了－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

		//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

	if (Input::GetVKey(VK_RIGHT) == true)  //右移動
	{
		m_ani_time++;//フレーム動作感覚タイムを進める
		m_vx += m_speed;
		m_pos = 0.0f;
	}
	if (Input::GetVKey(VK_LEFT) == true)  //左移動
	{
		m_ani_time++;//フレーム動作感覚タイムを進める
		m_vx += -m_speed;
		m_pos = 1.0f;
	}
	if (Input::GetVKey(VK_UP) == true)//上移動
	{
		m_vy += -m_speed*3;
	}
	if (Input::GetVKey(VK_DOWN) == true && m_py < 536)//下移動
	{
		m_vy += m_speed;
	}
	if(Input::GetVKey(VK_RIGHT) != true&& Input::GetVKey(VK_LEFT) != true)
	{
		m_ani_frame = 1;
	}
	//お金を置くーーーーーーーーーーーーー

	if (Input::GetVKey('C') == true)  //金塊を置く
	{
		//金塊は一度に一回だけ
		if (m_gold_flag == false && m_gold_spawn == false)
		{
			//block->SetMap((m_px + 64.0f) / 64.0f, m_py / 64.0f, 2);
			//金塊を生成
			CObjGold* kane = new CObjGold(m_px + 64.0f - block->GetScroll(), m_py);
			Objs::InsertObj(kane, OBJ_GOLD, 16);
			m_gold_flag = true;
		}
	}
	else
		m_gold_flag = false;

	//－－－－－－－－－－－－－－－－－－－


	//摩擦
	m_vx += -(m_vx * 0.15f);
	m_vy += -(m_vy * 0.15f);

	//移動終了---------------------------------------------------


	//自由落下運動
	m_vy += 9.8 / (16.0f);

	//ジャンプ終了ーーーーーーーーーーーーーーーーーーーーー
	//ブロック情報を持ってくる
	//CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//移動終了---------------------------------------------------
	block->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type,false
	);

	//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);


	//当たり判定関連
	HitBox();

	//位置の更新
	m_px += m_vx;
	m_py += m_vy;

}

		

//描画
void CObjHero::Draw()
{
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	//影の描画のためのカラー情報
	float shadowcolor[4] = { 1.0f,1.0f,1.0f,0.4f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	RECT_F src2; //描画元切り取り位置
	RECT_F dst2; //描画先表示位置

	 //切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f + m_ani_frame*64.0f;
	src.m_right = 64.0f+m_ani_frame*64.0f;
	src.m_bottom = 256.0f;

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0*m_pos) + m_px;
	dst.m_right = (64.0f-64.0f*m_pos) + m_px;
	dst.m_bottom = 64.0f + m_py;

	//描画
	Draw::Draw(3, &src, &dst, c, 0.0f);
	
	//残りの数字を描画する
	static wchar_t  c_siro[8];
	static float cl_siro[4] = { 0.0f,0.0f,0.0f,1.0f };
	//swprintf_s(c_siro, L"X %d", m_remaining);
	CDrawFont::StrDraw(c_siro, 735, 16, 32, cl_siro);

	//---------------------------------------------------------------------------------
	//得点の描画ーーーーーーーーーーーーーーーーーーーーーーーーーーー
	float cc[4] = { 0.0f,0.0f,0.0f,1.0f };
	wchar_t str[128];
	swprintf_s(str, L"得点：%d点", ((UserData*)Save::GetData())->m_point);
	Font::StrDraw(str, 350, 16, 32, cc);
	//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
}

void CObjHero::HitBox()
{
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	//CObjGold* gold = (CObjGold*)Objs::GetObj(OBJ_GOLD);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

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

				if (r2 >= 210 && r2 < 340)
				{

					CObjBlock* b = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

					//また、地面に当たっている判定にする
					m_vy = 0.0f;
					m_hit_down = true;
					if (r2 >= 310 && r2 < 340)
					{
						m_gold_spawn = true;
					}
					else
						m_gold_spawn = false;
				}
				if (r2 > 160 && r2 < 200)
				{
					//左
					m_hit_left = true;

					m_py -= 16.0f;
				}

				if (r2 < 45 && r2>0 || r2 > 330)
				{
					//右
					m_hit_right = true;

					m_py -= 10.0f;
				}
			}
		}

	}

	//ヒットボックスに触れていない時
	if (hit->CheckObjNameHit(OBJ_GOLD) == nullptr)
	{
		//金塊から降りているので金塊を置けるようにする。
		m_gold_spawn = false;
	}

}