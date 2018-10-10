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
#include "SceneOperation.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneOperation::CSceneOperation()
{

}

//�f�X�g���N�^
CSceneOperation::~CSceneOperation()
{

}

//�Q�[�����C�����������\�b�h
void CSceneOperation::InitScene()
{
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Operation\\Operation_key.png", 0, TEX_SIZE_1024);//�������
	//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Operation\\Operation_object.png", 1, TEX_SIZE_1024);//�ڂ��̐���
	//�O���O���t�B�b�N�t�@�C����ǂݍ���2�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Operation\\Operation_enemy.png", 2, TEX_SIZE_1024);//�G�̐���
	//�O���O���t�B�b�N�t�@�C����ǂݍ���6�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\Operation\\Operation_gimmick.png", 6, TEX_SIZE_1024);//�M�~�b�N�̐���

	//�O���O���t�B�b�N�t�@�C����ǂݍ���3�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Smartphone.png", 3, TEX_SIZE_256);    //�X�}�z���N
	//�O���O���t�B�b�N�t�@�C����ǂݍ���4�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\okama.png", 4, TEX_SIZE_512);    //�I�J�}
	//�O���O���t�B�b�N�t�@�C����ǂݍ���5�Ԃɓo�^(512�s�N�Z��)
	Draw::LoadImageW(L"Image\\object\\Track.png", 5, TEX_SIZE_512);    //�g���b�N



	//�����I�u�W�F�N�g�쐬
	CObjOperation* obj = new CObjOperation();
	Objs::InsertObj(obj, OBJ_OPERATION, 10);

	//�o�b�N�~���[�W�b�N�X�^�[�g
	Audio::LoadAudio(0, L"BGM&SE\\syareotu.wav", BACK_MUSIC);

	//���y�X�^�[�g
	Audio::Start(0);
}

//�Q�[�����C�����s�����\�b�h
void CSceneOperation::Scene()
{

}