//STLデバック機能をOFFにする
#define _SECURE_SCL (0)
#define _HAS_ITERATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\DrawFont.h"
#include "GameL\UserData.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "SceneMain.h"
#include "GameHead.h"


CSceneMain::CSceneMain()
{
	
}


//デストラクタ
CSceneMain::~CSceneMain()
{

}

//初期化メソッド
void CSceneMain::InitScene()
{
	//マップ作製
	int map[MAP_Y][MAP_X];
	MapCreate(map);
	//背景.ブロック----------------------------------------------------------------------------------------------------
	Draw::LoadImageW(L"Image\\back\\back.png", 0, TEX_SIZE_1024);    
	Draw::LoadImageW(L"Image\\back\\block.png", 1, TEX_SIZE_64);
	Draw::LoadImageW(L"Image\\back\\block2.png", 2, TEX_SIZE_64);
	//主人公関連----------------------------------------------------------------------------------------------------
	Draw::LoadImageW(L"Image\\hero\\hero1.png", 3, TEX_SIZE_256);
	Draw::LoadImageW(L"Image\\item\\gold.png", 4, TEX_SIZE_64);
	Draw::LoadImageW(L"Image\\item\\100yen.png", 7, TEX_SIZE_32);
	//敵関連----------------------------------------------------------------------------------------------------
	Draw::LoadImageW(L"Image\\enemy\\boo.png", 5, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\enemy\\jumpenemy.png", 6, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\enemy\\Golem.png", 11, TEX_SIZE_384);
	//ギミック----------------------------------------------------------------
	Draw::LoadImageW(L"Image\\gimmick\\Chest.png", 8, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\gimmick\\switch.png", 9, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\gimmick\\thorn.png", 10, TEX_SIZE_16);
	//--------------------------------------------------------------------------------------
	//主人公オブジェクト作成
	CObjHero* he = new CObjHero();
	Objs::InsertObj(he, OBJ_HERO, 13);

	////突進敵オブジェクト作成
	//CObjRushEnemy* boo = new CObjRushEnemy(450,100);
	//Objs::InsertObj(boo, OBJ_RUSH_ENEMY, 13);

	////ジャンプ敵オブジェクト作成
	//CObjJumpEnemy* jump = new CObjJumpEnemy(400, 500);z
	//Objs::InsertObj(jump, OBJ_JUMP_ENEMY, 13);

	//ゴーレムオブジェクト作成
	CObjGolem* golem = new CObjGolem(450,100);
	Objs::InsertObj(golem, OBJ_GOLEM, 13);

	//スイッチオブジェクト作成
	CObjswitch* swi = new CObjswitch(300, 480);
	Objs::InsertObj(swi, OBJ_SWITCH, 13);

	//背景（ブロック）オブジェクト作成
	CObjBlock* block = new CObjBlock(map);
	Objs::InsertObj(block, OBJ_BLOCK, 10);

	//補正オブジェクト作成
	//CObjCorrection* cor = new CObjCorrection();
	//Objs::InsertObj(cor, CORRECTION, 13);


	//音楽読み込み
	//Audio::LoadAudio(0, L"BGM&SE\\BGMGameMain_.wav", BACK_MUSIC);

	//Audio::LoadAudio(1, L"BGM&SE\\dashu_.wav", EFFECT); // 走る音
	//Audio::LoadAudio(2, L"BGM&SE\\Fier2__.wav", EFFECT); // 燃える音
	//Audio::LoadAudio(3, L"BGM&SE\\jump_.wav", EFFECT);  // ジャンプ
	//Audio::LoadAudio(4, L"BGM&SE\\rakka_.wav", EFFECT); // 落ちる音
	//Audio::LoadAudio(5, L"BGM&SE\\water_.wav", EFFECT); // 水に落ちた音
	//Audio::LoadAudio(6, L"BGM&SE\\track_.wav", EFFECT); // トラック
	//Audio::LoadAudio(7, L"BGM&SE\\gool.wav", EFFECT); // チェックポイントの歓声
	//Audio::LoadAudio(8, L"BGM&SE\\gool2.wav", EFFECT); // チェックポイントの歓声2
	//Audio::LoadAudio(9, L"BGM&SE\\himei.wav", EFFECT); // オカマの悲鳴
	//Audio::LoadAudio(10, L"BGM&SE\\kiss.wav", EFFECT); // オカマのキス


	////ボリュームを1.5増やす
	//float v = Audio::VolumeMaster(1.5);

	//音楽スタート
	//Audio::Start(0);
}

//実行中メソッド
void CSceneMain::Scene()
{

}

//ステージごとのマップ作成
void CSceneMain::MapCreate(int map[][MAP_X])
{
	//外部データの読み込み（ステージ情報）
	unique_ptr<wchar_t> p; //ステージ情報ポインター
	int size;			   //ステージ情報の大きさ

	//ステージごとにステージの名前を格納
	switch (((UserData*)Save::GetData())->m_stage_count = 1)
	{
	case 1:
		p = Save::ExternalDataOpen(L"Stage01.csv", &size);//外部データ読み込み
		break;
	default:
		MessageBox(0, L"ステージ番号が正しくありません。", NULL, MB_OK);
		break;
	}

	//外部データが読み込めなかったらエラーメッセージを出す。
	if (p == NULL)
	{
		MessageBox(0, L"外部データが読み込めませんでした。", NULL, MB_OK);
	}
	int count = 1;
	for (int i = 0; i < MAP_Y; i++)
	{
		for (int j = 0; j < MAP_X; j++)
		{
			int w = 0;
			swscanf_s(&p.get()[count], L"%d", &w);

			map[i][j] = w;
			if (w > 9)//10を超えた場合
				count += 3;//ずらす数を増やす
			else
				count += 2;
		}
	}
}