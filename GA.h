#pragma once

//---------------------------------------

void GA_Initialize();	//初期設定

void GA_Evaluation();	//価値算出
void Hyouka1(int data[22][12],int *DATA);
void Hyouka2(int data[22][12],int *DATA);
void hyouka3();
void Hyouka4(int data[22][12],int *DATA);//デットスペースの数を数える関数
void Hyouka5(int data[22][12],int *DATA);//9個揃えた行を数える関数
void Hyouka6(int data[22][12],int *DATA);//両端に置かせたい関数



void GA_Select();	//選択

void GA_Crossover();	//交叉

void GA_Mutation();	//突然変異

//----------------------------------------
void GA_Update();	//更新

void GA_Draw();		//描写

void GA_Reset();	//世代変更のための再設定

void GA_Move();         //リストに沿って動かす

void GA_Delete();       //行消し、峯下作

void GA_Komaput();      //下埋まってたら置く

void GA_Put();          //置く

void GA_Nextkoma();     //次の駒

void GA_Gameover();	//ゲームオーバー

void GA_Score();        //スコア描写、峯下作

void GA_Syokika();	//初期化
