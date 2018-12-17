//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"
#include "ObjCoin.h"
#include "GameL\Audio.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjCoin::CObjCoin(float x, float y)
{
	m_px = x;
	m_py = y;
}


//�C�j�V�����C�Y
void CObjCoin::Init()
{
	m_hero_pos = 0;
	m_del = false;
	m_vy = 0.0f;
	m_vx = 0.0f;
	//block�Ƃ̏Փˏ�Ԋm�F�p
	m_hit_up = false;
	m_hit_down = false;
	m_hit_left = false;
	m_hit_right = false;

	m_block_type = 0; //����ł���block�̎�ނ��m�F�p
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 32, 32, ELEMENT_HERO, OBJ_COIN, 1);

}

//�A�N�V����
void CObjCoin::Action()
{
	//��l�����������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	//�e�ۏ��ŏ���
	if (m_del == true)
	{

		this->SetStatus(false);
		Hits::DeleteHitBox(this);
		return;//���ŏ����́A�����ŃA�N�V�������]�b�h���I��������
	}
	
	//�e�ێ��s����
	if (m_hero_pos==0)
		m_vx += 0.3f;
	else
		m_vx -= 0.3f;
	m_px += m_vx;
	m_py += m_vy;
	block->Block32Hit(&m_px, &m_py, true,
		&m_hit_up, &m_hit_down, &m_hit_left, &m_hit_right, &m_vx, &m_vy,
		&m_block_type, 0
	);
	//�e�ۂ�HitBox�X�V�p�|�C���^�[�擾
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(m_px, m_py);    //HitBox�̈ʒu��e�ۂ̈ʒu�ɍX�V
								//�̈�O�ɏo����e�ۂ�j������

	if (m_px + block->GetScroll() < -32.0f ||m_px + block->GetScroll()>800.0f)
	{
		this->SetStatus(false);   //���g�ɍ폜���߂��o���B
		Hits::DeleteHitBox(this); //�e�ۂ����L����HitBox�ɍ폜����B
	}

	//�����蔻����s���I�u�W�F�N�g���S
	int data_base[2] =
	{
		OBJ_JUMP_ENEMY,
		OBJ_RUSH_ENEMY,
	};

	//�I�u�W�F�N�g���S�Ɠ����蔻��s���B�������Ă���΍폜
	for (int i = 0; i < 3; i++)
	{
		if (hit->CheckObjNameHit(data_base[i]) != nullptr||m_hit_left==true||m_hit_right==true)
		{
			m_del = true;				 //����
			hit->SetInvincibility(true); //�����蔻�薳��
		}
	}
}

//�h���[
void CObjCoin::Draw()
{
	//�`��J���[���@R=RED�@G=Green�@B=Blue�@A=alpha(���ߏ��)
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //�`�挳�؂���ʒu
	RECT_F dst; //�`���\���ʒu
				//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;
	//�\���ʒu�̐ݒ�
	dst.m_top = 0.0f + m_py;
	dst.m_left = 0.0f + m_px;
	dst.m_right = 32.0f + m_px;
	dst.m_bottom = 32.0f + m_py;

	//7�Ԗڂɓo�^�����O���t�B�b�N��src�Edst�Ec�E�̏������ɕ`��
	Draw::Draw(7, &src, &dst, c, 0.0);
}