//ヘッダファイルに関数毎に作者記入、無記入は作鳥井

#include "DxLib.h"
#include "Title.h"
#include "Menu.h"
#include "Tetris.h"
#include "GA.h"
#include "Option.h"
#include "SceneMgr.h"


static eScene Scene = eScene_Title;

void SceneMgr_Update(){
	switch(Scene){       
		case eScene_Title: 
        		break;
		case eScene_Menu: 
        		break;
		case eScene_Tetris:		
        		Tetris_Update();
        		break;
		case eScene_GA:
			GA_Update();
			break;
		case eScene_Option: 
        		Option_Update();
        		break;
    	}
}

void SceneMgr_Draw(){
    	switch(Scene){      
    		case eScene_Title:
        		Title_Draw();
        		break;
   		case eScene_Menu:
        		Menu_Draw();
        		break;
		case eScene_Tetris:
			Tetris_Draw();
			break;
		case eScene_GA:
			GA_Draw();
			break;
		case eScene_Option:
			Option_Draw();
			break;
    	}
}

void SceneMgr_ChangeScene(eScene NextScene){
	Scene = NextScene;
}
