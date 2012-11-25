#ifndef INPUT_H
#define INPUT_H

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>
#include <tchar.h>

class CInput {
private:

	LPDIRECTINPUT8 lpDI;
	LPDIRECTINPUTDEVICE8 lpDIDevice;

	char m_keys[256];

public:

	bool Left, Right, Z;

	// コンストラクタ
	CInput( HWND hWnd );
	~CInput();

	// キー入力の状態を取得
	void UpdataState();

	// 何も押されていない状態にする
	void Clear();
};

#endif