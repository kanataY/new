//STG�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"
#include "GameL\UserData.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "SceneGameOver.h"
#include "GameHead.h"

//�R���X�g���N�^
CSceneGameOver::CSceneGameOver()
{

}

//�f�X�g���N�^
CSceneGameOver::~CSceneGameOver()
{

}

//���������\�b�h
void CSceneGameOver::InitScene()
{
	//���y�ǂݍ���
	/*Audio::LoadAudio(0, L"gameover.wav", BACK_MUSIC);

	//�{�����[����1.0f�ɖ߂�
	float v = Audio::VolumeMaster(0);
	v = Audio::VolumeMaster((1.0 - v));

	//���y�X�^�[�g
	Audio::Start(0);*/

	//�O���O���t�B�b�N�t�@�C����ǂݍ���0�Ԃɓo�^(1024�~1024�s�N�Z��)
	Draw::LoadImageW(L"Image\\back\\gameover\\GameOver.png", 0, TEX_SIZE_1024);

	//�Q�[���I�[�o�[�I�u�W�F�N�g�쐬
	CObjGameOver* obj = new CObjGameOver();
	Objs::InsertObj(obj, OBJ_GAME_OVER, 10);

	Audio::LoadAudio(0, L"BGM&SE\\BGMGameOver_.wav", BACK_MUSIC);
	//���y�X�^�[�g
	Audio::Start(0);
}

//���s�����\�b�h
void CSceneGameOver::Scene()
{

}