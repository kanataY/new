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
#include "SceneRanking.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneRanking::CSceneRanking()
{

}

//�f�X�g���N�^
CSceneRanking::~CSceneRanking()
{

}

//�����L���O���������\�b�h
void CSceneRanking::InitScene()
{
	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(256�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\ranking\\Numeric.png", 0, TEX_SIZE_256);//�����L���O�̐����摜
	//�O���O���t�B�b�N�t�@�C����ǂݍ���1�Ԃɓo�^(1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\ranking\\ranking_back.png", 1, TEX_SIZE_1024);//�����L���O�̔w�i
	//�O���O���t�B�b�N�t�@�C����ǂݍ���2�Ԃɓo�^(64�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\ranking\\Bit.png", 2, TEX_SIZE_64);//�����L���O�̈ʂ̕���
	//�����L���O�I�u�W�F�N�g�쐬
	CObjRanking* obj = new CObjRanking();		//�����L���O�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_RANKING, 10);		//�����L���O�I�u�W�F�N�g�o�^

												//�o�b�N�~���[�W�b�N�X�^�[�g
	Audio::LoadAudio(0, L"BGM&SE\\ranking.wav", BACK_MUSIC);

	//���y�X�^�[�g
	Audio::Start(0);
}

//�����L���O���s�����\�b�h
void CSceneRanking::Scene()
{

}