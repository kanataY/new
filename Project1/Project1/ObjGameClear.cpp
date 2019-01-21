//使用するヘッダーファイル
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "ObjGameClear.h"
#include "GameHead.h"
//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CObjGameClear::Init()
{
	m_time = 0;
	m_ani_time = 0;
	m_ani_frame = 0;
	m_ani_max_time = 8;
}

//アクション
void CObjGameClear::Action()
{

	m_time++;


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
	//アニメーション終了−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−

	//メニュー画面へ
	if (Input::GetVKey(VK_RETURN) == true)
	{
		Scene::SetScene(new CSceneTitle());
	}

}

//ドロー
void CObjGameClear::Draw()
{
	//clear画面
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float color[4] = { 1.0f,1.0f,1.0f,0.5f };
	RECT_F src;	//描画先切り取り位置
	RECT_F dst;	//描画先表示位置

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

	Draw::Draw(m_ani_frame, &src, &dst, c, 0.0f);

	//切り取り位置設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//描画位置設定
	dst.m_top = 100.0f;
	dst.m_left = 120.0f;
	dst.m_right = dst.m_left+600.0f;
	dst.m_bottom = dst.m_top+300.0f;

	Draw::Draw(5, &src, &dst, c, 0.0f);
	
}