#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

#define MAP_X 100
#define MAP_Y 10

//シーン：メイン
class CSceneMain : public CScene
{
public:
	CSceneMain();
	~CSceneMain();
	void InitScene();//初期化メソッド
	void Scene();	 //実行中メソッド
private:
	void MapCreate(int map[][MAP_X]);	//ステージ番号ごとにマップ作成
};
