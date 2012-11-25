#include "Object.h"
#include <stdio.h>

//==================================================================
// コンストラクタ
CObject::CObject( int w, int h ) 
:	WindowWidth( w ), WindowHeight( h )
{
	SetBarTexture( NULL );
	SetBlockTexture( NULL );
	SetBallTexture( NULL );
	ResetObject();
}


//==================================================================
// デストラクタ
CObject::~CObject() {
	if( BlockTex != NULL ) {
		BlockTex->Release();
		BlockTex = NULL;
	}
	if( ball.BallTex != NULL ) {
		ball.BallTex->Release();
		ball.BallTex = NULL;
	}
	if( bar.BarTex != NULL ) {
		bar.BarTex->Release();
		bar.BarTex = NULL;
	}
}


//==============================================================
// バーの移動
void CObject::MoveBar( bool l, bool r ) {
	float BarSpeed = 4.5f;
	if( l )
		bar.x += -BarSpeed;
	if( r )
		bar.x += BarSpeed;
	if( bar.x < 0 )
		bar.x = 0;
	if( bar.x + BAR_WIDTH > WindowWidth )
		bar.x = (float)WindowWidth-BAR_WIDTH;
}


//==============================================================
// 玉の移動
void CObject::MoveBall() {
	srand( timeGetTime() );
	CheckBlock();
	if( ball.x < 0 || ball.x + BALL_WIDTH > WindowWidth ) ball.angle *= -1;
	if( ball.y < 0 )
		ball.angle = (float)(rand()%90 + 140);
	if( ball.angle <= 180 && ball.angle != 180 ) ball.angle += 0.5f;
	if( ball.angle >= 180 && ball.angle != 180 ) ball.angle -= 0.5f;
	if( ball.angle < 0 ) ball.angle += 360;
	if( ball.angle > 360 ) ball.angle += -360;
	float r = D3DXToRadian( ball.angle );
	ball.PrevX = ball.x;
	ball.PrevY = ball.y;
	ball.x = ball.x - BallSpeed * sinf(r);
	ball.y = ball.y - BallSpeed * cosf(r);
	if( ball.x+BALL_WIDTH < 0 || ball.y+BALL_HEIGHT < 0 ) {
		ball.x += (float)WindowWidth-20;
		ball.y += (float)WindowHeight-20;
	}
	if( ball.y > WindowHeight ) ball.y = (float)WindowHeight;
}


//==============================================================
// ブロックが弾に当たったら消去
void CObject::CheckBlock() {
	srand( timeGetTime() );
	int count=0;
	for( int y=0; y<BLOCK_TATENOKAZU; y++ ) {
		for( int x=0; x<BLOCK_YOKONOKAZU; x++ ) {
			if( block[ y * BLOCK_YOKONOKAZU + x ].x < ball.x+BALL_WIDTH &&
				ball.x < block[ y * BLOCK_YOKONOKAZU + x ].x+BLOCK_WIDTH &&
				block[ y * BLOCK_YOKONOKAZU + x ].y < ball.y+BALL_HEIGHT &&
				ball.y < block[ y * BLOCK_YOKONOKAZU + x ].y+BLOCK_HEIGHT
			) {
				if( block[ y * BLOCK_YOKONOKAZU + x ].flag == true ) {
					BallSpeed *= 1.014f;
					block[ y * BLOCK_YOKONOKAZU + x ].flag = false;
					if( count == 0 ) {
						ball.angle = (float)(rand()%360);
						count++;
					}
				}
			}
		}
	}
	if( bar.x < ball.x+BALL_WIDTH && ball.x < bar.x+BAR_WIDTH &&     
		bar.y < ball.y+BALL_HEIGHT && ball.y < bar.y+BAR_HEIGHT ) {
		ball.angle = (float)(rand()%90 - 50);
		/*if( ball.angle == 180 ) {
			ball.angle = 0;
		}
		if( ball.PrevX > ball.x )
			ball.angle = ball.angle - ( (int)ball.angle%90 )*2;
		else if( ball.PrevX < ball.x )
			ball.angle = ball.angle + ( 90-(int)ball.angle )*2;通常の処理*/

	}

}


//==============================================================
bool CObject::CheckClear() {
	for( int i=0; i<MAX_BLOCK; i++ ) {
		if( block[i].flag == true )
			return false;
	}
	return true;
}


//==============================================================
bool CObject::GameOver() {
	if( ball.y == WindowHeight )
		return true;

	return false;
}


//==============================================================
// オブジェクトの状態のリセット
void CObject::ResetObject() {
	bar.x = (float)( WindowWidth - BAR_WIDTH )/2;
	bar.y = 320;

	ball.x = (float)( WindowWidth - BALL_WIDTH )/2;
	ball.y = (float)( bar.y - BALL_HEIGHT );
	ball.angle = 0;

	BallSpeed = 3.5f;

	for( int y=0; y<BLOCK_TATENOKAZU; y++ ) {
		for( int x=0; x<BLOCK_YOKONOKAZU; x++ ) {
			if( (x+1)*(y+1) > MAX_BLOCK ) break;
			block[ y * BLOCK_YOKONOKAZU + x ].x = (float)( 6 + x*BLOCK_WIDTH );
			block[ y * BLOCK_YOKONOKAZU + x ].y = (float)( 6 + y*BLOCK_HEIGHT );
			block[ y * BLOCK_YOKONOKAZU + x ].flag = true;
		}
	}
}