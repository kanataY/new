//使用するヘッダーファイル
#include "GameL\DrawTexture.h"
#include "GameL\WinInputs.h"
#include "GameL\SceneManager.h"
#include "GameL\HitBoxManager.h"
#include "GameL\UserData.h"
#include "GameL\DrawFont.h"
#include "GameL\Audio.h"

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
	m_swich_time = 0;

	m_gold_flag = false;

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

	if (hx < 100 )
	{
		hero->SetX(100);			//主人公はラインを超えないようにする

		m_scroll -= hero->GetVX();

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
		//列の中から3を探す
		if (m_map[i][ex] == 3)
		{
			//ゴールを出す
			CObjGoal* goal = new CObjGoal(ex * 64, i * 64);
			Objs::InsertObj(goal, OBJ_GOAL, 16);
			m_map[i][ex] = 0;
		}
		//列の中から4を探す
		if (m_map[i][ex] == 4)
		{
			//針を出す
			CObjthorn* thorn = new CObjthorn(ex*64, i*64);
			Objs::InsertObj(thorn, OBJ_THORN, 16);
			m_map[i][ex] = 999;							//針を出した後に金塊の当たり判定を残すために999を利用
		}

		//列の中から5を探す
		if (m_map[i][ex] == 5)
		{
			//スイッチオブジェクト作成
			CObjswitch* swi = new CObjswitch(ex * 64, i * 64 + 32.0f);
			Objs::InsertObj(swi, OBJ_SWITCH, 13);
			m_map[i][ex] = 0;	
		}


		//列の中から6を探す
		if (m_map[i][ex] == 6)
		{
			//消えるブロックを出す
			CObjVanishBlock* vanish = new CObjVanishBlock(ex * 64, i * 64);
			Objs::InsertObj(vanish, OBJ_VANISHBLOCK, 11);
			if (((UserData*)Save::GetData())->m_stage_count == 3)	//ステージ３なら最初は描画しないので判定も変える
			{
				m_map[i][ex] = 97;	
			}
			m_map[i][ex] = 98;							//消えるブロックを出した後に消えるブロックの当たり判定を残すために98を利用
		}

		//列の中から7を探す
		if (m_map[i][ex] == 7)
		{
			//突進する敵を出す
			CObjRushEnemy* rush = new CObjRushEnemy(ex * 64, i * 64);
			Objs::InsertObj(rush, OBJ_RUSH_ENEMY, 16);
			m_map[i][ex] = 0;			
			m_map_Record[i][ex] = 0; //記録用も消す
		}

		//列の中から8を探す
		if (m_map[i][ex] == 8)
		{
			//ゴーレム＆ゴーレムの目の判定を出す
			CObjGolem* golem = new CObjGolem(ex * 64, i * 64);
			Objs::InsertObj(golem, OBJ_GOLEM, 13);

			CObjGolemJudgment* golemj = new CObjGolemJudgment(ex * 64, i * 64);
			Objs::InsertObj(golemj, GOLEM_JUDGMENT, 13);

			m_map[i][ex] = 0;
			m_map_Record[i][ex] = 0; //記録用も消す
		}

		//列の中から9を探す
		if (m_map[i][ex] == 9)
		{
			///ジャンプオブジェクト作成
			CObjJumpEnemy* junp = new CObjJumpEnemy(ex * 64, i * 64);
			Objs::InsertObj(junp, OBJ_JUMP_ENEMY, 13);

			m_map[i][ex] = 0;
			m_map_Record[i][ex] = 0; //記録用も消す
		}
	}

	//消えるブロックの判定を消すーーーーーーーーーーーーーーーーーーーー

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			//スイッチの情報を持ってくる
			CObjswitch* swi = (CObjswitch*)Objs::GetObj(OBJ_SWITCH);
			if (swi != nullptr)
			{
				if (swi->GetSwitchFlag() == true)//スイッチが押されてる場合は判定を消す
				{
					m_swich_time++;//スイッチが押されてからしばらくしたら通れるようにする

					if (m_swich_time > 60000)
					{
						//列の中から998を探す
						if (((UserData*)Save::GetData())->m_stage_count == 3)	//ステージ３なら最初は描画しないので判定も変える
						{
							if (m_map[i][j] == 97)
							{
								m_map[i][j] = 98;	//通れるようにする
							}
						}
						else
						{
							if (m_map[i][j] == 98)
							{
								m_map[i][j] = 97;	//通れるようにする
							}
						}

						if (((UserData*)Save::GetData())->m_stage_count == 5)	//ステージ３なら最初は描画しないので判定も変える
						{
							if (m_map[i][j] == 10)
							{
								///ジャンプオブジェクト作成
								CObjJumpEnemy* junp = new CObjJumpEnemy(j * 64, i * 64);
								Objs::InsertObj(junp, OBJ_JUMP_ENEMY, 13);

								m_map[i][j] = 0;
								m_map_Record[i][j] = 0; //記録用も消す
							}
						}
					}
					if (((UserData*)Save::GetData())->m_stage_count == 5 && Audio::CheckSound(14) == false)	//ステージ３なら最初は描画しないので判定も変える
					{
						Audio::Start(14);
					}
				}

				else if (swi->GetSwitchFlag() == false)//スイッチが押されてない場合は判定を消さない
				{
					m_swich_time = 0;
					//列の中から998を探す
					if (((UserData*)Save::GetData())->m_stage_count == 3)	//ステージ３なら最初は描画しないので判定も変える
					{
						//列の中から997を探す
						if (m_map[i][j] == 98)
						{
							m_map[i][j] = 97;	//通れなくする。
						}
					}
					else
					{
						//列の中から997を探す
						if (m_map[i][j] == 97)
						{
							m_map[i][j] = 98;	//通れなくする。
						}
					}
				}
			}
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

	//描画 ステージ１と２,3で背景を昼に変える
	if (((UserData*)Save::GetData())->m_stage_count == 1 || ((UserData*)Save::GetData())->m_stage_count == 2 )
	{
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}
	else if(((UserData*)Save::GetData())->m_stage_count == 3 || ((UserData*)Save::GetData())->m_stage_count == 4 || ((UserData*)Save::GetData())->m_stage_count == 5)//ステージ４，５は夕方にする
	{
		Draw::Draw(14, &src, &dst, c, 0.0f);
	}
	

	//マップチップによるblock設置
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < MAP_X_MAX; j++)
		{
			//表示位置の設定
			dst.m_top = i*64.0f;
			dst.m_left = j*64.0f + m_scroll;
			dst.m_right = dst.m_left + 64.0f;
			dst.m_bottom = dst.m_top + 64.0f;
			if (m_map[i][j] == 1)
			{
				//ブロック
				BlockDraw(0.0f, 0.0f, &dst, c , i ,j);
			}
			if (m_map[i][j] == 4)
			{
				;
			}
			
		}
	}
}

//調べたいマップの位置にあるマップ番号を返す
int CObjBlock::GetMap(int x, int y)
{
	if (0 <= y && y < 10 && 0 <= x && x < MAP_X_MAX)

		return m_map[y][x];

	return -99999;//無かった場合
}

//調べたいマップの位置にあるマップ番号を返す(記録版)
int CObjBlock::GetMapRecord(int x, int y)
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
void CObjBlock::BlockDraw(float x, float y, RECT_F* dst, float c[] , int i , int j)
{
	RECT_F src;
	src.m_top = y;
	src.m_left = x;
	src.m_right = src.m_left + 64.0f;
	src.m_bottom = src.m_top + 64.0f;
	//描画
	if (i > 0)
	{
		if (m_map[i - 1][j] == 1)
		{
			Draw::Draw(2, &src, dst, c, 0.0f);
		}
		else
			Draw::Draw(1, &src, dst, c, 0.0f);
	}
	else 
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
	float* vx, float*vy, int* bt, bool b,bool hero, float* yy,bool* gg,bool hero_hit
)
{
	
	//衝突状態確認用フラグの初期化
	*up = false;
	//ゴールドなら変化させない
	if(b == false)
	*down = false;
	*left = false;
	*right = false;

	//踏んでいるblockの種類の初期化
	*bt = 0;
	float m_cx = 0.0f;
	float m_cy = 0.f;

	//主人公ならm_cx（ブロックとの当たり判定）の幅を変える
	if (hero_hit == false)
	{
		 m_cx = 64.0f;
		 m_cy = 64.0f;
	}
	else
	{
		//主人公なら壁との判定もやる
		if (hero == true)
		{
			m_cx = 50.1f; //ブロックに上がれるように
			m_cy = 64.0f;
		}
		else
		{
			m_cx = 50.0f;
			m_cy = 64.0f;
		}
	}

	//m_mapの全要素にアクセス
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			//－－－－－－－－－－－－－－－－－－－－－－－－－－－－
			if (m_map[i][j]>0 && m_map[i][j] != 2 && m_map[i][j] != 3 && m_map[i][j] != 5 && m_map[i][j] != 10 && m_map[i][j] != 97)
			{
				//要素番号を座標に変更
				float bx = j*64.0f;
				float by = i*64.0f;

				//スクロールの影響
				float scroll = scroll_on ? m_scroll : 0;

				//主人公とブロックの当たり判定
				if ((*x + (-scroll) + m_cx > bx) && (*x + (-scroll) < bx + m_cx) && (*y + m_cy >= by) && (*y <= by + m_cy))
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
						//主人公なら壁との判定もやる
						if (hero == true)
						{
							//左上半分なら上げる
							if (r >= 155 && r < 183)
							{
								if (m_map[i - 1][j] == 0)	//当たっているブロックの一つ前が空白なら
								{
									*gg = true;//登れるようにヒーロー側＆ブロック側で処理をする
									*yy -= 35.0f;//登らせる
								}
							}
							
							//右上半分なら上げる
							else if (r < 25 && r >= 0 || r >= 350)
							{
								if (m_map[i - 1][j] == 0)//当たっているブロックの一つ前が空白なら
								{
									*gg = true;//登れるようにヒーロー側＆ブロック側で処理をする
									*yy -= 35.0f;
								}
							}
						}
						else
						{
							//角度で上下左右判定
							if (r < 45 && r >= 0 || r >= 315)
							{
								//右

								*right = true;//主人公の左の部分が衝突している
								*x = bx + m_cx + (scroll);//ブロックの位置ー主人公の幅
								
								*vx = -(*vx) * 0.1f;//-VX*反発係数

							}
							if (r >= 45 && r < 135)
							{
								//上
								*down = true;//主人公の下の部分が衝突している
								*y = by - 64.0f;//ブロックの位置ー主人公の幅
								
								//種類を渡すのスタートとg-流のみ変更する
								*vy = 0.0f;
							}

							if (r >= 135 && r < 225)
							{
								//左
								*left = true;//主人公の右の部分が衝突している
								*x = bx - m_cx + (scroll);//ブロックの位置ー主人公の幅
								*vx = -(*vx) * 0.1f;//-VX*反発係数

							}
							if (r >= 225 && r < 315)
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
}



// Block32Hit関数
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
//判定を行うobjectとブロック32×64限定で、当たり判定と上下左右判定を行う
//その結果は引数4～10に返す
void CObjBlock::Block32Hit(
	float *x, float *y, bool scroll_on,
	bool*up, bool* down, bool* left, bool* right,
	float* vx, float*vy, int* bt, float* yy
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
			if (m_map[i][j]>0 && m_map[i][j] != 2 && m_map[i][j] != 3 && m_map[i][j] != 5 && m_map[i][j] != 10 && m_map[i][j] != 97)
			{
				//要素番号を座標に変更
				float bx = j*64.0f;
				float by = i*64.0f;

				//スクロールの影響
				float scroll = scroll_on ? m_scroll : 0;

				//主人公とブロックの当たり判定
				if ((*x + (-scroll) + 32.0f > bx) && (*x + (-scroll) < bx + 32.0f) && (*y + 32.0f > by) && (*y < by + 32.0f))
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
					if (len < 88.0f)
					{
						*left = true;

						//角度で上下左右判定
						if (r < 45 && r >= 0 && r >= 315)
						{
							//右

							*right = true;//左の部分が衝突している
						//	*x = bx +32.0f+ (scroll);//ブロックの位置ー主人公の幅
						//	*vx = -(*vx) * 0.1f;//-VX*反発係数

						}
						if (r >= 45 && r < 135)
						{
							//上
							*down = true;//主人公の下の部分が衝突している
						//	*y = by - 32.0f;//ブロックの位置ー主人公の幅
							*left = true;
											//種類を渡すのスタートとg-流のみ変更する
						//	*vy = 0.0f;
						}

						if (r >= 135 && r < 225)
						{
							//左
							*left = true;//主人公の右の部分が衝突している
						//	*x = bx - 32.0f + (scroll);//ブロックの位置ー主人公の幅
						//	*vx = -(*vx) * 0.1f;//-VX*反発係数

						}
						if (r >= 225 && r < 315)
						{
							//下
							*up = true;  //主人公の上の部分が衝突している
						//	*y = by + 32.0f;//ブロックの位置＋主人公の幅
						//	if (*vy < 0)
						//	{
						//		*vy = 0.0f;
						//	}
							*left = true;
						}

					}
				}
			}
		}
	}
}