//STGデバッグ機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawFont.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneGameClear.h"
#include "GameHead.h"

//コンストラクタ
CSceneGameClear::CSceneGameClear()
{

}

//デストラクタ
CSceneGameClear::~CSceneGameClear()
{

}

//初期化メソッド
void CSceneGameClear::InitScene()
{
	
	/*Audio::LoadAudio(1, L"BGM&SE\\BGMClear_.wav", BACK_MUSIC);*/
	
	Draw::LoadImageW(L"image\\clear\\clear.png", 0, TEX_SIZE_1024);
	Draw::LoadImageW(L"image\\clear\\clear1.png", 1, TEX_SIZE_1024);
	Draw::LoadImageW(L"image\\clear\\clear2.png", 2, TEX_SIZE_1024);
	Draw::LoadImageW(L"image\\clear\\clear3.png", 3, TEX_SIZE_1024);

	Draw::LoadImageW(L"image\\clear\\congratulation.png", 5, TEX_SIZE_512);
	//クリアオブジェクト作成
	CObjGameClear* obj = new CObjGameClear();		//クリアオブジェクト作成
	Objs::InsertObj(obj, OBJ_GAME_CLEAR, 10);	//クリアオブジェクト登録
}

//実行中メソッド
void CSceneGameClear::Scene()
{


}