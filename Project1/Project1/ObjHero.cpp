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
	m_invincible = 0;
	m_speed = 0.8f;
	m_jamp_speed = 0.0f;

	m_hole_fall = 0.0f;

	m_torch_control = false;
	m_torch_time_control = 0;
	m_puddle_control = false;
	m_smart_control = false;
	m_hole_control = false;
	m_check_control = false;
	m_check_control_x = false;
	m_homing = false;
	m_check_time = 0;
	m_check_transfer = false;
	m_check_s1 = false;
	m_death = false;
	m_stick_fire = false;
	m_check_vx = false;
	m_rain = false;
	m_rain_time = true;
	m_gool = false;

	jamp_memo = 0.0f;
	m_jamp_control = false;
	m_jamp_control_2 = false;
	m_time = 0;

	m_jamp_y_1 = 1.6f;
	m_jamp_y_2 = 0.8f;

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
	Hits::SetHitBox(this, m_px, m_py, 18, 64, ELEMENT_HERO, OBJ_HERO, 1);
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


	//�Q�[�W���Ȃ��Ȃ�����----------------------------------------------------------------------
	//�Ȃ��Ȃ�u�Ԃ�

	//----------------------------------------------------------------------------------------
	else     //�Q�[�W���Ȃ��Ȃ��ĂȂ����͓���
	{
		//���񂾂Ƃ��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
		if (m_death == true)//���񂾂Ƃ�
		{
			//���ɗ����ĂȂ�������
			if (m_hole_control == false)
			{
				//�W�����v�����Ƃ��ɂ��̂܂܍s���Ă��܂��̂Ŗ߂��B
				if (m_py <= 277) //���H����ɍs���Ȃ��悤�ɂ���
					m_py = 277;

				m_vx = 0.0f; //���������㓮���̂�h��
				m_vy = 0.0f;

				m_stick_fire = false;
				m_hole_fall = 0.0;    //�����i�[�̕`������Ƃɖ߂�
				m_ani_max_time = 3;   //�A�j���[�V�����̑��x���グ��

				if (m_px < 300.0f)//�R�O�O�̒n�_�܂Ői��
					m_px += 2;
				else
				{
					m_death = false; //��������悤�ɂ���
					m_ani_max_time = 5;//�^�C����߂�
					m_invincible = 50; //���΂炭�̊Ԗ��G���Ԃ�݂���
					//Audio::Stop(1);//���鉹���~�߂�
				}
			}
		}

		//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[


			//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
			//�ړ��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
		if (m_stick_fire == true)
		{
			m_speed = 1.6f;
			m_jamp_speed = 1.2f;
		}
		else
		{
			m_speed = 0.8f;
			m_jamp_speed = 0.6f;
		}

		if (Input::GetVKey('D') == true)  //�E�ړ�
		{
			m_vx += m_speed;
		}
		if (Input::GetVKey('A') == true)  //���ړ�
		{
			m_vx += -m_speed;
		}
		if (Input::GetVKey('W') == true && m_py > 277)//��ړ�
		{
			m_vy += -m_speed;
			if (m_jamp_control_2 == true) //�W�����v���ĂȂ���Βʏ�ړ��@���Ă�Βx������
			{
				//�W�����v���Ă���Ƃ���S���������Ƃ��A�e�������悤�ɂ���
				m_jamp_y_position += -m_speed - 0.8f;
			}
		}
		if (Input::GetVKey('S') == true && m_py < 536)//���ړ�
		{
			if (m_jamp_control_2 == false) //�W�����v���ĂȂ���Βʏ�ړ��@���Ă�Βx������
			{
				m_vy += m_speed;
			}
			else
			{
				m_vy += m_speed - m_jamp_speed;
				//�W�����v���Ă���Ƃ���S���������Ƃ��A�e�������悤�ɂ���

				m_jamp_y_position += m_speed + m_jamp_speed;
			}
		}

		//���C
		m_vx += -(m_vx * 0.15f);
		m_vy += -(m_vy * 0.15f);

		//�ړ��I��---------------------------------------------------

		//�W�����v---------------------------
		//�`�F�b�N�|�C���g���o�Ă�����W�����v�ł��Ȃ�

		//�W�����v���Ă��Ȃ�
		if (m_jamp_control == false)
		{

			if (Input::GetVKey(VK_SPACE) == true)   //�W�����v����
			{
				m_jamp_y_position = m_py;
				m_jamp_control = true;		//�W�����v���Ă���
				m_jamp_control_2 = true;
				//Audio::Start(3);//�W�����v��
			}

		}

		if (m_jamp_control == true)//�W�����v���Ă���
		{
			m_time++;
			if (m_time > 20 && m_time < 45) //�W�����v���čō��_�ɓ��B
			{
				if (jamp_memo != 999.0f)    //�W�����v����Ƃ���̂ق��ɂ��Ȃ����W�ŏ����ړ��ł���
				{
					if (Input::GetVKey('W') == true)//��ړ�
					{
						if (m_py > 280)//�����M���M��
							m_vy += m_jamp_y_1;
						else
							m_vy += -m_jamp_y_2;

					}
					else
					{
						m_vy += m_jamp_y_1;//���R�����^��
					}

				}
				else
					//�W�����v����Ƃ���̂ق��ɂ����ꍇ�͂����W�����v����
					m_vy += m_jamp_y_1;


			}
			else if (m_time < 20)
			{
				if (m_py < 280)//�����M���M��
				{
					m_vy += -m_jamp_y_1;
					jamp_memo = 999.0f; //�W�����v���鎞��̂ق��ɂ����ꍇ�͋L�^����
				}
				else
				{
					if (Input::GetVKey('W') == true)//��ړ�
					{
						m_vy += -m_jamp_y_2;
					}
					else
					{
						m_vy += -m_jamp_y_1;//���R�����^��
					}
				}
			}
			if (m_time > 45 && m_time < 57)//���Ԃ�������W�����v���I��������
			{
				m_jamp_control_2 = false;
				m_vy = 0.0f;
			}
			if (m_time > 90) //���Ԃ������玩�R�ɓ�����悤�ɂȂ� (58�f�t�H���g)
			{
				if (Input::GetVKey(VK_SPACE) == false)   //�X�y�[�X�𗣂��Ȃ�����W�����v�����Ȃ�
				{
					m_jamp_control = false;
					m_time = 0;  //�^�C����������
				}
			}
		}
		
		//}

		//���R�����^��
		m_vy += 9.8 / (16.0f);

		//�W�����v�I���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

		//�u���b�N���������Ă���
		CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

		block->BlockHit(&m_px, &m_py, true,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
			&m_block_type
		);

		if (m_px < -50.0f && m_death == false) //�X�N���[���ɒx�ꂽ���͐^�񒆂ŕ���
		{
			//�W�����v�֘A�����ׂčŏ��ɖ߂��B
			m_time = 0;
			m_jamp_control = false;
			m_jamp_control_2 = false;
			//-----------------------------------------------
			m_death = true; //����
			//Audio::Start(1);
		}

		m_invincible--; //���G���Ԍ���


		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

		//HitBox�̈ʒu�̕ύX
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + 18.0f, m_py);


		//�����蔻��֘A
		HitBox();

		//�ʒu�̍X�V
		m_px += m_vx;
		m_py += m_vy;

		CObj::SetPrio((int)m_py); //�`��D�揇�ʕύX
	}
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

	//�����i�[�̂т傤��----------------------------------------------------
	
		//�؂���ʒu�̐ݒ� //���̐悪�ォ�猩���Ă����̂łP.0������
		//�`�F�b�N�|�C���g�ɓ����Ă����痧���p�ɕς���
		if (m_check_transfer == false)
		{
			src.m_top = 1.0f;
			src.m_left = 0.0f + m_ani_frame * 64;
			src.m_right = 64.0f + m_ani_frame * 64;
			src.m_bottom = 257.0f;
		}
		else
		{
			src.m_top = 1.0f;
			src.m_left = 0.0f + 64.0f;
			src.m_right = 64.0f + 64.0f;
			src.m_bottom = 257.0f;
		}

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py + (m_hole_fall / 3);   //���ɗ��������͕`�������������
		dst.m_left = 0.0f + m_px + (m_hole_fall /3);
		dst.m_right = 64.0f + m_px - m_hole_fall;
		dst.m_bottom = 64.0f + m_py - m_hole_fall;

		if (m_ani_change == 5)
		{
			src.m_top = 1.0f;
			src.m_left = 0.0f + m_ani_frame * 64;
			src.m_right = 64.0f + m_ani_frame * 64;
			src.m_bottom = 193.0f;

			//�\���ʒu�̐ݒ�
			dst.m_top = 0.0f + m_py;
			dst.m_left = 0.0f + m_px;
			dst.m_right = 64.0f + m_px;
			dst.m_bottom = 64.0f + m_py;

		}//�`��
		Draw::Draw(m_ani_change, &src, &dst, c, 0.0f);
	
	
	
	//--------------------------------���G�_��-----------------------------------�@
	if (m_invincible > 0 && m_death == false)
	{
		//�؂���ʒu�̐ݒ� //���̐悪�ォ�猩���Ă����̂łP.0������
		src.m_top = 1.0f;
		src.m_left = 0.0f + m_ani_frame * 64;
		src.m_right = 64.0f + m_ani_frame * 64;
		src.m_bottom = 257.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = 0.0f + m_px;
		dst.m_right = 64.0f + m_px;
		dst.m_bottom = 64.0f + m_py;

	}

	//�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[���΂̂��Ƃ��[�[�[�[�[�[�[�[�[�[�[�[
	//�؂���ʒu�̐ݒ� 
	src2.m_top = 1.0f;
	src2.m_left = 0.0f;
	src2.m_right = 64.0f;
	src2.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	if (m_ani_change == 2) //�r��U�艺�낵�Ă��Ȃ�
	{
		if (m_hole_control == true)  //���ɗ����Ă���ꍇ�i�������Ă���j
		{
			dst2.m_top = 0.0f + m_py - 10.0f + (m_hole_fall / 2);
			dst2.m_left = 0.0f + m_px + 25.0f;
			dst2.m_right = 20.0f + m_px + 40.0f - (m_hole_fall / 2) - 10.0f;
			dst2.m_bottom = 32.0f + m_py - 10.0f;
		}
		else
		{
			dst2.m_top = 0.0f + m_py - 10.0f;
			dst2.m_left = 0.0f + m_px + 40.0f;
			dst2.m_right = 20.0f + m_px + 40.0f;
			dst2.m_bottom = 32.0f + m_py - 10.0f;
		}

		//�`��
		Draw::Draw(11, &src2, &dst2, c, 0.0f);
	}
	else //�r��U�艺�낵�Ă���
	{

		dst2.m_top = 0.0f + m_py + 50.0f;
		dst2.m_left = 0.0f + m_px + 45.0f;
		dst2.m_right = 20.0f + m_px + 45.0f - m_hole_fall;
		dst2.m_bottom = 32.0f + m_py + 50.0f - m_hole_fall;


		//�`��
		Draw::Draw(11, &src2, &dst2, c, -100.0f);
	}

	
	//�e-------------------------------------------------------------
	//�W�����v���Ă��Ȃ��Ƃ�
	if (m_jamp_control_2 == false)
	{
		//���ɗ����Ă��Ȃ���Ε`��
		if (m_hole_control == false)
		{
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			//�\���ʒu�̐ݒ�
			dst.m_top = 60.0f + m_py;
			dst.m_left = -30.0f + m_px;
			dst.m_right = 55.0f + m_px;
			dst.m_bottom = 68.0f + m_py;

			//�`��
			Draw::Draw(25, &src, &dst, c, 1.0f);
		}
	}
	//�W�����v���Ă鎞
	else
	{
		//���ɗ����Ă��Ȃ���Ε`��
		if (m_hole_control == false)
		{
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			//�\���ʒu�̐ݒ�
			dst.m_top = 60.0f + m_jamp_y_position;
			dst.m_left = -30.0f + m_px;
			dst.m_right = 55.0f + m_px;
			dst.m_bottom = 68.0f + m_jamp_y_position;

			//�`��
			Draw::Draw(25, &src, &dst, shadowcolor, 1.0f);
		}
	}
	//--------------------------------------------------------------
	//�c�@-------------------------------------------------------------------------------
	if ((((UserData*)Save::GetData())->m_stage_count ==1))
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 64.0f;
		src.m_bottom = 192.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + 10.0f;
		dst.m_left = 0.0f + 680.0f;
		dst.m_right = 40.0f + 680.0f;
		dst.m_bottom = 40.0f + 10.0f;
	}
	if ((((UserData*)Save::GetData())->m_stage_count == 2))
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 64.0f;
		src.m_right = 128.0f;
		src.m_bottom = 192.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + 10.0f;
		dst.m_left = 0.0f + 680.0f;
		dst.m_right = 40.0f + 680.0f;
		dst.m_bottom = 40.0f + 10.0f;
	}
	if ((((UserData*)Save::GetData())->m_stage_count == 3))
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 128.0f;
		src.m_right = 192.0f;
		src.m_bottom = 192.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + 10.0f;
		dst.m_left = 0.0f + 680.0f;
		dst.m_right = 40.0f + 680.0f;
		dst.m_bottom = 40.0f + 10.0f;
	}
	//�c��̐�����`�悷��
	static wchar_t  c_siro[8];
	static float cl_siro[4] = { 0.0f,0.0f,0.0f,1.0f };
	swprintf_s(c_siro, L"X %d", m_remaining);
	CDrawFont::StrDraw(c_siro, 735, 16, 32, cl_siro);

	//�`��
	Draw::Draw(24, &src, &dst, c, 0.0f);
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