#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjMenu : public CObj
{
public:
	CObjMenu() {};
	~CObjMenu() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	int m_key_flag;//1:�X�e�[�W�Z���N�g2:�����L���O3:�^�C�g���ɖ߂�4:�������
	bool m_key_control;//�\���L�[�̐���p
	bool m_enter_control;//�G���^�[�L�[�̐���p�̃t���O
};