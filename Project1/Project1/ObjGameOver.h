#pragma once
//�g�p����w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�^�C�g��
class CObjGameOver : public CObj
{
public:
	CObjGameOver() {};
	~CObjGameOver() {};
	void Init();	//�C�j�V�����C�Y
	void Action();	//�A�N�V����
	void Draw();	//�h���[
	int GetTime() { return m_time; }
	bool GetRankingInFlag() { return m_ranking_in_floag; }
private:
	bool m_key_flag;//�L�[�t���O
	int   m_time;	//���ԊǗ�
	bool m_ranking_in_floag;//�����L���O������ʂ��������ǂ����t���O
};
