//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "ObjGameClear.h"
#include "GameHead.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjGameClear::Init()
{
	m_ranking_in_floag = false;
	m_time = 0;
	m_ani_time = 0;
	m_ani_frame = 0;
	m_ani_max_time = 5;
	m_o_tap_flag = false;
	m_audio_flag = false;

	//�����L���O�ɓ����
	Ranking();
}

//�A�N�V����
void CObjGameClear::Action()
{
	
	m_time++;

	//�^�C����100�𒴂���Ƃ�
	if (m_time > 100)
	{
		//o��������
		if (Input::GetVKey('O') == true)
		{
			//o���������Ƃ����t���O�𗧂Ă�
			m_o_tap_flag = true;

			if (m_audio_flag == false)
			{
				//���y�X�^�[�g
				Audio::Start(1);
				m_audio_flag = true;
			}
		}


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

		//���j���[��ʂ�
		if (Input::GetVKey('Z') == true)
		{
			//�����L���O�ɔ��f�����X�R�A������������
			((UserData*)Save::GetData())->m_point = 0;
			Scene::SetScene(new CSceneMenu());
		}

		//�����L���O��ʂ�
		if (Input::GetVKey('X') == true)
		{
			//�����L���O�ɔ��f�����X�R�A������������
			((UserData*)Save::GetData())->m_point = 0;
			Scene::SetScene(new CSceneRanking());
		}
	}
}

//�h���[
void CObjGameClear::Draw()
{
	//�^�C�g�����
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float color[4] = { 1.0f,1.0f,1.0f,0.5f };
	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�؂���ʒu
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 800.0f;
	src.m_bottom = 800.0f;

	if (m_time <= 40)
	{
		
		//�\���ʒu
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//�w�i�`��
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
	else if (m_time > 40 && m_time <= 80)
	{
	
		//�\���ʒu
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//�w�i�`��
		Draw::Draw(2, &src, &dst, c, 0.0f);
	}
	else if (m_time > 80)
	{
		//�\���ʒu
		dst.m_top = 0.0f;
		dst.m_left = 0.0f;
		dst.m_right = 800.0f;
		dst.m_bottom = 600.0f;

		//�w�i�`��
		Draw::Draw(3, &src, &dst, c, 0.0f);
	}

	if (m_time > 100)
	{
		//o��������Ă��Ȃ��Ƃ�
		if (m_o_tap_flag == false)
		{
			//�؂���ʒu
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 512.0f;
			src.m_bottom = 512.0f;

			//�\���ʒu
			dst.m_top = 20.0f;
			dst.m_left = 140.0f;
			dst.m_right = dst.m_left + 512.0f;
			dst.m_bottom = dst.m_top + 512.0f;

			//�w�i�`��
			Draw::Draw(4, &src, &dst, c, 0.0f);


			//�؂���ʒu
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 64.0f;
			src.m_bottom = 64.0f;

			//�\���ʒu
			dst.m_top = 350.0f;
			dst.m_left = 320.0f;
			dst.m_right = dst.m_left + 128.0f;
			dst.m_bottom = dst.m_top + 128.0f;
			//�w�i�`��
			Draw::Draw(5, &src, &dst, c, 0.0f);
		}
		else
		{

			//�w�i�̕`��--------------------------------------------------------------------
			//�؂���ʒu
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 800.0f;
			src.m_bottom = 800.0f;
			//�\���ʒu
			dst.m_top = 0.0f;
			dst.m_left = 0.0f;
			dst.m_right = 800.0f;
			dst.m_bottom = 600.0f;

			//�w�i�`��
			Draw::Draw(1, &src, &dst, c, 0.0f);
			//--------------------------------------------------------------------------

			//�΂̕`��-------------------------------------------------------
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f + m_ani_frame * 64;
			src.m_right = 64.0f + m_ani_frame * 64;
			src.m_bottom = 320.0f;

			//�\���ʒu�̐ݒ�
			dst.m_top = -105.0f;
			dst.m_left = 128.0f;
			dst.m_right = dst.m_left + 512.0f;
			dst.m_bottom = dst.m_top + 192.0f;
			//�΂̕`��
			Draw::Draw(0, &src, &dst, c, 0.0f);
			//--------------------------------------------------------------------------

			//�����̕`��------------------------------------------------------------------
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = 1024.0f;
			src.m_bottom = 1024.0f;

			//�\���ʒu�̐ݒ�
			dst.m_top = 30.0f;
			dst.m_left = 0.0f;
			dst.m_right = dst.m_left + 810.0f;
			dst.m_bottom = dst.m_top + 290.0f;
			//�΂̕`��
			Draw::Draw(6, &src, &dst, c, 0.0f);
			//--------------------------------------------------------------------------

			//�X�R�A
			//���_�̕`��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
			wchar_t str[128];
			swprintf_s(str, L"�X�R�A�F%d�_", ((UserData*)Save::GetData())->m_point);
			Font::StrDraw(str, 220, 380, 38, c);
			//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
			//���j���[�J�ڐ���
			Font::StrDraw(L"Z�Ń��j���[��", 180, 490, 24, c);

			//�����L���O�J�ڐ���
			Font::StrDraw(L"X�Ń����L���O��", 500, 490, 24, c);
		}
	}
}

//Ranking�֐�---------------------------------------------
//���e
//�ŏI�X�R�A�������L���O�̂ǂ��Ƀ����N�C�������ǂ����𒲂ׂă����L���O�ɓ����֐�
void CObjGameClear::Ranking()
{
	//�l�����p
	int w;

	//�X�R�A�������L���O�̍Ō�ɓ����
	((UserData*)Save::GetData())->m_ranking[RANKING_MAX_COUNT - 1] = ((UserData*)Save::GetData())->m_point;

	//�����L���O�ϓ��m�F
	//�o�u���\�[�g
	for (int i = 0; i < RANKING_MAX_COUNT - 1; i++)
	{
		for (int j = i + 1; j < RANKING_MAX_COUNT; j++)
		{
			if (((UserData*)Save::GetData())->m_ranking[i] < ((UserData*)Save::GetData())->m_ranking[j])
			{
				//�l�̕ύX
				w = ((UserData*)Save::GetData())->m_ranking[i];
				((UserData*)Save::GetData())->m_ranking[i] = ((UserData*)Save::GetData())->m_ranking[j];
				((UserData*)Save::GetData())->m_ranking[j] = w;
				
				//�X�R�A�������L���O������ʂ��������ǂ���
				if (j == RANKING_MAX_COUNT - 1)
				{
					m_ranking_in_floag = true;
				}
			}
		}
	}

	//�X�e�[�W1�ŏ���������
	((UserData*)Save::GetData())->m_stage_count = 1;

	Save::Seve();//�Z�[�u
}