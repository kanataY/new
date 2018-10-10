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
#include "SceneGameClear.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneGameClear::CSceneGameClear()
{

}

//�f�X�g���N�^
CSceneGameClear::~CSceneGameClear()
{

}

//���������\�b�h
void CSceneGameClear::InitScene()
{
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Clear\\Fire.png", 0, TEX_SIZE_320);
	//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Clear\\clear1.png", 1, TEX_SIZE_800);
	//�O���O���t�B�b�N�t�@�C����ǂݍ���2�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Clear\\clear2.png", 2, TEX_SIZE_800);
	//�O���O���t�B�b�N�t�@�C����ǂݍ���3�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Clear\\clear3.png", 3, TEX_SIZE_800);
	//�O���O���t�B�b�N�t�@�C����ǂݍ���4�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Clear\\clear_mozi.png", 4, TEX_SIZE_512);
	//�O���O���t�B�b�N�t�@�C����ǂݍ���5�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Clear\\o.png", 5, TEX_SIZE_64);
	//�O���O���t�B�b�N�t�@�C����ǂݍ���5�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Clear\\clear.png", 6, TEX_SIZE_1024);
	
	Audio::LoadAudio(1, L"BGM&SE\\BGMClear_.wav", BACK_MUSIC);
	

	//�N���A�I�u�W�F�N�g�쐬
	CObjGameClear* obj = new CObjGameClear();		//�N���A�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_GAME_CLEAR, 10);	//�N���A�I�u�W�F�N�g�o�^
}

//���s�����\�b�h
void CSceneGameClear::Scene()
{


}