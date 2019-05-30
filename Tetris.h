#pragma once

void Tetris_Update();	//更新,永井&鳥井作

void Tetris_Draw();     //描写    

void Tetris_Komaput();	//駒設置

void Tetris_Put();	//移動駒を配置駒に

void Tetris_Nextkoma(); //次の駒に変更、座標を初期値に

void Tetris_Dainyu();	//盤面に代入

void Tetris_Kousin();	//駒変更

void Tetris_Modosi();	//壁の外にいった場合、Tスピン等変な入れ方用

void Tetris_Ycount();	//Modosiで使う為の関数

void Tetris_Show();	//盤面表示

void Tetris_Fall();	//時間で駒落下

void Tetris_Delete();	//列消去,峯下作

void Tetris_Gameover();	//ゲームオーバー,峯下作

void Tetris_Hayasi();	//林GO

int Tetris_Koma(void);  //ランダム駒,林作

void Tetris_Syokika();  //初期化

void random_koma(int data[]); //林作

void Tetris_Effect();	//行消しエフェクト、峯下作

void Tetris_Score();    //スコア、峯下作

