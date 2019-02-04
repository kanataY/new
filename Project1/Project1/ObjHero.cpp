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
	if (((UserData*)Save::GetData())->m_stage_count == 4)  //�X�e�[�W4
	{
		m_py = 200.0f;	//�ʒu
	}
	else
		m_py = 400.0f;	//�ʒu
	m_vx = 0.0f;
	m_vy = 0.0f;	//�ړ��x�N�g��
	m_ppx = 0;
	m_ppy = 0;
	m_gold_time = 100;
	m_coin_time = 100;
	con = 0;
	m_speed = 0.8f;
	m_pos = 0.0f;//�E����
	m_gold_flag = false;
	m_gold_spawn = false;
	m_gold_Y = false;
	m_gold_M = false;
	m_coinshot_flag = false;
	m_goal_flag = false;

	m_ani_time = 0;
	m_ani_frame = 1;  //�Î~�t���[���������ɂ���
	m_ani_max_time = 8; //�A�j���[�V�����Ԋu��

	m_ani_change = 3;//�A�j���[�V������2��

	m_gold_restriction = 0; //����̌�����
	m_gold_restriction_max = 0;
	if((((UserData*)Save::GetData())->m_stage_count == 5))
		m_coin_restriction=8;//�R�C���̌�����
	else
		m_coin_restriction = 0;//�R�C���̌�����

	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_down_gold = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //����ł���block�̎�ނ��m�F�p
	m_drop_gold = false;//�S�[���h�E�������p

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 37, 50, ELEMENT_HERO, OBJ_HERO, 1);
}

//�A�N�V����
void CObjHero::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	CObjCoin* coin = ( CObjCoin*)Objs::GetObj(OBJ_COIN);    //�R�C�����
	CObjGolem* golem = (CObjGolem*)Objs::GetObj(OBJ_GOLEM);	//�S�[�������
	//�␳�̏��������Ă���
	//CObjCorrection* cor = (CObjCorrection*)Objs::GetObj(CORRECTION);

	//�S�[�����Ă��瓮�����Ȃ��悤�ɂ���
	if (m_goal_flag == false)
	{
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

		//HitBox�̈ʒu�̕ύX
		CHitBox* hit = Hits::GetHitBox(this);
		hit->SetPos(m_px + 15.0f, m_py + 15.0f);

		//�ړ������|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
		if (Input::GetVKey(VK_RIGHT) == true && hit->CheckObjNameHit(OBJ_GOLEM) == nullptr)  //�E�ړ�
		{
			m_ani_time++;//�t���[�����슴�o�^�C����i�߂�
			if (hit->CheckObjNameHit(OBJ_GOLEM) != nullptr)
				m_speed = 0.1f;
			m_vx += m_speed;
			m_pos = 0.0f;
		}
		if (Input::GetVKey(VK_LEFT) == true && hit->CheckObjNameHit(OBJ_GOLEM) == nullptr)  //���ړ�
		{
			m_ani_time++;//�t���[�����슴�o�^�C����i�߂�
			if (hit->CheckObjNameHit(OBJ_GOLEM) != nullptr)
				m_speed = 0.1f;
			m_vx += -m_speed;
			m_pos = 1.0f;
		}
		if (Input::GetVKey(VK_UP) == true)//��ړ�
		{
			m_vy += -m_speed * 3;
		}

		//�E�ƍ��������Ă��Ȃ����A�j���[�V���������ɖ߂�
		if (Input::GetVKey(VK_RIGHT) != true && Input::GetVKey(VK_LEFT) != true)
		{
			m_ani_frame = 1;
		}

		//--------------------------------------------------------------------------------------
		//������u���[�[�[�[�[�[�[�[�[�[�[�[�[
		m_gold_time++;//����̊Ԋu�𑝂₷
		m_coin_time++;
		//�X�e�[�W�̔ԍ��ɂ���Ă��������̐���ݒ�
		if (m_drop_gold == false)//��x�ݒ肵����㏑������p
		{
			switch (((UserData*)Save::GetData())->m_stage_count)
			{
			case 1://�X�e�[�W1
				m_gold_restriction_max = 7;
				m_drop_gold = true;
				break;
			case 2://�X�e�[�W2
				m_gold_restriction_max = 9;
				m_drop_gold = true;
				break;
			case 3://�X�e�[�W3
				m_gold_restriction_max = 12;
				m_drop_gold = true;
				break;
			case 4://�X�e�[�W4
				m_gold_restriction_max = 8;
				m_drop_gold = true;
				break;
			case 5://�X�e�[�W4
				m_gold_restriction_max = 15;
				m_drop_gold = true;
				break;
			}
		}
		//����A�C�e���ɐG�ꂽ�������O���₷
		if (hit->CheckObjNameHit(OBJ_DROP_GOLD) != nullptr)
		{
			m_gold_restriction_max += 3;
			Audio::Start(2); //����A�C�e���̎擾����炷
		}

		m_ppx = (m_px - block->GetScroll()) / 64; //��l���̈ʒu����}�b�v�̈ʒu������Ă���
		m_ppy = m_py / 64;

		if (m_pos == 0.0f) //�E�����̎��͒�������B
			m_ppx += 0.7f;		//�l�̌ܓ����鏀���A��������

		m_ppy += 0.5f;

		m_ppx = (int)m_ppx;	//int�^�ɕύX���Ďl�̌ܓ�����
		m_ppy = (int)m_ppy;

		if (block->GetMapRecord(m_ppx + 1, m_ppy) == 0 && m_pos == 0.0f ||
			block->GetMapRecord(m_ppx - 1, m_ppy) == 0 && m_pos == 1.0f ||
			block->GetMap(m_ppx + 1, m_ppy) == 97 && m_pos == 0.0f ||
			block->GetMap(m_ppx - 1, m_ppy) == 97 && m_pos == 1.0f)//������ʒu�̉E���A�������u���b�N������������u���Ȃ��悤�ɂ���
		{
			if (Input::GetVKey('C') == true)  //�����u��
			{
				//����͈�x�Ɉ�񂾂�,�u������Ԋu���󂢂Ă����ڂ�u����   �󒆂ł͂����Ȃ��悤��   ����̌����w�肳�ꂽ���������Ă��Ȃ����
				if (m_gold_flag == false && m_gold_spawn == false && m_gold_time > 50 && m_vy == 0.0f&&m_gold_restriction < m_gold_restriction_max)
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
					m_gold_restriction++;
				}
			}
			else
				m_gold_flag = false;
		}

		//�R�C���U��-----------------------------------------------------------------------------
		if (Input::GetVKey('V') == true)//V�Ŏˏo
		{
			//�R�C�����o���t���O���I�t�ŃR�C�������݂��Ȃ���
			if (m_coinshot_flag == false && m_coin_time > 50 && coin == nullptr&&m_coin_restriction < 10)
			{
				//�����ɂ���ďo���ꏊ��ς���
				if (m_pos == 1)//������
				{
					//�R�C�����o��
					CObjCoin* coin = new CObjCoin(m_px, m_py + 25.0f);
					Objs::InsertObj(coin, OBJ_COIN, 16);
					coin->SetHeroPos(1);//�R�C���Ɏ�l���̌����𑗂�
				}
				else//�E����
				{
					//�R�C�����o��
					CObjCoin* coin = new CObjCoin(m_px + 25.0f, m_py + 25.0f);
					Objs::InsertObj(coin, OBJ_COIN, 16);
					coin->SetHeroPos(0);//�R�C���Ɏ�l���̌����𑗂�
				}
				Audio::Start(10); //�R�C���𓊂��鉹���o���B
				//�R�C�����o���t���O���I���ɂ���
				m_coinshot_flag = true;
				m_coin_restriction++;
				m_coin_time = 0;//�Ԋu��������
			}
		}
		else//���˃{�^����������ĂȂ����R�C�����˃t���O�̓I�t�ɂ���
			m_coinshot_flag = false;
		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|--------------------------------------------
		//�X�R�A----------------------------------------------------------------------------



		//���C
		m_vx += -(m_vx * 0.15f);

		//���R�����^��
		m_vy += 9.8 / (8.0f);
		//�W�����v�I���[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[

		//�u���b�N�ɂ̂ڂ��悤�ɂ���
		float b = m_py + 32.0f;


		block->BlockHit(&m_px, &m_py, true,
			&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
			&m_block_type, false, false, 0, false, true
		);

		//�����蔻��֘A
		HitBox();

		if (m_vy == 0.0f) // �󒆂ɂ���Ƃ��ɏ��Ȃ�����B
			block->BlockHit(&m_px, &b, true,
				&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
				&m_block_type, false, true, &m_py, &m_gold_M, true
			);

		//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

		//�v���C���[���X�^�[�g����------------------------------------------------------------------------------
		if (hit->CheckObjNameHit(OBJ_JUMP_ENEMY) != nullptr || hit->CheckObjNameHit(OBJ_THORN) != nullptr
			|| Input::GetVKey('R') == true || m_py > 3000)
		{
			if (Audio::CheckSound(3) == false) //�����Ă��鉹�����ĂȂ���
			{
				((UserData*)Save::GetData())->m_restart += 1; //���X�^�[�g�������𑝂₷
				Scene::SetScene(new CSceneMain());
			}
		}
		//���������Ƃ��ɉ���炷�B
		if (m_py > 600)
		{
			if (Audio::CheckSound(3) == false)
				Audio::Start(3);
		}
		//------------------------------------------------------------------------------------------------
		//�ʒu�̍X�V
		m_px += m_vx;
		m_py += m_vy;
	}
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
	
	//�c��̐�����`�悷��-------------------------------------------------
	static wchar_t  c_siro[8];
	static float cl_kuro[4] = { 0.0f,0.0f,0.0f,1.0f };
	static float cl_siro[4] = { 1.0f,1.0f,1.0f,1.0f };
	//����c��
	swprintf_s(c_siro, L"X %d", m_gold_restriction_max-m_gold_restriction);
	if (((UserData*)Save::GetData())->m_stage_count == 5)//�X�e�[�W5�̎�������������̂ŏC��
	{
		CDrawFont::StrDraw(c_siro, 735, 16, 32, cl_siro);
	}
	else
	{
		CDrawFont::StrDraw(c_siro, 735, 16, 32, cl_kuro);
	}
	//�R�C���c��
	swprintf_s(c_siro, L"X %d", 10 - m_coin_restriction);
	if (((UserData*)Save::GetData())->m_stage_count == 5)//�X�e�[�W5�̎�������������̂ŏC��
	{
		CDrawFont::StrDraw(c_siro, 735, 64, 32, cl_siro);
	}
	else
	{
		CDrawFont::StrDraw(c_siro, 735, 64, 32, cl_kuro);
	}
	//����摜�`��----------------------------------------------------------------------------------------------------
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 128.0f;
	src.m_bottom = 128.0f;
	//�\���ʒu�̐ݒ�
	dst.m_top = 15.0f;
	dst.m_left = 695.0f;
	dst.m_right = dst.m_left + 32.0f;
	dst.m_bottom = dst.m_top+32.0f;
	//13�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�E�̏������ɕ`��
	Draw::Draw(13, &src, &dst, c, 0.0);
	//--------------------------------------------------------------------------
	//�R�C���̉摜�`��----------------------------------------------------------------------------------------------------
	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 33.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 65.0f;
	dst.m_left = 695.0f;
	dst.m_right = dst.m_left + 32.0f;
	dst.m_bottom = dst.m_top + 32.0f;
	//7�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�E�̏������ɕ`��
	Draw::Draw(7, &src, &dst, c, 0.0);
	//---------------------------------------------------------------------------------
	//���_�̕`��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	wchar_t str[128];
	swprintf_s(str, L"���_�F%d�_", ((UserData*)Save::GetData())->m_point);
	if (((UserData*)Save::GetData())->m_stage_count == 5)//�X�e�[�W5�̎�������������̂ŏC��
	{
		Font::StrDraw(str, 350, 16, 32, cl_siro);
	}
	else
	{
		Font::StrDraw(str, 350, 16, 32, cl_kuro);
	}
	//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|

	//���X�^�[�g�����̕`��[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[�[
	
	wchar_t str2[128];
	swprintf_s(str2, L"R�Ń��X�^�[�g");
	if (((UserData*)Save::GetData())->m_stage_count == 5)//�X�e�[�W5�̎�������������̂ŏC��
	{
		Font::StrDraw(str2, 20, 16, 32, cl_siro);
	}
	else
	{
		Font::StrDraw(str2, 20, 16, 32, cl_kuro);
	}
	//�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|�|
}

void CObjHero::HitBox()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	//hero_Hit
	CObjhero_hitbox* hero_hit = (CObjhero_hitbox*)Objs::GetObj(HERO_HITBOX);

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

				if (r2 >= 200 && r2 < 340)
				{
					CObjBlock* b = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

					//�܂��A�n�ʂɓ������Ă��锻��ɂ���
					m_vy = 0.0f;
					m_hit_down_gold = true;

					if (r2 >= 310 && r2 < 340 && m_pos == 1.0f)//����̍��[�ɂ���Ƃ��͋����u���Ȃ�����
					{
						m_gold_spawn = true;
					}
					else
						m_gold_spawn = false;
				}

				if (m_hit_down == true || m_hit_down_gold == true)		//�n��or����̏�ɂ���Ƃ�
				{
					if (r2 > 160 && r2 < 200 && m_pos == 1.0f && m_vy == 0.0f)
					{
						//��
						m_hit_left = true;  
						m_gold_Y = true;	//���򑤂Ŏ�l���̂������J������
						if (m_hit_down_gold == true)
							m_py -= 12.0f;
						else
							m_py -= 36.0f;		//�o���悤�ɂ���
						con++;
						break;
					}
					else if (/*r2 < 0 && r2>0 ||*/ r2 > 340 && m_pos == 0.0f && m_vy == 0.0f)
					{
						//�E
						m_hit_right = true;
						m_gold_Y    = true;	//���򑤂Ŏ�l���̂������J������
						if (m_hit_down_gold == true)
						  	 m_py -= 12.0f;
						else
							 m_py -= 36.0f;		//�o���悤�ɂ���
						con++;
						break;
					}
					else
					{
						m_gold_Y = false;
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
	
	//�q�b�g�{�b�N�X�ɐG��Ă��Ȃ���
	if (hit->CheckObjNameHit(OBJ_GOLD) == nullptr)
	{
		//���򂩂�~��Ă���̂ŋ����u����悤�ɂ���B
		m_gold_spawn = false;
	}

	//�S�[�������
	CObjGolem* golem = (CObjGolem*)Objs::GetObj(OBJ_GOLEM);

	//�S�[�����ɓ���������
	if (hit->CheckObjNameHit(OBJ_GOLEM) != nullptr)
	{
		//�S�[���������݂��Ă��鎞
		if (golem != nullptr)
		{
			float golem_x = golem->GetX();
			//�S�[�������E���ɂ���Ƃ��̔���
			if (golem->GetPos() == 0.0&&m_px <= golem_x + block->GetScroll())
				m_vx += -0.7f;
			if (golem->GetPos() == 1.0&&m_px <= golem_x + block->GetScroll())
				m_vx += -m_speed;
			//�S�[�����������ɂ���Ƃ��̔���
			if (golem->GetPos() == 0.0&&m_px >= golem_x + block->GetScroll())
				m_vx += m_speed;
			if (golem->GetPos() == 1.0&&m_px >= golem_x + block->GetScroll())
				m_vx += 0.7;

		}
	}

	//������u���b�N�i���u���b�N�o�[�W����S3�j�ɓ���������
	if (hit->CheckObjNameHit(OBJ_VANISHBLOCK) != nullptr)
	{
		m_vx = 0.0f; //�ʂ�Ȃ�����
		m_px -= 1.0f;//�ꏊ�͌��܂��Ă��č��ɂ���������Ȃ��̂ł�����g���Ă�
	}

	if (hit->CheckObjNameHit(OBJ_GOAL) != nullptr)
	{
		int m_gold_point = 0;//�|�C���g�ۑ��p
		if (m_gold_restriction_max - m_gold_restriction == 0)//����0
		{
			m_gold_point += 1000;//1000�|�C���g���Z
		}
		if (m_gold_restriction_max - m_gold_restriction > 0)//����0��葽��
		{
			m_gold_point += 2000 * (m_gold_restriction_max - m_gold_restriction);//2000�|�C���g*�c�����Z
		}
		//�X�R�A�ɃR�C���c���ɂ��|�C���g�Ƌ���̃|�C���g�����Z
		((UserData*)Save::GetData())->m_point += ((10-m_coin_restriction)*1000)+m_gold_point;
	}
	


	//�S�[���ɓ���������
	if (hit->CheckObjNameHit(OBJ_GOAL) != nullptr)
	{
		m_goal_flag = true;
	}
}