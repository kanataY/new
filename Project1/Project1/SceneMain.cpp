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
	//�X�e�[�W5�����u���b�N�Ɣw�i�ς���
	if (((UserData*)Save::GetData())->m_stage_count == 5)
	{
		Draw::LoadImageW(L"Image\\back\\block3.png", 1, TEX_SIZE_64);
		Draw::LoadImageW(L"Image\\back\\back3.png", 14, TEX_SIZE_1024);
	}
	else
	{
		Draw::LoadImageW(L"Image\\back\\block.png", 1, TEX_SIZE_64);
		Draw::LoadImageW(L"Image\\back\\back2.png", 14, TEX_SIZE_1024);
	}
	Draw::LoadImageW(L"Image\\back\\block2.png", 2, TEX_SIZE_64);
	
	
	//��l���֘A----------------------------------------------------------------------------------------------------
	Draw::LoadImageW(L"Image\\hero\\hero1.png", 3, TEX_SIZE_256);
	Draw::LoadImageW(L"Image\\item\\gold.png", 4, TEX_SIZE_64);
	Draw::LoadImageW(L"Image\\item\\100yen.png", 7, TEX_SIZE_32);
	Draw::LoadImageW(L"Image\\item\\goldbar.png", 13, TEX_SIZE_128);
	//�G�֘A----------------------------------------------------------------------------------------------------
	Draw::LoadImageW(L"Image\\enemy\\boo.png", 5, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\enemy\\jumpenemy.png", 6, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\enemy\\gold.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"Image\\enemy\\goldel2.png", 12, TEX_SIZE_384);
	//�M�~�b�N----------------------------------------------------------------
	Draw::LoadImageW(L"Image\\gimmick\\Chest.png", 8, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\gimmick\\switch.png", 9, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\gimmick\\thorn2.png", 10, TEX_SIZE_16);
	//--------------------------------------------------------------------------------------
	//��l���I�u�W�F�N�g�쐬
	CObjHero* he = new CObjHero();
	Objs::InsertObj(he, OBJ_HERO, 13);

	//�w�i�i�u���b�N�j�I�u�W�F�N�g�쐬
	CObjBlock* block = new CObjBlock(map);
	Objs::InsertObj(block, OBJ_BLOCK, 10);

	//��l���̃q�b�g�{�b�N�X��ځi�K�v�j
	CObjhero_hitbox* hero_hit = new CObjhero_hitbox();
	Objs::InsertObj(hero_hit, HERO_HITBOX, 10);

	//���y�ǂݍ��݁@BMG
	Audio::LoadAudio(0, L"BGM&SE\\main5.wav", BACK_MUSIC);
	Audio::LoadAudio(12, L"BGM&SE\\main3.wav", BACK_MUSIC);
	Audio::LoadAudio(13, L"BGM&SE\\main4.wav", BACK_MUSIC);

	//SE
	//��l��
	Audio::LoadAudio(1, L"BGM&SE\\gold.wav", EFFECT);		//�S�[���h�u������
	Audio::LoadAudio(2, L"BGM&SE\\gold_get.wav", EFFECT);	// �S�[���h�Q�b�g
	Audio::LoadAudio(3, L"BGM&SE\\rakka2.wav", EFFECT);		// ������
	Audio::LoadAudio(10, L"BGM&SE\\nageru.wav", EFFECT);    // �����𓊂���

	//�M�~�b�N
	Audio::LoadAudio(4, L"BGM&SE\\deru.wav", EFFECT);  // �u���b�N���ł�
	Audio::LoadAudio(5, L"BGM&SE\\kieru.wav", EFFECT); // �u���b�N��������
	Audio::LoadAudio(6, L"BGM&SE\\Goal.wav", EFFECT);  // �S�[��
	Audio::LoadAudio(14, L"BGM&SE\\karas.wav", EFFECT);  // �S�[��


	//�G
	Audio::LoadAudio(7, L"BGM&SE\\kuzureru.wav", EFFECT); // �S�[�����������
	Audio::LoadAudio(8, L"BGM&SE\\go-rem10.wav", EFFECT); // �S�[�����̑���
	Audio::LoadAudio(9, L"BGM&SE\\inosisi.wav", EFFECT);  // �C�m�V�V�̑���
	Audio::LoadAudio(11, L"BGM&SE\\attack.wav", EFFECT);   // �W�����v���U�����󂯂���

	////�{�����[����1.5���₷
	//float v = Audio::VolumeMaster(1.5);

	//���y�X�^�[�g     �X�e�[�W�P�ƂQ�ƂR��BGM��ς���
	if (((UserData*)Save::GetData())->m_stage_count == 1 || ((UserData*)Save::GetData())->m_stage_count == 2)
	{
		Audio::Start(0);
	}
	else if (((UserData*)Save::GetData())->m_stage_count == 3 || ((UserData*)Save::GetData())->m_stage_count == 4)   //�X�e�[�W3��4��BGM��ς��� 
	{
		Audio::Start(12);
	}
	else //�X�e�[�W�T��BGM��ς���
	{
		Audio::Start(13);
	}
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
	case 4:
		p = Save::ExternalDataOpen(L"Stage04.csv", &size);//�O���f�[�^�ǂݍ���
		break;
	case 5:
		p = Save::ExternalDataOpen(L"Stage05.csv", &size);//�O���f�[�^�ǂݍ���
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