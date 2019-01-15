//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjHero.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjHero::CObjHero()
{

}

//�C�j�V�����C�Y
void CObjHero::Init()
{
	m_px = 250.0f;
	m_py = 400.0f;	//�ʒu
	m_vx = 0.0f;
	m_vy = 0.0f;	//�ړ��x�N�g��
	m_ppx = 0;
	m_ppy = 0;
	m_gold_time = 100;
	con = 0;
	m_speed = 0.8f;
	m_pos = 0.0f;//�E����
	m_gold_flag = false;
	m_gold_spawn = false;
	m_gold_Y = false;
	m_gold_M = false;
	m_coinshot_flag = false;

	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 8; //�A�j���[�V�����Ԋu��

	m_ani_change = 2;//�A�j���[�V������2��

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //����ł���block�̎�ނ��m�F�p

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 37, 50, ELEMENT_HERO, OBJ_HERO, 1);
}

//�A�N�V����
void CObjHero::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	CObjCoin* coin = ( CObjCoin*)Objs::GetObj(OBJ_COIN);
	//�␳�̏��������Ă���
	//CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);


	//�A�j���[�V�����[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	
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

		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

	if (Input::GetVKey(VK_RIGHT) == true)  //�E�ړ�
	{
		m_ani_time++;//�t���[�����슴�o�^�C����i�߂�
		m_vx += m_speed;
		m_pos = 0.0f;
	}
	if (Input::GetVKey(VK_LEFT) == true)  //���ړ�
	{
		m_ani_time++;//�t���[�����슴�o�^�C����i�߂�
		m_vx += -m_speed;
		m_pos = 1.0f;
	}
	if (Input::GetVKey(VK_UP) == true)//��ړ�
	{
		m_vy += -m_speed*3;
	}
	if (Input::GetVKey(VK_DOWN) == true && m_py < 536)//���ړ�
	{
		m_vy += m_speed;
	}
	if(Input::GetVKey(VK_RIGHT) != true&& Input::GetVKey(VK_LEFT) != true)
	{
		m_ani_frame = 1;
	}
	//������u���[�[�[�[�[�[�[�[�[�[�[�[�[
	m_gold_time++;//����̊Ԋu�𑝂₷

	m_ppx = (m_px - block->GetScroll()) / 64; //��l���̈ʒu����}�b�v�̈ʒu������Ă���
	m_ppy = m_py / 64;

	if(m_pos == 0.0f) //�E�����̎��͒�������B
		m_ppx += 0.8f;		//�l�̌ܓ����鏀���A��������

	m_ppy += 0.5f;
	m_ppx = (int)m_ppx;	//int�^�ɕύX���Ďl�̌ܓ�����
	m_ppy = (int)m_ppy;

	if (block->GetMapRecord(m_ppx + 1, m_ppy) == 0 && m_pos == 0.0f ||
		block->GetMapRecord(m_ppx - 1, m_ppy) == 0 && m_pos == 1.0f)//������ʒu�̉E���A�������u���b�N������������u���Ȃ��悤�ɂ���
	{
		if (Input::GetVKey('C') == true)  //�����u��
		{
			//����͈�x�Ɉ�񂾂�,�u������Ԋu���󂢂Ă����ڂ�u����   �󒆂ł͂����Ȃ��悤��
			if (m_gold_flag == false && m_gold_spawn == false && m_gold_time > 50 && m_vy == 0.0f)
			{
				//����𐶐�
				//������
				if (m_pos == 1)
				{
					CObjGold* kane = new CObjGold(m_px - 75.0f - block->GetScroll(), m_py);
					Objs::InsertObj(kane, OBJ_GOLD, 16);
				}
				else//�E����
				{
					CObjGold* kane = new CObjGold(m_px + 75.0f - block->GetScroll(), m_py);
					Objs::InsertObj(kane, OBJ_GOLD, 16);
				}
				m_gold_flag = true;
				m_gold_time = 0;//�Ԋu��������
			}
		}
		else
			m_gold_flag = false;
	}

	//�R�C���U��-----------------------------------------------------------------------------
	if (Input::GetVKey('V') == true)//V�Ŏˏo(��)
	{
		//�R�C�����o���t���O���I�t�ŃR�C�������݂��Ȃ���
		if (m_coinshot_flag == false&&coin==nullptr)
		{
			//�����ɂ���ďo���ꏊ��ς���
			if (m_pos == 1)//������
			{
				//�R�C�����o��
				CObjCoin* coin = new CObjCoin(m_px, m_py+25.0f);
				Objs::InsertObj(coin, OBJ_COIN, 16);
				coin->SetHeroPos(1);//�R�C���Ɏ�l���̌����𑗂�
			}
			else//�E����
			{
				//�R�C�����o��
				CObjCoin* coin = new CObjCoin(m_px+25.0f, m_py+25.0f);
				Objs::InsertObj(coin, OBJ_COIN, 16);
				coin->SetHeroPos(0);//�R�C���Ɏ�l���̌����𑗂�
			}
		}
		//�R�C�����o���t���O���I���ɂ���
		m_coinshot_flag = true;
	}
	else//���˃{�^����������ĂȂ����R�C�����˃t���O�̓I�t�ɂ���
		m_coinshot_flag = false;
	//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|--------------------------------------------


	//���C
	m_vx += -(m_vx * 0.15f);
	m_vy += -(m_vy * 0.15f);

	//�ړ��I��---------------------------------------------------


	//���R�����^��
	m_vy += 9.8 / (8.0f);

	//�W�����v�I���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + 15.0f, m_py + 15.0f);

	//�����蔻��֘A
	HitBox();

	//�ړ��I��---------------------------------------------------
	//�u���b�N�ɂ̂ڂ��悤�ɂ���
	float b = m_py + 32.0f;

	if(m_vy == 0.0f)
		block->BlockHit(&m_px, &b, true,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
			&m_block_type, false, true, &m_py,&m_gold_M,true
		);
	

	block->BlockHit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type, false, false, 0,false,true
	);

	//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

	//�v���C���[���S����------------------------------------------------------------------------------
	if (hit->CheckObjNameHit(OBJ_THORN)!=nullptr)
	{
		Scene::SetScene(new CSceneMain());
	}
	//------------------------------------------------------------------------------------------------
	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;
}

		

//�`��
void CObjHero::Draw()
{
	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };
	//�e�̕`��̂��߂̃J���[���
	float shadowcolor[4] = { 1.0f,1.0f,1.0f,0.4f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
	RECT_F src2; //�`�挳�؂���ʒu
	RECT_F dst2; //�`���\���ʒu

	 //�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f + m_ani_frame*64.0f;
	src.m_right = 64.0f+m_ani_frame*64.0f;
	src.m_bottom = 256.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = (64.0*m_pos) + m_px;
	dst.m_right = (64.0f-64.0f*m_pos) + m_px;
	dst.m_bottom = 64.0f + m_py;

	//�`��
	Draw::Draw(3, &src, &dst, c, 0.0f);
	
	//�c��̐�����`�悷��
	static wchar_t  c_siro[8];
	static float cl_siro[4] = { 0.0f,0.0f,0.0f,1.0f };
	//swprintf_s(c_siro, L"X %d", m_remaining);
	CDrawFont::StrDraw(c_siro, 735, 16, 32, cl_siro);

	//---------------------------------------------------------------------------------
	//���_�̕`��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	float cc[4] = { 0.0f,0.0f,0.0f,1.0f };
	wchar_t str[128];
	swprintf_s(str, L"���_�F%d�_", ((UserData*)Save::GetData())->m_point);
	Font::StrDraw(str, 350, 16, 32, cc);
	//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
}

void CObjHero::HitBox()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	CObjGold* gold = (CObjGold*)Objs::GetObj(OBJ_GOLD);
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//����ɓ������Ă���Γo��or����悤�ɂ���
	if (hit->CheckObjNameHit(OBJ_GOLD) != nullptr)
	{
		//�ǂ̊p�x�œ������Ă��邩���m�F
		HIT_DATA** hit_data;                        //���������Ƃ��ׂ̍₩�ȏ������邽�߂̍\����
		hit_data = hit->SearchObjNameHit(OBJ_GOLD);  //hit_data��HitBox�Ƃ̏�������

		for (int i = 0; i < hit->GetCount(); i++)
		{
			if (hit_data[i] != NULL)
			{
				float r2 = hit_data[i]->r;

				if (r2 >= 210 && r2 < 340)
				{
					CObjBlock* b = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

					//�܂��A�n�ʂɓ������Ă��锻��ɂ���
					m_vy = 0.0f;
					m_hit_down = true;

					if (r2 >= 310 && r2 < 340 && m_pos == 1.0f)//����̍��[�ɂ���Ƃ��͋����u���Ȃ�����
					{
						m_gold_spawn = true;
					}
					else
						m_gold_spawn = false;
				}

				if (m_hit_down == true)		//�n��or����̏�ɂ���Ƃ�
				{
					if (/*r2 > 150 &&*/ r2 < 200 && m_pos == 1.0f)
					{
						//��
						m_hit_left = true;  
						m_gold_Y = true;	//���򑤂Ŏ�l���̂������J������
						m_py -= 20.0f;		//�o���悤�ɂ���
						con++;
					}
					else if (/*r2 < 0 && r2>0 ||*/ r2 > 340 && m_pos == 0.0f)
					{
						//�E
						m_hit_right = true;
						m_gold_Y = true;	//���򑤂Ŏ�l���̂������J������
						m_py -= 24.0f;		//�o���悤�ɂ���
						con++;
					}
					else
					{
						m_gold_Y = false;
						con = 0;
					}
				}
			}
		}
	}
	else
	{
		m_gold_M = false;
		con = 0;
	}
	
	//�ǂ����邩�Y�ݒ��c
	/*if (con == 1) {
		m_py -= 24.0f; con = 0;
	}
	else if (con > 1 && m_pos == 1.0f)
	{
		m_gold_Y = true;
		m_vx = 0.0f;
		m_px += 0.5f;
		m_vy = 0.0f;
	}
	else if (con > 1 && m_pos == 0.0f)
	{
		m_gold_Y = true;
		m_vx = 0.0f;
		m_px -= 0.5f;
		m_vy = 0.0f;
	}*/

		

	//�q�b�g�{�b�N�X�ɐG��Ă��Ȃ���
	if (hit->CheckObjNameHit(OBJ_GOLD) == nullptr)
	{
		//���򂩂�~��Ă���̂ŋ����u����悤�ɂ���B
		m_gold_spawn = false;
	}

}