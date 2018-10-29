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
CObjHero::CObjHero(int r)
{
	m_remaining = r; //残機
}

//イニシャライズ
void CObjHero::Init()
{
	m_px = 250.0f;
	m_py = 200.0f;	//位置
	m_vx = 0.0f;
	m_vy = 0.0f;	//移動ベクトル
	m_invincible = 0;
	m_speed = 0.8f;
	m_jamp_speed = 0.0f;

	m_hole_fall = 0.0f;

	m_torch_control = false;
	m_torch_time_control = 0;
	m_puddle_control = false;
	m_smart_control = false;
	m_hole_control = false;
	m_check_control = false;
	m_check_control_x = false;
	m_homing = false;
	m_check_time = 0;
	m_check_transfer = false;
	m_check_s1 = false;
	m_death = false;
	m_stick_fire = false;
	m_check_vx = false;
	m_rain = false;
	m_rain_time = true;
	m_gool = false;

	jamp_memo = 0.0f;
	m_jamp_control = false;
	m_jamp_control_2 = false;
	m_time = 0;

	m_jamp_y_1 = 1.6f;
	m_jamp_y_2 = 0.8f;

	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
	m_ani_max_time = 5; //アニメーション間隔幅

	m_ani_change = 2;//アニメーションを2に

	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //踏んでいるblockの種類を確認用


	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 18, 64, ELEMENT_HERO, OBJ_HERO, 1);
}

//アクション
void CObjHero::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//補正の情報を持ってくる
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);


	//アニメーションーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	m_ani_time++;//フレーム動作感覚タイムを進める
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


	//ゲージがなくなった時----------------------------------------------------------------------
	//なくなる瞬間に

	//----------------------------------------------------------------------------------------
	else     //ゲージがなくなってない時は動く
	{
		//死んだときーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
		if (m_death == true)//死んだとき
		{
			//穴に落ちてない時だけ
			if (m_hole_control == false)
			{
				//ジャンプしたときにそのまま行ってしまうので戻す。
				if (m_py <= 277) //道路より上に行かないようにする
					m_py = 277;

				m_vx = 0.0f; //復活した後動くのを防ぐ
				m_vy = 0.0f;

				m_stick_fire = false;
				m_hole_fall = 0.0;    //ランナーの描画をもとに戻す
				m_ani_max_time = 3;   //アニメーションの速度を上げる

				if (m_px < 300.0f)//３００の地点まで進む
					m_px += 2;
				else
				{
					m_death = false; //動かせるようにする
					m_ani_max_time = 5;//タイムを戻す
					m_invincible = 50; //しばらくの間無敵時間を設ける
					//Audio::Stop(1);//走る音を止める
				}
			}
		}

		//ーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー


			//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
			//移動ーーーーーーーーーーーーーーーーーーーーー
		if (m_stick_fire == true)
		{
			m_speed = 1.6f;
			m_jamp_speed = 1.2f;
		}
		else
		{
			m_speed = 0.8f;
			m_jamp_speed = 0.6f;
		}

		if (Input::GetVKey('D') == true)  //右移動
		{
			m_vx += m_speed;
		}
		if (Input::GetVKey('A') == true)  //左移動
		{
			m_vx += -m_speed;
		}
		if (Input::GetVKey('W') == true && m_py > 277)//上移動
		{
			m_vy += -m_speed;
			if (m_jamp_control_2 == true) //ジャンプしてなければ通常移動　してれば遅くする
			{
				//ジャンプしているときにSを押したとき、影も動くようにする
				m_jamp_y_position += -m_speed - 0.8f;
			}
		}
		if (Input::GetVKey('S') == true && m_py < 536)//下移動
		{
			if (m_jamp_control_2 == false) //ジャンプしてなければ通常移動　してれば遅くする
			{
				m_vy += m_speed;
			}
			else
			{
				m_vy += m_speed - m_jamp_speed;
				//ジャンプしているときにSを押したとき、影も動くようにする

				m_jamp_y_position += m_speed + m_jamp_speed;
			}
		}

		//摩擦
		m_vx += -(m_vx * 0.15f);
		m_vy += -(m_vy * 0.15f);

		//移動終了---------------------------------------------------

		//ジャンプ---------------------------
		//チェックポイントが出てきたらジャンプできない

		//ジャンプしていない
		if (m_jamp_control == false)
		{

			if (Input::GetVKey(VK_SPACE) == true)   //ジャンプする
			{
				m_jamp_y_position = m_py;
				m_jamp_control = true;		//ジャンプしている
				m_jamp_control_2 = true;
				//Audio::Start(3);//ジャンプ音
			}

		}

		if (m_jamp_control == true)//ジャンプしている
		{
			m_time++;
			if (m_time > 20 && m_time < 45) //ジャンプして最高点に到達
			{
				if (jamp_memo != 999.0f)    //ジャンプするとき上のほうにいなければWで少し移動できる
				{
					if (Input::GetVKey('W') == true)//上移動
					{
						if (m_py > 280)//道幅ギリギリ
							m_vy += m_jamp_y_1;
						else
							m_vy += -m_jamp_y_2;

					}
					else
					{
						m_vy += m_jamp_y_1;//自由落下運動
					}

				}
				else
					//ジャンプするとき上のほうにいた場合はただジャンプする
					m_vy += m_jamp_y_1;


			}
			else if (m_time < 20)
			{
				if (m_py < 280)//道幅ギリギリ
				{
					m_vy += -m_jamp_y_1;
					jamp_memo = 999.0f; //ジャンプする時上のほうにいた場合は記録する
				}
				else
				{
					if (Input::GetVKey('W') == true)//上移動
					{
						m_vy += -m_jamp_y_2;
					}
					else
					{
						m_vy += -m_jamp_y_1;//自由落下運動
					}
				}
			}
			if (m_time > 45 && m_time < 57)//時間が来たらジャンプを終了させる
			{
				m_jamp_control_2 = false;
				m_vy = 0.0f;
			}
			if (m_time > 90) //時間が来たら自由に動けるようになる (58デフォルト)
			{
				if (Input::GetVKey(VK_SPACE) == false)   //スペースを離さない限りジャンプさせない
				{
					m_jamp_control = false;
					m_time = 0;  //タイムを初期化
				}
			}
		}
		
		//}

		//自由落下運動
		m_vy += 9.8 / (16.0f);

		//ジャンプ終了ーーーーーーーーーーーーーーーーーーーーー

		//ブロック情報を持ってくる
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		block->BlockHit(&m_px, &m_py, true,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
			&m_block_type
		);

		if (m_px < -50.0f && m_death == false) //スクロールに遅れた時は真ん中で復活
		{
			//ジャンプ関連をすべて最初に戻す。
			m_time = 0;
			m_jamp_control = false;
			m_jamp_control_2 = false;
			//-----------------------------------------------
			m_death = true; //死んだ
			//Audio::Start(1);
		}

		m_invincible--; //無敵時間減少


		//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

		//HitBoxの位置の変更
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + 18.0f, m_py);


		//当たり判定関連
		HitBox();

		//位置の更新
		m_px += m_vx;
		m_py += m_vy;

		CObj::SetPrio((int)m_py); //描画優先順位変更
	}
}


		

//描画
void CObjHero::Draw()
{
	//ランナー-----------------------------------------------------------------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	//影の描画のためのカラー情報
	float shadowcolor[4] = { 1.0f,1.0f,1.0f,0.4f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
	RECT_F src2; //描画元切り取り位置
	RECT_F dst2; //描画先表示位置

	//ランナーのびょうが----------------------------------------------------
	
		//切り取り位置の設定 //足の先が上から見えていたので１.0ｆから
		//チェックポイントに入っていたら立ち姿に変える
		if (m_check_transfer == false)
		{
			src.m_top = 1.0f;
			src.m_left = 0.0f + m_ani_frame * 64;
			src.m_right = 64.0f + m_ani_frame * 64;
			src.m_bottom = 257.0f;
		}
		else
		{
			src.m_top = 1.0f;
			src.m_left = 0.0f + 64.0f;
			src.m_right = 64.0f + 64.0f;
			src.m_bottom = 257.0f;
		}

		//表示位置の設定
		dst.m_top = 0.0f + m_py + (m_hole_fall / 3);   //穴に落ちた時は描画を小さくする
		dst.m_left = 0.0f + m_px + (m_hole_fall /3);
		dst.m_right = 64.0f + m_px - m_hole_fall;
		dst.m_bottom = 64.0f + m_py - m_hole_fall;

		if (m_ani_change == 5)
		{
			src.m_top = 1.0f;
			src.m_left = 0.0f + m_ani_frame * 64;
			src.m_right = 64.0f + m_ani_frame * 64;
			src.m_bottom = 193.0f;

			//表示位置の設定
			dst.m_top = 0.0f + m_py;
			dst.m_left = 0.0f + m_px;
			dst.m_right = 64.0f + m_px;
			dst.m_bottom = 64.0f + m_py;

		}//描画
		Draw::Draw(m_ani_change, &src, &dst, c, 0.0f);
	
	
	
	//--------------------------------無敵点滅-----------------------------------　
	if (m_invincible > 0 && m_death == false)
	{
		//切り取り位置の設定 //足の先が上から見えていたので１.0ｆから
		src.m_top = 1.0f;
		src.m_left = 0.0f + m_ani_frame * 64;
		src.m_right = 64.0f + m_ani_frame * 64;
		src.m_bottom = 257.0f;

		//表示位置の設定
		dst.m_top = 0.0f + m_py;
		dst.m_left = 0.0f + m_px;
		dst.m_right = 64.0f + m_px;
		dst.m_bottom = 64.0f + m_py;

	}

	//ーーーーーーーーーーーーーーーーー聖火のもつとこーーーーーーーーーーーー
	//切り取り位置の設定 
	src2.m_top = 1.0f;
	src2.m_left = 0.0f;
	src2.m_right = 64.0f;
	src2.m_bottom = 64.0f;

	//表示位置の設定
	if (m_ani_change == 2) //腕を振り下ろしていない
	{
		if (m_hole_control == true)  //穴に落ちている場合（当たっている）
		{
			dst2.m_top = 0.0f + m_py - 10.0f + (m_hole_fall / 2);
			dst2.m_left = 0.0f + m_px + 25.0f;
			dst2.m_right = 20.0f + m_px + 40.0f - (m_hole_fall / 2) - 10.0f;
			dst2.m_bottom = 32.0f + m_py - 10.0f;
		}
		else
		{
			dst2.m_top = 0.0f + m_py - 10.0f;
			dst2.m_left = 0.0f + m_px + 40.0f;
			dst2.m_right = 20.0f + m_px + 40.0f;
			dst2.m_bottom = 32.0f + m_py - 10.0f;
		}

		//描画
		Draw::Draw(11, &src2, &dst2, c, 0.0f);
	}
	else //腕を振り下ろしている
	{

		dst2.m_top = 0.0f + m_py + 50.0f;
		dst2.m_left = 0.0f + m_px + 45.0f;
		dst2.m_right = 20.0f + m_px + 45.0f - m_hole_fall;
		dst2.m_bottom = 32.0f + m_py + 50.0f - m_hole_fall;


		//描画
		Draw::Draw(11, &src2, &dst2, c, -100.0f);
	}

	
	//影-------------------------------------------------------------
	//ジャンプしていないとき
	if (m_jamp_control_2 == false)
	{
		//穴に落ちていなければ描画
		if (m_hole_control == false)
		{
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			//表示位置の設定
			dst.m_top = 60.0f + m_py;
			dst.m_left = -30.0f + m_px;
			dst.m_right = 55.0f + m_px;
			dst.m_bottom = 68.0f + m_py;

			//描画
			Draw::Draw(25, &src, &dst, c, 1.0f);
		}
	}
	//ジャンプしてる時
	else
	{
		//穴に落ちていなければ描画
		if (m_hole_control == false)
		{
			//切り取り位置の設定
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			//表示位置の設定
			dst.m_top = 60.0f + m_jamp_y_position;
			dst.m_left = -30.0f + m_px;
			dst.m_right = 55.0f + m_px;
			dst.m_bottom = 68.0f + m_jamp_y_position;

			//描画
			Draw::Draw(25, &src, &dst, shadowcolor, 1.0f);
		}
	}
	//--------------------------------------------------------------
	//残機-------------------------------------------------------------------------------
	if ((((UserData*)Save::GetData())->m_stage_count ==1))
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 192.0f;

		//表示位置の設定
		dst.m_top = 0.0f + 10.0f;
		dst.m_left = 0.0f + 680.0f;
		dst.m_right = 40.0f + 680.0f;
		dst.m_bottom = 40.0f + 10.0f;
	}
	if ((((UserData*)Save::GetData())->m_stage_count == 2))
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 64.0f;
		src.m_right = 128.0f;
		src.m_bottom = 192.0f;

		//表示位置の設定
		dst.m_top = 0.0f + 10.0f;
		dst.m_left = 0.0f + 680.0f;
		dst.m_right = 40.0f + 680.0f;
		dst.m_bottom = 40.0f + 10.0f;
	}
	if ((((UserData*)Save::GetData())->m_stage_count == 3))
	{
		//切り取り位置の設定
		src.m_top = 0.0f;
		src.m_left = 128.0f;
		src.m_right = 192.0f;
		src.m_bottom = 192.0f;

		//表示位置の設定
		dst.m_top = 0.0f + 10.0f;
		dst.m_left = 0.0f + 680.0f;
		dst.m_right = 40.0f + 680.0f;
		dst.m_bottom = 40.0f + 10.0f;
	}
	//残りの数字を描画する
	static wchar_t  c_siro[8];
	static float cl_siro[4] = { 0.0f,0.0f,0.0f,1.0f };
	swprintf_s(c_siro, L"X %d", m_remaining);
	CDrawFont::StrDraw(c_siro, 735, 16, 32, cl_siro);

	//描画
	Draw::Draw(24, &src, &dst, c, 0.0f);
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

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
}