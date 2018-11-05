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

	m_scroll = 0.0f;
	m_scroll_run = 800.0f;
	m_scroll_num = 0;
}

//�A�N�V����
void CObjBlock::Action()
{
	//�w�i�֘A�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	//�����i�[�̈ʒu���擾
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	float hx = hero->GetX();
	float hy = hero->GetY();

	if (hx < -50 ) //��ʂ�荶���ɍs���Ȃ��悤�ɂ���
	{
		//�w�i1�̓���
		m_bx1 -= 0.0f;

		//�w�i2�̓���
		m_bx2 -= 0.0f;
	}
	//�O���X�N���[�����C��
	else if (hx > 400 )
	{
		hero->SetX(400);			//��l���̓��C���𒴂��Ȃ��悤�ɂ���

		m_scroll -= hero->GetVX();//��l�����{�������ׂ����̒l��m_scroll�ɉ�����

		//�w�i1�̓���
		m_bx1 -= hero->GetVX();
		if (m_bx1 < -800.0f)
		{
			m_bx1 = 800.0f;
			m_scroll_num++;//�w�i1���I���΃J�E���g����
		}
		//�w�i2�̓���
		m_bx2 -= hero->GetVX();
		if (m_bx2 < -800.0f)
			m_bx2 = 800.0f;

	}


	//�}�b�v�֘A�[�[�[�[�[�[�[�[�[�[
	float line = 0.0f;

	//�G�o�����C��
	//��l���̈ʒu+800 - �����i�[�̈ʒu��G�o�����C���ɂ���
	line = hx + (-m_scroll) + (800 - hx);

	//�G�o�����C����v�f�ԍ���
	int ex = ((int)line) / 64;

	//�G�o�����C���̗������
	for (int i = 0; i < 10; i++)
	{
		//��̒�����P��T��
		if (m_map[i][ex] == 1)
		{
			;
		}
	}
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

	//�\���ʒu�̐ݒ�
	//�S�|���w�i�`��
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 700.0f;

	//�`��
	Draw::Draw(0, &src, &dst, c, 0.0f);

}

//���ׂ����}�b�v�̈ʒu�ɂ���}�b�v�ԍ���Ԃ�
int CObjBlock::GetMap(int x, int y)
{
	if (0 <= y && y < 10 && 0 <= x && x < MAP_X_MAX)

		return m_map_Record[y][x];

	return -99999;//���������ꍇ
}

//BlockDrawMethod�֐�
//�����P float   x    :���\�[�X�؂���ʒuX
//�����Q float   y    :���\�[�X�؂���ʒuY
//�����R RECT_F* dst  :�`��ʒu
//�����S float   c[]  :�J���[���
//�u���b�N��64�~64����`��p�B���\�[�X�؂���ʒu�݂̂��E����
//�ݒ�ł���
void CObjBlock::BlockDraw(float x, float y, RECT_F* dst, float c[])
{
	RECT_F src;
	src.m_top = y;
	src.m_left = x;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;
	//�`��
	Draw::Draw(1, &src, dst, c, 0.0f);

}

//BlockHit�֐�
//�����P�@float* x          :������s��object��X�ʒu
//�����Q�@float* y          :������s��object��Y�ʒu
//�����R�@bool   scroll_on  :������s��object�̓X�N���[���̉e���^���邩�ǂ����itrue���^����@false=�^���Ȃ��j
//�����S�@bool*  up         :�㉺���E�̏㕔���ɓ������Ă��邩�ǂ����Ԃ�
//�����T�@bool*  down       :�㉺���E�̉������ɓ������Ă��邩�ǂ����Ԃ�
//�����U�@bool*  left       :�㉺���E�̍������ɓ������Ă��邩�ǂ����Ԃ�
//�����V�@bool*  right      :�㉺���E�̉E�����ɓ������Ă��邩�ǂ����Ԃ�
//�����W�@float* vx         :���E���莞�̔����ɂ��ړ������E�͂̒l��ς��ĕԂ�
//�����X�@float* vy         :�㉺���莞�ɂ�鎩�R�����^���̈ړ������E�͂̒l��ς��ĕԂ�
//�����P�Oint*   bt         :���������莞�A����ȃu���b�N�̃^�C�v��Ԃ�
//������s��object�ƃu���b�N64�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�
void CObjBlock::BlockHit(
	float *x, float *y, bool scroll_on,
	bool*up, bool* down, bool* left, bool* right,
	float* vx, float*vy, int* bt
)
{

	//�Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//����ł���block�̎�ނ̏�����
	*bt = 0;

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j]>0 && m_map[i][j] != 4)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j*64.0f;
				float by = i*64.0f;

				//�X�N���[���̉e��
				float scroll = scroll_on ? m_scroll : 0;

				//��l���ƃu���b�N�̓����蔻��
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 64.0f > by) && (*y < by + 64.0f))
				{
					//�㉺���E����

					//vector�̍쐬
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;
					//���������߂�
					float len = sqrt(rvx*rvx + rvy*rvy);

					//�p�x�����߂�
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					//len��������̒������Z���ꍇ����ɓ���
					if (len<88.0f)
					{
						//�p�x�ŏ㉺���E����
						if (r<45 && r>0 || r>315)
						{
							//�E

								*right = true;//��l���̍��̕������Փ˂��Ă���
								*x = bx + 64.0f + (scroll);//�u���b�N�̈ʒu�[��l���̕�
								*vx = -(*vx) * 0.1f;//-VX*�����W��
							

						}
						if (r>45 && r<135)
						{
							//��
							*down = true;//��l���̉��̕������Փ˂��Ă���
							*y = by - 64.0f;//�u���b�N�̈ʒu�[��l���̕�
											//��ނ�n���̃X�^�[�g��g-���̂ݕύX����
							*vy = 0.0f;
						}
						if (r>135 && r<225)
						{
							//��
							*left = true;//��l���̉E�̕������Փ˂��Ă���
							*x = bx - 64.0f + (scroll);//�u���b�N�̈ʒu�[��l���̕�
							*vx = -(*vx) * 0.1f;//-VX*�����W��
						
						}
						if (r > 225 && r < 315)
						{
							//��
							*up = true;  //��l���̏�̕������Փ˂��Ă���
							*y = by + 64.0f;//�u���b�N�̈ʒu�{��l���̕�
							if (*vy < 0)
							{
								*vy = 0.0f;
							}
						}
					}
				}
			}
		}
	}
}