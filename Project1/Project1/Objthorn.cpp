//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "Objthorn.h"
#include "GameL\Audio.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjthorn::CObjthorn(float x, float y)
{
	m_px = x;
	m_py = y;
}
//�C�j�V�����C�Y
void CObjthorn::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;
	m_pos = 0.0f;
	m_block_type = 0; //����ł���block�̎�ނ��m�F�p
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_THORN, 1);

}
//�A�N�V����
void CObjthorn::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);

	float c = m_px + block->GetScroll();

	block->BlockHit(&c, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type, false, false, 0, false, false
	);

	if (m_hit_up == true)
	{
		m_pos = 1.0f;
	}
	else
	{
		m_pos = 0.0f;
	}
}
//�h���[
void CObjthorn::Draw()
{
	//�`��J���[���@R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = src.m_left + 16.0f;
	src.m_bottom = src.m_top + 16.0f;

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	if (m_pos == 0.0f)
	{
		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = 64.0f + m_px + block->GetScroll();
		dst.m_right = 0.0f + m_px + block->GetScroll();
		dst.m_bottom = 64.0f + m_py;
	}
	else
	{
		//�\���ʒu�̐ݒ�
		dst.m_top = 64.0f + m_py;
		dst.m_left = 64.0f + m_px + block->GetScroll();
		dst.m_right = 0.0f + m_px + block->GetScroll();
		dst.m_bottom = 0.0f + m_py;
	}
	//10�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�E�̏������ɕ`��
	Draw::Draw(10, &src, &dst, c, 0.0);
}