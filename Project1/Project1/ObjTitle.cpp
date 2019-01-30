//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\MultiThread.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "GameL\UserData.h"
#include "ObjTitle.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjTitle::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;  //静止フレームを初期にする
	m_ani_max_time = 15; //アニメーション間隔幅

	m_ani_time2 = 0;
	m_ani_max_time2 = 3;
	m_ani_start_flag = false;

	m_key_flag = 0;
	m_key_control = false;
	m_enter_control = false;
	m_scene_start_control = 0;

	//ゲーム実行して一回のみ
	static bool init_point = false;
	if (init_point == false)
	{
		//ランキング初期化
		for (int i = 0; i < RANKING_MAX_COUNT - 1; i++)
		{
			((UserData*)Save::GetData())->m_ranking[i] = 0;
		}

		//ロード
		Save::Open();//同フォルダ「UserData」からデータ取得

		init_point = true;
	}

	//スコアを0で初期化する
	((UserData*)Save::GetData())->m_point = 0;

	
}

//アクション
void CObjTitle::Action()
{
	m_scene_start_control++;

	//十字キーの上か下を押したとき
	if (Input::GetVKey(VK_LEFT) == true && m_ani_frame == 4)
	{
		//キーのコントロールがfalseなら
		if (m_key_control == false)
		{
			//キーのコントロールをtrueにする
			m_key_control = true;

			//フラグが0の時
			if (m_key_flag == 0)
			{
				//フラグを1に
				m_key_flag = 1;
				Audio::Start(1);
			}

			//フラグが１の時
			else if (m_key_flag == 1)
			{
				//フラグを0に
				m_key_flag = 0;
				Audio::Start(1);
			}
		}
	}
	//十字キーが押されてない時
	else
	{
		//キーのコントロールはfalse
		m_key_control = false;
	}
	//エンターキーを押された時2frame経っていたら
	if (Input::GetVKey(VK_RETURN) == true && m_ani_frame==4)
	{
		//エンターコントロールがfalseの時
		if (m_enter_control==false)
		{
			//メニューへの位置なら
			if (m_key_flag == 0)
			{
				m_ani_start_flag = true;
				Audio::Start(2);
			}
			//終了の位置なら
			if (m_key_flag == 1)
			{
				//ゲームを終了させる
				CMultiThread::End();
			}
			//エンターキーを押した状態と判定する
			m_enter_control = true;
		}
	}
	//エンターキーを押された時2frame経っていなかったら
	else if (Input::GetVKey(VK_RETURN) == true && m_scene_start_control <= 2)
	{
		//エンターキーは押している状態とする。
		m_enter_control = true;
	}
	else
	{
		//エンターキーは押してはいない状態とする
		m_enter_control = false;
	}

	//アニメーションーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーーー
	if (m_ani_frame < 4)//frameが5になるまではアニメーションさせる。
	{
		m_ani_time++;//フレーム動作感覚タイムを進める
	}
	if (m_ani_time > m_ani_max_time)//フレーム動作感覚タイムが最大まで行ったら
	{
		m_ani_frame++;//フレームを進める
		m_ani_time = 0;
	}

	if (m_ani_start_flag == true)
	{
		m_ani_time2++;
	}
	if (m_ani_time2 > m_ani_max_time2)
	{
		if (m_ani_frame < 10)
		{
			m_ani_frame++;//frame進める
			m_ani_time2 = 0;
		}
	}
	if (m_ani_frame == 10 && Audio::CheckSound(2) == false)//フレームが最後まで進んだら戻す
	{
		
		//シーンをメニューへ
		((UserData*)Save::GetData())->m_stage_count = 1; //メインに変える
		Scene::SetScene(new CSceneMain());
	}
	//アニメーション終了－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－

}

//ドロー
void CObjTitle::Draw()
{
	//タイトル画面
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//描画先切り取り位置
	RECT_F dst;	//描画先表示位置

	//タイトル画面---------------------------------------
	//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//描画位置設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;
	if (m_ani_frame < 11)//シーン遷移の時11に登録している画像が出てくるので制御する
	{
		//m_ani_frameと同じ番号に登録しているsrc・dst・cで描画する
		Draw::Draw(m_ani_frame, &src, &dst, c, 0.0f);
	}
	//---------------------------------------------------------

	//タイトルの文字-------------------------------------------
	//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//描画位置設定
	dst.m_top = -80.0f;
	dst.m_left = 120.0f;
	dst.m_right = dst.m_left+512.0f;
	dst.m_bottom = dst.m_top+512.0f;

	//1番目に登録しているsrc・dst・cで描画する
	Draw::Draw(15, &src, &dst, c, 0.0f);
	//-------------------------------------------------------------

	//スタートの文字-------------------------------------------
	//切り取り位置設定
	if (m_ani_frame >= 4 && m_key_flag == 0)
	{
		//切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//描画位置設定
		dst.m_top = 420.0f;
		dst.m_left = 545.0f;
		dst.m_right = dst.m_left + 256.0f;
		dst.m_bottom = dst.m_top + 134.0f;

		//11番目に登録しているsrc・dst・cで描画する
		Draw::Draw(11, &src, &dst, c, 0.0f);
	}
	if (m_ani_frame >= 4 && m_key_flag == 1)
	{
		//切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//描画位置設定
		dst.m_top = 420.0f;
		dst.m_left = 545.0f;
		dst.m_right = dst.m_left + 256.0f;
		dst.m_bottom = dst.m_top + 134.0f;

		//12番目に登録しているsrc・dst・cで描画する
		Draw::Draw(12, &src, &dst, c, 0.0f);
	}
	///-------------------------------------------------------------
	//ランキングの文字-------------------------------------------
	if (m_ani_frame >= 4 && m_key_flag == 1)
	{
		//切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//描画位置設定
		dst.m_top = 425.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + 256.0f;
		dst.m_bottom = dst.m_top + 128.0f;

		//13番目に登録しているsrc・dst・cで描画する
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	if (m_ani_frame >= 4 && m_key_flag == 0)
	{
		//切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//描画位置設定
		dst.m_top = 425.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + 256.0f;
		dst.m_bottom = dst.m_top + 128.0f;

		//14番目に登録しているsrc・dst・cで描画する
		Draw::Draw(14, &src, &dst, c, 0.0f);
	}
	///-------------------------------------------------------------
	//終了の文字-------------------------------------------
	if (m_ani_frame >= 4&&m_key_flag==1)
	{
		//切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//描画位置設定
		dst.m_top = 425.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + 256.0f;
		dst.m_bottom = dst.m_top + 128.0f;

		//15番目に登録しているsrc・dst・cで描画する
		Draw::Draw(15, &src, &dst, c, 0.0f);
	}
	if(m_ani_frame >= 4 && m_key_flag == 0)
	{
		//切り取り位置設定
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//描画位置設定
		dst.m_top = 425.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + 256.0f;
		dst.m_bottom = dst.m_top + 128.0f;

		//14番目に登録しているsrc・dst・cで描画する
		Draw::Draw(14, &src, &dst, c, 0.0f);
	}
	///-------------------------------------------------------------
}