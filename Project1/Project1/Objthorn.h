#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g : �j
class CObjthorn : public CObj
{
public:
	CObjthorn(float x, float y);//�R���X�g���N�^
	~CObjthorn() {};
	void Init();   //�C�j�V�����C�Y
	void Action(); //�A�N�V����
	void Draw();   //�h���[
private:
	float m_px;     //�j��X�����̈ʒu�p�ϐ�
	float m_py;     //�j��Y�����̈ʒu�p�ϐ�
};