#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�X�C�b�`
class CObjswitch : public CObj
{
public:
	CObjswitch(float x, float y);
	~CObjswitch() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	void SetSwitchFlag(bool ssf) { switch_on_flag = ssf; }
private:
	float m_px;//�ʒu
	float m_py;
	bool switch_on_flag;//�X�C�b�`�ɓ����������̃t���O
};