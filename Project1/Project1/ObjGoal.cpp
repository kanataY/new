//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "GameL\UserData.h"

#include "ObjGoal.h"
#include "GameL\Audio.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGoal::CObjGoal(float x, float y)
{
	m_px = x;
	m_py = y;
}
//�C�j�V�����C�Y
void CObjGoal::Init()
{
	m_hit_draw = 64.0f;

	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 10, 10, ELEMENT_ENEMY, OBJ_GOAL, 1);
}
//�A�N�V����
void CObjGoal::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 25.0f + block->GetScroll(), m_py + 30.0f);

	Hit();
}
//�h���[
void CObjGoal::Draw()
{
	//�`��J���[���@R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.f;
	src.m_left = m_hit_draw -64.0f;
	src.m_right = m_hit_draw;
	src.m_bottom = 128.0f;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//8�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�E�̏������ɕ`��
	Draw::Draw(8, &src, &dst, c, 0.0);
}

//�q�b�g�֘A
void CObjGoal::Hit()
{
	//HitBox�擾
	CHitBox* hit = Hits::GetHitBox(this);

	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		m_hit_draw = 128.0f; // ��l���ɓ�������

		//�X�e�[�W���P�i�߂�
		((UserData*)Save::GetData())->m_stage_count +=1;
		if (((UserData*)Save::GetData())->m_stage_count < 5)
			Scene::SetScene(new CSceneMain());
		else
			Scene::SetScene(new CSceneGameClear());
	}
}