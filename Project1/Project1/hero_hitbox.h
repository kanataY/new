#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F��l���̃q�b�g�{�b�N�X�̂�
class CObjhero_hitbox : public CObj
{
public:
	CObjhero_hitbox();
	~CObjhero_hitbox() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	bool HitCheck() { return hit_check; } //����̏�Ƀq�b�g���Ă��邩�ǂ�����n��
	float GetY() { return m_py; }			//�q�b�g�{�b�N�X��Y�ʒu��n���B

private:
	float m_px;//�ʒu
	float m_py;

	bool hit_check;  //����ɓ������Ă�����ture:
};