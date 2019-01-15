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


CSceneMain::CSceneMain()
{
	
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
	//�w�i.�u���b�N----------------------------------------------------------------------------------------------------
	Draw::LoadImageW(L"Image\\back\\back.png", 0, TEX_SIZE_1024);    
	Draw::LoadImageW(L"Image\\back\\block.png", 1, TEX_SIZE_64);
	Draw::LoadImageW(L"Image\\back\\block2.png", 2, TEX_SIZE_64);
	//��l���֘A----------------------------------------------------------------------------------------------------
	Draw::LoadImageW(L"Image\\hero\\hero1.png", 3, TEX_SIZE_256);
	Draw::LoadImageW(L"Image\\item\\gold.png", 4, TEX_SIZE_64);
	Draw::LoadImageW(L"Image\\item\\100yen.png", 7, TEX_SIZE_32);
	//�G�֘A----------------------------------------------------------------------------------------------------
	Draw::LoadImageW(L"Image\\enemy\\boo.png", 5, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\enemy\\jumpenemy.png", 6, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\enemy\\Golem.png", 11, TEX_SIZE_384);
	//�M�~�b�N----------------------------------------------------------------
	Draw::LoadImageW(L"Image\\gimmick\\Chest.png", 8, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\gimmick\\switch.png", 9, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\gimmick\\thorn.png", 10, TEX_SIZE_16);
	//--------------------------------------------------------------------------------------
	//��l���I�u�W�F�N�g�쐬
	CObjHero* he = new CObjHero();
	Objs::InsertObj(he, OBJ_HERO, 13);

	////�ːi�G�I�u�W�F�N�g�쐬
	//CObjRushEnemy* boo = new CObjRushEnemy(450,100);
	//Objs::InsertObj(boo, OBJ_RUSH_ENEMY, 13);

	////�W�����v�G�I�u�W�F�N�g�쐬
	//CObjJumpEnemy* jump = new CObjJumpEnemy(400, 500);z
	//Objs::InsertObj(jump, OBJ_JUMP_ENEMY, 13);

	//�S�[�����I�u�W�F�N�g�쐬
	CObjGolem* golem = new CObjGolem(450,100);
	Objs::InsertObj(golem, OBJ_GOLEM, 13);

	//�X�C�b�`�I�u�W�F�N�g�쐬
	CObjswitch* swi = new CObjswitch(300, 480);
	Objs::InsertObj(swi, OBJ_SWITCH, 13);

	//�w�i�i�u���b�N�j�I�u�W�F�N�g�쐬
	CObjBlock* block = new CObjBlock(map);
	Objs::InsertObj(block, OBJ_BLOCK, 10);

	//�␳�I�u�W�F�N�g�쐬
	//CObjCorrection* cor = new CObjCorrection();
	//Objs::InsertObj(cor, CORRECTION, 13);


	//���y�ǂݍ���
	//Audio::LoadAudio(0, L"BGM&SE\\BGMGameMain_.wav", BACK_MUSIC);

	//Audio::LoadAudio(1, L"BGM&SE\\dashu_.wav", EFFECT); // ���鉹
	//Audio::LoadAudio(2, L"BGM&SE\\Fier2__.wav", EFFECT); // �R���鉹
	//Audio::LoadAudio(3, L"BGM&SE\\jump_.wav", EFFECT);  // �W�����v
	//Audio::LoadAudio(4, L"BGM&SE\\rakka_.wav", EFFECT); // �����鉹
	//Audio::LoadAudio(5, L"BGM&SE\\water_.wav", EFFECT); // ���ɗ�������
	//Audio::LoadAudio(6, L"BGM&SE\\track_.wav", EFFECT); // �g���b�N
	//Audio::LoadAudio(7, L"BGM&SE\\gool.wav", EFFECT); // �`�F�b�N�|�C���g�̊���
	//Audio::LoadAudio(8, L"BGM&SE\\gool2.wav", EFFECT); // �`�F�b�N�|�C���g�̊���2
	//Audio::LoadAudio(9, L"BGM&SE\\himei.wav", EFFECT); // �I�J�}�̔ߖ�
	//Audio::LoadAudio(10, L"BGM&SE\\kiss.wav", EFFECT); // �I�J�}�̃L�X


	////�{�����[����1.5���₷
	//float v = Audio::VolumeMaster(1.5);

	//���y�X�^�[�g
	//Audio::Start(0);
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
	switch (((UserData*)Save::GetData())->m_stage_count = 1)
	{
	case 1:
		p = Save::ExternalDataOpen(L"Stage01.csv", &size);//�O���f�[�^�ǂݍ���
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