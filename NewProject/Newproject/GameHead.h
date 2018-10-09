#pragma once

//�I�u�W�F�N�g�l�[��------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//�I�u�W�F�N�g������(�֎~)
	//�Q�[���Ŏg���I�u�W�F�N�g�̖��O
	//OBJ_�����ƕ\�L
	OBJ_RUNNER,				//�����i�[
	OBJ_BLOCK,				//�u���b�N
	OBJ_GAUGE,				//�Q�[�W
	OBJ_CRATES,				//�ؔ�
	OBJ_SMARTPHONE,			//�X�}�z���N
	OBJ_FIRE,				//��
	OBJ_TORCH,				//����
	OBJ_PUDDLE,				//�����܂�
	OBJ_RAIN,               //�J
	OBJ_OKAMA,              //�I�J�}
	OBJ_HOLE,				//��
	OBJ_CHECK_POINT,		//�`�F�b�N�|�C���g
	OBJ_TRACK,				//�g���b�N
	OBJ_WARNING,			//�x��

	//�␳
	CORRECTION,				//�␳

	//�V�[��
	OBJ_TITLE,				//�^�C�g��
	OBJ_GAME_OVER,			//�Q�[���I�[�o�[
	OBJ_GAME_CLEAR,			//�Q�[���N���A
	OBJ_RANKING,			//�����L���O
	OBJ_MENU,				//���j���[
	OBJ_OPERATION,			//�������
};
//------------------------------------------------

//�����蔻�葮��----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//�������� �S�Ă̑����Ɠ����蔻�肪���s�����
	//�ȉ��@�����������m�ł͓����蔻��͎��s����Ȃ�
	//�����͒ǉ��\�����A�f�o�b�N���̐F�͏����ݒ蕪��������
	ELEMENT_RUNNER,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
};
//------------------------------------------------
//�Q�[�����Ŏg�p�����O���[�o���ϐ��E�萔�E��--
#define RANKING_MAX_COUNT (4) // �����L���O��+1
#define MAX_CHAR_COUNT (6)	   // ���͂ł��镶���� 
//------------------------------------------------
//�Z�[�u�����[�h�ƃV�[���Ԃ̂���肷��f�[�^
struct UserData
{
	int mSeveData;	//�T���v���Z�[�u�f�[�^
	int m_point;		//GameMain�œ����|�C���g
	int m_stage_count;//�X�e�[�W�̎��
	int m_ranking[RANKING_MAX_COUNT];//�����L���O�i�[�z��
	/*wchar_t m_name[RANKING_MAX_COUNT][MAX_CHAR_COUNT];*/
};
//------------------------------------------------


//�Q�[�����Ŏg�p����N���X�w�b�_------------------


//------------------------------------------------

//�Q�[���V�[���I�u�W�F�N�g�w�b�_------------------
#include "ObjRunner.h"			//�����i�[
#include "ObjBlock.h"			//�u���b�N
#include "ObjGauge.h"			//�Q�[�W	
#include "ObjTitle.h"			//�^�C�g��
#include "ObjCrates.h"			//�ؔ�
#include "ObjSmartPhone.h"		//�X�}�z���N
#include "ObjFire.h"			//��
#include "ObjTorch.h"			//����
#include "ObjPuddle.h"			//�����܂�
#include "ObjRain.h"			//�J
#include "ObjOkama.h"			//�I�J�}
#include "ObjHole.h"			//��
#include "ObjTrack.h"			//�g���b�N
#include "ObjCheckPoint.h"		//�`�F�b�N�|�C���g
#include "ObjWarning.h"			//�x��

#include "ObjTitle.h"			//�^�C�g��
#include "ObjGameOver.h"		//�Q�[���I�[�o�[
#include "ObjRanking.h"			//�����L���O
#include "ObjMenu.h"			//���j���[
#include "ObjGameClear.h"		//�N���A
#include "ObjOperation.h"		//�������
//�⏕�n
#include "Correction.h"			//�␳
//------------------------------------------------

//�Q�[���V�[���N���X�w�b�_------------------------
#include "SceneMain.h"			//�V�[���^�C�g��
#include "SceneTitle.h"			//�V�[�����C��
#include "SceneGameOver.h"		//�V�[���Q�[���I�[�o�[
#include "SceneMenu.h"			//�V�[�����j���[
#include "SceneRanking.h"		//�V�[�������L���O
#include "SceneGameClear.h"		//�V�[���N���A
#include "SceneOperation.h"		//�V�[���������

//-----------------------------------------------

//�V�[���X�^�[�g�N���X---------------------------
//�Q�[���J�n���̃V�[���N���X�o�^
#define SET_GAME_START CSceneTitle
//-----------------------------------------------