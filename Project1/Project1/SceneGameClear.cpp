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
	
	Audio::LoadAudio(1, L"BGM&SE\\BGMClear_.wav", BACK_MUSIC);
	

	//�N���A�I�u�W�F�N�g�쐬
	CObjGameClear* obj = new CObjGameClear();		//�N���A�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_GAME_CLEAR, 10);	//�N���A�I�u�W�F�N�g�o�^
}

//���s�����\�b�h
void CSceneGameClear::Scene()
{


}