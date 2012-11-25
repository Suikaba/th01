#ifndef WINDOWBASE_H
#define WINDOWBASE_H

#include <windows.h>
#include "Graphics.h"
#include "Input.h"
#include "Object.h"
#include <tchar.h>

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 400


//=================================================================
// ウィンドウの本体のクラス
class CWindowBase {
private:

	// ウィンドウハンドル
	HWND hWnd, DesktophWnd;

	// アプリケーション名
	string AppName;

	// グラフィクス
	CGraphics* Graphics;

	// オブジェクト（ブロック、バー、ボール）
	CObject* Object;

	// キー情報
	CInput* Input;

	// メニューのテクスチャ
	LPDIRECT3DTEXTURE9 menu;
	LPDIRECT3DTEXTURE9 gameover;
	LPDIRECT3DTEXTURE9 clear;

	void DrawScene();

	void DrawMenu();
	void DrawClear();
	void DrawGameOver();

	enum shikensu {
		MENU,
		GAMEMAIN,
		CLEAR,
		GAMEOVER,
	};

	int shikensu;

	DWORD time;

public:

	// コンストラクタ
	CWindowBase( HINSTANCE hInstance, LPCTSTR appname );
	~CWindowBase();

	// メッセージハンドら
	virtual LRESULT CALLBACK WndProc( UINT msg, WPARAM wParam, LPARAM lParam );

	// オブジェクトのテクスチャのロード
	void SetObjectTexture();

	// 画面のリセット
	void ResetScreen();

	// キー入力の更新
	void InputUpdate();

	virtual void ObjectDraw();

	// クリアしてるかどうか確認
	void ClearCheck();

	// ゲームの実行
	void Run();

	void Move();

	// ゲームオーバーかどうか
	void CheckGameOver();

	// シーケンスの入れ替え
	void ShikensuChenge();

};


#endif

