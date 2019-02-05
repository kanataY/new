#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�ːi�G
class CObjRushEnemy : public CObj
{
public:
	CObjRushEnemy(float x, float y);
	~CObjRushEnemy() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[
	void Hit();     //�����蔻��
	float GetX() { return m_px; }						//m_px,m_py�̒l��n��
	float GetY() { return m_py; }

private:
	float m_px;//�ʒu
	float m_py;
	float m_vy; //�ړ���
	float m_vx;
	float m_speed;
	float m_xmemo; //�ʒu�L�^
	//-�A�j���[�V����
	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
	
	//����
	bool m_move;//�ړ�����
	float  m_pos;//�����Ă����
	//����ł���block�̎�ނ��m�F�p
	int m_block_type;
};