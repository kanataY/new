#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjTitle : public CObj
{
public:
	CObjTitle() {};
	~CObjTitle() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	int m_key_flag;//1:���j���[��2:�I��
	bool m_key_control;//�L�[�̐���p
	bool m_enter_control;//�G���^�[���������ς̎��̃t���O
	int m_scene_start_control;//�^�C�g���ɔ�񂾎��ɂ���Menu�ɔ�Ԃ̂�h���ϐ�
	//-�A�j���[�V����
	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l
	int m_ani_time2; //�A�j���[�V�����t���[�����슴�o
	float m_ani_max_time2;   //�A�j���[�V��������Ԋu�ő�l
	bool m_ani_start_flag;   //�A�j���슴�o2���n�������邽�߂̃t���O

};