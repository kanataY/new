//�g�p����w�b�_�[�t�@�C��
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "Correction.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CObjCorrection::CObjCorrection()
{

}

//�C�j�V�����C�Y
void CObjCorrection::Init()
{
	m_py = 0.0f;
	m_px = 0.0f;
	m_screen_out = false;
	m_hole_control = false;
}

void CObjCorrection::Action()
{

}

void CObjCorrection::Draw()
{

}

//�I�u�W�F�N�g���������Ƃ���Y��������͈͂��O�����������璲������
float CObjCorrection::RangeY(float y, bool b)
{
	//�X�}�z���N�͉��ɂ��s��
	if (b == false)
	{
		if (y > OUTOFRANGE_DOWN)  //������͈͂�艺�ɂ���ꍇ�M���M���܂Ŗ߂�
			return OUTOFRANGE_DOWN;
	}
	if (y < OUTOFRANGE_UP)//������͈͂���ɂ���ꍇ�M���M���܂Ŗ߂�
		return OUTOFRANGE_UP;

	return y;
}

//�I�u�W�F�N�g���������Ƃ���Y��������͈͂��O�����������璲�����鐅���܂�o�[�W����
float CObjCorrection::RangeYPuddle(float y)
{

	if (y > OUTOFRANGE_DOWN_PUDDLE)  //������͈͂�艺�ɂ���ꍇ�M���M���܂Ŗ߂�
		return OUTOFRANGE_DOWN_PUDDLE;
	else if (y < OUTOFRANGE_UP_PUDDLE)//������͈͂���ɂ���ꍇ�M���M���܂Ŗ߂�
		return OUTOFRANGE_UP_PUDDLE;

	return y;
}

//�I�u�W�F�N�g���������Ƃ���Y��������͈͂��O�����������璲������g���b�N�o�[�W����
float CObjCorrection::RangeYTrack(float y)
{

	if (y > 480.0f)  //������͈͂�艺�ɂ���ꍇ�M���M���܂Ŗ߂�
		return 480.0f;
	else if (y < 220.0f)//������͈͂���ɂ���ꍇ�M���M���܂Ŗ߂�
		return 220.0f;

	return y;
}


//��ʊO�ɍs���Ə����鏈��
bool CObjCorrection::Screen_Out(float x)
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
	
	//��ʊO�Ȃ�true��Ԃ�
	if (x + block->GetScroll() < -50)
	{
		return true;
	}

	return false;
}

//��ʊO�ɍs���Ə����鏈��
float CObjCorrection::Screen_In(float x)
{
	//�u���b�N���������Ă���
	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);

	//�����i�[�̈ʒu���擾
	CObjRunner* runner = (CObjRunner*)Objs::GetObj(OBJ_RUNNER);
	
	//��ʊO�Ȃ�true��Ԃ�
	if (x > 750.0f)
	{
		x = 750.0f;
	}

	return x;
}