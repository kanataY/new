//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjRushEnemy.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjRushEnemy::CObjRushEnemy(float x, float y)
{
	m_px = x;
	m_py = y;

}

//�C�j�V�����C�Y
void CObjRushEnemy::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_speed = 1.0f;
	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 12; //�A�j���[�V�����Ԋu��

	m_move = true;
	m_pos = 1.0f;//������
	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //����ł���block�̎�ނ��m�F�p

					  //HitBox
	Hits::SetHitBox(this, m_px, m_py, 64, 40, ELEMENT_ENEMY, OBJ_RUSH_ENEMY, 1);
}

//�A�N�V����
void CObjRushEnemy::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//���R�����^��
	m_vy += 9.8 / (16.0f);
	


	//�A�j���[�V�����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	m_ani_time++;//�t���[�����슴�o�^�C����i�߂�
	if (m_ani_time > m_ani_max_time)//�t���[�����슴�o�^�C�����ő�܂ōs������
	{
		m_ani_frame++;//�t���[����i�߂�
		m_ani_time = 0;
	}
	if (m_ani_frame == 2)//�t���[�����Ō�܂Ői�񂾂�߂�
	{
		m_ani_frame = 0;
	}
	//�A�j���[�V�����I���|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

	

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py+24);

	float c = m_px + block->GetScroll();

	block->BlockHit(&c, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type,false, false,0
	);
	//�������ǂɓ�����Ɣ��]
	if (m_hit_left == true)
	{
		m_move = true;
		
	}
	//�E�����ǂɓ�����Ɣ��]
	if (m_hit_right == true)
	{
		m_move = false;
		
	}

	//�ړ�����
	if (m_move == true)
	{
		m_vx -= m_speed;
		m_pos = 1.0f;
	}
	if (m_move == false)
	{
		m_vx += m_speed;
		m_pos = 0.0f;
	}
	m_vx += -(m_vx * 0.16f);
	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;
}

//�h���[
void CObjRushEnemy::Draw()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

				//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + m_ani_frame * 64;
	src.m_right = 64.0f + m_ani_frame * 64;
	src.m_bottom =128.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = -20.0f + m_py;
	dst.m_left = (64.0f*m_pos) + m_px + block->GetScroll();
	dst.m_right = (64.0f-64.0f*m_pos) + m_px + block->GetScroll();
	dst.m_bottom = 64.0f + m_py;

	//�`��
	Draw::Draw(5, &src, &dst, c, 0.0f);

}