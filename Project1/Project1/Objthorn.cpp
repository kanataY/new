//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "Objthorn.h"
#include "GameL\Audio.h"
//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjthorn::CObjthorn(float x, float y)
{
	m_px = x;
	m_py = y;
}


//イニシャライズ
void CObjthorn::Init()
{
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_HERO, OBJ_COIN, 1);

}

//アクション
void CObjthorn::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
}

//ドロー
void CObjthorn::Draw()
{
	//描画カラー情報　R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置
				//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;
	//表示位置の設定
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 32.0f;
	dst.m_bottom = 32.0f;

	//7番目に登録したグラフィックをsrc・dst・c・の情報を元に描画
	Draw::Draw(10, &src, &dst, c, 0.0);
}