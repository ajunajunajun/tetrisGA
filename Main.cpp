//�w�b�_�t�@�C���Ɋ֐����ɍ�ҋL���A���L���͍쒹��

#include <math.h>

#include "DxLib.h"
#include "Main.h"
#include "Keyboard.h"
#include "SceneMgr.h"

int HandleB1;

static int starttime;	//����J�n����
static int count;	//�J�E���^
static float fps;	//�t���[�����[�g
static const int N = 60;	//���ς����T���v����
int FPS = 100;	//�ݒ肵��FPS


bool Update(){
	if(count==0){		//1�t���[���ڂȂ玞�����L��
		starttime = GetNowCount();
	}
	if(count==N){		//60�t���[���ڂȂ畽�ς��v�Z����
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
	int tookTime = GetNowCount() - starttime;	//������������
	int waitTime = count*1000/FPS - tookTime;	//�҂ׂ�����
	if( waitTime > 0 ){
		Sleep(waitTime);	//�ҋ@
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
        
		Wait();		//�ҋ@
		Update();	//�X�V
		Draw();		//�`��
	
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
