//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "GameL\UserData.h"

#include "ObjGoal.h"
#include "GameL\Audio.h"
//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjGoal::CObjGoal(float x, float y)
{
	m_px = x;
	m_py = y;
}
//イニシャライズ
void CObjGoal::Init()
{
	m_hit_draw = 64.0f;

	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 10, 10, ELEMENT_ENEMY, OBJ_GOAL, 1);
}
//アクション
void CObjGoal::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 25.0f + block->GetScroll(), m_py + 30.0f);

	Hit();
}
//ドロー
void CObjGoal::Draw()
{
	//描画カラー情報　R=RED　G=Green　B=Blue　A=alpha(透過情報)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.f;
	src.m_left = m_hit_draw -64.0f;
	src.m_right = m_hit_draw;
	src.m_bottom = 128.0f;

	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//表示位置の設定
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//8番目に登録したグラフィックをsrc・dst・c・の情報を元に描画
	Draw::Draw(8, &src, &dst, c, 0.0);
}

//ヒット関連
void CObjGoal::Hit()
{
	//HitBox取得
	CHitBox* hit = Hits::GetHitBox(this);

	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_hit_draw = 128.0f; // 主人公に当たった

		//ステージを１進める
		((UserData*)Save::GetData())->m_stage_count +=1;
		if (((UserData*)Save::GetData())->m_stage_count < 5)
			Scene::SetScene(new CSceneMain());
		else
			Scene::SetScene(new CSceneGameClear());
	}
}