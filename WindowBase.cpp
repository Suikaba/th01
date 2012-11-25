#include "WindowBase.h"


//==================================================================
// ウィンドウプロシージャ
static LRESULT CALLBACK windowProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	CWindowBase* Window = (CWindowBase*)GetWindowLong( hWnd, GWL_USERDATA );
	if( Window ) {
		Window->WndProc( msg, wParam, lParam );
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

LRESULT CALLBACK CWindowBase::WndProc( UINT msg, WPARAM wParam, LPARAM lParam ) {
	switch( msg ) {
	
		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}


//==================================================================
// コンストラクタ
CWindowBase::CWindowBase( HINSTANCE hInstance, LPCTSTR appname ) 
: time( 0 ), menu( NULL ), gameover( NULL ), clear( NULL )
{
	// ウィンドウクラスの登録
	WNDCLASSEX wc;
	ZeroMemory( &wc, sizeof( wc ) );
	wc.cbSize = sizeof( wc );
	wc.lpfnWndProc = windowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = appname;
	wc.style = CS_CLASSDC;
	if( !RegisterClassEx( &wc ) )
		return;

	AppName = appname;

	RECT wr;
	DesktophWnd = GetDesktopWindow();
	GetWindowRect( DesktophWnd, &wr );
	long style = WS_CAPTION | WS_VISIBLE | WS_SYSMENU;
	RECT r = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRect( &r, style, false );
	hWnd = CreateWindow(
		wc.lpszClassName, wc.lpszClassName, style,
		( wr.right - ( r.right-r.left ) )/2, ( wr.bottom - ( r.bottom-r.top ) )/2, // ウィンドウを中心に配置
		r.right - r.left, r.bottom - r.top,
		NULL, NULL, wc.hInstance, NULL );

	Graphics = new CGraphics( hWnd );
	Object = new CObject( WINDOW_WIDTH, WINDOW_HEIGHT );
	Graphics->Clear();
	Graphics->Present();
	Input = new CInput( hWnd );
	menu = Graphics->LoadTexture( _T("Menu.bmp") );
	clear = Graphics->LoadTexture( _T("Clear.bmp"), 0, 0, 0 );
	gameover = Graphics->LoadTexture( _T("GameOver.bmp"), 0, 0, 0 );
	SetObjectTexture();
	shikensu = MENU;
}


//==================================================================
// デストラクタ
CWindowBase::~CWindowBase() {
	delete Graphics;
	delete Object;
	delete Input;
	if( gameover != NULL ) {
		gameover->Release();
		gameover = NULL;
	}
	if( menu != NULL ) {
		menu->Release();
		menu = NULL;
	}
	if( clear != NULL ) {
		clear->Release();
		clear = NULL;
	}
}


//==================================================================
// ゲーム実行
void CWindowBase::Run() {

	SetWindowLong( hWnd, GWL_USERDATA, (LONG)this );

	// メッセージループ
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );
	while( msg.message != WM_QUIT ) {
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ) {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		} else {
			DrawScene();
			ShikensuChenge();
		}
	}

	SetWindowLong( hWnd, GWL_USERDATA, (long)::windowProc );

	// 終了処理
	UnregisterClass( AppName.c_str(), GetModuleHandle( NULL ) );
	return;
}


//==================================================================
// オブジェクトのテクスチャのロード
void CWindowBase::SetObjectTexture() {
	Object->SetBlockTexture( Graphics->LoadTexture( _T("block.bmp") ) );
	Object->SetBarTexture( Graphics->LoadTexture( _T("bar.bmp") ) );
	Object->SetBallTexture( Graphics->LoadTexture( _T("ball.bmp"), 0, 0, 0 ) );
}


//==================================================================
// オブジェクトの描画
void CWindowBase::ObjectDraw() {
	for( int i=0; i<BLOCK_TATENOKAZU; i++ ) {
		for( int j=0; j<BLOCK_YOKONOKAZU; j++ ) {
			if( Object->GetBlock( i * BLOCK_YOKONOKAZU + j ).flag == true ) {
				float x = Object->GetBlock( i * BLOCK_YOKONOKAZU + j ).x;
				float y = Object->GetBlock( i * BLOCK_YOKONOKAZU + j ).y;
				Graphics->SpriteDraw( x, y, Object->GetBlockTexture() );
			}
		}
	}
	float x = Object->GetBall().x;
	float y = Object->GetBall().y;
	Graphics->SpriteDraw( x, y, Object->GetBall().BallTex );
	x = Object->GetBar().x;
	y = Object->GetBar().y;
	Graphics->SpriteDraw( x, y, Object->GetBar().BarTex );
}


//==================================================================
// シーンのリセット
void CWindowBase::ResetScreen() {
	Graphics->ResetDevice();
}
				

//==================================================================
// 描画
void CWindowBase::DrawScene() {
	
	LPDIRECT3DDEVICE9 lpd3dDev = Graphics->GetDevice();

	// デバイスが消失していたら再構築
	switch( Graphics->GetDevice()->TestCooperativeLevel() ) {
		case D3DERR_DEVICELOST:
			Sleep( 50 );
			return;
		case D3DERR_DEVICENOTRESET:
			ResetScreen();
			return;
	}

	Graphics->Clear( D3DCOLOR_XRGB( 20, 90, 100 ) );

	InputUpdate();

	// 描画の開始
	Graphics->BeginScene();
	Graphics->BeginSprite();

	switch( shikensu ) {
		case MENU:
			DrawMenu();
			break;

		case GAMEMAIN:
			ObjectDraw();
			Move();
			break;

		case CLEAR:
			ObjectDraw();
			DrawClear();
			break;

		case GAMEOVER:
			ObjectDraw();
			DrawGameOver();
			break;
	}

	Graphics->EndSprite();
	Graphics->EndScene();

	Graphics->Present();
}


//==============================================================
// キー入力の更新
void CWindowBase::InputUpdate() {
	Input->Clear();
	Input->UpdataState();
}


//==============================================================
// 移動
void CWindowBase::Move() {
	Object->MoveBar( Input->Left, Input->Right );
	Object->MoveBall();
}


//==============================================================
// クリアしてるか確認
void CWindowBase::ClearCheck() {
	if( Object->CheckClear() ) {
		shikensu = CLEAR;
		if( time == 0 )
			time = timeGetTime();
	}
}


//==============================================================
// メニューの描画
void CWindowBase::DrawMenu() {
	if( Input->Z ) {
		shikensu = GAMEMAIN;
		Sleep(1);
		return;
	}
	Graphics->SpriteDraw( 0, 0, menu );
}


//==============================================================
// ゲームオーバー処理
void CWindowBase::DrawGameOver() {
	Graphics->SpriteDraw( 0, 0, gameover );
}


//==============================================================
// クリアのときの処理
void CWindowBase::DrawClear() {
	Graphics->SpriteDraw( 0, 0, clear );
}


//==============================================================
// ゲームオーバーの確認
void CWindowBase::CheckGameOver() {
	if( Object->GameOver() ) {
		shikensu = GAMEOVER;
		if( time == 0 )
			time = timeGetTime();
	}
}


//==============================================================
// シーケンスの入れ替え
void CWindowBase::ShikensuChenge() {
	CheckGameOver();
	ClearCheck();
	if( shikensu == GAMEOVER || shikensu == CLEAR ) {
		if( ( timeGetTime() - time )/1000 >= 8 ) {
			shikensu = MENU;
			Object->ResetObject();
			time = 0;
		}
	}
}

