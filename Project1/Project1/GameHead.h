#pragma once

//オブジェクトネーム------------------------------
enum OBJ_NAME
{
	OBJ_NO_NAME,	//オブジェクト名無し(禁止)
	//ゲームで使うオブジェクトの名前
	//OBJ_○○と表記
	OBJ_HERO,				//ランナー
	OBJ_BLOCK,				//ブロック
	OBJ_GOLD,				//金塊
	OBJ_COIN,				//コイン

	//敵
	OBJ_RUSH_ENEMY,			//突進する敵
	OBJ_JUMP_ENEMY,			//ジャンプする敵
	OBJ_GOLEM,				//ゴーレム
	GOLEM_JUDGMENT,			//ゴーレムの判定

	//ギミック
	OBJ_THORN,				//針
	OBJ_SWITCH,				//スイッチ
	OBJ_GOAL,				//ゴール
	OBJ_VANISHBLOCK,		//消えるブロック

	//補正
	CORRECTION,				//補正
	HERO_HITBOX,			//主人公のヒットボックス二個目

	//アイテム
	OBJ_DROP_GOLD,			//落ちる金塊

	//シーン
	OBJ_TITLE,				//タイトル
	OBJ_GAME_OVER,			//ゲームオーバー
	OBJ_GAME_CLEAR,			//ゲームクリア
	OBJ_RANKING,			//ランキング
	OBJ_MENU,				//メニュー
	OBJ_OPERATION,			//操作説明
};
//------------------------------------------------

//当たり判定属性----------------------------------
enum HIT_ELEMENTS
{
	ELEMENT_NULL,//属性無し 全ての属性と当たり判定が実行される
	//以下　同じ属性同士では当たり判定は実行されない
	//属性は追加可能だが、デバック時の色は初期設定分しか無い
	ELEMENT_HERO,
	ELEMENT_ENEMY,
	ELEMENT_ITEM,
	ELEMENT_JUDGMENT,//ゴーレムのダメージ判定
};
//------------------------------------------------
//ゲーム内で使用されるグローバル変数・定数・列挙--
#define RANKING_MAX_COUNT (4) // ランキング数+1
#define MAX_CHAR_COUNT (6)	   // 入力できる文字数 
//------------------------------------------------
//セーブ＆ロードとシーン間のやり取りするデータ
struct UserData
{
	int mSeveData;	//サンプルセーブデータ
	int m_point;		//GameMainで得たポイント
	int m_stage_count;//ステージの種類
	int m_ranking[RANKING_MAX_COUNT];//ランキング格納配列
	int m_restart;
	/*wchar_t m_name[RANKING_MAX_COUNT][MAX_CHAR_COUNT];*/
};
//------------------------------------------------


//ゲーム内で使用するクラスヘッダ------------------


//------------------------------------------------

//ゲームシーンオブジェクトヘッダ------------------
//プレイヤー
#include "ObjHero.h"			//主人公
#include "ObjBlock.h"			//ブロック
#include "ObjGold.h"            //金塊
#include "ObjCoin.h"			//コイン

//敵
#include "ObjRushEnemy.h"		//突進する敵
#include "ObjJumpEnemy.h"		//ジャンプする敵
#include "ObjGolem.h"			//ゴーレム
#include "GolemJudgment.h"      //ゴーレムの判定
//ギミック
#include "Objthorn.h"			//針
#include "Objswitch.h"			//スイッチ
#include "ObjGoal.h"			//ゴール
#include "ObjVanishBlock.h"		//消えるブロック
//シーン
#include "ObjTitle.h"			//タイトル
#include "ObjRanking.h"			//ランキング
#include "ObjGameClear.h"		//クリア
#include "ObjOperation.h"		//操作説明
//補助系
#include "Correction.h"			//補正
#include "hero_hitbox.h"		//主人公のヒットボックス二個目
//アイテム
#include "ObjDropGold.h"        //敵から落ちる金塊
//------------------------------------------------

//ゲームシーンクラスヘッダ------------------------
#include "SceneMain.h"			//シーンタイトル
#include "SceneTitle.h"			//シーンメイン
#include "SceneRanking.h"		//シーンランキング
#include "SceneGameClear.h"		//シーンクリア
#include "SceneOperation.h"		//シーン操作説明

//-----------------------------------------------

//シーンスタートクラス---------------------------
//ゲーム開始時のシーンクラス登録
#define SET_GAME_START CSceneTitle
//-----------------------------------------------