#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�j
class CObjthorn : public CObj
{
public:
	CObjthorn(float x, float y);
	~CObjthorn() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	float m_px;//�ʒu
	float m_py;
	float m_vx;//�ړ�
	float m_vy;
	//�����蔻��
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_left;
	bool m_hit_right;
	//�ǂ����̌����ɓ������Ă邩�̊m�F
	float m_pos;
	//�u���b�N�̃^�C�v�m�F
	int m_block_type;
	
};