#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjOperation : public CObj
{
public:
	CObjOperation() {};
	~CObjOperation() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
private:
	int m_scene_flag;//�摜�ύX�p �@0:������� 1:�ڂ��̐���
	bool m_enter_control;//�G���^�[�L�[�̐���p�̃t���O
	bool m_zkey_control; //Z�L�[�̐���p�̃t���O
	int  m_scene_start_control_time;//��x�����Ȃ��Ɛi�܂Ȃ����ۂ����P���邽�߂̕ϐ�

	//-�A�j���[�V����
	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l

	int m_okam_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_okam_ani_frame;//�`��t���[��
	float m_okam_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l
};