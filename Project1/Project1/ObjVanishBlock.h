#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�S�[��
class CObjVanishBlock : public CObj
{
public:
	CObjVanishBlock(float x, float y);
	~CObjVanishBlock() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	void Hit();     //�q�b�g�֘A
private:
	float m_px;//�ʒu
	float m_py;

	float  m_hit_draw; //�`��̉����@��l���ɓ���������ύX
	float  m_draw_right;    //���̕`��
	float  m_draw_bottom;	//�c�̕`��
	bool   m_swich_flag;     //�X�C�b�`��������Ă��邩�ǂ���������ϐ�
};
