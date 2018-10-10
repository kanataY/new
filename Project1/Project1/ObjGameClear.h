#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjGameClear : public CObj
{
public:
	CObjGameClear() {};
	~CObjGameClear() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	int GetTime() { return m_time; }
	bool GetRankingInFlag() { return m_ranking_in_floag; }
private:
	int m_time; //���ԊǗ�
	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l
	bool m_o_tap_flag;  //o�����������̃t���O

	bool m_audio_flag;  //���y��炷�Ƃ��̃t���O
	bool m_ranking_in_floag; //�����L���O���肵�����ǂ����t���O�@ON:�����@OFF�F���Ă��Ȃ�
	void Ranking();//�X�R�A�̌��ʂ������L���O�̒��Ƀ����N�C���������ǂ����𒲂ׂ�֐�
};
