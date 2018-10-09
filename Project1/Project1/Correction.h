#pragma once
//�g�p�w�b�_�[
#include "GameL\SceneObjManager.h"
//�g�p����l�[���X�y�[�X
using namespace GameL;

#define OUTOFRANGE_UP 277.0f		  //�͈͊O���ǂ������ׂ�l
#define OUTOFRANGE_DOWN 536.0f
#define OUTOFRANGE_UP_PUDDLE 328.0f   //�͈͊O���ǂ������ׂ�l�@�����܂�o�[�W����
#define OUTOFRANGE_DOWN_PUDDLE 536.0f

//�I�u�W�F�N�g�F�␳
class CObjCorrection : public CObj
{
public:
	CObjCorrection();
	~CObjCorrection() {};
	void Init();									//�C�j�V�����C�Y
	void Action();									//�A�N�V����
	void Draw();									//�h���[
	float RangeY(float y, bool b);							//�͈͊O�ɂ���Ƃ��ɂ�����
	float RangeYPuddle(float y);					//�͈͊O�ɂ���Ƃ��ɂ����������܂�o�[�W����
	float RangeYTrack(float y);					//�͈͊O�ɂ���Ƃ��ɂ������g���b�N�o�[�W����
	void  FireDisplayCrates(float x, float y);		//����\�������� ������
	void  FireDisplay(float x, float y);			//����\��������
	bool  Screen_Out(float x);						//��ʊO�ɍs���Ə����鏈��
	float  Screen_In(float x);						//�E�ɍs���߂��Ȃ��悤�ɂ��鏈��
private:
	float m_px;		//�ʒu
	float m_py;
	bool  m_screen_out;  //��ʊO�ɂ������ǂ���������ϐ�
	bool m_hole_control;			//������

};