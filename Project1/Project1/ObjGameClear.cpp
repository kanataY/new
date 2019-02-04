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
	m_time = 0;
	m_ani_time = 0;
	m_ani_frame = 0;
	m_ani_max_time = 8;

	//�����L���O�ɓ����
	Ranking();
}

//�A�N�V����
void CObjGameClear::Action()
{

	m_time++;


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
	if (Input::GetVKey(VK_RETURN) == true)
	{
		Scene::SetScene(new CSceneTitle());
	}


	
}

//�h���[
void CObjGameClear::Draw()
{
	//clear���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	float color[4] = { 0.0f,0.0f,0.0f,1.0f };
	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

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

	Draw::Draw(m_ani_frame, &src, &dst, c, 0.0f);

	//�؂���ʒu�ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 512.0f;
	src.m_bottom = 512.0f;

	//�`��ʒu�ݒ�
	dst.m_top = 100.0f;
	dst.m_left = 120.0f;
	dst.m_right = dst.m_left + 600.0f;
	dst.m_bottom = dst.m_top + 300.0f;

	Draw::Draw(5, &src, &dst, c, 0.0f);


	wchar_t str[128];
	swprintf_s(str, L"���_�F%d�_", ((UserData*)Save::GetData())->m_point);
	Font::StrDraw(str, 200, 64,48, color);

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
			/*	if (j == RANKING_MAX_COUNT - 1)
				{
					m_ranking_in_floag = true;
				}*/
			}
		}
	}

	//�X�e�[�W1�ŏ���������
	((UserData*)Save::GetData())->m_stage_count = 1;

	Save::Seve();//�Z�[�u
}