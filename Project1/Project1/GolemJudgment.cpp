//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "GolemJudgment.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGolemJudgment::CObjGolemJudgment(float x, float y)
{
	m_px = x;
	m_py = y;

}

//�C�j�V�����C�Y
void CObjGolemJudgment::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 24, 12, ELEMENT_JUDGMENT, GOLEM_JUDGMENT, 1);
}

//�A�N�V����
void CObjGolemJudgment::Action()
{
	//�u���b�N���������Ă���
	CObjGolem* golem = (CObjGolem*)Objs::GetObj(OBJ_GOLEM);
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	//�S�[�����̌����Ńq�b�g�{�b�N�X�̈ʒu�ύX
	if (golem != nullptr)
	{
		if (golem->GetPos() == 1.0)
			hit->SetPos(m_px + 33 + block->GetScroll(), m_py + 10);
		else
			hit->SetPos(m_px + 8 + block->GetScroll(), m_py + 10);

		//�ʒu���S�[�����̈ʒu�Ɠ����ɂ���B
		m_px = golem->GetX();
		m_py = golem->GetY();
	}
	//�S�[�������S����
	if (hit->CheckObjNameHit(OBJ_COIN) != nullptr)
	{
		hit->SetInvincibility(true); //�����蔻�薳��
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		golem->SetDelFlag(true);
	}

}
//�h���[
void CObjGolemJudgment::Draw()
{
	
}
