#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

//�}�N���@
#define MAP_X_MAX 200

//�I�u�W�F�N�g�F�u���b�N���w�i
class CObjBlock : public CObj
{
public:
	CObjBlock(int map[10][MAP_X_MAX]);
	~CObjBlock() {};
	void Init();	//�C�j�V�����C�Y
	void Action();  //�A�N�V����
	void Draw();	//�h���[
	
	void  SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }

	int  GetMap(int x, int y);//�}�b�v���̎擾
	void  SetMap(int x, int y, int m) { m_map[y][x] = m; }
	bool  GetRain() { return m_rain; }//�J�̏��̎擾
	void  SetRain(bool r) { m_rain = r; }
	

private:
	float m_px;		//�ʒu
	float m_py;
	float m_bx1;     //�w�i�̓����l
	float m_bx2;     //�w�i�̓����l2
	bool  m_rain;    //�J���~�炷
	
	float m_scroll; //�X�N���[���ʒu
	float m_scroll_run; //�����i�[�̈ʒu�ŃX�N��ς���悤�̕ϐ�

	int m_scroll_num;//�X�N���[���̐��𒲂ׂ�ϐ�

	int m_map[10][MAP_X_MAX];//�}�b�v���
	int m_map_Record[10][MAP_X_MAX];//�}�b�v���L�^��
};