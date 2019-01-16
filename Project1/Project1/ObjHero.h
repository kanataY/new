#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F�����i�[
class CObjHero : public CObj
{
public:
	CObjHero();
	~CObjHero() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[
	void HitBox();  //�����蔻��֘A
	float GetX() { return m_px; }						//m_px,m_py�̒l��n��
	float GetY() { return m_py; }
	float GetVY() { return m_vy; }						//m_vx,m_vy�̒l��n��
	float GetVX() { return m_vx; }
	int   GetPos() { return m_pos; }					//pos�̒l�n��
	bool Gety() { return m_gold_M; }
	bool GetHitLeft() { return m_hit_left; }			//�����ǂɓ������Ă邩�̏��n��
	bool GetHitRight() { return m_hit_right; }			//�E���ǂɓ������Ă邩�̏��n��

	void  SetX(float x) { m_px = x; }					//m_px,m_py�̒l���ق���cpp�ł��������悤�ɂ���
	void  SetY(float y) { m_py = y; }
	void  SetVX(float x) { m_vx = x; }					//m_vx,m_vy�̒l���ق���cpp�ł��������悤�ɂ���
	bool  SetG() { return m_gold_Y; }
	void  SetVY(float y) { m_vy = y; }
	void Sety(bool b) { m_gold_M = b; }
	void SetBT(int bt) { m_block_type = bt; }//����ł���̂̏����󂯎��
	
private:
	float m_px;			//�ʒu
	float m_py;
	float m_vx;			//�ړ��x�N�g��
	float m_vy;
	float m_ppx, m_ppy; //�}�b�v��������ϐ�
	float m_speed;      //��l���̈ړ��ʂ̃X�s�[�h�Ǘ�
	int   m_gold_time;  //����̒u���Ԋu
	int con;
	
	//����n---------
	bool m_gold_flag;  //������o�������Ȃ��悤�ɂ��邽��
	bool m_gold_spawn; //������o����ʒu�����߂�
	bool m_coinshot_flag;//�R�C�����o�������Ȃ��悤�ɂ��邽��
	bool m_gold_Y;
	bool m_gold_M;

	//-�A�j���[�V����
	int m_ani_time; //�A�j���[�V�����t���[�����슴�o
	int m_ani_frame;//�`��t���[��
	float m_ani_max_time;   //�A�j���[�V��������Ԋu�ő�l
	int m_ani_change; //�A�j���[�V�����ύX�ϐ�

	//block�Ƃ̏Փˏ�Ԋm�F�p
	bool m_hit_up;
	bool m_hit_down;
	bool m_hit_down_gold; //����̏�ɏ�����Ă��鎞�p
	bool m_hit_left;
	bool m_hit_right;

	//����
	int  m_pos;//�����Ă����
	//����ł���block�̎�ނ��m�F�p
	int m_block_type;
};