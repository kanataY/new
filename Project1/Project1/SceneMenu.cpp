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
	
	
	//�o�b�N�~���[�W�b�N�X�^�[�g
	//float Volume = Audio::VolumeMaster(0.0f);
	Audio::LoadAudio(0, L"BGM&SE\\Menu.wav", BACK_MUSIC);
	//���y�X�^�[�g
	//Audio::Start(0);

	//���j���[�I�u�W�F�N�g�쐬
	CObjMenu* obj = new CObjMenu();		//���j���[�I�u�W�F�N�g�쐬
	Objs::InsertObj(obj, OBJ_MENU, 10);  //��l���I�u�W�F�N�g�o�^
}

//�Q�[�����C�����s�����\�b�h
void CSceneMenu::Scene()
{

}