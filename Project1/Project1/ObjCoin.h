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
	float m_x;     //�e�ۂ�X�����̈ʒu�p�ϐ�
	float m_y;     //�e�ۂ�Y�����̈ʒu�p�ϐ�
	float m_vx;    //�e�ۂ�X�����̑��x�p�ϐ�
	int    m_ani;     //���e�A�j���[�V�����p
	int    m_ani_time;//���e�A�j���[�V�����폜
	bool   m_del;     //�폜�`�F�b�N
};