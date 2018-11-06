//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjHero::CObjHero(int r)
{
	m_remaining = r; //�c�@
}

//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_px = 250.0f;
	m_py = 200.0f;	//�ʒu
	m_vx = 0.0f;
	m_vy = 0.0f;	//�ړ��x�N�g��
	
	m_speed = 0.8f;

	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 5; //�A�j���[�V�����Ԋu��

	m_ani_change = 2;//�A�j���[�V������2��

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //����ł���block�̎�ނ��m�F�p


	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 64, 64, ELEMENT_HERO, OBJ_HERO, 1);
}

//�A�N�V����
void CObjHero::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�␳�̏��������Ă���
	CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);


	//�A�j���[�V�����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	m_ani_time++;//�t���[�����슴�o�^�C����i�߂�
	if (m_ani_time > m_ani_max_time)//�t���[�����슴�o�^�C�����ő�܂ōs������
	{
		m_ani_frame++;//�t���[����i�߂�
		m_ani_time = 0;
	}
	if (m_ani_frame == 4)//�t���[�����Ō�܂Ői�񂾂�߂�
	{
		m_ani_frame = 0;
	}
	//�A�j���[�V�����I���|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

	if (Input::GetVKey('D') == true)  //�E�ړ�
	{
		m_vx += m_speed;
	}
	if (Input::GetVKey('A') == true)  //���ړ�
	{
		m_vx += -m_speed;
	}
	if (Input::GetVKey('W') == true)//��ړ�
	{
		m_vy += -m_speed*3;
	}
	if (Input::GetVKey('S') == true && m_py < 536)//���ړ�
	{
		m_vy += m_speed;
	}

	//���C
	m_vx += -(m_vx * 0.15f);
	m_vy += -(m_vy * 0.15f);

	//�ړ��I��---------------------------------------------------


	//���R�����^��
	m_vy += 9.8 / (16.0f);

	//�W�����v�I���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	//�u���b�N���������Ă���
	//CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�ړ��I��---------------------------------------------------
	block->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type
	);

	//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px , m_py);


	//�����蔻��֘A
	HitBox();

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

}

		

//�`��
void CObjHero::Draw()
{
	//�����i�[-----------------------------------------------------------------
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	//�e�̕`��̂��߂̃J���[���
	float shadowcolor[4] = { 1.0f,1.0f,1.0f,0.4f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	RECT_F src2; //�`�挳�؂���ʒu
	RECT_F dst2; //�`���\���ʒu

	 //�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px;
	dst.m_right = 64.0f + m_px;
	dst.m_bottom = 64.0f + m_py;

	//�`��
	Draw::Draw(3, &src, &dst, c, 0.0f);
	
	//�c��̐�����`�悷��
	static wchar_t  c_siro[8];
	static float cl_siro[4] = { 0.0f,0.0f,0.0f,1.0f };
	swprintf_s(c_siro, L"X %d", m_remaining);
	CDrawFont::StrDraw(c_siro, 735, 16, 32, cl_siro);

	//---------------------------------------------------------------------------------
	//���_�̕`��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	float cc[4] = { 0.0f,0.0f,0.0f,1.0f };
	wchar_t str[128];
	swprintf_s(str, L"���_�F%d�_", ((UserData*)Save::GetData())->m_point);
	Font::StrDraw(str, 350, 16, 32, cc);
	//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
}

void CObjHero::HitBox()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
}