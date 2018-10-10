//�g�p����w�b�_�[�t�@�C��
#include <string.h>
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\Audio.h"
#include "GameHead.h"
#include "GameL\UserData.h"
#include <mbstring.h>

#include "ObjRanking.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void CObjRanking::Init()
{
	//�߂�Ƃ��̕����̃T�C�Y
	//�o�C�g�����P�̂Ƃ�0.5	�Q�̂Ƃ�1.0�Ƃ���
	float m_interval = 6.5f;
}

//�A�N�V����
void CObjRanking::Action()
{
	//Z�L�[�������ꂽ��V�[�����j���[��
	if (Input::GetVKey('Z') == true)
	{
		Scene::SetScene(new CSceneMenu());
	}
}

//�h���[
void CObjRanking::Draw()
{
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	//�����L���O��p�w�i�`��
	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�ő包���i�[�p�ϐ�
	int max_number = 0;

	//�����L���O���Ƃ̌������i�[�p�ϐ�
	int number[RANKING_MAX_COUNT];

	//���l�̍ő包���𒲂ׂ�(�����낦�����邽��)
	for (int ranking_count = 0; ranking_count < RANKING_MAX_COUNT; ranking_count++)
	{
		//�����j���O��ranking_count�Ԃ̐��l���i�[
		int ranking = ((UserData*)Save::GetData())->m_ranking[ranking_count];
		//���l��9���`1���̊Ԃŉ������邩�Ȃǂ𒲂ׂ�
		for (int num_max = 100000000, digit = 9; num_max >= 1; num_max /= 10, digit--)
		{
			//�����𒲂ׂ�
			if ((ranking / num_max != 0 && ranking > 0) || num_max == 1)
			{
				//�����i�[
				number[ranking_count] = digit;
				//�����ő包���ȏ�Ȃ�㏑��
				if (max_number < digit)
				{
					max_number = digit;
				}
				break;
			}
		}
	}

	//�w�i�̕`��----------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 600.0f;

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);
	//-----------------------------------------------------------------

	//�����L���O�𕶎���
	for (int ranking_count = 0; ranking_count < RANKING_MAX_COUNT - 1; ranking_count++)
	{
		//�����L���O��ranking_count�Ԃ̐��l���i�[
		int ranking = ((UserData*)Save::GetData())->m_ranking[ranking_count];
		
		//���ʕ`��
		DrawNumber(128.0f* ranking_count + 128.0f, 64.0f + 64.0f, 64.0f, ranking_count + 1, m_interval, c);
		//�����L���O�̒l�`�揈��
		DrawNumber(128.0f* ranking_count + 128.0f, 224.0f + (max_number - number[ranking_count]) * 64.0f, 64.0f, ranking, m_interval, c);
	}
	//�ʂ̕`��-------------------------------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 138.0f;
	dst.m_left =175.0f;
	dst.m_right =dst.m_left+56.0f;
	dst.m_bottom =dst.m_top+56.0f;
	//�`��
	Draw::Draw(2, &src, &dst, c, 0.0f);

	//�\���ʒu�̐ݒ�
	dst.m_top = 265.0f;
	dst.m_left = 175.0f;
	dst.m_right = dst.m_left + 56.0f;
	dst.m_bottom = dst.m_top + 56.0f;
	//�`��
	Draw::Draw(2, &src, &dst, c, 0.0f);

	//�\���ʒu�̐ݒ�
	dst.m_top = 392.0f;
	dst.m_left = 175.0f;
	dst.m_right = dst.m_left + 56.0f;
	dst.m_bottom = dst.m_top + 56.0f;
	//�`��
	Draw::Draw(2, &src, &dst, c, 0.0f);
	//------------------------------------------------------------------------------
	wchar_t str[128];
	//�߂�Ƃ��Ɏg�������ݒ�
	swprintf_s(str, L"Zkey��Menu��");
	//�߂�Ƃ��Ɏg��������`��
	Font::StrDraw(str, 5, 580, 20, c);

}


//������`��֐�
//����1	float dst_top	:Y�ʒu���	
//����2	float dst_left	:X�ʒu���
//����3	float dst_size	:�`�悳����l�̑傫��
//����4	int num			:�`�悳����l
//����5	float�@interval	:�l�ƒl�̊Ԃ̊Ԋu�������߂�l(�傫���������΂����ƂɂȂ��)
//����6	float c[4]		:�`��J���[���
//���l��`�悳����(Draw�ŕ`��)
void CObjRanking::DrawNumber(float dst_top, float dst_left, float dst_size, int num, float interval, float c[4])
{
	//�����̐��@�@��j1568�Ȃ琔���̐���4
	int numeric_number = 0;

	//�����𕪉��������i�[�p
	int num_decomposition[100] = { 0 };

	//�ꌅ�łȂ����ǂ���	false=�ꌅ�@true=�ꌅ�ł͖����@
	bool not_one_digits = false;

	float a = 10.0f;

	//����num��9���`1���̊Ԃŉ������邩�Ȃǂ𒲂ׂ�
	for (int num_max = 100000000; num_max >= 1; num_max /= 10)
	{
		//
		if (num / num_max >= 1 || not_one_digits == true)
		{
			//
			num_decomposition[numeric_number] = num / num_max;
			//
			num %= num_max;

			numeric_number++;
			not_one_digits = true;
		}
	}

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

				//����num�̌������O��������
	if (numeric_number == 0)
	{
		//�������P���₷
		numeric_number++;
		//�ꌅ�ڂ��O�ɂ���
		num_decomposition[0] = 0;
	}
	//���������[�v����
	for (int number = 0; number < numeric_number; number++)
	{
		//�����Ƃɐ������ׂ�
		switch (num_decomposition[number])
		{
		case 0:
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 1:
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 2:
			//�؂���ʒu�̐ݒ�
			src.m_top = 0.0f;
			src.m_left = 64.0f * 2;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 3:
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 4:
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f;
			src.m_left = 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 5:
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f;
			src.m_left = 64.0f * 2;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 6:
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f * 2;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 7:
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f * 2;
			src.m_left = 64.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 8:
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f * 2;
			src.m_left = 64.0f * 2;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		case 9:
			//�؂���ʒu�̐ݒ�
			src.m_top = 64.0f * 3;
			src.m_left = 0.0f;
			src.m_right = src.m_left + 64.0f;
			src.m_bottom = src.m_top + 64.0f;
			break;
		}

		//�\���ʒu�̐ݒ�
		dst.m_top = dst_top;
		dst.m_left = number * dst_size + dst_left - (number * a);
		dst.m_right = dst.m_left + dst_size;
		dst.m_bottom = dst.m_top + dst_size;

		//�`��
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
}