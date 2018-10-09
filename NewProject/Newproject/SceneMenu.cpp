//STG�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneMenu.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneMenu::CSceneMenu()
{

}

//�f�X�g���N�^
CSceneMenu::~CSceneMenu()
{

}

//�Q�[�����C�����������\�b�h
void CSceneMenu::InitScene()
{
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu.png", 0, TEX_SIZE_1024);

	//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_start.png", 1, TEX_SIZE_512);//�X�e�[�W�Z���N�g���S

    //�O���O���t�B�b�N�t�@�C����ǂݍ���2�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_ranking.png", 2, TEX_SIZE_512);//ranking���S

	//�O���O���t�B�b�N�t�@�C����ǂݍ���3�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_title.png", 3, TEX_SIZE_512);//title�ɖ߂郍�S

	//�O���O���t�B�b�N�t�@�C����ǂݍ���4�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_operation.png", 4, TEX_SIZE_512);//����������S

	//�O���O���t�B�b�N�t�@�C����ǂݍ���5�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_start_red.png", 5, TEX_SIZE_512);//�X�e�[�W�Z���N�g���S(��)

	//�O���O���t�B�b�N�t�@�C����ǂݍ���6�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_ranking_red.png", 6, TEX_SIZE_512);//ranking���S(��)

    //�O���O���t�B�b�N�t�@�C����ǂݍ���7�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_title_red.png", 7, TEX_SIZE_512);//title�ɖ߂郍�S(��)

	//�O���O���t�B�b�N�t�@�C����ǂݍ���8�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Menu\\Menu_operation_red.png", 8, TEX_SIZE_512);//����������S(��)
	
	//�o�b�N�~���[�W�b�N�X�^�[�g
	//float Volume = Audio::VolumeMaster(0.0f);
	Audio::LoadAudio(0, L"BGM&SE\\Menu.wav", BACK_MUSIC);
	//���y�X�^�[�g
	Audio::Start(0);

	//���j���[�I�u�W�F�N�g�쐬
	CObjMenu* obj = new CObjMenu();		//���j���[�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_MENU, 10);  //��l���I�u�W�F�N�g�o�^
}

//�Q�[�����C�����s�����\�b�h
void CSceneMenu::Scene()
{

}