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
	if (((UserData*)Save::GetData())->m_stage_count == 4)  //ステージ4
	{
		m_py = 200.0f;	//位置
	}
	else
		m_py = 400.0f;	//位置
	m_vx = 0.0f;
	m_vy = 0.0f;	//移動ベクトル
	m_ppx = 0;
	m_ppy = 0;
	m_gold_time = 100;
	m_coin_time = 100;
	con = 0;
	m_speed = 0.8f;
	m_pos = 0.0f;//右向き
	m_gold_flag = false;
	m_gold_spawn = false;
	m_gold_Y = false;
	m_gold_M = false;
	m_coinshot_flag = false;
	m_goal_flag = false;

	m_r_tap_flag = false;
	m_tap_time = 0;

	m_ani_time = 0;
	m_ani_frame = 1;  //静止フレームを初期にする
	m_ani_max_time = 8; //アニメーション間隔幅

	m_ani_change = 3;//アニメーションを2に

	m_gold_restriction = 0; //金塊の個数制限
	m_gold_restriction_max = 0;
	if((((UserData*)Save::GetData())->m_stage_count == 5))
		m_coin_restriction=8;//コインの個数制限
	else
		m_coin_restriction = 0;//コインの個数制限

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_down_gold = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //踏んでいるblockの種類を確認用
	m_drop_gold = false;//ゴールド拾った時用

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 37, 50, ELEMENT_HERO, OBJ_HERO, 1);
}

//アクション
void CObjHero::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	CObjCoin* coin = (CObjCoin*)Objs::GetObj(OBJ_COIN);    //コイン情報
	CObjGolem* golem = (CObjGolem*)Objs::GetObj(OBJ_GOLEM);	//ゴーレム情報

	//ゴールしてたら動かせないようにする
	if (m_goal_flag == false)
	{
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
		//アニメーション終了−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−

		//HitBoxの位置の変更
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + 15.0f, m_py + 15.0f);

		//移動処理−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
		if (Input::GetVKey(VK_RIGHT) == true && hit->CheckObjNameHit(OBJ_GOLEM) == nullptr)  //右移動
		{
			m_ani_time++;//フレーム動作感覚タイムを進める
			if (hit->CheckObjNameHit(OBJ_GOLEM) != nullptr)
				m_speed = 0.1f;
			m_vx += m_speed;
			m_pos = 0.0f;
		}
		if (Input::GetVKey(VK_LEFT) == true && hit->CheckObjNameHit(OBJ_GOLEM) == nullptr)  //左移動
		{
			m_ani_time++;//フレーム動作感覚タイムを進める
			if (hit->CheckObjNameHit(OBJ_GOLEM) != nullptr)
				m_speed = 0.1f;
			m_vx += -m_speed;
			m_pos = 1.0f;
		}
		if (Input::GetVKey(VK_UP) == true)//上移動
		{
			m_vy += -m_speed * 3;
		}

		//右と左を押していない時アニメーションを左に戻す
		if (Input::GetVKey(VK_RIGHT) != true && Input::GetVKey(VK_LEFT) != true)
		{
			m_ani_frame = 1;
		}

		//--------------------------------------------------------------------------------------
		//お金を置くーーーーーーーーーーーーー
		m_gold_time++;//金塊の間隔を増やす
		m_coin_time++;
		//ステージの番号によっておける金塊の数を設定
		if (m_drop_gold == false)//一度設定した後上書きする用
		{
			switch (((UserData*)Save::GetData())->m_stage_count)
			{
			case 1://ステージ1
				m_gold_restriction_max = 7;
				m_drop_gold = true;
				break;
			case 2://ステージ2
				m_gold_restriction_max = 9;
				m_drop_gold = true;
				break;
			case 3://ステージ3
				m_gold_restriction_max = 12;
				m_drop_gold = true;
				break;
			case 4://ステージ4
				m_gold_restriction_max = 8;
				m_drop_gold = true;
				break;
			case 5://ステージ4
				m_gold_restriction_max = 15;
				m_drop_gold = true;
				break;
			}
		}
		//金塊アイテムに触れたら上限を三個増やす
		if (hit->CheckObjNameHit(OBJ_DROP_GOLD) != nullptr)
		{
			m_gold_restriction_max += 3;
			Audio::Start(2); //金塊アイテムの取得音を鳴らす
		}

		m_ppx = (m_px - block->GetScroll()) / 64; //主人公の位置からマップの位置を取ってくる
		m_ppy = m_py / 64;

		if (m_pos == 0.0f) //右向きの時は調整する。
			m_ppx += 0.7f;		//四捨五入する準備、調整する

		m_ppy += 0.5f;

		m_ppx = (int)m_ppx;	//int型に変更して四捨五入する
		m_ppy = (int)m_ppy;

		if (block->GetMapRecord(m_ppx + 1, m_ppy) == 0 && m_pos == 0.0f ||
			block->GetMapRecord(m_ppx - 1, m_ppy) == 0 && m_pos == 1.0f ||
			block->GetMap(m_ppx + 1, m_ppy) == 97 && m_pos == 0.0f ||
			block->GetMap(m_ppx - 1, m_ppy) == 97 && m_pos == 1.0f)//今いる位置の右側、左側がブロックだったら金塊を置けないようにする
		{
			if (Input::GetVKey('C') == true)  //金塊を置く
			{
				//金塊は一度に一回だけ,置いた後間隔が空いてから二個目を置ける   空中ではおけないように   金塊の個数が指定された数をこえていなければ
				if (m_gold_flag == false && m_gold_spawn == false && m_gold_time > 50 && m_vy == 0.0f&&m_gold_restriction < m_gold_restriction_max)
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
					m_gold_restriction++;
				}
			}
			else
				m_gold_flag = false;
		}

		//コイン攻撃-----------------------------------------------------------------------------
		if (Input::GetVKey('V') == true)//Vで射出
		{
			//コインを出すフラグがオフでコインが存在しない時
			if (m_coinshot_flag == false && m_coin_time > 50 && coin == nullptr&&m_coin_restriction < 10)
			{
				//向きによって出す場所を変える
				if (m_pos == 1)//左向き
				{
					//コインを出す
					CObjCoin* coin = new CObjCoin(m_px, m_py + 25.0f);
					Objs::InsertObj(coin, OBJ_COIN, 16);
					coin->SetHeroPos(1);//コインに主人公の向きを送る
				}
				else//右向き
				{
					//コインを出す
					CObjCoin* coin = new CObjCoin(m_px + 25.0f, m_py + 25.0f);
					Objs::InsertObj(coin, OBJ_COIN, 16);
					coin->SetHeroPos(0);//コインに主人公の向きを送る
				}
				Audio::Start(10); //コインを投げる音を出す。
				//コインを出すフラグをオンにする
				m_coinshot_flag = true;
				m_coin_restriction++;
				m_coin_time = 0;//間隔をあける
			}
		}
		else//発射ボタンが押されてない時コイン発射フラグはオフにする
			m_coinshot_flag = false;
		//−−−−−−−−−−−−−−−−−−−--------------------------------------------
		//スコア----------------------------------------------------------------------------



		//摩擦
		m_vx += -(m_vx * 0.15f);

		//自由落下運動
		m_vy += 9.8 / (8.0f);
		//ジャンプ終了ーーーーーーーーーーーーーーーーーーーーー

		//ブロックにのぼれるようにする
		float b = m_py + 32.0f;


		block->BlockHit(&m_px, &m_py, true,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
			&m_block_type, false, false, 0, false, true
		);

		//当たり判定関連
		HitBox();

		if (m_vy == 0.0f) // 空中にいるときに上れなくする。
			block->BlockHit(&m_px, &b, true,
				&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
				&m_block_type, false, true, &m_py, &m_gold_M, true
			);

		//−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
		//プレイヤーリスタート処理------------------------------------------------------------------------------
		m_tap_time++;
		if (Input::GetVKey('R') == true)
		{
			if (m_tap_time > 180)
			{
				m_r_tap_flag = true;
				m_tap_time = 0;
			}
		}
		else
		{
			m_r_tap_flag = false;
		}
		if (hit->CheckObjNameHit(OBJ_JUMP_ENEMY) != nullptr || hit->CheckObjNameHit(OBJ_THORN) != nullptr
			||  m_r_tap_flag==true || m_py > 3000)
		{
			if (Audio::CheckSound(3) == false) //落ちている音が鳴ってない時
			{
				((UserData*)Save::GetData())->m_restart += 1; //リスタートした数を増やす
				Scene::SetScene(new CSceneMain());
			}
		}
		//落下したときに音を鳴らす。
		if (m_py > 600)
		{
			if (Audio::CheckSound(3) == false)
				Audio::Start(3);
		}
		//------------------------------------------------------------------------------------------------
		//位置の更新
		m_px += m_vx;
		m_py += m_vy;
	}
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
	
	//残りの数字を描画する-------------------------------------------------
	static wchar_t  c_siro[8];
	static float cl_kuro[4] = { 0.0f,0.0f,0.0f,1.0f };
	static float cl_siro[4] = { 1.0f,1.0f,1.0f,1.0f };
	//金塊残数
	swprintf_s(c_siro, L"X %d", m_gold_restriction_max-m_gold_restriction);
	if (((UserData*)Save::GetData())->m_stage_count == 5)//ステージ5の時文字が見えんので修正
	{
		CDrawFont::StrDraw(c_siro, 735, 16, 32, cl_siro);
	}
	else
	{
		CDrawFont::StrDraw(c_siro, 735, 16, 32, cl_kuro);
	}
	//コイン残数
	swprintf_s(c_siro, L"X %d", 10 - m_coin_restriction);
	if (((UserData*)Save::GetData())->m_stage_count == 5)//ステージ5の時文字が見えんので修正
	{
		CDrawFont::StrDraw(c_siro, 735, 62, 32, cl_siro);
	}
	else
	{
		CDrawFont::StrDraw(c_siro, 735, 62, 32, cl_kuro);
	}
	//金塊画像描画----------------------------------------------------------------------------------------------------
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 128.0f;
	src.m_bottom = 128.0f;
	//表示位置の設定
	dst.m_top = 15.0f;
	dst.m_left = 695.0f;
	dst.m_right = dst.m_left + 32.0f;
	dst.m_bottom = dst.m_top + 32.0f;
	//13番目に登録したグラフィックをsrc・dst・c・の情報を元に描画
	Draw::Draw(13, &src, &dst, c, 0.0);
	//--------------------------------------------------------------------------
	//コインの画像描画----------------------------------------------------------------------------------------------------
	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	//表示位置の設定
	dst.m_top = 64.0f;
	dst.m_left = 695.0f;
	dst.m_right = dst.m_left + 32.0f;
	dst.m_bottom = dst.m_top + 32.0f;
	//7番目に登録したグラフィックをsrc・dst・c・の情報を元に描画
	Draw::Draw(7, &src, &dst, c, 0.0);
	//---------------------------------------------------------------------------------
	//得点の描画ーーーーーーーーーーーーーーーーーーーーーーーーーーー
	wchar_t str[128];
	swprintf_s(str, L"得点：%d点", ((UserData*)Save::GetData())->m_point);
	if (((UserData*)Save::GetData())->m_stage_count == 5)//ステージ5の時文字が見えんので修正
	{
		Font::StrDraw(str, 350, 16, 32, cl_siro);
	}
	else
	{
		Font::StrDraw(str, 350, 16, 32, cl_kuro);
	}
	//−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−

	//リスタート文字の描画ーーーーーーーーーーーーーーーーーーーーーーーーーー
	
	wchar_t str2[128];
	swprintf_s(str2, L"Rでリスタート");
	if (((UserData*)Save::GetData())->m_stage_count == 5)//ステージ5の時文字が見えんので修正
	{
		Font::StrDraw(str2, 20, 16, 32, cl_siro);
	}
	else
	{
		Font::StrDraw(str2, 20, 16, 32, cl_kuro);
	}
	//−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
}

void CObjHero::HitBox()
{
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);

	//hero_Hit
	CObjhero_hitbox* hero_hit = (CObjhero_hitbox*)Objs::GetObj(HERO_HITBOX);

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

				if (r2 >= 200 && r2 < 340)
				{
					CObjBlock* b = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

					//また、地面に当たっている判定にする
					m_vy = 0.0f;
					m_hit_down_gold = true;

					if (r2 >= 310 && r2 < 340 && m_pos == 1.0f)//金塊の左端にいるときは金塊を置けなくする
					{
						m_gold_spawn = true;
					}
					else
						m_gold_spawn = false;
				}

				if (m_hit_down == true || m_hit_down_gold == true)		//地面or金塊の上にいるとき
				{
					if (r2 > 160 && r2 < 200 && m_pos == 1.0f && m_vy == 0.0f)
					{
						//左
						m_hit_left = true;  
						m_gold_Y = true;	//金塊側で主人公のｖｙを開放する
						if (m_hit_down_gold == true)
							m_py -= 12.0f;
						else
							m_py -= 36.0f;		//登れるようにする
						con++;
						break;
					}
					else if (/*r2 < 0 && r2>0 ||*/ r2 > 340 && m_pos == 0.0f && m_vy == 0.0f)
					{
						//右
						m_hit_right = true;
						m_gold_Y    = true;	//金塊側で主人公のｖｙを開放する
						if (m_hit_down_gold == true)
						  	 m_py -= 12.0f;
						else
							 m_py -= 36.0f;		//登れるようにする
						con++;
						break;
					}
					else
					{
						m_gold_Y = false;
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
	
	//ヒットボックスに触れていない時
	if (hit->CheckObjNameHit(OBJ_GOLD) == nullptr)
	{
		//金塊から降りているので金塊を置けるようにする。
		m_gold_spawn = false;
	}

	//ゴーレム情報
	CObjGolem* golem = (CObjGolem*)Objs::GetObj(OBJ_GOLEM);

	//ゴーレムに当たった時
	if (hit->CheckObjNameHit(OBJ_GOLEM) != nullptr)
	{
		//ゴーレムが存在している時
		if (golem != nullptr)
		{
			float golem_x = golem->GetX();
			//ゴーレムが右側にいるときの反射
			if (golem->GetPos() == 0.0&&m_px <= golem_x + block->GetScroll())
				m_vx += -0.7f;
			if (golem->GetPos() == 1.0&&m_px <= golem_x + block->GetScroll())
				m_vx += -m_speed;
			//ゴーレムが左側にいるときの反射
			if (golem->GetPos() == 0.0&&m_px >= golem_x + block->GetScroll())
				m_vx += m_speed;
			if (golem->GetPos() == 1.0&&m_px >= golem_x + block->GetScroll())
				m_vx += 0.7;

		}
	}

	//消えるブロック（半ブロックバージョンS3）に当たった時
	if (hit->CheckObjNameHit(OBJ_VANISHBLOCK) != nullptr)
	{
		m_vx = 0.0f; //通れなくする
		m_px -= 1.0f;//場所は決まっていて左にしか当たらないのでこれを使ってる
	}

	if (hit->CheckObjNameHit(OBJ_GOAL) != nullptr)
	{
		int m_gold_point = 0;//ポイント保存用
		if (m_gold_restriction_max - m_gold_restriction == 0)//金塊が0
		{
			m_gold_point += 1000;//1000ポイント加算
		}
		if (m_gold_restriction_max - m_gold_restriction > 0)//金塊が0より多い
		{
			m_gold_point += 2000 * (m_gold_restriction_max - m_gold_restriction);//2000ポイント*残数加算
		}
		//スコアにコイン残数によるポイントと金塊のポイントを加算
		((UserData*)Save::GetData())->m_point += ((10-m_coin_restriction)*1000)+m_gold_point;
	}
	


	//ゴールに当たった時
	if (hit->CheckObjNameHit(OBJ_GOAL) != nullptr)
	{
		m_goal_flag = true;
	}
}