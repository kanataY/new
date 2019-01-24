//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjJumpEnemy.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjJumpEnemy::CObjJumpEnemy(float x, float y)
{
	m_px = x;
	m_py = y;

}

//�C�j�V�����C�Y
void CObjJumpEnemy::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_speed = 0.8f;
	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_jump_flag = false;
	m_pos = 1.0f;//������
	m_block_type = 0; //����ł���block�̎�ނ��m�F�p

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_ENEMY, OBJ_JUMP_ENEMY, 1);
}

//�A�N�V����
void CObjJumpEnemy::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py);

	float c = m_px + block->GetScroll();

	block->BlockHit(&c, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type,false, false,0, false,false
	);

	//�������ǂɓ�����Ɣ��]
	if (m_hit_left == true)
	{
		//�E������
		m_pos = 1.0f;
	}
	//�E�����ǂɓ�����Ɣ��]
	if (m_hit_right == true)
	{
		//��������
		m_pos = 0.0f;
	}
	//�u���b�N�ɐG��ĂȂ���
	if (m_hit_down == false)
	{
		//�W�����v�t���O::true
		m_jump_flag = true;
	}
	else
	{
		//�G��Ă��Ȃ��Ƃ���false�ɂ��Ă���
		m_jump_flag = false;
	}
	//�W�����v�t���O��true�̎�
	if (m_jump_flag == true)
	{
		//�W�����v���̎��Ԃ��v��
		m_jump_time++;
	}
	else
	{
		//���łȂ�����0�ɂ��Ă���
		m_jump_time = 0;
	}
	//�G�̌����ɂ���Ĉړ�������ς���
	if (m_pos == 0.0f)
	{
		m_vx += m_speed;
		//�W�����v���Ԃ�0���ォ��30��艺�Ȃ��ɔ��
		if (m_jump_time >= 0 && m_jump_time < 40)
			m_vy += -m_speed;
		else
			m_vy -= -m_speed;

	}
	if (m_pos == 1.0f)
	{
		m_vx -= m_speed;
		//�W�����v���Ԃ�0���ォ��30��艺�Ȃ��ɔ��
		if (m_jump_time >= 0 && m_jump_time < 40)
			m_vy += -m_speed;
		else
			m_vy -= -m_speed;

	}
	//���R�����^��
	m_vy += 9.8 / (16.0f);

	//���C
	m_vx += -(m_vx * 0.16f);
	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	//�폜�����@�R�C���ɓ�����A���ɗ�����
	if(m_py > 1500 || hit->CheckObjNameHit(OBJ_COIN) != nullptr) //���ɗ������玀��
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;//���ŏ����́A�����ŃA�N�V�������]�b�h���I��������
	}
}

//�h���[
void CObjJumpEnemy::Draw()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 128.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0f*m_pos) + m_px + block->GetScroll();
	dst.m_right = (64.0f - 64.0f*m_pos) + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//�`��
	Draw::Draw(6, &src, &dst, c, 0.0f);
}