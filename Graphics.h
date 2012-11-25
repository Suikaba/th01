#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <d3dx9.h>
#include <string>
using namespace std;


class CGraphics {
private:

	LPDIRECT3D9 lpD3D;
	LPDIRECT3DDEVICE9 lpd3dDev;
	LPD3DXSPRITE lpSprite;

	// ウィンドウハンドル
	HWND hWnd, DesktophWnd;

	// 元のウィンドウスタイル
	DWORD WindowStyle;

	// 幅、高さ
	int Width, Height;

public:

	// コンストラクタ
	CGraphics( HWND hwnd );
	~CGraphics();

	// 各種情報
	LPDIRECT3DDEVICE9 GetDevice() { return lpd3dDev; }
	LPD3DXSPRITE GetSprite() { return lpSprite; }
	HWND GetWindowHandle() { return hWnd; }
	int GetWidth() { return Width; }
	int GetHeight() { return Height; }

	// 各種情報の設定
	void SetWidth( int w ) { Width = w; }
	void SetHeight( int h ) { Height = h; }

	// デバイスのリセット
	bool ResetDevice();

	// 描画の設定
	void InitDraw();

	// 画面消去、プリップ
	void Clear( D3DCOLOR color = D3DCOLOR_ARGB( 255, 0, 0, 0 ) );
	bool Present();

	// シーン描画の開始、終了
	void BeginScene() { lpd3dDev->BeginScene(); }
	void EndScene() { lpd3dDev->EndScene(); }

	// スプライト描画の開始、終了
	void BeginSprite() { lpSprite->Begin( NULL ); }
	void EndSprite() { lpSprite->End(); }

	// スプライト描画
	void SpriteDraw( float x, float y, LPDIRECT3DTEXTURE9 texture );

	// テクスチャの読み込み
	LPDIRECT3DTEXTURE9 LoadTexture( string file );
	LPDIRECT3DTEXTURE9 LoadTexture( string file, int r, int g, int b );
};

#endif