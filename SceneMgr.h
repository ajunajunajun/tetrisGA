#pragma once

typedef enum {                // ��`
	eScene_Title, 
	eScene_Tetris,
	eScene_Menu,
	eScene_GA,
	eScene_Option
}eScene;

void SceneMgr_Update();	// �X�V

void SceneMgr_Draw();	// �`��

void SceneMgr_ChangeScene(eScene nextScene);	// �V�[���ύX
