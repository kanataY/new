//STGデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneTitle.h"
#include "GameHead.h"

//コンストラクタ
CSceneTitle::CSceneTitle()
{

}

//デストラクタ
CSceneTitle::~CSceneTitle()
{

}

//ゲームメイン初期化メソッド
void CSceneTitle::InitScene()
{
	Draw::LoadImageW(L"Image\\Title\\title1.png", 0, TEX_SIZE_1024);
	Draw::LoadImageW(L"Image\\Title\\title2.png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"Image\\Title\\title3.png", 2, TEX_SIZE_1024);
	Draw::LoadImageW(L"Image\\Title\\title4.png", 3, TEX_SIZE_1024);
	Draw::LoadImageW(L"Image\\Title\\title5.png", 4, TEX_SIZE_1024);
	Draw::LoadImageW(L"Image\\Title\\title6.png", 5, TEX_SIZE_1024);
	Draw::LoadImageW(L"Image\\Title\\title7.png", 6, TEX_SIZE_1024);
	Draw::LoadImageW(L"Image\\Title\\title8.png", 7, TEX_SIZE_1024);
	Draw::LoadImageW(L"Image\\Title\\title9.png", 8, TEX_SIZE_1024);
	Draw::LoadImageW(L"Image\\Title\\title10.png", 9, TEX_SIZE_1024);

	//音楽情報の読み込み

	////バックミュージックスタート
	//Audio::LoadAudio(0, L"BGM&SE\\BGMTitle_.wav", BACK_MUSIC);

	//音楽スタート
	//Audio::Start(0);

	//タイトルオブジェクト作成
	CObjTitle* obj = new CObjTitle();
	Objs::InsertObj(obj, OBJ_TITLE, 10);
}

//ゲームメイン実行中メソッド
void CSceneTitle::Scene()
{

}