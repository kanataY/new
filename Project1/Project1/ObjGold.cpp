//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

#include "GameHead.h"
#include "ObjGold.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjGold::CObjGold(float x,float y)
{
	m_px = x;
	m_py = y;

}

//�C�j�V�����C�Y
void CObjGold::Init()
{
	m_vx = 0.0f;
	m_vy = 0.0f;
	m_gold_vy = 0;
	m_gold_flag = false;
	m_hero_flag = false;
	m_switch_gold_flag = false;
	m_audio = false;

	m_switch_time = 0;
	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //����ł���block�̎�ނ��m�F�p

	//HitBox
	Hits::SetHitBox(this, m_px, m_py, 64, 32, ELEMENT_NULL, OBJ_GOLD, 1);
}

//�A�N�V����
void CObjGold::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	Hit();
	//���򂪗�����鎞���R����������
	if (m_gold_vy == 0)
		m_vy += 9.8 / (250.0f);
	else
		m_vy = 0.0f;//���̏�ɂƂǂ߂Ă����i����ɂ��Ȃ���j

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px + block->GetScroll(), m_py +32.0f);

	float c = m_px + block->GetScroll();

	block->BlockHit(&c, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type,true, false,0, false,false
	);

	//�ʒu�̍X�V
	m_px += m_vx;
	m_py += m_vy;

	//���򂪗����Ă��Ȃ��ꍇ�͉������炷�B
	if (m_vy == 0.0f && m_audio == false)
	{
		Audio::Start(1); //�����u������炷
		m_audio = true;
	}

	if (m_py > 700) //���ɗ����������
	{
		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;//���ŏ����́A�����ŃA�N�V�������]�b�h���I��������
	}
}

//�h���[
void CObjGold::Draw()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�`��J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py + 32.0f;
	dst.m_left = 0.0f + m_px + block->GetScroll();
	dst.m_right = 64.0f + m_px + block->GetScroll();
	dst.m_bottom = 32.0f + m_py +32.0f;

	//�`��
	Draw::Draw(4, &src, &dst, c, 0.0f);

}

void CObjGold::Hit()
{
	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);

	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//�X�C�b�`�̏��擾
	CObjswitch* swch=(CObjswitch*)Objs::GetObj(OBJ_SWITCH);
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//hero_Hit
	CObjhero_hitbox* hero_hit = (CObjhero_hitbox*)Objs::GetObj(HERO_HITBOX);

	if (m_gold_vy == 0 && m_hit_down == false)
	{
		//�q�b�g�{�b�N�X�ɐG��Ă��鎞
		if (hit->CheckObjNameHit(OBJ_GOLD) != nullptr)
		{
			//�S�[���h�ɓ������Ă���Ȃ瓮�����~�߂�
			m_vy = 0.0f;
			m_gold_vy = 1;
		}
	}

	if (swch != nullptr)
	{
		//����̉����ɃX�C�b�`���������Ă��鎞
		if (hit->CheckObjNameHit(OBJ_SWITCH) != nullptr)
		{
			int a = 0;
		}

		//����̉����ɃX�C�b�`���������Ă��鎞
		if (hit->CheckObjNameHit(OBJ_SWITCH) != nullptr/*&& m_hit_down == false*/ && m_vy != 0.0f)
		{
			//�X�C�b�`�̃t���O���I���ɂ���
			swch->SetSwitchFlag(true);
			m_switch_time++;//�������Ă���̎��Ԃ��v��
			m_switch_gold_flag = true;//�X�C�b�`�𓥂�ł���i�ːi����G��false�ɂ��Ȃ��悤�ɂ���j

			//�v������5F��ɋ���̓������~�߂�
			if (m_switch_time >= 8)
			{
				m_vy = 0.0f;
				m_gold_vy = 1;
			}
		}
	}

	if (hit->CheckObjNameHit(OBJ_HERO) != nullptr)
	{
		//�ǂ̊p�x�œ������Ă��邩���m�F
		HIT_DATA** hit_data;                         //���������Ƃ��ׂ̍₩�ȏ������邽�߂̍\����
		hit_data = hit->SearchObjNameHit(OBJ_HERO);  //hit_data��HitBox�Ƃ̏�������

		for (int i = 0; i < hit->GetCount(); i++)
		{
			if (hit_data[i] != NULL)
			{
				float r2 = hit_data[i]->r;

				//��l������ɏ�����Ă���ꍇ��l���̈ړ��ʂ�0�ɂ���B
				if (r2 >= 20&& r2 < 160 /*&& hero->GetY() < m_py */)
				{
					//��
					//��l��������̍��E�ɓ����������A��l�����u���b�N��o�낤�Ƃ��Ă�Ƃ��ɉ���
					if (hero->SetG() == false && hero->Gety() == false /*&& hero_hit->HitCheck() == true*/ && hero_hit->GetY() > m_py)
						hero->SetY(m_py - 30.0f);//��l��������̏�ɓ\��t���ɂ���B
				}
			}
		}
	}
	else
	{
		m_hero_flag = false;
	}
}