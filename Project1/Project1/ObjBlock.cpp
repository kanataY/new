//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

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
	m_swich_time = 0;

	m_gold_flag = false;

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

	if (hx < 100 )
	{
		hero->SetX(100);			//��l���̓��C���𒴂��Ȃ��悤�ɂ���

		m_scroll -= hero->GetVX();

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
		//��̒�����3��T��
		if (m_map[i][ex] == 3)
		{
			//�S�[�����o��
			CObjGoal* goal = new CObjGoal(ex * 64, i * 64);
			Objs::InsertObj(goal, OBJ_GOAL, 16);
			m_map[i][ex] = 0;
		}
		//��̒�����4��T��
		if (m_map[i][ex] == 4)
		{
			//�j���o��
			CObjthorn* thorn = new CObjthorn(ex*64, i*64);
			Objs::InsertObj(thorn, OBJ_THORN, 16);
			m_map[i][ex] = 999;							//�j���o������ɋ���̓����蔻����c�����߂�999�𗘗p
		}

		//��̒�����5��T��
		if (m_map[i][ex] == 5)
		{
			//�X�C�b�`�I�u�W�F�N�g�쐬
			CObjswitch* swi = new CObjswitch(ex * 64, i * 64 + 32.0f);
			Objs::InsertObj(swi, OBJ_SWITCH, 13);
			m_map[i][ex] = 0;	
		}


		//��̒�����6��T��
		if (m_map[i][ex] == 6)
		{
			//������u���b�N���o��
			CObjVanishBlock* vanish = new CObjVanishBlock(ex * 64, i * 64);
			Objs::InsertObj(vanish, OBJ_VANISHBLOCK, 11);
			if (((UserData*)Save::GetData())->m_stage_count == 3)	//�X�e�[�W�R�Ȃ�ŏ��͕`�悵�Ȃ��̂Ŕ�����ς���
			{
				m_map[i][ex] = 97;	
			}
			m_map[i][ex] = 98;							//������u���b�N���o������ɏ�����u���b�N�̓����蔻����c�����߂�98�𗘗p
		}

		//��̒�����7��T��
		if (m_map[i][ex] == 7)
		{
			//�ːi����G���o��
			CObjRushEnemy* rush = new CObjRushEnemy(ex * 64, i * 64);
			Objs::InsertObj(rush, OBJ_RUSH_ENEMY, 16);
			m_map[i][ex] = 0;			
			m_map_Record[i][ex] = 0; //�L�^�p������
		}

		//��̒�����8��T��
		if (m_map[i][ex] == 8)
		{
			//�S�[�������S�[�����̖ڂ̔�����o��
			CObjGolem* golem = new CObjGolem(ex * 64, i * 64);
			Objs::InsertObj(golem, OBJ_GOLEM, 13);

			CObjGolemJudgment* golemj = new CObjGolemJudgment(ex * 64, i * 64);
			Objs::InsertObj(golemj, GOLEM_JUDGMENT, 13);

			m_map[i][ex] = 0;
			m_map_Record[i][ex] = 0; //�L�^�p������
		}

		//��̒�����9��T��
		if (m_map[i][ex] == 9)
		{
			///�W�����v�I�u�W�F�N�g�쐬
			CObjJumpEnemy* junp = new CObjJumpEnemy(ex * 64, i * 64);
			Objs::InsertObj(junp, OBJ_JUMP_ENEMY, 13);

			m_map[i][ex] = 0;
			m_map_Record[i][ex] = 0; //�L�^�p������
		}
	}

	//������u���b�N�̔���������[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			//�X�C�b�`�̏��������Ă���
			CObjswitch* swi = (CObjswitch*)Objs::GetObj(OBJ_SWITCH);
			if (swi != nullptr)
			{
				if (swi->GetSwitchFlag() == true)//�X�C�b�`��������Ă�ꍇ�͔��������
				{
					m_swich_time++;//�X�C�b�`��������Ă��炵�΂炭������ʂ��悤�ɂ���

					if (m_swich_time > 60000)
					{
						//��̒�����998��T��
						if (((UserData*)Save::GetData())->m_stage_count == 3)	//�X�e�[�W�R�Ȃ�ŏ��͕`�悵�Ȃ��̂Ŕ�����ς���
						{
							if (m_map[i][j] == 97)
							{
								m_map[i][j] = 98;	//�ʂ��悤�ɂ���
							}
						}
						else
						{
							if (m_map[i][j] == 98)
							{
								m_map[i][j] = 97;	//�ʂ��悤�ɂ���
							}
						}

						if (((UserData*)Save::GetData())->m_stage_count == 5)	//�X�e�[�W�R�Ȃ�ŏ��͕`�悵�Ȃ��̂Ŕ�����ς���
						{
							if (m_map[i][j] == 10)
							{
								///�W�����v�I�u�W�F�N�g�쐬
								CObjJumpEnemy* junp = new CObjJumpEnemy(j * 64, i * 64);
								Objs::InsertObj(junp, OBJ_JUMP_ENEMY, 13);

								m_map[i][j] = 0;
								m_map_Record[i][j] = 0; //�L�^�p������
							}
						}
					}
					if (((UserData*)Save::GetData())->m_stage_count == 5 && Audio::CheckSound(14) == false)	//�X�e�[�W�R�Ȃ�ŏ��͕`�悵�Ȃ��̂Ŕ�����ς���
					{
						Audio::Start(14);
					}
				}

				else if (swi->GetSwitchFlag() == false)//�X�C�b�`��������ĂȂ��ꍇ�͔���������Ȃ�
				{
					m_swich_time = 0;
					//��̒�����998��T��
					if (((UserData*)Save::GetData())->m_stage_count == 3)	//�X�e�[�W�R�Ȃ�ŏ��͕`�悵�Ȃ��̂Ŕ�����ς���
					{
						//��̒�����997��T��
						if (m_map[i][j] == 98)
						{
							m_map[i][j] = 97;	//�ʂ�Ȃ�����B
						}
					}
					else
					{
						//��̒�����997��T��
						if (m_map[i][j] == 97)
						{
							m_map[i][j] = 98;	//�ʂ�Ȃ�����B
						}
					}
				}
			}
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

	//�`�� �X�e�[�W�P�ƂQ,3�Ŕw�i�𒋂ɕς���
	if (((UserData*)Save::GetData())->m_stage_count == 1 || ((UserData*)Save::GetData())->m_stage_count == 2 )
	{
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	else if(((UserData*)Save::GetData())->m_stage_count == 3 || ((UserData*)Save::GetData())->m_stage_count == 4 || ((UserData*)Save::GetData())->m_stage_count == 5)//�X�e�[�W�S�C�T�͗[���ɂ���
	{
		Draw::Draw(14, &src, &dst, c, 0.0f);
	}
	

	//�}�b�v�`�b�v�ɂ��block�ݒu
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			//�\���ʒu�̐ݒ�
			dst.m_top = i*64.0f;
			dst.m_left = j*64.0f + m_scroll;
			dst.m_right = dst.m_left + 64.0f;
			dst.m_bottom = dst.m_top + 64.0f;
			if (m_map[i][j] == 1)
			{
				//�u���b�N
				BlockDraw(0.0f, 0.0f, &dst, c , i ,j);
			}
			if (m_map[i][j] == 4)
			{
				;
			}
			
		}
	}
}

//���ׂ����}�b�v�̈ʒu�ɂ���}�b�v�ԍ���Ԃ�
int CObjBlock::GetMap(int x, int y)
{
	if (0 <= y && y < 10 && 0 <= x && x < MAP_X_MAX)

		return m_map[y][x];

	return -99999;//���������ꍇ
}

//���ׂ����}�b�v�̈ʒu�ɂ���}�b�v�ԍ���Ԃ�(�L�^��)
int CObjBlock::GetMapRecord(int x, int y)
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
void CObjBlock::BlockDraw(float x, float y, RECT_F* dst, float c[] , int i , int j)
{
	RECT_F src;
	src.m_top = y;
	src.m_left = x;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;
	//�`��
	if (i > 0)
	{
		if (m_map[i - 1][j] == 1)
		{
			Draw::Draw(2, &src, dst, c, 0.0f);
		}
		else
			Draw::Draw(1, &src, dst, c, 0.0f);
	}
	else 
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
	float* vx, float*vy, int* bt, bool b,bool hero, float* yy,bool* gg,bool hero_hit
)
{
	
	//�Փˏ�Ԋm�F�p�t���O�̏�����
	*up = false;
	//�S�[���h�Ȃ�ω������Ȃ�
	if(b == false)
	*down = false;
	*left = false;
	*right = false;

	//����ł���block�̎�ނ̏�����
	*bt = 0;
	float m_cx = 0.0f;
	float m_cy = 0.f;

	//��l���Ȃ�m_cx�i�u���b�N�Ƃ̓����蔻��j�̕���ς���
	if (hero_hit == false)
	{
		 m_cx = 64.0f;
		 m_cy = 64.0f;
	}
	else
	{
		//��l���Ȃ�ǂƂ̔�������
		if (hero == true)
		{
			m_cx = 50.1f; //�u���b�N�ɏオ���悤��
			m_cy = 64.0f;
		}
		else
		{
			m_cx = 50.0f;
			m_cy = 64.0f;
		}
	}

	//m_map�̑S�v�f�ɃA�N�Z�X
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
			if (m_map[i][j]>0 && m_map[i][j] != 2 && m_map[i][j] != 3 && m_map[i][j] != 5 && m_map[i][j] != 10 && m_map[i][j] != 97)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j*64.0f;
				float by = i*64.0f;

				//�X�N���[���̉e��
				float scroll = scroll_on ? m_scroll : 0;

				//��l���ƃu���b�N�̓����蔻��
				if ((*x + (-scroll) + m_cx > bx) && (*x + (-scroll) < bx + m_cx) && (*y + m_cy >= by) && (*y <= by + m_cy))
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
						//��l���Ȃ�ǂƂ̔�������
						if (hero == true)
						{
							//���㔼���Ȃ�グ��
							if (r >= 155 && r < 183)
							{
								if (m_map[i - 1][j] == 0)	//�������Ă���u���b�N�̈�O���󔒂Ȃ�
								{
									*gg = true;//�o���悤�Ƀq�[���[�����u���b�N���ŏ���������
									*yy -= 35.0f;//�o�点��
								}
							}
							
							//�E�㔼���Ȃ�グ��
							else if (r < 25 && r >= 0 || r >= 350)
							{
								if (m_map[i - 1][j] == 0)//�������Ă���u���b�N�̈�O���󔒂Ȃ�
								{
									*gg = true;//�o���悤�Ƀq�[���[�����u���b�N���ŏ���������
									*yy -= 35.0f;
								}
							}
						}
						else
						{
							//�p�x�ŏ㉺���E����
							if (r < 45 && r >= 0 || r >= 315)
							{
								//�E

								*right = true;//��l���̍��̕������Փ˂��Ă���
								*x = bx + m_cx + (scroll);//�u���b�N�̈ʒu�[��l���̕�
								
								*vx = -(*vx) * 0.1f;//-VX*�����W��

							}
							if (r >= 45 && r < 135)
							{
								//��
								*down = true;//��l���̉��̕������Փ˂��Ă���
								*y = by - 64.0f;//�u���b�N�̈ʒu�[��l���̕�
								
								//��ނ�n���̃X�^�[�g��g-���̂ݕύX����
								*vy = 0.0f;
							}

							if (r >= 135 && r < 225)
							{
								//��
								*left = true;//��l���̉E�̕������Փ˂��Ă���
								*x = bx - m_cx + (scroll);//�u���b�N�̈ʒu�[��l���̕�
								*vx = -(*vx) * 0.1f;//-VX*�����W��

							}
							if (r >= 225 && r < 315)
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
}



// Block32Hit�֐�
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
//������s��object�ƃu���b�N32�~64����ŁA�����蔻��Ə㉺���E������s��
//���̌��ʂ͈���4�`10�ɕԂ�
void CObjBlock::Block32Hit(
	float *x, float *y, bool scroll_on,
	bool*up, bool* down, bool* left, bool* right,
	float* vx, float*vy, int* bt, float* yy
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
			if (m_map[i][j]>0 && m_map[i][j] != 2 && m_map[i][j] != 3 && m_map[i][j] != 5 && m_map[i][j] != 10 && m_map[i][j] != 97)
			{
				//�v�f�ԍ������W�ɕύX
				float bx = j*64.0f;
				float by = i*64.0f;

				//�X�N���[���̉e��
				float scroll = scroll_on ? m_scroll : 0;

				//��l���ƃu���b�N�̓����蔻��
				if ((*x + (-scroll) + 32.0f > bx) && (*x + (-scroll) < bx + 32.0f) && (*y + 32.0f > by) && (*y < by + 32.0f))
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
					if (len < 88.0f)
					{
						*left = true;

						//�p�x�ŏ㉺���E����
						if (r < 45 && r >= 0 && r >= 315)
						{
							//�E

							*right = true;//���̕������Փ˂��Ă���
						//	*x = bx +32.0f+ (scroll);//�u���b�N�̈ʒu�[��l���̕�
						//	*vx = -(*vx) * 0.1f;//-VX*�����W��

						}
						if (r >= 45 && r < 135)
						{
							//��
							*down = true;//��l���̉��̕������Փ˂��Ă���
						//	*y = by - 32.0f;//�u���b�N�̈ʒu�[��l���̕�
							*left = true;
											//��ނ�n���̃X�^�[�g��g-���̂ݕύX����
						//	*vy = 0.0f;
						}

						if (r >= 135 && r < 225)
						{
							//��
							*left = true;//��l���̉E�̕������Փ˂��Ă���
						//	*x = bx - 32.0f + (scroll);//�u���b�N�̈ʒu�[��l���̕�
						//	*vx = -(*vx) * 0.1f;//-VX*�����W��

						}
						if (r >= 225 && r < 315)
						{
							//��
							*up = true;  //��l���̏�̕������Փ˂��Ă���
						//	*y = by + 32.0f;//�u���b�N�̈ʒu�{��l���̕�
						//	if (*vy < 0)
						//	{
						//		*vy = 0.0f;
						//	}
							*left = true;
						}

					}
				}
			}
		}
	}
}