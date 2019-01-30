//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjGolem.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGolem::CObjGolem(float x, float y)
{
	m_px = x;
	m_py = y;

}

//�C�j�V�����C�Y
void CObjGolem::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_speed = 0.5f;
	m_audio_flag = false;
	m_audio_footsteps_flag = false;

	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 15; //�A�j���[�V�����Ԋu��

	m_ani_time_del = 0;
	m_ani_frame_del = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time_del = 10; //�A�j���[�V�����Ԋu��

	m_move = true;
	m_pos = 0.0f;//������
				 //block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //����ł���block�̎�ނ��m�F�p

	m_del = false;//���ʂƂ��̃t���O
	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 40, 64, ELEMENT_ENEMY, OBJ_GOLEM, 1);
}

//�A�N�V����
void CObjGolem::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//��l���̏��������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//�A�j���[�V�����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	m_ani_time++;//�t���[�����슴�o�^�C����i�߂�
	if (m_ani_time > m_ani_max_time)//�t���[�����슴�o�^�C�����ő�܂ōs������
	{
		m_ani_frame++;//�t���[����i�߂�
		m_ani_time = 0;
	}
	if (m_ani_frame == 8)//�t���[�����Ō�܂Ői�񂾂�߂�
	{
		m_ani_frame = 0;
	}

	//�������ł�A�j���[�V�������ɑ������o��
	if ((m_ani_frame == 3 && m_audio_footsteps_flag == false) || (m_ani_frame == 7 && m_audio_footsteps_flag == false))
	{
		Audio::Start(8);
		m_audio_footsteps_flag = true;	//���̂ݖ炷
	}

	if(m_ani_frame == 4 || m_ani_frame == 1)//�t���[�����i�񂾂������x�点��悤�ɖ߂�
	{
		m_audio_footsteps_flag = false;
	}

	//�A�j���[�V�����I���|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	if (m_pos == 1.0)
	hit->SetPos(m_px+15 + block->GetScroll(), m_py);
	else
		hit->SetPos(m_px+10 + block->GetScroll(), m_py);
	float c = m_px + block->GetScroll();

	block->BlockHit(&c, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type, false,false,0,false,false
	);

	Hit(); //�����蔻��

    //�������ǂɓ�����Ɣ��]
	if (m_hit_left == true || hit->CheckObjNameHit(OBJ_HERO) != nullptr && hero->GetHitLeft() == true)
	{
		m_move = true;
	}
	//�E�����ǂɓ�����Ɣ��]
	if (m_hit_right == true || hit->CheckObjNameHit(OBJ_HERO) != nullptr && hero->GetHitRight() == true)
	{
		m_move = false;
	}

	//�ړ�����
	if (m_move == false&&m_del==false)
	{
		m_vx += m_speed;
		m_pos = 1.0f;
	}
	if (m_move == true && m_del == false)
	{
		m_vx -= m_speed;
		m_pos = 0.0f;
	}
	
	//���R�����^��
	m_vy += 9.8 / (16.0f);
	
	m_vx += -(m_vx * 0.16f);

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	//�����Ă���Ƃ�
	if (m_py > 600.0f)
		Audio::Stop(8);    //����������

	//���񂾂Ƃ������o��
	if (m_del == true && m_audio_flag == false)
	{
		Audio::Start(7); //����鉹
		m_audio_flag = true;
	}

	//���S����
	if (m_ani_frame_del > 2)
	{
		m_ani_max_time_del = 15;
	}
	if (m_del == true &&m_ani_frame_del<6 )
	{
		m_ani_time_del++;
	}
	if (m_ani_time_del > m_ani_max_time_del)//�t���[�����슴�o�^�C�����ő�܂ōs������
	{
		m_ani_frame_del++;//�t���[����i�߂�
		m_ani_time_del = 0;
	}
	if (m_ani_frame_del == 5)//�t���[�����Ō�܂Ői�񂾂�߂�
	{
		//�h���b�v�A�C�e������
		CObjDropGold* drop = new CObjDropGold(m_px, m_py+40);
		Objs::InsertObj(drop, OBJ_DROP_GOLD, 16);

		Audio::Stop(7);//����鉹���~�߂�
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;//���ŏ����́A�����ŃA�N�V�������]�b�h���I��������
	}
}

//�h���[
void CObjGolem::Draw()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	if (m_del == false)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame * 64;
		src.m_right = 64.0f + m_ani_frame * 64;
		src.m_bottom = 512.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = (64.0f*m_pos) + m_px + block->GetScroll();
		dst.m_right = (64.0f - 64.0f*m_pos) + m_px + block->GetScroll();
		dst.m_bottom = 64.0f + m_py;

		Draw::Draw(11, &src, &dst, c, 0.0f);
	}
	//�`��
	if (m_del == true)
	{
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame_del * 64;
		src.m_right = 64.0f + m_ani_frame_del * 64;
		src.m_bottom = 384.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 0.0f + m_py;
		dst.m_left = (64.0f*m_pos) + m_px + block->GetScroll();
		dst.m_right = (64.0f - 64.0f*m_pos) + m_px + block->GetScroll();
		dst.m_bottom = 64.0f + m_py;
		Draw::Draw(12, &src, &dst, c, 0.0f);
	}
		


}

//�����蔻��
void CObjGolem::Hit()
{
	//HitBox���擾
	CHitBox* hit = Hits::GetHitBox(this);
	
	//����ɓ������Ă��鎞
	if (hit->CheckObjNameHit(OBJ_GOLD) != nullptr)
	{
		//�ǂ̊p�x�œ������Ă��邩���m�F
		HIT_DATA** hit_data;                        //���������Ƃ��ׂ̍₩�ȏ������邽�߂̍\����
		hit_data = hit->SearchObjNameHit(OBJ_GOLD); //hit_data��HitBox�Ƃ̏�������

		for (int i = 0; i < hit->GetCount(); i++)
		{
			if (hit_data[i] != NULL)
			{
				float r2 = hit_data[i]->r;

				//��ɏ���悤�ɂ���
				if (r2 >= 210 && r2 < 340)
				{
					//�܂��A�n�ʂɓ������Ă��锻��ɂ���
					m_vy = 0.0f;
					m_hit_down = true;
				}
				if (r2 > 160 && r2 < 200)
				{
					//��
					m_hit_right = true;

				}

				if (r2 < 45 && r2>0 || r2 > 330)
				{
					//�E
					m_hit_left = true;
				}
			}
		}
	}
}