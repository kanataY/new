//STG�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneTitle.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneTitle::CSceneTitle()
{

}

//�f�X�g���N�^
CSceneTitle::~CSceneTitle()
{

}

//�Q�[�����C�����������\�b�h
void CSceneTitle::InitScene()
{
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\title\\title_back.png", 0, TEX_SIZE_1024);//�w�i

	//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\title\\title_title.png", 1, TEX_SIZE_512);//�^�C�g���̕���

	//�O���O���t�B�b�N�t�@�C����ǂݍ���2�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\title\\title_menu.png", 2, TEX_SIZE_512);//���j���[�̕���

	//�O���O���t�B�b�N�t�@�C����ǂݍ���3�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\title\\title_exit.png", 3, TEX_SIZE_512);//�I���̕���

	//�O���O���t�B�b�N�t�@�C����ǂݍ���2�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\title\\Frame.png", 4, TEX_SIZE_512);//�g

	//���y���̓ǂݍ���

	//�o�b�N�~���[�W�b�N�X�^�[�g
	Audio::LoadAudio(0, L"BGM&SE\\BGMTitle_.wav", BACK_MUSIC);

	//���y�X�^�[�g
	Audio::Start(0);

	//�^�C�g���I�u�W�F�N�g�쐬
	CObjTitle* obj = new CObjTitle();
	Objs::InsertObj(obj, OBJ_TITLE, 10);
}

//�Q�[�����C�����s�����\�b�h
void CSceneTitle::Scene()
{

}