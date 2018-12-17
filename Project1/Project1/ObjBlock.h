#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"
//使用するネームスペース
using namespace GameL;

//マクロ　
#define MAP_X_MAX 100

//オブジェクト：ブロック＆背景
class CObjBlock : public CObj
{
public:
	CObjBlock(int map[10][MAP_X_MAX]);
	~CObjBlock() {};
	void Init();	//イニシャライズ
	void Action();  //アクション
	void Draw();	//ドロー
	
	void  SetScroll(float s) { m_scroll = s; }
	float GetScroll() { return m_scroll; }

	int  GetMap(int x, int y);//マップ情報の取得
	int  GetMapRecord(int x, int y);//マップ情報の取得(記録版)
	void  SetMap(int x, int y, int m) { m_map[y][x] = m; }
	bool  GetGold() { return m_gold_flag; }

	//ブロックとの当たり判定
	void BlockHit(
		float* x, float* y, bool scroll_on,
		bool* up, bool* down, bool* left, bool* right,
		float* vx, float* vy, int* bt,bool b, bool hero,float* yy,bool* gg
	);

private:

	void BlockDraw(float x, float y, RECT_F* dst, float c[],int i, int j);

	float m_px;		//位置
	float m_py;
	float m_bx1;     //背景の動く値
	float m_bx2;     //背景の動く値2

	bool m_gold_flag; //壁上るときに金塊の判定を消す

	float m_scroll; //スクロール位置
	float m_scroll_run; //ランナーの位置でスクを変えるようの変数

	int m_scroll_num;//スクロールの数を調べる変数

	int m_map[10][MAP_X_MAX];//マップ情報
	int m_map_Record[10][MAP_X_MAX];//マップ情報記録役
};