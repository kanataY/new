//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\MultiThread.h"

#include "GameHead.h"
#include "GameL\UserData.h"
#include "ObjTitle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjTitle::Init()
{

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
	if (Input::GetVKey(VK_UP) == true || Input::GetVKey(VK_DOWN) == true)
	{
		//�L�[�̃R���g���[����false�Ȃ�
		if (m_key_control == false)
		{
			//�L�[�̃R���g���[����true�ɂ���
			m_key_control = true;

			//�t���O��0�̎�
			if (m_key_flag == 0)
				//�t���O��1��
				m_key_flag = 1;

			//�t���O���P�̎�
			else if (m_key_flag == 1)
				//�t���O��0��
				m_key_flag = 0;
		}
	}
	//�\���L�[��������ĂȂ���
	else
	{
		//�L�[�̃R���g���[����false
		m_key_control = false;
	}
	//�G���^�[�L�[�������ꂽ��2frame�o���Ă�����
	if (Input::GetVKey(VK_RETURN) == true&&m_scene_start_control >=2)
	{
		//�G���^�[�R���g���[����false�̎�
		if (m_enter_control==false)
		{
			//���j���[�ւ̈ʒu�Ȃ�
			if (m_key_flag == 0)
			{
				
				//�V�[�������j���[��
				Scene::SetScene(new CSceneMenu());
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

	//0�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
	Draw::Draw(0, &src, &dst, c, 0.0f);
	//---------------------------------------------------------

	//�^�C�g���̕���-------------------------------------------
	//�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//�`��ʒu�ݒ�
	dst.m_top = 80.0f;
	dst.m_left = 90.0f;
	dst.m_right = dst.m_left+590.0f;
	dst.m_bottom = dst.m_top+140.0f;

	//1�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
	Draw::Draw(1, &src, &dst, c, 0.0f);
	//-------------------------------------------------------------

	//���j���[�̕���-------------------------------------------
	//�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//�`��ʒu�ݒ�
	dst.m_top = 290.0f;
	dst.m_left = 150.0f;
	dst.m_right = dst.m_left + 512.0f;
	dst.m_bottom = dst.m_top + 120.0f;

	//2�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
	Draw::Draw(2, &src, &dst, c, 0.0f);
	///-------------------------------------------------------------

	//�I���̕���-------------------------------------------
	//�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//�`��ʒu�ݒ�
	dst.m_top = 420.0f;
	dst.m_left = 150.0f;
	dst.m_right = dst.m_left + 512.0f;
	dst.m_bottom = dst.m_top + 120.0f;

	//3�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
	Draw::Draw(3, &src, &dst, c, 0.0f);
	///-------------------------------------------------------------

	//�g�̕`��-------------------------------------------
	if (m_key_flag == 0)
	{
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

		//�`��ʒu�ݒ�
		dst.m_top = 282.0f;
		dst.m_left = 130.0f;
		dst.m_right = dst.m_left + 520.0f;
		dst.m_bottom = dst.m_top + 130.0f;

		//4�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	else
	{
		
		//�؂���ʒu�ݒ�
		src.m_top = 0.0f;
		src.m_left = 0.0f;
		src.m_right = 512.0f;
		src.m_bottom = 512.0f;

		//�`��ʒu�ݒ�
		dst.m_top = 412.0f;
		dst.m_left = 130.0f;
		dst.m_right = dst.m_left + 520.0f;
		dst.m_bottom = dst.m_top + 130.0f;

		//4�Ԗڂɓo�^���Ă���src�Edst�Ec�ŕ`�悷��
		Draw::Draw(4, &src, &dst, c, 0.0f);
	}
	//-------------------------------------------------------------
}