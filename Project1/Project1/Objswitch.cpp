//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "Objthorn.h"
#include "GameL\Audio.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjswitch::CObjswitch(float x, float y)
{
	m_px = x;
	m_py = y;
	
}
//�C�j�V�����C�Y
void CObjswitch::Init()
{
	switch_on_flag = false;
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 25, ELEMENT_ENEMY, OBJ_SWITCH, 1);
}
//�A�N�V����
void CObjswitch::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	if (switch_on_flag == false)
	{
		hit->SetPos(m_px + block->GetScroll(), m_py + 9.0f);
	}
	else
	{
		hit->SetPos(m_px + block->GetScroll(), m_py + 18.0f);
	}
}
//�h���[
void CObjswitch::Draw()
{
	//�`��J���[���@R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

    //�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_bottom = 128.0f;
	if (switch_on_flag == false)
	{
		src.m_left = 0.0f;
		src.m_right = 64.0f;
	}
	else
	{
		src.m_left = 64.0f;
		src.m_right = 128.0f;
	}
	

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�\���ʒu�̐ݒ�
	dst.m_top = -32.0f + m_py;
	dst.m_left = 64.0f + m_px + block->GetScroll();
	dst.m_right = 0.0f + m_px + block->GetScroll();
	dst.m_bottom = 32.0f + m_py;

	//9�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�E�̏������ɕ`��
	Draw::Draw(9, &src, &dst, c, 0.0);
}