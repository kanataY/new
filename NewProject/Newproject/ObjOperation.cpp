//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\MultiThread.h"

#include "GameHead.h"
#include "GameL\UserData.h"
#include "ObjOperation.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjOperation::Init()
{
	m_scene_flag = 0;
	m_enter_control = false;
	m_zkey_control = false;
	m_scene_start_control_time = 0;

	m_ani_time = 0;
	m_ani_frame = 0;
	m_ani_max_time = 5;

	m_okam_ani_time = 0;
	m_okam_ani_frame = 0;
	m_okam_ani_max_time = 5;
}

//�A�N�V����
void CObjOperation::Action()
{
	m_scene_start_control_time++;
	////�G���^�[�L�[���������Ƃ��ɃR���g���[���^�C����2��艺�̎�
	if (Input::GetVKey(VK_RETURN) == true&& m_scene_start_control_time<2)
	{
		//�G���^�[�������Ă��Ȃ�����Ȃ�
		if (m_enter_control == false)
		{
			m_scene_flag = 0;
			m_enter_control = true;
		}
	}
	
	//�G���^�[�L�[���������Ƃ��ɃR���g���[���^�C����2�ȏ�̎�
	else if (Input::GetVKey(VK_RETURN) == true&&m_scene_start_control_time>=2)
	{
		//�G���^�[�L�[�������ĂȂ���Ԃł����
		if (m_enter_control == false)
		{
			//�V�[���t���O�̐��l��3����Ȃ���
			if (m_scene_flag!=3)
			{
				//�G���^�[�L�[�������ĂȂ���
				if (m_enter_control == false)
				{
					//�G���^�[�L�[����������ԂƔ��肷��
					m_enter_control = true;
					m_scene_flag++;
				}
			}

			//�V�[���t���O�̐��l���R�̎�
			else
			{
				//�G���^�[�L�[�������ĂȂ���
				if (m_enter_control == false)
				{
					//�G���^�[�L�[����������ԂƔ��肷��
					m_enter_control = true;

					//�V�[�������j���[�ɐ؂�ւ���
					Scene::SetScene(new CSceneMenu());
				}
			}
		}
	}
	//�G���^�[�L�[�������Ă��Ȃ���
	else
	{
		//�G���^�[�L�[�͉����Ă��Ȃ��Ɣ��肷��B
		m_enter_control = false;
	}
	
	//Z�L�[���������Ƃ�
	if (Input::GetVKey('Z') == true)
	{
		//Z�L�[�������ĂȂ���Ԃł����
		if (m_zkey_control == false)
		{
			//�V�[���t���O�̐��l��0����Ȃ���
			if (m_scene_flag !=0)
			{

				//Z�L�[�������ĂȂ��Ȃ�
				if (m_zkey_control == false)
				{
					//Z�L�[����������ԂƔ��肷��
					m_zkey_control = true;
					m_scene_flag --;
				}

			}
			//�V�[���t���O�̐��l��0�̎�
			else
			{
				//Z�L�[�������ĂȂ���
				if (m_zkey_control == false)
				{
					//Z�L�[����������ԂƔ��肷��
					m_zkey_control = true;

					//�V�[�������j���[�ɐ؂�ւ���
					Scene::SetScene(new CSceneMenu());
				}
			}
		}
	}
	//Z�L�[�������Ă��Ȃ���
	else
	{
		//Z�L�[�͉����Ă��Ȃ��Ɣ��肷��B
		m_zkey_control = false;
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

	m_okam_ani_time++;//�t���[�����슴�o�^�C����i�߂�
	if (m_okam_ani_time > m_okam_ani_max_time)//�t���[�����슴�o�^�C�����ő�܂ōs������
	{
		m_okam_ani_frame++;//�t���[����i�߂�
		m_okam_ani_time = 0;
	}
	if (m_okam_ani_frame == 7)//�t���[�����Ō�܂Ői�񂾂�߂�
	{
		m_okam_ani_frame = 0;
	}
	//�A�j���[�V�����I���|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
	
}

//�h���[
void CObjOperation::Draw()
{
	//�^�C�g�����
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	wchar_t str[128];

	//����������------------------------------------
	//�V�[��1�̎�
	if (m_scene_flag == 0)
	{
		
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
		//0�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(0, &src, &dst, c, 0.0f);

		//�i�Ƃ��Ɏg�������ݒ�
		swprintf_s(str, L"Enterkey�Ŏ���");
		//�i�Ƃ��Ɏg��������`��
		Font::StrDraw(str, 655, 580, 20, c);

		//�߂�Ƃ��Ɏg�������ݒ�
		swprintf_s(str, L"Zkey��Menu��");
		//�߂�Ƃ��Ɏg��������`��
		Font::StrDraw(str, 5, 580, 20, c);
	}
	//�V�[��2�̎�
	if (m_scene_flag == 1)
	{
		//�w�i----------------------------------------------------------------------------------------
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
		//1�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(1, &src, &dst, c, 0.0f);
		//--------------------------------------------------------------------------
		//�X�}�z-----------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame * 64;
		src.m_right = 64.0f + m_ani_frame * 64;
		src.m_bottom = 256.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 280.0f;
		dst.m_left = 90.0f;
		dst.m_right = dst.m_left + 80.0f;
		dst.m_bottom = dst.m_top + 64.0f;

		//�`��
		Draw::Draw(3, &src, &dst, c, 0.0f);
		//-----------------------------------------------------------

		//������-------------------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_okam_ani_frame * 64;
		src.m_right = 64.0f + m_okam_ani_frame * 64;
		src.m_bottom = 512.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 380.0f;
		dst.m_right = 90.0f;
		dst.m_left = dst.m_right + 80.0f;
		dst.m_bottom = dst.m_top + 64.0f;

		//4�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(4, &src, &dst, c, 0.0f);
		//-----------------------------------------------------------------------
		//�g���b�N-----------------------------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame * 128;
		src.m_right = 128.0f + m_ani_frame * 128;
		src.m_bottom = 512.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 480.0f;
		dst.m_right = 90.0f;
		dst.m_left = 90.0f + dst.m_right;
		dst.m_bottom = dst.m_top + 70.0f;

		//�`��
		Draw::Draw(5, &src, &dst, c, 0.0f);
		//--------------------------------------------------------------------------


		//�i�Ƃ��Ɏg�������ݒ�
		swprintf_s(str, L"Enterkey�Ŏ���");
		//�i�Ƃ��Ɏg��������`��
		Font::StrDraw(str, 655, 580, 20, c);
		//�߂�Ƃ��Ɏg�������ݒ�
		swprintf_s(str, L"Zkey�őO��");
		//�߂�Ƃ��Ɏg��������`��
		Font::StrDraw(str, 5, 580, 20, c);
	}

	//�V�[��3�̎�
	if (m_scene_flag == 2)
	{
		//�w�i--------------------------------------------------
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
		//2�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(2, &src, &dst, c, 0.0f);
		//--------------------------------------------------------------

		//�X�}�z-----------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame * 64;
		src.m_right = 64.0f + m_ani_frame * 64;
		src.m_bottom = 256.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 200.0f;
		dst.m_left = 90.0f;
		dst.m_right = dst.m_left + 80.0f;
		dst.m_bottom = dst.m_top + 64.0f;

		//�`��
		Draw::Draw(3, &src, &dst, c, 0.0f);
		//-----------------------------------------------------------

		//������-------------------------------------------------------------
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_okam_ani_frame * 64;
		src.m_right = 64.0f + m_okam_ani_frame * 64;
		src.m_bottom = 512.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 330.0f;
		dst.m_right = 90.0f;
		dst.m_left = dst.m_right + 80.0f;
		dst.m_bottom = dst.m_top + 64.0f;

		//4�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(4, &src, &dst, c, 0.0f);
		//-----------------------------------------------------------------------
		//�g���b�N-----------------------------------------------------------------------
		//�؂���ʒu�̐ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f + m_ani_frame * 128;
		src.m_right = 128.0f + m_ani_frame * 128;
		src.m_bottom = 512.0f;

		//�\���ʒu�̐ݒ�
		dst.m_top = 450.0f;
		dst.m_right = 90.0f;
		dst.m_left = 90.0f+ dst.m_right;
		dst.m_bottom = dst.m_top+90.0f;

		//�`��
		Draw::Draw(5, &src, &dst, c, 0.0f);

		//----------------------------------------------------------------------------------------

		//�i�Ƃ��Ɏg�������ݒ�
		swprintf_s(str, L"Enterkey�Ŏ���");
		//�i�Ƃ��Ɏg��������`��
		Font::StrDraw(str, 655, 580, 20, c);
		//�߂�Ƃ��Ɏg�������ݒ�
		swprintf_s(str, L"Zkey�őO��");
		//�߂�Ƃ��Ɏg��������`��
		Font::StrDraw(str, 5, 580, 20, c);
	}
	//---------------------------------------------------------
	if (m_scene_flag == 3)
	{
		//�w�i--------------------------------------------------
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
		//2�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(6, &src, &dst, c, 0.0f);
		//--------------------------------------------------------------

		//�i�Ƃ��Ɏg�������ݒ�
		swprintf_s(str, L"Enterkey��Menu��");
		//�i�Ƃ��Ɏg��������`��
		Font::StrDraw(str, 635, 580, 20, c);
		//�߂�Ƃ��Ɏg�������ݒ�
		swprintf_s(str, L"Zkey�őO��");
		//�߂�Ƃ��Ɏg��������`��
		Font::StrDraw(str, 5, 580, 20, c);
	}
}