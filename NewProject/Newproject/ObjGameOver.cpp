//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameHead.h"
#include "ObjGameOver.h"
#include "GameL\UserData.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjGameOver::Init()
{
	m_key_flag = false;
	
	m_time = 0;
	m_ranking_in_floag = false;


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
				//�l�̕ύX�E���O�̕ύX
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

	//�Z�[�u
	Save::Seve();
}

//�A�N�V����
void CObjGameOver::Action()
{
	m_time++;

	//���j���[��ʂ�
	if (Input::GetVKey('Z') == true)
	{
		//�����L���O�ɔ��f�����X�R�A������������
		((UserData*)Save::GetData())->m_point = 0;
		//���j���[�Ɉڍs
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

//�h���[
void CObjGameOver::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//Font::StrDraw(L"GAMEOVER", 10, 10, 100, c);

	RECT_F src;	//�`���؂���ʒu
	RECT_F dst;	//�`���\���ʒu

	//�w�i--------------------------------
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	Draw::Draw(0, &src, &dst, c, 0.0f);

	//�X�R�A
	//���_�̕`��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	wchar_t str[128];
	swprintf_s(str, L"�X�R�A�F%d�_", ((UserData*)Save::GetData())->m_point);
	Font::StrDraw(str, 220, 210, 38, c);
	//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
	//���j���[�J�ڐ���
	Font::StrDraw(L"Z�Ń��j���[��", 20, 550, 24, c);

	//�����L���O�J�ڐ���
	Font::StrDraw(L"X�Ń����L���O��", 600, 550, 24, c);
	//----------------------------------------------------

}