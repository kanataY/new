#pragma once
//使用ヘッダー
#include "GameL\SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：スイッチ
class CObjswitch : public CObj
{
public:
	CObjswitch(float x, float y);
	~CObjswitch() {};
	void Init();	//イニシャライズ
	void Action();	//アクション
	void Draw();	//ドロー
	bool GetSwitchFlag() { return switch_on_flag; }
	void SetSwitchFlag(bool ssf) { switch_on_flag = ssf; }
private:
	float m_px;//位置
	float m_py;
	bool switch_on_flag;//スイッチに当たった時のフラグ
};