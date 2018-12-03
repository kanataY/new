#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g : �e��
class CObjCoin : public CObj
{
public:
	CObjCoin(float x, float y);//�R���X�g���N�^
	~CObjCoin() {};
	void Init();   //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw();   //�h���[
private:
	float m_px;     //�e�ۂ�X�����̈ʒu�p�ϐ�
	float m_py;     //�e�ۂ�Y�����̈ʒu�p�ϐ�
	float m_vx;    //�e�ۂ�X�����̑��x�p�ϐ�
	float m_vy;//�e�ۂ�Y�����̑��x�p�ϐ�
	int   m_hero_pos;//��l���̌����ۑ��p
	bool   m_del;     //�폜�`�F�b�N

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
	//����ł���block�̎�ނ��m�F�p
	int m_block_type;
};