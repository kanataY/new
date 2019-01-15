//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "GolemJudgment.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjGolemJudgment::CObjGolemJudgment(float x, float y)
{
	m_px = x;
	m_py = y;

}

//イニシャライズ
void CObjGolemJudgment::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 24, 12, ELEMENT_JUDGMENT, GOLEM_JUDGMENT, 1);
}

//アクション
void CObjGolemJudgment::Action()
{
	//ブロック情報を持ってくる
	CObjGolem* golem = (CObjGolem*)Objs::GetObj(OBJ_GOLEM);
	//ブロック情報を持ってくる
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	
	//HitBoxの位置の変更
	CHitBox* hit = Hits::GetHitBox(this);
	//ゴーレムの向きでヒットボックスの位置変更
	if (golem != nullptr)
	{
		if (golem->GetPos() == 1.0)
			hit->SetPos(m_px + 33 + block->GetScroll(), m_py + 10);
		else
			hit->SetPos(m_px + 8 + block->GetScroll(), m_py + 10);

		//位置をゴーレムの位置と同じにする。
		m_px = golem->GetX();
		m_py = golem->GetY();
	}
	//ゴーレム死亡処理
	if (hit->CheckObjNameHit(OBJ_COIN) != nullptr)
	{
		hit->SetInvincibility(true); //当たり判定無効
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		golem->SetDelFlag(true);
	}

}
//ドロー
void CObjGolemJudgment::Draw()
{
	
}
