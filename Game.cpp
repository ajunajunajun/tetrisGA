#include "DxLib.h"
#include "Keyboard.h"
#include "SceneMgr.h"


static Cr = GetColor(255,255,255);

void Tetris_Update(){

	if(Keyboard_Get(KEY_INPUT_ESCAPE)==1){
		SceneMgr_ChangeScene(eScene_Title);
	}

}
	
void Tetris_Draw(){
	
	DrawString(0,0,"Tetris‚¾‚æ",Cr);
	DrawString(0,100,"Esc‚ÅTitle",Cr);

	
}
