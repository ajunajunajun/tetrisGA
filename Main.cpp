//ヘッダファイルに関数毎に作者記入、無記入は作鳥井

#include <math.h>

#include "DxLib.h"
#include "Main.h"
#include "Keyboard.h"
#include "SceneMgr.h"

int HandleB1;

static int starttime;	//測定開始時刻
static int count;	//カウンタ
static float fps;	//フレームレート
static const int N = 60;	//平均を取るサンプル数
int FPS = 100;	//設定したFPS


bool Update(){
	if(count==0){		//1フレーム目なら時刻を記憶
		starttime = GetNowCount();
	}
	if(count==N){		//60フレーム目なら平均を計算する
		int t = GetNowCount();
		fps = 1000.f/((t-starttime)/(float)N);
		count = 0;
		starttime = t;
	}
	count++;
	return true;
}

void Draw(){
	DrawFormatString(0, 0, GetColor(255,127,0), "%.1f", fps);
}

void Wait(){
	int tookTime = GetNowCount() - starttime;	//かかった時間
	int waitTime = count*1000/FPS - tookTime;	//待つべき時間
	if( waitTime > 0 ){
		Sleep(waitTime);	//待機
	}
}


int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
	SetBackgroundColor(255,255,255);
	ChangeWindowMode(true);
	SetGraphMode(1024,768,16);
	SetAlwaysRunFlag(true);
	SetWaitVSyncFlag(false);
        DxLib_Init();    
	SetMainWindowText("tetris");
	SetDrawScreen( DX_SCREEN_BACK );        

	while( Process() ){
	
		SceneMgr_Update();
	        Keyboard_Update();
		SceneMgr_Draw(); 
        
		Wait();		//待機
		Update();	//更新
		Draw();		//描画
	
	}
	
	DxLib_End();
	InitSoundMem();
        return 0;
}

bool Process(){
	char Key[256];
	if(ScreenFlip()!=0)return false; 
	if(ProcessMessage()!=0)return false;
	if(ClearDrawScreen()!=0)return false;
	return true; 
}
