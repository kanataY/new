#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�����L���O
class CObjRanking : public CObj
{
public:
	CObjRanking() {};
	~CObjRanking() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	void DrawNumber(float dst_top, float dst_left, float dst_size, int num, float interval, float c[4]);//������`��֐�
private:
	float m_interval;//�l�ƒl�̊Ԋu�������΂߂�l
};