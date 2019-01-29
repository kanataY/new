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
#include "SceneRanking.h"
#include "GameHead.h"

//コンストラクタ
CSceneRanking::CSceneRanking()
{

}

//デストラクタ
CSceneRanking::~CSceneRanking()
{

}

//ランキング初期化メソッド
void CSceneRanking::InitScene()
{
	Draw::LoadImageW(L"Image\\ranking\\Numeric.png", 0, TEX_SIZE_256);//ランキングの数字画像															
	Draw::LoadImageW(L"Image\\ranking\\ranking_back.png", 1, TEX_SIZE_1024);//ランキングの背景																  
	Draw::LoadImageW(L"Image\\ranking\\Bit.png", 2, TEX_SIZE_64);//ランキングの位の文字
	Draw::LoadImageW(L"Image\\ranking\\ranking.png", 3, TEX_SIZE_256);//ランキングの位の文字
	CObjRanking* obj = new CObjRanking();		//ランキングオブジェクト作成
	Objs::InsertObj(obj, OBJ_RANKING, 10);		//ランキングオブジェクト登録

												//バックミュージックスタート
	Audio::LoadAudio(0, L"BGM&SE\\ranking.wav", BACK_MUSIC);

	//音楽スタート
	Audio::Start(0);
}

//ランキング実行中メソッド
void CSceneRanking::Scene()
{

}