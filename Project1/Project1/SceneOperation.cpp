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