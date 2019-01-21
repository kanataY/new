//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "GameL\UserData.h"

#include "ObjVanishBlock.h"
#include "GameL\Audio.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjVanishBlock::CObjVanishBlock(float x, float y)
{
	m_px = x;
	m_py = y;
}
//�C�j�V�����C�Y
void CObjVanishBlock::Init()
{
	if (((UserData*)Save::GetData())->m_stage_count == 3)	//�X�e�[�W�R�Ȃ�ŏ��͕`�悵�Ȃ�
	{
		m_hit_draw = 0.0f;
		m_draw_right = 0.0f;
		m_draw_bottom = 0.0f;
	}
	else
	{
		m_hit_draw = 64.0f;
		m_draw_right = 64.0f;
		m_draw_bottom = 576.0f;
	}
	m_swich_flag = false;

	//�����蔻��pHitBox���쐬
	//Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_GOAL, 1);
}
//�A�N�V����
void CObjVanishBlock::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	//CHitBox* hit = Hits::GetHitBox(this);
	//hit->SetPos(m_px + block->GetScroll(), m_py);

	Hit();
}
//�h���[
void CObjVanishBlock::Draw()
{
	//�`��J���[���@R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top    =        0.f;
	src.m_left   =       0.0f;
	src.m_right  = m_hit_draw;
	src.m_bottom = m_hit_draw;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top    =								0.0f + m_py;
	dst.m_left   =		   0.0f + m_px + block->GetScroll();
	dst.m_right  = m_draw_right + m_px + block->GetScroll();
	dst.m_bottom =					   m_draw_bottom + m_py;

	//8�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�E�̏������ɕ`��
	if (((UserData*)Save::GetData())->m_stage_count == 3)  //�X�e�[�W�R�Ȃ�`��ω�
	{
		Draw::Draw(1, &src, &dst, c, 0.0);
	}
	else if (m_swich_flag == false)
		Draw::Draw(1, &src, &dst, c, 0.0);
}

//�q�b�g�֘A
void CObjVanishBlock::Hit()
{
	//�X�C�b�`�̏��������Ă���
	CObjswitch* swi = (CObjswitch*)Objs::GetObj(OBJ_SWITCH);
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	if (swi != nullptr)
	{
		if (swi->GetSwitchFlag() == true) //�X�C�b�`��������Ă����ꍇ
		{
			if (block->GetSwichTime() > 50000)//�X�C�b�`��������Ă��炵�΂炭������`�������
			{
				m_swich_flag = true;
				if (((UserData*)Save::GetData())->m_stage_count == 3)  //�X�e�[�W�R�Ȃ�`��ω�
				{
					m_hit_draw = 64.0f;
					m_draw_right = 256.0f;  //���̕`�敝��ς���
					m_draw_bottom = 64.0f;  //�c
				}
			}
		}
		else
		{
			m_swich_flag = false;//������Ă��Ȃ��ꍇ�͕`��������Ȃ��悤�ɂ���
		}
	}
}