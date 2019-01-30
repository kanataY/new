//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\MultiThread.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "GameL\UserData.h"
#include "ObjTitle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTitle::Init()
{
	m_ani_time = 0;
	m_ani_frame = 0;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 15; //�A�j���[�V�����Ԋu��

	m_ani_time2 = 0;
	m_ani_max_time2 = 3;
	m_ani_start_flag = false;

	m_key_flag = 0;
	m_key_control = false;
	m_enter_control = false;
	m_scene_start_control = 0;

	//�Q�[�����s���Ĉ��̂�
	static bool init_point = false;
	if (init_point == false)
	{
		//�����L���O������
		for (int i = 0; i < RANKING_MAX_COUNT - 1; i++)
		{
			((UserData*)Save::GetData())->m_ranking[i] = 0;
		}

		//���[�h
		Save::Open();//���t�H���_�uUserData�v����f�[�^�擾

		init_point = true;
	}

	//�X�R�A��0�ŏ���������
	((UserData*)Save::GetData())->m_point = 0;

	
}

//�A�N�V����
void CObjTitle::Action()
{
	m_scene_start_control++;

	//�\���L�[�̏ォ�����������Ƃ�
	if (Input::GetVKey(VK_LEFT) == true && m_ani_frame == 4)
	{
		//�L�[�̃R���g���[����false�Ȃ�
		if (m_key_control == false)
		{
			//�L�[�̃R���g���[����true�ɂ���
			m_key_control = true;

			//�t���O��0�̎�
			if (m_key_flag == 0)
			{
				//�t���O��1��
				m_key_flag = 1;
				Audio::Start(1);
			}

			//�t���O���P�̎�
			else if (m_key_flag == 1)
			{
				//�t���O��0��
				m_key_flag = 0;
				Audio::Start(1);
			}
		}
	}
	//�\���L�[��������ĂȂ���
	else
	{
		//�L�[�̃R���g���[����false
		m_key_control = false;
	}
	//�G���^�[�L�[�������ꂽ��2frame�o���Ă�����
	if (Input::GetVKey(VK_RETURN) == true && m_ani_frame==4)
	{
		//�G���^�[�R���g���[����false�̎�
		if (m_enter_control==false)
		{
			//���j���[�ւ̈ʒu�Ȃ�
			if (m_key_flag == 0)
			{
				m_ani_start_flag = true;
				Audio::Start(2);
			}
			//�I���̈ʒu�Ȃ�
			if (m_key_flag == 1)
			{
				//�Q�[�����I��������
				CMultiThread::End();
			}
			//�G���^�[�L�[����������ԂƔ��肷��
			m_enter_control = true;
		}
	}
	//�G���^�[�L�[�������ꂽ��2frame�o���Ă��Ȃ�������
	else if (Input::GetVKey(VK_RETURN) == true && m_scene_start_control <= 2)
	{
		//�G���^�[�L�[�͉����Ă����ԂƂ���B
		m_enter_control = true;
	}
	else
	{
		//�G���^�[�L�[�͉����Ă͂��Ȃ���ԂƂ���
		m_enter_control = false;
	}

	//�A�j���[�V�����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	if (m_ani_frame < 4)//frame��5�ɂȂ�܂ł̓A�j���[�V����������B
	{
		m_ani_time++;//�t���[�����슴�o�^�C����i�߂�
	}
	if (m_ani_time > m_ani_max_time)//�t���[�����슴�o�^�C�����ő�܂ōs������
	{
		m_ani_frame++;//�t���[����i�߂�
		m_ani_time = 0;
	}

	if (m_ani_start_flag == true)
	{
		m_ani_time2++;
	}
	if (m_ani_time2 > m_ani_max_time2)
	{
		if (m_ani_frame < 10)
		{
			m_ani_frame++;//frame�i�߂�
			m_ani_time2 = 0;
		}
	}
	if (m_ani_frame == 10 && Audio::CheckSound(2) == false)//�t���[�����Ō�܂Ői�񂾂�߂�
	{
		
		//�V�[�������j���[��
		((UserData*)Save::GetData())->m_stage_count = 1; //���C���ɕς���
		Scene::SetScene(new CSceneMain());
	}
	//�A�j���[�V�����I���|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

}

//�h���[
void CObjTitle::Draw()
{
	//�^�C�g�����
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�^�C�g�����---------------------------------------
	//�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//�`��ʒu�ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;
	if (m_ani_frame < 11)//�V�[���J�ڂ̎�11�ɓo�^���Ă���摜���o�Ă���̂Ő��䂷��
	{
		//m_ani_frame�Ɠ����ԍ��ɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(m_ani_frame, &src, &dst, c, 0.0f);
	}
	//---------------------------------------------------------

	//�^�C�g���̕���-------------------------------------------
	//�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//�`��ʒu�ݒ�
	dst.m_top = -80.0f;
	dst.m_left = 120.0f;
	dst.m_right = dst.m_left+512.0f;
	dst.m_bottom = dst.m_top+512.0f;

	//1�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
	Draw::Draw(15, &src, &dst, c, 0.0f);
	//-------------------------------------------------------------

	//�X�^�[�g�̕���-------------------------------------------
	//�؂���ʒu�ݒ�
	if (m_ani_frame >= 4 && m_key_flag == 0)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//�`��ʒu�ݒ�
		dst.m_top = 420.0f;
		dst.m_left = 545.0f;
		dst.m_right = dst.m_left + 256.0f;
		dst.m_bottom = dst.m_top + 134.0f;

		//11�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(11, &src, &dst, c, 0.0f);
	}
	if (m_ani_frame >= 4 && m_key_flag == 1)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//�`��ʒu�ݒ�
		dst.m_top = 420.0f;
		dst.m_left = 545.0f;
		dst.m_right = dst.m_left + 256.0f;
		dst.m_bottom = dst.m_top + 134.0f;

		//12�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(12, &src, &dst, c, 0.0f);
	}
	///-------------------------------------------------------------
	//�����L���O�̕���-------------------------------------------
	if (m_ani_frame >= 4 && m_key_flag == 1)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//�`��ʒu�ݒ�
		dst.m_top = 425.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + 256.0f;
		dst.m_bottom = dst.m_top + 128.0f;

		//13�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(13, &src, &dst, c, 0.0f);
	}
	if (m_ani_frame >= 4 && m_key_flag == 0)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//�`��ʒu�ݒ�
		dst.m_top = 425.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + 256.0f;
		dst.m_bottom = dst.m_top + 128.0f;

		//14�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(14, &src, &dst, c, 0.0f);
	}
	///-------------------------------------------------------------
	//�I���̕���-------------------------------------------
	if (m_ani_frame >= 4&&m_key_flag==1)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//�`��ʒu�ݒ�
		dst.m_top = 425.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + 256.0f;
		dst.m_bottom = dst.m_top + 128.0f;

		//15�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(15, &src, &dst, c, 0.0f);
	}
	if(m_ani_frame >= 4 && m_key_flag == 0)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 256.0f;
		src.m_bottom = 256.0f;

		//�`��ʒu�ݒ�
		dst.m_top = 425.0f;
		dst.m_left = 0.0f;
		dst.m_right = dst.m_left + 256.0f;
		dst.m_bottom = dst.m_top + 128.0f;

		//14�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(14, &src, &dst, c, 0.0f);
	}
	///-------------------------------------------------------------
}