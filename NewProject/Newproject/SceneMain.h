#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

#define MAP_X 200
#define MAP_Y 10

//�V�[���F���C��
class CSceneMain : public CScene
{
public:
	CSceneMain(int r);
	~CSceneMain();
	void InitScene();//���������\�b�h
	void Scene();	 //���s�����\�b�h
private:
	int remaining;//�c�@�Ǘ�
	void MapCreate(int map[][MAP_X]);	//�X�e�[�W�ԍ����ƂɃ}�b�v�쐬
};
