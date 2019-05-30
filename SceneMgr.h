#pragma once

typedef enum {                // 定義
	eScene_Title, 
	eScene_Tetris,
	eScene_Menu,
	eScene_GA,
	eScene_Option
}eScene;

void SceneMgr_Update();	// 更新

void SceneMgr_Draw();	// 描写

void SceneMgr_ChangeScene(eScene nextScene);	// シーン変更
