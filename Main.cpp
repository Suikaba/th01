#include "WindowBase.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPTSTR, int ) {
	CWindowBase* Window = new CWindowBase( hInst, _T("Mystery Breakout") );
	Window->Run();
	delete Window;
	return 0;
}