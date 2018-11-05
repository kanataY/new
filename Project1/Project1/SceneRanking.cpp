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