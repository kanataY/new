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
	switch (((UserData*)Save::GetData())->m_stage_count)
	{
	case 1://�X�e�[�W��1�̎�
		//�w�i�̉摜�o�^-------------------------------------------------------------------
		//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(1024�s�N�Z��)
		Draw::LoadImageW(L"Image\\back\\back\\back1-1.png", 0, TEX_SIZE_1024); //�w�i1
		//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(1024�s�N�Z��)
		Draw::LoadImageW(L"Image\\back\\back\\back2-1.png", 1, TEX_SIZE_1024); //�w�i2  
		//�O���O���t�B�b�N�t�@�C����ǂݍ���29�Ԃɓo�^(1024�s�N�Z��)
		Draw::LoadImageW(L"Image\\back\\back\\back_final.png", 26, TEX_SIZE_1024); //�w�i�Ō�
		//----------------------------------------------------------------------------------

		//�����i�[�̉摜�o�^-------------------------------------------------------------------------------------
		//�O���O���t�B�b�N�t�@�C����ǂݍ���2�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\runner.png", 2, TEX_SIZE_256);    //��ꑖ��
		//�O���O���t�B�b�N�t�@�C����ǂݍ���3�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\runner_transfer.png", 3, TEX_SIZE_256);    //�ꑖ�҂̉΂��������[�V����
		//�O���O���t�B�b�N�t�@�C����ǂݍ���4�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\runner_invincible.png", 4, TEX_SIZE_256);    //��ꑖ�҂̓_��
		//�O���O���t�B�b�N�t�@�C����ǂݍ���5�Ԃɓo�^(192�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\runner_death.png", 5, TEX_SIZE_192);  //��ꑖ�҂̎��S

		//�����i--------------------------------------------------------------------------------------
		//�O���O���t�B�b�N�t�@�C����ǂݍ���27�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\youtuber.png", 27, TEX_SIZE_256);    //YouTuber
		//�O���O���t�B�b�N�t�@�C����ǂݍ���28�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\youtuber_transfer.png", 28, TEX_SIZE_256);  //YouTuber�̐U�肩����
		//---------------------------------------------------------------------------------------------
		break;

	case 2://�X�e�[�W��2�̎�
		//�w�i�̉摜�o�^-------------------------------------------------------------------
		//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(1024�s�N�Z��)
		Draw::LoadImageW(L"Image\\back\\back\\back1-2.png", 0, TEX_SIZE_1024); //�w�i1
		//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(1024�s�N�Z��)
		Draw::LoadImageW(L"Image\\back\\back\\back2-2.png", 1, TEX_SIZE_1024); //�w�i2
		//�O���O���t�B�b�N�t�@�C����ǂݍ���26�Ԃɓo�^(1024�s�N�Z��)
		Draw::LoadImageW(L"Image\\back\\back\\back_final2.png", 26, TEX_SIZE_1024); //�w�i�Ō�
		//---------------------------------------------------------------------------------------------

		//�����i--------------------------------------------------------------------------------------
		//�O���O���t�B�b�N�t�@�C����ǂݍ���2�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\youtuber.png", 2, TEX_SIZE_256);    //YouTuber
		//�O���O���t�B�b�N�t�@�C����ǂݍ���3�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\youtuber_transfer.png", 3, TEX_SIZE_256);  //YouTuber�̐U�肩����
		//�O���O���t�B�b�N�t�@�C����ǂݍ���4�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\youtuber_invincible.png", 4, TEX_SIZE_256);    //YouTuber�̓_��
		//�O���O���t�B�b�N�t�@�C����ǂݍ���5�Ԃɓo�^(192�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\youtuber_death.png", 5, TEX_SIZE_192);    //YouTuber�̎��S
		//-------------------------------------------------------------------------------------

		//�S�[���n�_�̃����i--------------------------------------------------------------------------------------
		//�O���O���t�B�b�N�t�@�C����ǂݍ���27�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\grandfather.png", 27, TEX_SIZE_256);    //����������
		//�O���O���t�B�b�N�t�@�C����ǂݍ���28�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\grandfather_transfer.png", 28, TEX_SIZE_256);  //����������̐U�肩����
		//---------------------------------------------------------------------------------------------
		break;
	case 3://�X�e�[�W��3�̎�
		//�w�i�̉摜�o�^-------------------------------------------------------------------
		//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(1024�s�N�Z��)
		Draw::LoadImageW(L"Image\\back\\back\\back1.png", 0, TEX_SIZE_1024); //�w�i1
		//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(1024�s�N�Z��)
		Draw::LoadImageW(L"Image\\back\\back\\back2.png", 1, TEX_SIZE_1024); //�w�i2
		//�O���O���t�B�b�N�t�@�C����ǂݍ���26�Ԃɓo�^(1024�s�N�Z��)
		Draw::LoadImageW(L"Image\\back\\back\\back_final3.png", 26, TEX_SIZE_1024); //�w�i�Ō�
		//---------------------------------------------------------------------------------------------

		//�����i--------------------------------------------------------------------------------------
		//�O���O���t�B�b�N�t�@�C����ǂݍ���2�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\grandfather.png", 2, TEX_SIZE_256);    //��l��3
		//�O���O���t�B�b�N�t�@�C����ǂݍ���3�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\grandfather_transfer.png", 3, TEX_SIZE_256);    //��l��3�̈ڂ�
		//�O���O���t�B�b�N�t�@�C����ǂݍ���4�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\grandfather_invincible.png", 4, TEX_SIZE_256);    //��l��3�̖��G
		//�O���O���t�B�b�N�t�@�C����ǂݍ���5�Ԃɓo�^(256�s�N�Z��)
		Draw::LoadImageW(L"Image\\hero\\grandfather_death.png", 5, TEX_SIZE_192);    //��l��3�̎��S
		//----------------------------------------------------------------------------------------

		break;
	}
	
	//��l���I�u�W�F�N�g�쐬
	CObjRunner* obj = new CObjRunner(remaining);
	Objs::InsertObj(obj, OBJ_RUNNER, 13);

	//�w�i�i�u���b�N�j�I�u�W�F�N�g�쐬
	CObjBlock* block = new CObjBlock(map);
	Objs::InsertObj(block, OBJ_BLOCK, 10);

	//�␳�I�u�W�F�N�g�쐬
	CObjCorrection* cor = new CObjCorrection();
	Objs::InsertObj(cor, CORRECTION, 13);


	//���y�ǂݍ���
	Audio::LoadAudio(0, L"BGM&SE\\BGMGameMain_.wav", BACK_MUSIC);

	Audio::LoadAudio(1, L"BGM&SE\\dashu_.wav", EFFECT); // ���鉹
	Audio::LoadAudio(2, L"BGM&SE\\Fier2__.wav", EFFECT); // �R���鉹
	Audio::LoadAudio(3, L"BGM&SE\\jump_.wav", EFFECT);  // �W�����v
	Audio::LoadAudio(4, L"BGM&SE\\rakka_.wav", EFFECT); // �����鉹
	Audio::LoadAudio(5, L"BGM&SE\\water_.wav", EFFECT); // ���ɗ�������
	Audio::LoadAudio(6, L"BGM&SE\\track_.wav", EFFECT); // �g���b�N
	Audio::LoadAudio(7, L"BGM&SE\\gool.wav", EFFECT); // �`�F�b�N�|�C���g�̊���
	Audio::LoadAudio(8, L"BGM&SE\\gool2.wav", EFFECT); // �`�F�b�N�|�C���g�̊���2
	Audio::LoadAudio(9, L"BGM&SE\\himei.wav", EFFECT); // �I�J�}�̔ߖ�
	Audio::LoadAudio(10, L"BGM&SE\\kiss.wav", EFFECT); // �I�J�}�̃L�X


	////�{�����[����1.5���₷
	//float v = Audio::VolumeMaster(1.5);

	//���y�X�^�[�g
	Audio::Start(0);
}

//���s�����\�b�h
void CSceneMain::Scene()
{

}

//�X�e�[�W���Ƃ̃}�b�v�쐬
void CSceneMain::MapCreate(int map[][MAP_X])
{
	//�O���f�[�^�̓ǂݍ��݁i�X�e�[�W���j
	unique_ptr<wchar_t> p; //�X�e�[�W���|�C���^�[
	int size;			   //�X�e�[�W���̑傫��

	//�X�e�[�W���ƂɃX�e�[�W�̖��O���i�[
	switch (((UserData*)Save::GetData())->m_stage_count)
	{
	case 1:
		p = Save::ExternalDataOpen(L"Stage01.csv", &size);//�O���f�[�^�ǂݍ���
		break;
	case 2:
		p = Save::ExternalDataOpen(L"Stage02.csv", &size);//�O���f�[�^�ǂݍ���
		break;
	case 3:
		p = Save::ExternalDataOpen(L"Stage03.csv", &size);//�O���f�[�^�ǂݍ���
		break;
	default:
		MessageBox(0, L"�X�e�[�W�ԍ�������������܂���B", NULL, MB_OK);
		break;
	}

	//�O���f�[�^���ǂݍ��߂Ȃ�������G���[���b�Z�[�W���o���B
	if (p == NULL)
	{
		MessageBox(0, L"�O���f�[�^���ǂݍ��߂܂���ł����B", NULL, MB_OK);
	}
	int count = 1;
	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			if (w > 9)//10�𒴂����ꍇ
				count += 3;//���炷���𑝂₷
			else
				count += 2;
		}
	}
}