//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"

#include "hero_hitbox.h"
#include "GameL\Audio.h"
//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjhero_hitbox::CObjhero_hitbox()
{

}
//イニシャライズ
void CObjhero_hitbox::Init()
{
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 37, 20, ELEMENT_NULL, HERO_HITBOX, 1);
}
//アクション
void CObjhero_hitbox::Action()
{
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//主人公の情報を持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//Y位置更新
	m_py = hero->GetY() + 44.0f;

	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(hero->GetX() + 15.0f /*- block->GetScroll()*/, m_py);

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

				if (r2 >= 202 && r2 < 330)
				{
					hit_check = true;
				}
				else
					hit_check = false;
			}
		}
	}
}
//ドロー
void CObjhero_hitbox::Draw()
{

}