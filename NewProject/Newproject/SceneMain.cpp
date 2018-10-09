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

		//�����܌n--------------------------------------------------------------------------------------------
		//�O���O���t�B�b�N�t�@�C����ǂݍ���14�Ԃɓo�^(512�s�N�Z��)
		Draw::LoadImageW(L"Image\\object\\okama.png", 14, TEX_SIZE_512);    //�I�J�}
		//�O���O���t�B�b�N�t�@�C����ǂݍ���15�Ԃɓo�^(512�s�N�Z��)
		Draw::LoadImageW(L"Image\\object\\okama2.png", 15, TEX_SIZE_512);    //�I�J�}(�ڂ��n�[�g)
		//�O���O���t�B�b�N�t�@�C����ǂݍ���16�Ԃɓo�^(512�s�N�Z��)
		Draw::LoadImageW(L"Image\\object\\okama_hug.png", 16, TEX_SIZE_512);    //�I�J�}�n�O
		//-----------------------------------------------------------------------------------�|�|�|�|�|�|�|�|�|�|�|-------

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

		//�����܌n--------------------------------------------------------------------------------------------
		//�O���O���t�B�b�N�t�@�C����ǂݍ���14�Ԃɓo�^(512�s�N�Z��)
		Draw::LoadImageW(L"Image\\object\\fan.png", 14, TEX_SIZE_512);    //�t�@��
		//�O���O���t�B�b�N�t�@�C����ǂݍ���15�Ԃɓo�^(512�s�N�Z��)
		Draw::LoadImageW(L"Image\\object\\fan2.png", 15, TEX_SIZE_512);    //�t�@���ڂ��n�[�g
		//�O���O���t�B�b�N�t�@�C����ǂݍ���16�Ԃɓo�^(512�s�N�Z��)
		Draw::LoadImageW(L"Image\\object\\fan_hug.png", 16, TEX_SIZE_512);    //�t�@���n�O
	
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

		//�����܌n--------------------------------------------------------------------------------------------
		//�O���O���t�B�b�N�t�@�C����ǂݍ���14�Ԃɓo�^(512�s�N�Z��)
		Draw::LoadImageW(L"Image\\object\\grandmother.png", 14, TEX_SIZE_512);    //�΂�����
		//�O���O���t�B�b�N�t�@�C����ǂݍ���15�Ԃɓo�^(512�s�N�Z��)
		Draw::LoadImageW(L"Image\\object\\grandmother2.png", 15, TEX_SIZE_512);    //�΂�����(�ڂ��n�[�g)
		//�O���O���t�B�b�N�t�@�C����ǂݍ���16�Ԃɓo�^(512�s�N�Z��)
		Draw::LoadImageW(L"Image\\object\\grandmother_hug.png", 16, TEX_SIZE_512);    //�΂�����n�O
		//---------------------------------------------------------------------------------------------

		break;
	}
	
	
	//�O���O���t�B�b�N�t�@�C����ǂݍ���6�Ԃɓo�^(192�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Fire Gauge.png", 6, TEX_SIZE_192);    //�Q�[�W
	//�O���O���t�B�b�N�t�@�C����ǂݍ���7�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Cratesx64.png", 7, TEX_SIZE_64);    //�ؔ�
    //�O���O���t�B�b�N�t�@�C����ǂݍ���8�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Smartphone.png", 8, TEX_SIZE_256);    //�X�}�z���N
	//�O���O���t�B�b�N�t�@�C����ǂݍ���9�Ԃɓo�^(320�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Fire.png", 9, TEX_SIZE_320);    //��
	//�O���O���t�B�b�N�t�@�C����ǂݍ���10�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Puddle.png", 10, TEX_SIZE_64);    //�����܂�
	//�O���O���t�B�b�N�t�@�C����ǂݍ���11�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\torch.png", 11, TEX_SIZE_64);    //���΂̎��Ƃ�
	//�O���O���t�B�b�N�t�@�C����ǂݍ���12�Ԃɓo�^(800�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Rain\\rain1.png", 12, TEX_SIZE_800);    //�J�P
	//�O���O���t�B�b�N�t�@�C����ǂݍ���13�Ԃɓo�^(800�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Rain\\a3.png", 13, TEX_SIZE_800);    //�J�Q
	//�O���O���t�B�b�N�t�@�C����ǂݍ���17�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\hole.png", 17, TEX_SIZE_64);    //��
	//�O���O���t�B�b�N�t�@�C����ǂݍ���18�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\characterkey.png", 18, TEX_SIZE_256);    //�����L�[
	//�O���O���t�B�b�N�t�@�C����ǂݍ���19�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\battered.png", 19, TEX_SIZE_256);    //�����I�I�I�̕���
	//�O���O���t�B�b�N�t�@�C����ǂݍ���20�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\checkpoint.png", 20, TEX_SIZE_256);    //�`�F�b�N�|�C���g
    //�O���O���t�B�b�N�t�@�C����ǂݍ���21�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Track.png", 21, TEX_SIZE_512);    //�g���b�N
	//�O���O���t�B�b�N�t�@�C����ǂݍ���22�Ԃɓo�^(128�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\warning.png", 22, TEX_SIZE_128);    //�x��
	//�O���O���t�B�b�N�t�@�C����ǂݍ���23�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Track2.png", 23, TEX_SIZE_512);    //�g���b�N2
	//�O���O���t�B�b�N�t�@�C����ǂݍ���24�Ԃɓo�^(128�s�N�Z��)
	Draw::LoadImageW(L"Image\\hero\\remaining.png", 24, TEX_SIZE_192);    //�c�@
	//�O���O���t�B�b�N�t�@�C����ǂݍ���28�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\hero\\Shadow.png", 25, TEX_SIZE_64);    //�e

	//��l���I�u�W�F�N�g�쐬
	CObjRunner* obj = new CObjRunner(remaining);
	Objs::InsertObj(obj, OBJ_RUNNER, 13);

	//�w�i�i�u���b�N�j�I�u�W�F�N�g�쐬
	CObjBlock* block = new CObjBlock(map);
	Objs::InsertObj(block, OBJ_BLOCK, 10);

	//�Q�[�W�I�u�W�F�N�g�쐬
	CObjGauge* gauge = new CObjGauge();
	Objs::InsertObj(gauge, OBJ_GAUGE, 13);

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