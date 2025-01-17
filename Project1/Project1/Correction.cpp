////使用するヘッダーファイル
//#include "GameL\DrawTexture.h"
//#include "GameL\WinInputs.h"
//#include "GameL\SceneManager.h"
//#include "GameL\HitBoxManager.h"
//#include "GameL\UserData.h"
//
//#include "GameHead.h"
//#include "Correction.h"
//
////使用するネームスペース
//using namespace GameL;
//
//CObjCorrection::CObjCorrection()
//{
//
//}
//
////イニシャライズ
//void CObjCorrection::Init()
//{
//	m_py = 0.0f;
//	m_px = 0.0f;
//	m_screen_out = false;
//	m_hole_control = false;
//}
//
//void CObjCorrection::Action()
//{
//
//}
//
//void CObjCorrection::Draw()
//{
//
//}
//
////オブジェクト生成したときにYが歩ける範囲より外か中だったら調整する
//float CObjCorrection::RangeY(float y, bool b)
//{
//	//スマホ少年は下にも行く
//	if (b == false)
//	{
//		if (y > OUTOFRANGE_DOWN)  //歩ける範囲より下にいる場合ギリギリまで戻す
//			return OUTOFRANGE_DOWN;
//	}
//	if (y < OUTOFRANGE_UP)//歩ける範囲より上にいる場合ギリギリまで戻す
//		return OUTOFRANGE_UP;
//
//	return y;
//}
//
////オブジェクト生成したときにYが歩ける範囲より外か中だったら調整する水たまりバージョン
//float CObjCorrection::RangeYPuddle(float y)
//{
//
//	if (y > OUTOFRANGE_DOWN_PUDDLE)  //歩ける範囲より下にいる場合ギリギリまで戻す
//		return OUTOFRANGE_DOWN_PUDDLE;
//	else if (y < OUTOFRANGE_UP_PUDDLE)//歩ける範囲より上にいる場合ギリギリまで戻す
//		return OUTOFRANGE_UP_PUDDLE;
//
//	return y;
//}
//
////オブジェクト生成したときにYが歩ける範囲より外か中だったら調整するトラックバージョン
//float CObjCorrection::RangeYTrack(float y)
//{
//
//	if (y > 480.0f)  //歩ける範囲より下にいる場合ギリギリまで戻す
//		return 480.0f;
//	else if (y < 220.0f)//歩ける範囲より上にいる場合ギリギリまで戻す
//		return 220.0f;
//
//	return y;
//}
//
//
////画面外に行くと消える処理
//bool CObjCorrection::Screen_Out(float x)
//{
//	//ブロック情報を持ってくる
//	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
//	
//	//画面外ならtrueを返す
//	if (x + block->GetScroll() < -50)
//	{
//		return true;
//	}
//
//	return false;
//}
//
////画面外に行くと消える処理
//float CObjCorrection::Screen_In(float x)
//{
//	//ブロック情報を持ってくる
//	CObjBlock* block = (CObjBlock*)Objs::GetObj(OBJ_BLOCK);
//
//	//ランナーの位置を取得
//	CObjHero* hero = (CObjHero*)Objs::GetObj(OBJ_HERO);
//	
//	//画面外ならtrueを返す
//	if (x > 750.0f)
//	{
//		x = 750.0f;
//	}
//
//	return x;
//}