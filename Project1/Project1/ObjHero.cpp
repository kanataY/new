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
	m_py = 400.0f;	//位置
	m_vx = 0.0f;
	m_vy = 0.0f;	//移動ベクトル
	m_ppx = 0;
	m_ppy = 0;
	m_gold_time = 100;
	con = 0;
	m_speed = 0.8f;
	m_pos = 0.0f;//右向き
	m_gold_flag = false;
	m_gold_spawn = false;
	m_gold_Y = false;
	m_gold_M = false;
	m_coinshot_flag = false;

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
	Hits::SetHitBox(this, m_px, m_py, 37, 50, ELEMENT_HERO, OBJ_HERO, 1);
}

//アクション
void CObjHero::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	CObjCoin* coin = ( CObjCoin*)Objs::GetObj(OBJ_COIN);
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
	m_gold_time++;//金塊の間隔を増やす

	m_ppx = (m_px - block->GetScroll()) / 64; //主人公の位置からマップの位置を取ってくる
	m_ppy = m_py / 64;

	if(m_pos == 0.0f) //右向きの時は調整する。
		m_ppx += 0.8f;		//四捨五入する準備、調整する

	m_ppy += 0.5f;
	m_ppx = (int)m_ppx;	//int型に変更して四捨五入する
	m_ppy = (int)m_ppy;

	if (block->GetMapRecord(m_ppx + 1, m_ppy) == 0 && m_pos == 0.0f ||
		block->GetMapRecord(m_ppx - 1, m_ppy) == 0 && m_pos == 1.0f)//今いる位置の右側、左側がブロックだったら金塊を置けないようにする
	{
		if (Input::GetVKey('C') == true)  //金塊を置く
		{
			//金塊は一度に一回だけ,置いた後間隔が空いてから二個目を置ける   空中ではおけないように
			if (m_gold_flag == false && m_gold_spawn == false && m_gold_time > 50 && m_vy == 0.0f)
			{
				//金塊を生成
				//左向き
				if (m_pos == 1)
				{
					CObjGold* kane = new CObjGold(m_px - 75.0f - block->GetScroll(), m_py);
					Objs::InsertObj(kane, OBJ_GOLD, 16);
				}
				else//右向き
				{
					CObjGold* kane = new CObjGold(m_px + 75.0f - block->GetScroll(), m_py);
					Objs::InsertObj(kane, OBJ_GOLD, 16);
				}
				m_gold_flag = true;
				m_gold_time = 0;//間隔をあける
			}
		}
		else
			m_gold_flag = false;
	}

	//コイン攻撃-----------------------------------------------------------------------------
	if (Input::GetVKey('V') == true)//Vで射出(仮)
	{
		//コインを出すフラグがオフでコインが存在しない時
		if (m_coinshot_flag == false&&coin==nullptr)
		{
			//向きによって出す場所を変える
			if (m_pos == 1)//左向き
			{
				//コインを出す
				CObjCoin* coin = new CObjCoin(m_px, m_py+25.0f);
				Objs::InsertObj(coin, OBJ_COIN, 16);
				coin->SetHeroPos(1);//コインに主人公の向きを送る
			}
			else//右向き
			{
				//コインを出す
				CObjCoin* coin = new CObjCoin(m_px+25.0f, m_py+25.0f);
				Objs::InsertObj(coin, OBJ_COIN, 16);
				coin->SetHeroPos(0);//コインに主人公の向きを送る
			}
		}
		//コインを出すフラグをオンにする
		m_coinshot_flag = true;
	}
	else//発射ボタンが押されてない時コイン発射フラグはオフにする
		m_coinshot_flag = false;
	//－－－－－－－－－－－－－－－－－－－--------------------------------------------


	//摩擦
	m_vx += -(m_vx * 0.15f);
	m_vy += -(m_vy * 0.15f);

	//移動終了---------------------------------------------------


	//自由落下運動
	m_vy += 9.8 / (8.0f);

	//ジャンプ終了ーーーーーーーーーーーーーーーーーーーーー

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 15.0f, m_py + 15.0f);

	//当たり判定関連
	HitBox();

	//移動終了---------------------------------------------------
	//ブロックにのぼれるようにする
	float b = m_py + 32.0f;

	if(m_vy == 0.0f)
		block->BlockHit(&m_px, &b, true,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
			&m_block_type, false, true, &m_py,&m_gold_M,true
		);
	

	block->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type, false, false, 0,false,true
	);

	//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

	//プレイヤー死亡処理------------------------------------------------------------------------------
	if (hit->CheckObjNameHit(OBJ_THORN)!=nullptr)
	{
		Scene::SetScene(new CSceneMain());
	}
	//------------------------------------------------------------------------------------------------
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

	CObjGold* gold = (CObjGold*)Objs::GetObj(OBJ_GOLD);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//金塊に当たっていれば登るor乗れるようにする
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

					if (r2 >= 310 && r2 < 340 && m_pos == 1.0f)//金塊の左端にいるときは金塊を置けなくする
					{
						m_gold_spawn = true;
					}
					else
						m_gold_spawn = false;
				}

				if (m_hit_down == true)		//地面or金塊の上にいるとき
				{
					if (/*r2 > 150 &&*/ r2 < 200 && m_pos == 1.0f)
					{
						//左
						m_hit_left = true;  
						m_gold_Y = true;	//金塊側で主人公のｖｙを開放する
						m_py -= 20.0f;		//登れるようにする
						con++;
					}
					else if (/*r2 < 0 && r2>0 ||*/ r2 > 340 && m_pos == 0.0f)
					{
						//右
						m_hit_right = true;
						m_gold_Y = true;	//金塊側で主人公のｖｙを開放する
						m_py -= 24.0f;		//登れるようにする
						con++;
					}
					else
					{
						m_gold_Y = false;
						con = 0;
					}
				}
			}
		}
	}
	else
	{
		m_gold_M = false;
		con = 0;
	}
	
	//どうするか悩み中…
	/*if (con == 1) {
		m_py -= 24.0f; con = 0;
	}
	else if (con > 1 && m_pos == 1.0f)
	{
		m_gold_Y = true;
		m_vx = 0.0f;
		m_px += 0.5f;
		m_vy = 0.0f;
	}
	else if (con > 1 && m_pos == 0.0f)
	{
		m_gold_Y = true;
		m_vx = 0.0f;
		m_px -= 0.5f;
		m_vy = 0.0f;
	}*/

		

	//ヒットボックスに触れていない時
	if (hit->CheckObjNameHit(OBJ_GOLD) == nullptr)
	{
		//金塊から降りているので金塊を置けるようにする。
		m_gold_spawn = false;
	}

}