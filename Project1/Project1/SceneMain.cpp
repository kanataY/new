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


CSceneMain::CSceneMain(int r)
{
	remaining = r;	//残機
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
	//ステージごとに主人公と背景を格納
	//switch (((UserData*)Save::GetData())->m_stage_count)
	//{
	//case 1://ステージが1の時
	//	//背景の画像登録-------------------------------------------------------------------
	//	//外部グラフィックファイルを読み込み0番に登録(1024ピクセル)
	//	Draw::LoadImageW(L"Image\\back\\back\\back1-1.png", 0, TEX_SIZE_1024); //背景1
	//	//外部グラフィックファイルを読み込み1番に登録(1024ピクセル)
	//	Draw::LoadImageW(L"Image\\back\\back\\back2-1.png", 1, TEX_SIZE_1024); //背景2  
	//	//外部グラフィックファイルを読み込み29番に登録(1024ピクセル)
	//	Draw::LoadImageW(L"Image\\back\\back\\back_final.png", 26, TEX_SIZE_1024); //背景最後
	//	//----------------------------------------------------------------------------------
	//	break;

	//case 2://ステージが2の時
	//	//背景の画像登録-------------------------------------------------------------------
	//	//外部グラフィックファイルを読み込み0番に登録(1024ピクセル)
	//	Draw::LoadImageW(L"Image\\back\\back\\back1-2.png", 0, TEX_SIZE_1024); //背景1
	//	//外部グラフィックファイルを読み込み1番に登録(1024ピクセル)
	//	Draw::LoadImageW(L"Image\\back\\back\\back2-2.png", 1, TEX_SIZE_1024); //背景2
	//	//外部グラフィックファイルを読み込み26番に登録(1024ピクセル)
	//	Draw::LoadImageW(L"Image\\back\\back\\back_final2.png", 26, TEX_SIZE_1024); //背景最後
	//	//---------------------------------------------------------------------------------------------

	//	break;
	//case 3://ステージが3の時
	//	//背景の画像登録-------------------------------------------------------------------
	//	//外部グラフィックファイルを読み込み0番に登録(1024ピクセル)
	//	Draw::LoadImageW(L"Image\\back\\back\\back1.png", 0, TEX_SIZE_1024); //背景1
	//	//外部グラフィックファイルを読み込み1番に登録(1024ピクセル)
	//	Draw::LoadImageW(L"Image\\back\\back\\back2.png", 1, TEX_SIZE_1024); //背景2
	//	//外部グラフィックファイルを読み込み26番に登録(1024ピクセル)
	//	Draw::LoadImageW(L"Image\\back\\back\\back_final3.png", 26, TEX_SIZE_1024); //背景最後
	//	//---------------------------------------------------------------------------------------------
	//	break;
	//}
	
	
	

	//主人公オブジェクト作成
	

	//背景（ブロック）オブジェクト作成
	CObjBlock* block = new CObjBlock(map);
	Objs::InsertObj(block, OBJ_BLOCK, 10);

	//ゲージオブジェクト作成
	

	//補正オブジェクト作成
	CObjCorrection* cor = new CObjCorrection();
	Objs::InsertObj(cor, CORRECTION, 13);


	//音楽読み込み
	


	////ボリュームを1.5増やす
	//float v = Audio::VolumeMaster(1.5);

	//音楽スタート
	//Audio::Start(0);
}

//実行中メソッド
void CSceneMain::Scene()
{

}

////ステージごとのマップ作成
//void CSceneMain::MapCreate(int map[][MAP_X])
//{
//	//外部データの読み込み（ステージ情報）
//	unique_ptr<wchar_t> p; //ステージ情報ポインター
//	int size;			   //ステージ情報の大きさ
//
//	//ステージごとにステージの名前を格納
//	switch (((UserData*)Save::GetData())->m_stage_count)
//	{
//	case 1:
//		p = Save::ExternalDataOpen(L"Stage01.csv", &size);//外部データ読み込み
//		break;
//	case 2:
//		p = Save::ExternalDataOpen(L"Stage02.csv", &size);//外部データ読み込み
//		break;
//	case 3:
//		p = Save::ExternalDataOpen(L"Stage03.csv", &size);//外部データ読み込み
//		break;
//	default:
//		MessageBox(0, L"ステージ番号が正しくありません。", NULL, MB_OK);
//		break;
//	}
//
//	//外部データが読み込めなかったらエラーメッセージを出す。
//	if (p == NULL)
//	{
//		MessageBox(0, L"外部データが読み込めませんでした。", NULL, MB_OK);
//	}
//	int count = 1;
//	for (int i = 0; i < MAP_Y; i++)
//	{
//		for (int j = 0; j < MAP_X; j++)
//		{
//			int w = 0;
//			swscanf_s(&p.get()[count], L"%d", &w);
//
//			map[i][j] = w;
//			if (w > 9)//10を超えた場合
//				count += 3;//ずらす数を増やす
//			else
//				count += 2;
//		}
//	}
//}