#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F����
class CObjGold : public CObj
{
public:
	CObjGold(float x,float y);
	~CObjGold() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[
	float GetX() { return m_px; }						//m_px,m_py�̒l��n��
	float GetY() { return m_py; }
	void  Hit();

private:
	float m_px;//�ʒu
	float m_py;
	float m_vy; //�ړ���
	float m_vx;
	int a;
				//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;

	//����ł���block�̎�ނ��m�F�p
	int m_block_type;
};