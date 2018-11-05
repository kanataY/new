//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"

#include "GameHead.h"
#include "ObjBlock.h"

//使用するネームスペース
using namespace GameL;

//コンストラクタ
CObjBlock::CObjBlock(int map[10][MAP_X_MAX])
{
	//マップデータをコピー
	memcpy(m_map, map, sizeof(int)*(10 * MAP_X_MAX));
	//マップデータを記録するほうにコピー
	memcpy(m_map_Record, map, sizeof(int)*(10 * MAP_X_MAX));
}

//イニシャライズ
void CObjBlock::Init()
{
	m_px = 0.0f;
	m_py = 0.0f;	//位置
	m_bx1 = 0.0f;
	m_bx2 = 800.0f;

	m_scroll = 0.0f;
	m_scroll_run = 800.0f;
	m_scroll_num = 0;
}

//アクション
void CObjBlock::Action()
{
	//背景関連ーーーーーーーーーーーーーーーーーーーーーーーー
	//ランナーの位置を取得
	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);

	float hx = hero->GetX();
	float hy = hero->GetY();

	if (hx < -50 ) //画面より左側に行けないようにする
	{
		//背景1の動作
		m_bx1 -= 0.0f;

		//背景2の動作
		m_bx2 -= 0.0f;
	}
	//前方スクロールライン
	else if (hx > 400 )
	{
		hero->SetX(400);			//主人公はラインを超えないようにする

		m_scroll -= hero->GetVX();//主人公が本来動くべき分の値をm_scrollに加える

		//背景1の動作
		m_bx1 -= hero->GetVX();
		if (m_bx1 < -800.0f)
		{
			m_bx1 = 800.0f;
			m_scroll_num++;//背景1が終わればカウントする
		}
		//背景2の動作
		m_bx2 -= hero->GetVX();
		if (m_bx2 < -800.0f)
			m_bx2 = 800.0f;

	}


	//マップ関連ーーーーーーーーーー
	float line = 0.0f;

	//敵出現ライン
	//主人公の位置+800 - ランナーの位置を敵出現ラインにする
	line = hx + (-m_scroll) + (800 - hx);

	//敵出現ラインを要素番号化
	int ex = ((int)line) / 64;

	//敵出現ラインの列を検索
	for (int i = 0; i < 10; i++)
	{
		//列の中から１を探す
		if (m_map[i][ex] == 1)
		{
			;
		}
	}
}
	

//描画
void CObjBlock::Draw()
{

	//-----------背景-----------
	//描画カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src; //描画元切り取り位置
	RECT_F dst; //描画先表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 1024.0f;
	src.m_bottom = 1024.0f;
	//背景1が4回スクロールした時

	//表示位置の設定
	//ゴ－ル背景描画
	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = 800.0f;
	dst.m_bottom = 700.0f;

	//描画
	Draw::Draw(0, &src, &dst, c, 0.0f);

}

//調べたいマップの位置にあるマップ番号を返す
int CObjBlock::GetMap(int x, int y)
{
	if (0 <= y && y < 10 && 0 <= x && x < MAP_X_MAX)

		return m_map_Record[y][x];

	return -99999;//無かった場合
}

//BlockDrawMethod関数
//引数１ float   x    :リソース切り取り位置X
//引数２ float   y    :リソース切り取り位置Y
//引数３ RECT_F* dst  :描画位置
//引数４ float   c[]  :カラー情報
//ブロックを64×64限定描画用。リソース切り取り位置のみｘ・ｙで
//設定できる
void CObjBlock::BlockDraw(float x, float y, RECT_F* dst, float c[])
{
	RECT_F src;
	src.m_top = y;
	src.m_left = x;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;
	//描画
	Draw::Draw(1, &src, dst, c, 0.0f);

}

//BlockHit関数
//引数１　float* x          :判定を行うobjectのX位置
//引数２　float* y          :判定を行うobjectのY位置
//引数３　bool   scroll_on  :判定を行うobjectはスクロールの影響与えるかどうか（true＝与える　false=与えない）
//引数４　bool*  up         :上下左右の上部分に当たっているかどうか返す
//引数５　bool*  down       :上下左右の下部分に当たっているかどうか返す
//引数６　bool*  left       :上下左右の左部分に当たっているかどうか返す
//引数７　bool*  right      :上下左右の右部分に当たっているかどうか返す
//引数８　float* vx         :左右判定時の反発による移動方向・力の値を変えて返す
//引数９　float* vy         :上下判定時による自由落下運動の移動方向・力の値を変えて返す
//引数１０int*   bt         :下部分判定時、特殊なブロックのタイプを返す
//判定を行うobjectとブロック64×64限定で、当たり判定と上下左右判定を行う
//その結果は引数4～10に返す
void CObjBlock::BlockHit(
	float *x, float *y, bool scroll_on,
	bool*up, bool* down, bool* left, bool* right,
	float* vx, float*vy, int* bt
)
{

	//衝突状態確認用フラグの初期化
	*up = false;
	*down = false;
	*left = false;
	*right = false;

	//踏んでいるblockの種類の初期化
	*bt = 0;

	//m_mapの全要素にアクセス
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (m_map[i][j]>0 && m_map[i][j] != 4)
			{
				//要素番号を座標に変更
				float bx = j*64.0f;
				float by = i*64.0f;

				//スクロールの影響
				float scroll = scroll_on ? m_scroll : 0;

				//主人公とブロックの当たり判定
				if ((*x + (-scroll) + 64.0f > bx) && (*x + (-scroll) < bx + 64.0f) && (*y + 64.0f > by) && (*y < by + 64.0f))
				{
					//上下左右判定

					//vectorの作成
					float rvx = (*x + (-scroll)) - bx;
					float rvy = *y - by;
					//長さを求める
					float len = sqrt(rvx*rvx + rvy*rvy);

					//角度を求める
					float r = atan2(rvy, rvx);
					r = r * 180.0f / 3.14f;

					if (r <= 0.0f)
						r = abs(r);
					else
						r = 360.0f - abs(r);

					//lenがある一定の長さより短い場合判定に入る
					if (len<88.0f)
					{
						//角度で上下左右判定
						if (r<45 && r>0 || r>315)
						{
							//右

								*right = true;//主人公の左の部分が衝突している
								*x = bx + 64.0f + (scroll);//ブロックの位置ー主人公の幅
								*vx = -(*vx) * 0.1f;//-VX*反発係数
							

						}
						if (r>45 && r<135)
						{
							//上
							*down = true;//主人公の下の部分が衝突している
							*y = by - 64.0f;//ブロックの位置ー主人公の幅
											//種類を渡すのスタートとg-流のみ変更する
							*vy = 0.0f;
						}
						if (r>135 && r<225)
						{
							//左
							*left = true;//主人公の右の部分が衝突している
							*x = bx - 64.0f + (scroll);//ブロックの位置ー主人公の幅
							*vx = -(*vx) * 0.1f;//-VX*反発係数
						
						}
						if (r > 225 && r < 315)
						{
							//下
							*up = true;  //主人公の上の部分が衝突している
							*y = by + 64.0f;//ブロックの位置＋主人公の幅
							if (*vy < 0)
							{
								*vy = 0.0f;
							}
						}
					}
				}
			}
		}
	}
}