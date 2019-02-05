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
	//ステージ5だけブロックと背景変える
	if (((UserData*)Save::GetData())->m_stage_count == 5)
	{
		Draw::LoadImageW(L"Image\\back\\block3.png", 1, TEX_SIZE_64);
		Draw::LoadImageW(L"Image\\back\\back3.png", 14, TEX_SIZE_1024);
	}
	else
	{
		Draw::LoadImageW(L"Image\\back\\block.png", 1, TEX_SIZE_64);
		Draw::LoadImageW(L"Image\\back\\back2.png", 14, TEX_SIZE_1024);
	}
	Draw::LoadImageW(L"Image\\back\\block2.png", 2, TEX_SIZE_64);
	
	
	//主人公関連----------------------------------------------------------------------------------------------------
	Draw::LoadImageW(L"Image\\hero\\hero1.png", 3, TEX_SIZE_256);
	Draw::LoadImageW(L"Image\\item\\gold.png", 4, TEX_SIZE_64);
	Draw::LoadImageW(L"Image\\item\\100yen.png", 7, TEX_SIZE_32);
	Draw::LoadImageW(L"Image\\item\\goldbar.png", 13, TEX_SIZE_128);
	//敵関連----------------------------------------------------------------------------------------------------
	Draw::LoadImageW(L"Image\\enemy\\boo.png", 5, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\enemy\\jumpenemy.png", 6, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\enemy\\gold.png", 11, TEX_SIZE_512);
	Draw::LoadImageW(L"Image\\enemy\\goldel2.png", 12, TEX_SIZE_384);
	//ギミック----------------------------------------------------------------
	Draw::LoadImageW(L"Image\\gimmick\\Chest.png", 8, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\gimmick\\switch.png", 9, TEX_SIZE_128);
	Draw::LoadImageW(L"Image\\gimmick\\thorn2.png", 10, TEX_SIZE_16);
	//--------------------------------------------------------------------------------------
	//主人公オブジェクト作成
	CObjHero* he = new CObjHero();
	Objs::InsertObj(he, OBJ_HERO, 13);

	//背景（ブロック）オブジェクト作成
	CObjBlock* block = new CObjBlock(map);
	Objs::InsertObj(block, OBJ_BLOCK, 10);

	//主人公のヒットボックス二個目（必要）
	CObjhero_hitbox* hero_hit = new CObjhero_hitbox();
	Objs::InsertObj(hero_hit, HERO_HITBOX, 10);

	//音楽読み込み　BMG
	Audio::LoadAudio(0, L"BGM&SE\\main5.wav", BACK_MUSIC);
	Audio::LoadAudio(12, L"BGM&SE\\main3.wav", BACK_MUSIC);
	Audio::LoadAudio(13, L"BGM&SE\\main4.wav", BACK_MUSIC);

	//SE
	//主人公
	Audio::LoadAudio(1, L"BGM&SE\\gold.wav", EFFECT);		//ゴールド置いた音
	Audio::LoadAudio(2, L"BGM&SE\\gold_get.wav", EFFECT);	// ゴールドゲット
	Audio::LoadAudio(3, L"BGM&SE\\rakka2.wav", EFFECT);		// 落下音
	Audio::LoadAudio(10, L"BGM&SE\\nageru.wav", EFFECT);    // お金を投げる

	//ギミック
	Audio::LoadAudio(4, L"BGM&SE\\deru.wav", EFFECT);  // ブロックがでる
	Audio::LoadAudio(5, L"BGM&SE\\kieru.wav", EFFECT); // ブロックが消える
	Audio::LoadAudio(6, L"BGM&SE\\Goal.wav", EFFECT);  // ゴール
	Audio::LoadAudio(14, L"BGM&SE\\karas.wav", EFFECT);  // ゴール


	//敵
	Audio::LoadAudio(7, L"BGM&SE\\kuzureru.wav", EFFECT); // ゴーレムが崩れる
	Audio::LoadAudio(8, L"BGM&SE\\go-rem10.wav", EFFECT); // ゴーレムの足音
	Audio::LoadAudio(9, L"BGM&SE\\inosisi.wav", EFFECT);  // イノシシの足音
	Audio::LoadAudio(11, L"BGM&SE\\attack.wav", EFFECT);   // ジャンプが攻撃を受けた時

	////ボリュームを1.5増やす
	//float v = Audio::VolumeMaster(1.5);

	//音楽スタート     ステージ１と２と３でBGMを変える
	if (((UserData*)Save::GetData())->m_stage_count == 1 || ((UserData*)Save::GetData())->m_stage_count == 2)
	{
		Audio::Start(0);
	}
	else if (((UserData*)Save::GetData())->m_stage_count == 3 || ((UserData*)Save::GetData())->m_stage_count == 4)   //ステージ3と4はBGMを変える 
	{
		Audio::Start(12);
	}
	else //ステージ５はBGMを変える
	{
		Audio::Start(13);
	}
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
	switch (((UserData*)Save::GetData())->m_stage_count)
	{
	case 1:
		p = Save::ExternalDataOpen(L"Stage01.csv", &size);//外部データ読み込み
		break;
	case 2:
		p = Save::ExternalDataOpen(L"Stage02.csv", &size);//外部データ読み込み
		break;
	case 3:
		p = Save::ExternalDataOpen(L"Stage03.csv", &size);//外部データ読み込み
		break;
	case 4:
		p = Save::ExternalDataOpen(L"Stage04.csv", &size);//外部データ読み込み
		break;
	case 5:
		p = Save::ExternalDataOpen(L"Stage05.csv", &size);//外部データ読み込み
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