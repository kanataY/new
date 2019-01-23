//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\HitBoxManager.h"
#include "GameHead.h"

#include "hero_hitbox.h"
#include "GameL\Audio.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�R���X�g���N�^
CObjhero_hitbox::CObjhero_hitbox()
{

}
//�C�j�V�����C�Y
void CObjhero_hitbox::Init()
{
	//�����蔻��pHitBox���쐬
	Hits::SetHitBox(this, m_px, m_py, 37, 20, ELEMENT_NULL, HERO_HITBOX, 1);
}
//�A�N�V����
void CObjhero_hitbox::Action()
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//��l���̏��������Ă���
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	//Y�ʒu�X�V
	m_py = hero->GetY() + 44.0f;

	//HitBox�̈ʒu�̕ύX
	CHitBox* hit = Hits::GetHitBox(this);
	hit->SetPos(hero->GetX() + 15.0f /*- block->GetScroll()*/, m_py);

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

				if (r2 >= 202 && r2 < 330)
				{
					hit_check = true;
				}
				else
					hit_check = false;
			}
		}
	}
}
//�h���[
void CObjhero_hitbox::Draw()
{

}