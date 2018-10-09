//STL�f�o�b�N�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneMain.h"
#include "GameHead.h"


CSceneMain::CSceneMain(int r)
{
	remaining = r;	//�c�@
}


//�f�X�g���N�^
CSceneMain::~CSceneMain()
{

}

//���������\�b�h
void CSceneMain::InitScene()
{
	//�}�b�v�쐻
	int map[MAP_Y][MAP_X];
	MapCreate(map);
	//�X�e�[�W���ƂɎ�l���Ɣw�i���i�[
	//switch (((UserData*)Save::GetData())->m_stage_count)
	//{
	//case 1://�X�e�[�W��1�̎�
	//	//�w�i�̉摜�o�^-------------------------------------------------------------------
	//	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(1024�s�N�Z��)
	//	Draw::LoadImageW(L"Image\\back\\back\\back1-1.png", 0, TEX_SIZE_1024); //�w�i1
	//	//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(1024�s�N�Z��)
	//	Draw::LoadImageW(L"Image\\back\\back\\back2-1.png", 1, TEX_SIZE_1024); //�w�i2  
	//	//�O���O���t�B�b�N�t�@�C����ǂݍ���29�Ԃɓo�^(1024�s�N�Z��)
	//	Draw::LoadImageW(L"Image\\back\\back\\back_final.png", 26, TEX_SIZE_1024); //�w�i�Ō�
	//	//----------------------------------------------------------------------------------
	//	break;

	//case 2://�X�e�[�W��2�̎�
	//	//�w�i�̉摜�o�^-------------------------------------------------------------------
	//	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(1024�s�N�Z��)
	//	Draw::LoadImageW(L"Image\\back\\back\\back1-2.png", 0, TEX_SIZE_1024); //�w�i1
	//	//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(1024�s�N�Z��)
	//	Draw::LoadImageW(L"Image\\back\\back\\back2-2.png", 1, TEX_SIZE_1024); //�w�i2
	//	//�O���O���t�B�b�N�t�@�C����ǂݍ���26�Ԃɓo�^(1024�s�N�Z��)
	//	Draw::LoadImageW(L"Image\\back\\back\\back_final2.png", 26, TEX_SIZE_1024); //�w�i�Ō�
	//	//---------------------------------------------------------------------------------------------

	//	break;
	//case 3://�X�e�[�W��3�̎�
	//	//�w�i�̉摜�o�^-------------------------------------------------------------------
	//	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(1024�s�N�Z��)
	//	Draw::LoadImageW(L"Image\\back\\back\\back1.png", 0, TEX_SIZE_1024); //�w�i1
	//	//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(1024�s�N�Z��)
	//	Draw::LoadImageW(L"Image\\back\\back\\back2.png", 1, TEX_SIZE_1024); //�w�i2
	//	//�O���O���t�B�b�N�t�@�C����ǂݍ���26�Ԃɓo�^(1024�s�N�Z��)
	//	Draw::LoadImageW(L"Image\\back\\back\\back_final3.png", 26, TEX_SIZE_1024); //�w�i�Ō�
	//	//---------------------------------------------------------------------------------------------
	//	break;
	//}
	
	
	

	//��l���I�u�W�F�N�g�쐬
	

	//�w�i�i�u���b�N�j�I�u�W�F�N�g�쐬
	CObjBlock* block = new CObjBlock(map);
	Objs::InsertObj(block, OBJ_BLOCK, 10);

	//�Q�[�W�I�u�W�F�N�g�쐬
	

	//�␳�I�u�W�F�N�g�쐬
	CObjCorrection* cor = new CObjCorrection();
	Objs::InsertObj(cor, CORRECTION, 13);


	//���y�ǂݍ���
	


	////�{�����[����1.5���₷
	//float v = Audio::VolumeMaster(1.5);

	//���y�X�^�[�g
	//Audio::Start(0);
}

//���s�����\�b�h
void CSceneMain::Scene()
{

}

////�X�e�[�W���Ƃ̃}�b�v�쐬
//void CSceneMain::MapCreate(int map[][MAP_X])
//{
//	//�O���f�[�^�̓ǂݍ��݁i�X�e�[�W���j
//	unique_ptr<wchar_t> p; //�X�e�[�W���|�C���^�[
//	int size;			   //�X�e�[�W���̑傫��
//
//	//�X�e�[�W���ƂɃX�e�[�W�̖��O���i�[
//	switch (((UserData*)Save::GetData())->m_stage_count)
//	{
//	case 1:
//		p = Save::ExternalDataOpen(L"Stage01.csv", &size);//�O���f�[�^�ǂݍ���
//		break;
//	case 2:
//		p = Save::ExternalDataOpen(L"Stage02.csv", &size);//�O���f�[�^�ǂݍ���
//		break;
//	case 3:
//		p = Save::ExternalDataOpen(L"Stage03.csv", &size);//�O���f�[�^�ǂݍ���
//		break;
//	default:
//		MessageBox(0, L"�X�e�[�W�ԍ�������������܂���B", NULL, MB_OK);
//		break;
//	}
//
//	//�O���f�[�^���ǂݍ��߂Ȃ�������G���[���b�Z�[�W���o���B
//	if (p == NULL)
//	{
//		MessageBox(0, L"�O���f�[�^���ǂݍ��߂܂���ł����B", NULL, MB_OK);
//	}
//	int count = 1;
//	for (int i = 0; i < MAP_Y; i++)
//	{
//		for (int j = 0; j < MAP_X; j++)
//		{
//			int w = 0;
//			swscanf_s(&p.get()[count], L"%d", &w);
//
//			map[i][j] = w;
//			if (w > 9)//10�𒴂����ꍇ
//				count += 3;//���炷���𑝂₷
//			else
//				count += 2;
//		}
//	}
//}