#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�ːi�G
class CObjGolemJudgment : public CObj
{
public:
	CObjGolemJudgment(float x, float y);
	~CObjGolemJudgment() {};
	void Init();	//�C�j�V�����C�Y
	void Action();
	void Draw();	//�h���[
private:
	float m_px;//�ʒu
	float m_py;
	float m_vy; //�ړ���
	float m_vx;
};