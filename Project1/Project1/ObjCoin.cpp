//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjCoin.h"
#include "GameL\Audio.h"
//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjCoin::CObjCoin(float x, float y)
{
	m_px = x;
	m_py = y;
}


//イニシャライズ
void CObjCoin::Init()
{
	m_hero_pos = 0;
	m_del = false;
	m_vy = 0.0f;
	m_vx = 0.0f;
	//blockとの衝突状態確認用
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //踏んでいるblockの種類を確認用
	//当たり判定用HitBoxを作成
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_HERO, OBJ_COIN, 1);

}

//アクション
void CObjCoin::Action()
{
	//主人公情報を持ってくる
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//弾丸消滅処理
	if (m_del == true)
	{

		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;//消滅処理は、ここでアクションメゾッドを終了させる
	}
	
	//弾丸実行処理
	if (m_hero_pos==0)
		m_vx += 0.3f;
	else
		m_vx -= 0.3f;
	m_px += m_vx;
	m_py += m_vy;
	block->Block32Hit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type, 0
	);
	//弾丸のHitBox更新用ポインター取得
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);    //HitBoxの位置を弾丸の位置に更新
								//領域外に出たら弾丸を破棄する

	if (m_px + block->GetScroll() < -32.0f ||m_px + block->GetScroll()>800.0f)
	{
		this->SetStatus(false);   //自身に削除命令を出す。
		Hits::DeleteHitBox(this); //弾丸が所有するHitBoxに削除する。
	}

	//当たり判定を行うオブジェクト情報郡
	int data_base[2] =
	{
		OBJ_JUMP_ENEMY,
		OBJ_RUSH_ENEMY,
	};

	//オブジェクト情報郡と当たり判定行い。当たっていれば削除
	for (int i = 0; i < 3; i++)
	{
		if (hit->CheckObjNameHit(data_base[i]) != nullptr||m_hit_left==true||m_hit_right==true)
		{
			m_del = true;				 //消滅
			hit->SetInvincibility(true); //当たり判定無効
		}
	}
}

//ドロー
void CObjCoin::Draw()
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
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px;
	dst.m_right = 32.0f + m_px;
	dst.m_bottom = 32.0f + m_py;

	//7番目に登録したグラフィックをsrc・dst・c・の情報を元に描画
	Draw::Draw(7, &src, &dst, c, 0.0);
}