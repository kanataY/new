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
#include "SceneOperation.h"
#include "GameHead.h"

//コンストラクタ
CSceneOperation::CSceneOperation()
{

}

//デストラクタ
CSceneOperation::~CSceneOperation()
{

}

//ゲームメイン初期化メソッド
void CSceneOperation::InitScene()
{




	//説明オブジェクト作成
	CObjOperation* obj = new CObjOperation();
	Objs::InsertObj(obj, OBJ_OPERATION, 10);

	//バックミュージックスタート
	Audio::LoadAudio(0, L"BGM&SE\\syareotu.wav", BACK_MUSIC);

	//音楽スタート
	Audio::Start(0);
}

//ゲームメイン実行中メソッド
void CSceneOperation::Scene()
{

}