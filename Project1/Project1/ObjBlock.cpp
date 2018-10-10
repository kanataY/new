//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjBlock.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjBlock::CObjBlock(int map[10][MAP_X_MAX])
{
	//�}�b�v�f�[�^���R�s�[
	memcpy(m_map, map, sizeof(int)*(10 * MAP_X_MAX));
	//�}�b�v�f�[�^���L�^����ق��ɃR�s�[
	memcpy(m_map_Record, map, sizeof(int)*(10 * MAP_X_MAX));
}

//�C�j�V�����C�Y
void CObjBlock::Init()
{
	m_px = 0.0f;
	m_py = 0.0f;	//�ʒu
	m_bx1 = 0.0f;
	m_bx2 = 800.0f;
	m_rain = false;

	m_scroll = 0.0f;
	m_scroll_run = 800.0f;
	m_scroll_num = 0;
}

//�A�N�V����
void CObjBlock::Action()
{
	//�w�i�֘A�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);

	float rx = runner->GetX();
	float ry = runner->GetY();

	//�`�F�b�N�|�C���g�̂��o�ĂȂ�������Ƃ܂�Ȃ��悤�ɂ���
	float m_check_x = 999.0f;


	//�`�F�b�N�|�C���g�̕`�悪���ׂ�Window�Ɏ��܂��Ă���ꍇ
	if (m_check_x < 400.0f)
	{
		//�w�i1�̓���
		m_bx1 -= 0.0f;

		//�w�i2�̓���
		m_bx2 -= 0.0f;
	}

	////���
	//else if (runner->GetCheckPoint() == true && m_check_x < 400.0f || gau->GetGauge() == 192)
	//{
	//	//�w�i1�̓���
	//	m_bx1 -= 0.0f;

	//	//�w�i2�̓���
	//	m_bx2 -= 0.0f;
	//}

	else if (rx < -50 || runner->GetHoleFallCon() == true || runner->GetDeath() == true) //��ʂ�荶���ɍs���Ȃ��悤�ɂ���
	{
		//�w�i1�̓���
		m_bx1 -= 0.0f;

		//�w�i2�̓���
		m_bx2 -= 0.0f;
	}
	//�O���X�N���[�����C��
	else if (rx > -50 && runner->GetHoleFallCon() == false)
	{
		// ��l�������ɓ������Ă���ꍇ�X�N���[�����{�ɂ���
		if (runner->GetStickFire() == true)
		{
			m_scroll -= 4.0f;//��l�����{�������ׂ����̒l��m_scroll�ɉ�����

			//�w�i1�̓���
			m_bx1 -= 4.0f;
			if (m_bx1 < -800.0f)
			{
				m_bx1 = 800.0f;
				m_scroll_num++;//�w�i1���I���΃J�E���g����
			}
			//�w�i2�̓���
			m_bx2 -= 4.0f;
			if (m_bx2 < -800.0f)
				m_bx2 = 800.0f;
		}
		else
		{
			m_scroll -= 2.0f;//��l�����{�������ׂ����̒l��m_scroll�ɉ�����

			//�w�i1�̓���
			m_bx1 -= 2.0f;
			if (m_bx1 < -800.0f)
			{
				m_bx1 = 800.0f;
				m_scroll_num++;//�w�i1���I���΃J�E���g����
			}
			//�w�i2�̓���
			m_bx2 -= 2.0f;
			if (m_bx2 < -800.0f)
				m_bx2 = 800.0f;
		}

	}


	//�}�b�v�֘A�[�[�[�[�[�[�[�[�[�[
	float line = 0.0f;

	//�G�o�����C��
	//��l���̈ʒu+800 - �����i�[�̈ʒu��G�o�����C���ɂ���
	line = rx + (-m_scroll) + (800 - rx);

	//�G�o�����C����v�f�ԍ���
	int ex = ((int)line) / 64;
}
	

//�`��
void CObjBlock::Draw()
{
	
	//-----------�w�i-----------
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;
	//�w�i1��4��X�N���[��������
	if (m_scroll_num>=4)
	{
		//�\���ʒu�̐ݒ�
		//�S�|���w�i�`��
		dst.m_top = 0.0f;
		dst.m_left = 0.0f + m_bx1;
		dst.m_right = 806.0f + m_bx1;
		dst.m_bottom = 700.0f;

		//�`��
		Draw::Draw(26, &src, &dst, c, 0.0f);
	}
	else
	{

		//�\���ʒu�̐ݒ�
		//�w�i�P
		dst.m_top = 0.0f;
		dst.m_left = 0.0f + m_bx1;
		dst.m_right = 806.0f + m_bx1;
		dst.m_bottom = 700.0f;

		//�`��
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	//�w�i�Q
	dst.m_top = 0.0f;
	dst.m_left = 0.0f + m_bx2;
	dst.m_right = 806.0f + m_bx2;
	dst.m_bottom = 700.0f;

	//�`��
	Draw::Draw(1, &src, &dst, c, 0.0f);
}

//���ׂ����}�b�v�̈ʒu�ɂ���}�b�v�ԍ���Ԃ�
int CObjBlock::GetMap(int x, int y)
{
	if (0 <= y && y < 10 && 0 <= x && x < MAP_X_MAX)

		return m_map_Record[y][x];

	return -99999;//���������ꍇ
}