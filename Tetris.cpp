//ヘッダファイルに関数毎に作者記入、無記入は作鳥井

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include "DxLib.h"
#include "Tetris.h"
#include "Keyboard.h"
#include "SceneMgr.h"

//ao色
static Cr = GetColor(0,255,255); //Iミノ
static Cr2 = GetColor(255,255,0);//Oミノ
static Cr3 = GetColor(255,0,255);//Tミノ
static Cr4 = GetColor(0,0,255); //Jミノ
static Cr5 = GetColor(255,127,0); //Lミノ
static Cr6 = GetColor(0,255,0);  //Sミノ
static Cr7 = GetColor(255,0,0); //Zミノ
static Cr8 = GetColor(0,0,0);//壁

extern int HandleV1;

//------------------------------------------------------------------------------



//どれだけ落ちてきているか  
int xzahyo=4,yzahyo=0;

//駒の形、駒の角度
int Nowselect=1;
int kakudo=0;

//stock作成用
int renzoku=0;
int s_count=0;


//落ちてくる駒
int a[7];
int b[7];

//駒の形変える時1にする。
int nextkoma=1;


//readygo owattaka
int readygo=0;
//yzahyo2マスカウント
static int ycount=0;

//駒の回転させない時用
int kaiten=0;
int Rcount=0;

//自由落下用
static int updatetime=0;
static int jikan=0;

//駒選択用
static int start=0;
static int Jcount=0;

//宣言部分
static int EffectCount[4]={0,0,0,0};
static int DeleteLine=0;
static int sokudoCount=0;
static int sokudo = 1000;
static int sokudolevel=1;

static int ScoreTime = GetNowCount();
static int time2[2];
static int Linetime[2];
static int ScoreTime2,ScoreTime3;



int stage[22][12]={3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,0,0,0,0,0,0,0,0,0,0,3,
		   3,3,3,3,3,3,3,3,3,3,3,3};

// 動かす駒
int nowkoma[4][4]={0,0,0,0,
	 	   0,0,0,0,
	           0,0,0,0,
		   0,0,0,0};


int koma1U[4][4]={0,0,0,0,
		  1,1,1,1,
		  0,0,0,0,
		  0,0,0,0};

int koma1R[4][4]={0,0,1,0,
		  0,0,1,0,
		  0,0,1,0,
		  0,0,1,0};

int koma1D[4][4]={0,0,0,0,
		  0,0,0,0,
		  1,1,1,1,
		  0,0,0,0};

int koma1L[4][4]={0,1,0,0,
		  0,1,0,0,
		  0,1,0,0,
		  0,1,0,0};

int koma2U[4][4]={0,0,0,0,
		  0,5,5,0,
		  0,5,5,0,
		  0,0,0,0};

int koma2R[4][4]={0,0,0,0,
		  0,5,5,0,
		  0,5,5,0,
		  0,0,0,0};

int koma2D[4][4]={0,0,0,0,
		  0,5,5,0,
		  0,5,5,0,
		  0,0,0,0};

int koma2L[4][4]={0,0,0,0,
		  0,5,5,0,
		  0,5,5,0,
		  0,0,0,0};

int koma3U[4][4]={0,0,0,0,
		  0,0,6,0,
		  0,6,6,6,
		  0,0,0,0};

int koma3R[4][4]={0,0,0,0,
		  0,0,6,0,
		  0,0,6,6,
		  0,0,6,0};

int koma3D[4][4]={0,0,0,0,
		  0,0,0,0,
		  0,6,6,6,
		  0,0,6,0};

int koma3L[4][4]={0,0,0,0,
		  0,0,6,0,
		  0,6,6,0,
		  0,0,6,0};

int koma4U[4][4]={0,0,0,0,
		  0,7,0,0,
		  0,7,7,7,
		  0,0,0,0};

int koma4R[4][4]={0,0,0,0,
		  0,0,7,7,
		  0,0,7,0,
		  0,0,7,0};

int koma4D[4][4]={0,0,0,0,
		  0,0,0,0,
		  0,7,7,7,
		  0,0,0,7};

int koma4L[4][4]={0,0,0,0,
		  0,0,7,0,
		  0,0,7,0,
		  0,7,7,0};

int koma5U[4][4]={0,0,0,0,
		  0,0,0,8,
		  0,8,8,8,
		  0,0,0,0};

int koma5R[4][4]={0,0,0,0,
		  0,0,8,0,
		  0,0,8,0,
		  0,0,8,8};

int koma5D[4][4]={0,0,0,0,
		  0,0,0,0,
		  0,8,8,8,
		  0,8,0,0};

int koma5L[4][4]={0,0,0,0,
		  0,8,8,0,
		  0,0,8,0,
		  0,0,8,0};

int koma6U[4][4]={0,0,0,0,
		  0,0,9,9,
		  0,9,9,0,
		  0,0,0,0};

int koma6R[4][4]={0,9,0,0,
		  0,9,9,0,
		  0,0,9,0,
		  0,0,0,0};

int koma6D[4][4]={0,0,0,0,
		  0,0,9,9,
		  0,9,9,0,
		  0,0,0,0};

int koma6L[4][4]={0,9,0,0,
		  0,9,9,0,
		  0,0,9,0,
		  0,0,0,0};

int koma7U[4][4]={0,0,0,0,
		  0,10,10,0,
		  0,0,10,10,
		  0,0,0,0};

int koma7R[4][4]={0,0,10,0,
		  0,10,10,0,
		  0,10,0,0,
		  0,0,0,0};

int koma7D[4][4]={0,0,0,0,
		  0,10,10,0,
		  0,0,10,10,
		  0,0,0,0};

int koma7L[4][4]={0,0,10,0,
		  0,10,10,0,
		  0,10,0,0,
		  0,0,0,0};

int stock[4][4]={0,0,0,0,
		 0,0,0,0,
		 0,0,0,0,
		 0,0,0,0};

//------------------------------------------------------------------------------
	int hairetu1[4][4]={0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0};
	int hairetu2[4][4]={0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0};
	int hairetu3[4][4]={0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0};
	int hairetu4[4][4]={0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0};
	int hairetu5[4][4]={0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0};
	int hairetu6[4][4]={0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0};


		 
//------------------------------------------------------------------------------

//操作
void Tetris_Update(){
	static int c,i,j,v,w,x,y,z=21;
	static int stocknow;
	static int stocknowsub;
			 
	static int stock_sub[4][4]={0,0,0,0,
	 		     0,0,0,0,
			     0,0,0,0,
			     0,0,0,0};

	if(Keyboard_Get(KEY_INPUT_ESCAPE)==1){
		SceneMgr_ChangeScene(eScene_Menu);
	}
	if(Keyboard_Get(KEY_INPUT_X)==1){	//Ｚキーの入力処理(左回転)
		kakudo=(kakudo+3)%4;
		kaiten=1;

	}
	if(Keyboard_Get(KEY_INPUT_Z)==1){	//Ｘキーの入力処理(右回転)
		kakudo=(kakudo+1)%4;
		kaiten=2;
	}
	if(Keyboard_Get(KEY_INPUT_UP)==1){	//十字キー「上」の入力処理
		for(c=0,y=0,z=21;c<=4 && y<=3;y++){
			for(x=0;c<=4 && x<=3;x++){
				if(nowkoma[y][x]!=0){
					i=nowkoma[y][x];
					c++;
					for(w=0,v=yzahyo;w==0;v++){
						if(stage[v+y][xzahyo+x]!=0 && stage[v+y][xzahyo+x]!=i){
							v--;
							if(z>v){
								z=v;
							}
							w=1;
						}
					}
				}
			}
		}
		if(c==4){
			yzahyo=z;
		}
		updatetime=1;
		jikan=GetNowCount();	
	}
	if((Keyboard_Get(KEY_INPUT_DOWN))%3==1){	//十字キー「下」の入力処理(加速)
		updatetime=0;
	}
	if((Keyboard_Get(KEY_INPUT_LEFT))%7==1){	//十字キー「左」の入力処理(左移動)
		xzahyo--;
		
		for(y=0;y<=3;y++){
			for(x=0;x<=3;x++){
				if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
					if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3  || stage[yzahyo+y][xzahyo+x]==11  || stage[yzahyo+y][xzahyo+x]==12  || stage[yzahyo+y][xzahyo+x]==13  || stage[yzahyo+y][xzahyo+x]==14  || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
						xzahyo++;
					}
				}	
			}
		}		

	}
	if((Keyboard_Get(KEY_INPUT_RIGHT))%7==1){	//十字キー「右」の入力処理(右移動)
		xzahyo++;

		for(y=0;y<=3;y++){
			for(x=0;x<=3;x++){
				if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
					if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3  || stage[yzahyo+y][xzahyo+x]==11  || stage[yzahyo+y][xzahyo+x]==12  || stage[yzahyo+y][xzahyo+x]==13  || stage[yzahyo+y][xzahyo+x]==14  || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
						xzahyo--;
					}
				}	
			}
		}		

	}
	if(Keyboard_Get(KEY_INPUT_LSHIFT)==1){	//左シフトキーの入力処理(ストック)
		if(renzoku==0){
			kakudo=0;	
			//駒更新
			Tetris_Dainyu();
			/* ストックが空の時 */
			if(s_count==0){
				for(i=0;i<=3;i++){
					for(j = 0 ; j <= 3 ; j++){
						stock[i][j] = nowkoma[i][j];
					}
				}
				stocknow=Nowselect;
				nextkoma=1;	
				s_count=1;
			}
                	/* ストックが入の時 */
			else{
				for(y=0;y<=3;y++){
					for(x=0;x<=3;x++){
						stock_sub[y][x] = nowkoma[y][x];
						nowkoma[y][x] = stock[y][x];
						stock[y][x] = stock_sub[y][x];
					}			
				}
				stocknowsub=Nowselect;	
				Nowselect=stocknow;
				stocknow=stocknowsub;
				Tetris_Kousin();
				yzahyo=0;
				xzahyo=4;
			}
			renzoku=1;
		}
	}

	/* nowkomaの予測線 */
/*	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(nowkoma[y][x]==1){
				for(c=0;yzahyo<=21 || c==0;yzahyo++){
					if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3){
						yzahyo--;
						stage[yzahyo+y][xzahyo+x]=4;
						c=1;
					}	
				}
			}
		}
	}
	//予測線
	if(stage[i+2][j]==4){
		DrawString(570+j*20,240+i*20,"〇",Cr);
	}
*/

}

	
//ゲーム本体（ここに追加してく）
void Tetris_Draw(){

        static int ikkai=0;
	static int HandleB1;
	static int HandleF;
	//枠表示
	if(ikkai==0){
		HandleF=LoadGraph("frame1.png",TRUE);
		ikkai++;
	}
	//背景
	DrawGraph(0,0,HandleV1,TRUE);
		
	DrawGraph(245,154,HandleF,TRUE);
	
	Tetris_Hayasi();
	
	if(readygo==1){

		Tetris_Koma();		//駒を配列に入れる
		
		Tetris_Fall();   	//時間で落とす
		Tetris_Komaput();       //下埋まってた時に移動したら置く
		Tetris_Kousin();        //駒、角度を変更する
		Tetris_Nextkoma();      //次の駒に変更する
		Tetris_Delete();        //列揃ったら消す
		Tetris_Effect();	//エフェクト
		Tetris_Score();		//スコア
		Tetris_Show();	        //ステージ、駒を表示する
		Tetris_Gameover();	//ゲームオーバー判定
	
	}

}

void Tetris_Komaput(){
	//座標指定用
	static int x,y;

	//もし移動先が埋まってたら次の駒
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
				if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
					yzahyo--;
					Tetris_Put();
					nextkoma=1;
					renzoku=0;
				}
			}	
		}
	}		
	Tetris_Nextkoma();
}

void Tetris_Put(){
	//座標指定用
	static int x,y;

	//移動中の駒を固定する
	for(y=0;y<=21;y++){
		for(x=0;x<=11;x++){
			if(stage[y][x]==1){	
				stage[y][x]=2;
			}
			if(stage[y][x]==5){	
				stage[y][x]=11;
			}
			if(stage[y][x]==6){	
				stage[y][x]=12;
			}
			if(stage[y][x]==7){	
				stage[y][x]=13;
			}
			if(stage[y][x]==8){	
				stage[y][x]=14;
			}
			if(stage[y][x]==9){	
				stage[y][x]=15;
			}
			if(stage[y][x]==10){	
				stage[y][x]=16;
			}
		}
	}
}

void Tetris_Nextkoma(){

	if(nextkoma==1){
		Nowselect=a[0];
		yzahyo=0;
		xzahyo=4;
		kakudo=0;
		Rcount=0;
		nextkoma=0;		
        }
}	



void Tetris_Dainyu(){
	//座標指定用
	static int x,y;
			
	//駒設定        
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			//駒選択
			switch(Nowselect){
				case 1:
					//角度選択、上右下左
					switch(kakudo){
						case 0:
							nowkoma[y][x]=koma1D[y][x];
							break;
						case 1:
							nowkoma[y][x]=koma1R[y][x];
							break;
						case 2:
							nowkoma[y][x]=koma1U[y][x];
							break;
						case 3:
							nowkoma[y][x]=koma1L[y][x];
							break;
					}
					break;
				case 2:
					switch(kakudo){
						case 0:
							nowkoma[y][x]=koma2D[y][x];
							break;
						case 1:
							nowkoma[y][x]=koma2R[y][x];
							break;
						case 2:
							nowkoma[y][x]=koma2U[y][x];
							break;
						case 3:
							nowkoma[y][x]=koma2L[y][x];
							break;
					}
					break;
				case 3:
					switch(kakudo){
						case 0:
							nowkoma[y][x]=koma3D[y][x];
							break;
						case 1:
							nowkoma[y][x]=koma3R[y][x];
							break;
						case 2:
							nowkoma[y][x]=koma3U[y][x];
							break;
						case 3:
							nowkoma[y][x]=koma3L[y][x];
							break;
					}
					break;
				case 4:
					switch(kakudo){
						case 0:
							nowkoma[y][x]=koma4D[y][x];
							break;
						case 1:
							nowkoma[y][x]=koma4R[y][x];
							break;
						case 2:
							nowkoma[y][x]=koma4U[y][x];
							break;
						case 3:
							nowkoma[y][x]=koma4L[y][x];
							break;
					}
					break;
				case 5:
					switch(kakudo){
						case 0:                   
							nowkoma[y][x]=koma5D[y][x];
							break;
						case 1:
							nowkoma[y][x]=koma5R[y][x];
							break;
						case 2:
							nowkoma[y][x]=koma5U[y][x];
							break;
						case 3:
							nowkoma[y][x]=koma5L[y][x];
							break;
					}
					break;
				case 6:
					switch(kakudo){
						case 0:
							nowkoma[y][x]=koma6D[y][x];
							break;
						case 1:
							nowkoma[y][x]=koma6R[y][x];
							break;
						case 2:
							nowkoma[y][x]=koma6U[y][x];
							break;
						case 3:
							nowkoma[y][x]=koma6L[y][x];
							break;
					}
					break;
				case 7:
					switch(kakudo){
						case 0:
							nowkoma[y][x]=koma7D[y][x];
							break;
						case 1:
							nowkoma[y][x]=koma7R[y][x];
							break;
						case 2:
							nowkoma[y][x]=koma7U[y][x];
							break;
						case 3:
							nowkoma[y][x]=koma7L[y][x];
							break;
					}
					break;
			}	
		}
	}	
}

void Tetris_Kousin(){
	//座標指定用
	static int x,y;

	//駒更新
	Tetris_Dainyu();
	//移動前駒消し			
	for(y=0;y<=21;y++){
		for(x=0;x<=11;x++){
			if(stage[y][x]==1 || stage[y][x]==5 || stage[y][x]==6 || stage[y][x]==7 || stage[y][x]==8 || stage[y][x]==9 || stage[y][x]==10){	
				stage[y][x]=0;
			}
		}
	}
	//移動先で駒再表示
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(stage[yzahyo+y][xzahyo+x]==0){	
				stage[yzahyo+y][xzahyo+x]=nowkoma[y][x];
			}
		}
	}

	//壁に埋まった場合	
	Tetris_Modosi();
	Tetris_Ycount();

	//移動前駒消し			
	for(y=0;y<=21;y++){
		for(x=0;x<=11;x++){
			if(stage[y][x]==1 || stage[y][x]==5 || stage[y][x]==6 || stage[y][x]==7 || stage[y][x]==8 || stage[y][x]==9 || stage[y][x]==10){	
				stage[y][x]=0;
			}
		}
	}
	//移動先で駒再表示
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(stage[yzahyo+y][xzahyo+x]==0){	
				stage[yzahyo+y][xzahyo+x]=nowkoma[y][x];
			}
		}
	}
}

void Tetris_Modosi(){
	//座標指定用
	static int x,y;

	//yzahyo戻す用
	static int modosi=0;
	
	//for文用
	static int idou=0;

	//もし移動先が埋まってた場合
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
				//左埋まってたら右へ1マス
				if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
					idou=1;
				}
			}
		}
	}
	if(idou==1){
		xzahyo++;
		idou=0;
	}
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
				//右埋まってたら左へ2マス
				if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
					idou=1;
				}
			}
		}	
        }
	if(idou==1){
		xzahyo-=2;
		idou=0;
	}
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
				//まだ埋まってたら右へ1マス下1マス
				if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
					idou=1;
				}
			}
		}
	}
	if(idou==1){
		xzahyo++;
		yzahyo++;
		idou=0;
	}
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
				//まだ埋まってたら右へ1マス
				if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
					idou=1;
				}
			}
		}
	}
	if(idou==1){
		xzahyo++;
		idou=0;
	}
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
				//まだ埋まってたら左へ2マス
				if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
					idou=1;
				}
			}
		}
	}
	if(idou==1){
		xzahyo-=2;
		idou=0;
	}
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
				//まだ埋まってたら右へ1マス下1マス
				if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
					idou=1;
				}
			}
		}
	}
	if(idou==1){
		xzahyo++;
		yzahyo++;
		idou=0;
	}
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
				//まだ埋まってたら右へ1マス
				if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
					idou=1;
				}
			}
		}
	}
	if(idou==1){
		xzahyo++;
		idou=0;
	}
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
				//まだ埋まってたら左へ2マス
				if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
					idou=1;
				}
			}
		}
	}
	if(idou==1){
		xzahyo-=2;
		idou=0;
	}
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
				//それでも埋まっていたら
				if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
					modosi=1;
				}
			}
		}
	}
	while(modosi==1){
		//元の場所の上でおける場所
		for(y=0;y<=3;y++){
			for(x=0;x<=3;x++){
				if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
					//それでも埋まっていたら
					if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
						idou=1;
					}
				}
			}
		}
		if(idou==1){
			yzahyo--;
			idou=0;
			ycount++;
		}
		else{
			//ループ抜ける
			modosi=0;  
		}
		
		if(ycount==1){
			//ループ抜ける
			modosi=0;
		}		
	}									
}

void Tetris_Ycount(){
	//2マス以上戻る場合回れなくする
	if(ycount==1){
		//countした分戻す
		yzahyo-=ycount;
		//最後にZ押したなら
		if(kaiten==1){
			kakudo=(kakudo+1)%4;	
		}
		//最後にX押したなら
		else if(kaiten==2){
			kakudo=(kakudo+3)%4;			
		}
		//カウント初期化
		kaiten=0;
		Tetris_Dainyu();
		Tetris_Modosi();
		ycount=0;
	}	
}

void Tetris_Show(){
	
	
	int hairetu1[4][4]={0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0};
	int hairetu2[4][4]={0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0};
	int hairetu3[4][4]={0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0};
	int hairetu4[4][4]={0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0};
	int hairetu5[4][4]={0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0};
	int hairetu6[4][4]={0,0,0,0,
			0,0,0,0,
			0,0,0,0,
			0,0,0,0};
			
	
	// i：縦、j：横
	static int i,j;
	//stage表示
	for(i=0;i<20;i++){   	
		for(j=0;j<12;j++){
			//移動中の駒
			if(stage[i+2][j]==1){
				DrawString(370+j*20,240+i*20,"■",Cr);
			}
			if(stage[i+2][j]==5){
				DrawString(370+j*20,240+i*20,"■",Cr2);
			}
			if(stage[i+2][j]==6){
				DrawString(370+j*20,240+i*20,"■",Cr3);
			}
			if(stage[i+2][j]==7){
				DrawString(370+j*20,240+i*20,"■",Cr4);
			}
			if(stage[i+2][j]==8){
				DrawString(370+j*20,240+i*20,"■",Cr5);
			}
			if(stage[i+2][j]==9){
				DrawString(370+j*20,240+i*20,"■",Cr6);
			}
			if(stage[i+2][j]==10){
				DrawString(370+j*20,240+i*20,"■",Cr7);
			}
			//止まってる駒  
			if(stage[i+2][j]==2){
				DrawString(370+j*20,240+i*20,"■",Cr);
			}
			if(stage[i+2][j]==11){
				DrawString(370+j*20,240+i*20,"■",Cr2);
			}
			if(stage[i+2][j]==12){
				DrawString(370+j*20,240+i*20,"■",Cr3);
			}
			if(stage[i+2][j]==13){
				DrawString(370+j*20,240+i*20,"■",Cr4);
			}
			if(stage[i+2][j]==14){
				DrawString(370+j*20,240+i*20,"■",Cr5);
			}
			if(stage[i+2][j]==15){
				DrawString(370+j*20,240+i*20,"■",Cr6);
			}
			if(stage[i+2][j]==16){
				DrawString(370+j*20,240+i*20,"■",Cr7);
			}
			//壁
/*			if(stage[i+2][j]==3){
				DrawString(370+j*20,240+i*20,"■",Cr8);
			}
*/		}
	}
	//stock表示
	for(i=0;i<=3;i++){
		for(j=0;j<=3;j++){
			if(stock[i][j]==1){
				DrawString(260+j*20,210+i*20,"■",Cr);
			}
			if(stock[i][j]==5){
				DrawString(260+j*20,220+i*20,"■",Cr2);
			}
			if(stock[i][j]==6){
				DrawString(250+j*20,200+i*20,"■",Cr3);
			}
			if(stock[i][j]==7){
				DrawString(250+j*20,200+i*20,"■",Cr4);
			}
			if(stock[i][j]==8){
				DrawString(250+j*20,200+i*20,"■",Cr5);
			}
			if(stock[i][j]==9){
				DrawString(250+j*20,220+i*20,"■",Cr6);
			}
			if(stock[i][j]==10){
				DrawString(250+j*20,220+i*20,"■",Cr7);
			}
		}
	}
	//次の駒表示の為の代入
	if(a[0]==1){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu1[i][j]=koma1D[i][j];
			}
		}
	}
	if(a[0]==2){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu1[i][j]=koma2D[i][j];
			}
		}
	}
	if(a[0]==3){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
			hairetu1[i][j]=koma3D[i][j];
			}
		}
	}
	if(a[0]==4){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu1[i][j]=koma4D[i][j];
			}
		}
	}
	if(a[0]==5){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu1[i][j]=koma5D[i][j];
			}
		}
	}
	if(a[0]==6){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu1[i][j]=koma6D[i][j];
			}
		}
	}
	if(a[0]==7){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu1[i][j]=koma7D[i][j];
			}
		}
	}
	if(a[1]==1){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu2[i][j]=koma1D[i][j];
			}
		}
	}
	if(a[1]==2){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu2[i][j]=koma2D[i][j];
			}
		}
	}
	if(a[1]==3){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu2[i][j]=koma3D[i][j];
			}
		}
	}
	if(a[1]==4){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu2[i][j]=koma4D[i][j];
			}
		}
	}
	if(a[1]==5){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu2[i][j]=koma5D[i][j];
			}
		}
	}
	if(a[1]==6){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu2[i][j]=koma6D[i][j];
			}
		}
	}
	if(a[1]==7){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu2[i][j]=koma7D[i][j];
			}
		}
	}
	if(a[2]==1){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu3[i][j]=koma1D[i][j];
			}
		}
	}
	if(a[2]==2){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu3[i][j]=koma2D[i][j];
			}
		}
	}
	if(a[2]==3){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu3[i][j]=koma3D[i][j];
			}
		}
	}
	if(a[2]==4){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu3[i][j]=koma4D[i][j];
			}
		}
	}
	if(a[2]==5){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu3[i][j]=koma5D[i][j];
			}
		}
	}
	if(a[2]==6){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu3[i][j]=koma6D[i][j];
			}
		}
	}
	if(a[2]==7){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu3[i][j]=koma7D[i][j];
			}
		}
	}
	if(a[3]==1){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu4[i][j]=koma1D[i][j];
			}
		}
	}
	if(a[3]==2){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu4[i][j]=koma2D[i][j];
			}
		}
	}
	if(a[3]==3){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu4[i][j]=koma3D[i][j];
			}
		}
	}
	if(a[3]==4){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu4[i][j]=koma4D[i][j];
			}
		}
	}
	if(a[3]==5){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu4[i][j]=koma5D[i][j];
			}
		}
	}
	if(a[3]==6){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu4[i][j]=koma6D[i][j];
			}
		}
	}
	if(a[3]==7){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu4[i][j]=koma7D[i][j];
			}
		}
	}
	if(a[4]==1){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu5[i][j]=koma1D[i][j];
			}
		}
	}
	if(a[4]==2){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu5[i][j]=koma2D[i][j];
			}
		}
	}
	if(a[4]==3){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu5[i][j]=koma3D[i][j];
			}
		}
	}
	if(a[4]==4){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu5[i][j]=koma4D[i][j];
			}
		}
	}
	if(a[4]==5){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu5[i][j]=koma5D[i][j];
			}
		}
	}
	if(a[4]==6){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu5[i][j]=koma6D[i][j];
			}
		}
	}
	if(a[4]==7){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu5[i][j]=koma7D[i][j];
			}
		}
	}
	if(a[5]==1){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu6[i][j]=koma1D[i][j];
			}
		}
	}
	if(a[5]==2){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu6[i][j]=koma2D[i][j];
			}
		}
	}
	if(a[5]==3){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu6[i][j]=koma3D[i][j];
			}
		}
	}
	if(a[5]==4){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu6[i][j]=koma4D[i][j];
			}
		}
	}
	if(a[5]==5){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu6[i][j]=koma5D[i][j];
			}
		}
	}
	if(a[5]==6){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu6[i][j]=koma6D[i][j];
			}
		}
	}
	if(a[5]==7){
		for(i=0;i<=3;i++){
			for(j=0;j<=3;j++){
				hairetu6[i][j]=koma7D[i][j];
			}
		}
	}
                     

	//次の駒表示
	for(i=0;i<=3;i++){
		for(j=0;j<=3;j++){
			if(hairetu1[i][j]==1){
				DrawString(648+j*20,150+i*20,"■",Cr);
			}
			if(hairetu1[i][j]==5){
				DrawString(650+j*20,165+i*20,"■",Cr2);
			}
			if(hairetu1[i][j]==6){
				DrawString(640+j*20,145+i*20,"■",Cr3);
			}
			if(hairetu1[i][j]==7){
				DrawString(640+j*20,145+i*20,"■",Cr4);
			}
			if(hairetu1[i][j]==8){
				DrawString(640+j*20,145+i*20,"■",Cr5);
			}
			if(hairetu1[i][j]==9){
				DrawString(640+j*20,165+i*20,"■",Cr6);
			}
			if(hairetu1[i][j]==10){
				DrawString(640+j*20,165+i*20,"■",Cr7);
			}
		}
	}
	for(i=0;i<=3;i++){
		for(j=0;j<=3;j++){
			if(hairetu2[i][j]==1){
				DrawString(648+j*20,235+i*20,"■",Cr);
			}
			if(hairetu2[i][j]==5){
				DrawString(650+j*20,250+i*20,"■",Cr2);
			}
			if(hairetu2[i][j]==6){
				DrawString(640+j*20,230+i*20,"■",Cr3);
			}
			if(hairetu2[i][j]==7){
				DrawString(640+j*20,230+i*20,"■",Cr4);
			}
			if(hairetu2[i][j]==8){
				DrawString(640+j*20,230+i*20,"■",Cr5);
			}
			if(hairetu2[i][j]==9){
				DrawString(640+j*20,250+i*20,"■",Cr6);
			}
			if(hairetu2[i][j]==10){
				DrawString(640+j*20,250+i*20,"■",Cr7);
			}
		}
	}
	for(i=0;i<=3;i++){
		for(j=0;j<=3;j++){
			if(hairetu3[i][j]==1){
				DrawString(648+j*20,320+i*20,"■",Cr);
			}
			if(hairetu3[i][j]==5){
				DrawString(650+j*20,335+i*20,"■",Cr2);
			}                           
			if(hairetu3[i][j]==6){
				DrawString(640+j*20,315+i*20,"■",Cr3);
			}
			if(hairetu3[i][j]==7){
				DrawString(640+j*20,315+i*20,"■",Cr4);
			}
			if(hairetu3[i][j]==8){
				DrawString(640+j*20,315+i*20,"■",Cr5);
			}                            
			if(hairetu3[i][j]==9){
				DrawString(640+j*20,335+i*20,"■",Cr6);
			}
			if(hairetu3[i][j]==10){
				DrawString(640+j*20,335+i*20,"■",Cr7);
			}                            
		}
	}
	for(i=0;i<=3;i++){
		for(j=0;j<=3;j++){
			if(hairetu4[i][j]==1){
				DrawString(648+j*20,410+i*20,"■",Cr);
			}
			if(hairetu4[i][j]==5){
				DrawString(650+j*20,420+i*20,"■",Cr2);
			}
			if(hairetu4[i][j]==6){
				DrawString(640+j*20,400+i*20,"■",Cr3);
			}
			if(hairetu4[i][j]==7){
				DrawString(640+j*20,400+i*20,"■",Cr4);
			}                           
			if(hairetu4[i][j]==8){
				DrawString(640+j*20,400+i*20,"■",Cr5);
			}
			if(hairetu4[i][j]==9){
				DrawString(640+j*20,420+i*20,"■",Cr6);
			}
			if(hairetu4[i][j]==10){
				DrawString(640+j*20,420+i*20,"■",Cr7);
			}                            
		}
	}
	for(i=0;i<=3;i++){
		for(j=0;j<=3;j++){
			if(hairetu5[i][j]==1){
				DrawString(648+j*20,490+i*20,"■",Cr);
			}
			if(hairetu5[i][j]==5){
				DrawString(650+j*20,510+i*20,"■",Cr2);
			}
			if(hairetu5[i][j]==6){
				DrawString(640+j*20,490+i*20,"■",Cr3);
			}
			if(hairetu5[i][j]==7){
				DrawString(640+j*20,490+i*20,"■",Cr4);
			}
			if(hairetu5[i][j]==8){
				DrawString(640+j*20,490+i*20,"■",Cr5);
			}                            
			if(hairetu5[i][j]==9){
				DrawString(640+j*20,510+i*20,"■",Cr6);
			}                            
			if(hairetu5[i][j]==10){
				DrawString(640+j*20,510+i*20,"■",Cr7);
			}
		}
	}
	for(i=0;i<=3;i++){
		for(j=0;j<=3;j++){
			if(hairetu6[i][j]==1){
				DrawString(648+j*20,580+i*20,"■",Cr);
			}
			if(hairetu6[i][j]==5){
				DrawString(650+j*20,595+i*20,"■",Cr2);
			}
			if(hairetu6[i][j]==6){
				DrawString(640+j*20,575+i*20,"■",Cr3);
			}                           
			if(hairetu6[i][j]==7){
				DrawString(640+j*20,575+i*20,"■",Cr4);
			}
			if(hairetu6[i][j]==8){       
				DrawString(640+j*20,575+i*20,"■",Cr5);
			}
			if(hairetu6[i][j]==9){
				DrawString(640+j*20,595+i*20,"■",Cr6);
			}
			if(hairetu6[i][j]==10){
				DrawString(640+j*20,595+i*20,"■",Cr7);
			}
		
		}         
	}
		
}

void Tetris_Fall(){
	//時間入手用,更新用
	static int jikan=0;
	
	if(updatetime==0){
		jikan=GetNowCount();
		yzahyo++;
		updatetime=1;
	}                                     
	
	if(DeleteLine >= 10 && DeleteLine <= 19){
		sokudo = 900;
		sokudolevel=2;
	}
	
	else if(DeleteLine >= 20 && DeleteLine <= 29){
		sokudo = 800;
		sokudolevel=3;
	}
	
	else if(DeleteLine >= 30 && DeleteLine <= 39){
		sokudo = 700;
		sokudolevel=4;
	}
	
	else if(DeleteLine >= 40 && DeleteLine <= 49){
		sokudo = 600;
		sokudolevel=5;
	}
	
	else if(DeleteLine >= 50 && DeleteLine <= 59){
		sokudo = 500;
		sokudolevel=6;
	}
	
	else if(DeleteLine >= 60 && DeleteLine <= 69){
		sokudo = 400;
		sokudolevel=7;
	}
	
	else if(DeleteLine >= 70 && DeleteLine <= 79){
		sokudo = 300;
		sokudolevel=8;
	}
	
	else if(DeleteLine >= 80 && DeleteLine <= 89){
		sokudo = 200;
		sokudolevel=9;
	}
	
	else if(DeleteLine >= 90 && DeleteLine <= 99){
		sokudo = 100;
		sokudolevel=10;
	}
	
	//時間指定、1500位がちょうどいい
	if(GetNowCount() - jikan > sokudo){
		updatetime=0;
	}
	
}



void Tetris_Delete(){
                                                                                                    
	int a,b,x,y,z,yoko=390,tate=240,aa=0;
	                  
	for(b=1; b<=22; b++){
		for(a=1; a<=11 && (stage[b][a]==2 || stage[b][a]==11 || stage[b][a]==12 || stage[b][a]==13 || stage[b][a]==14 || stage[b][a]==15  || stage[b][a]==16); a++){
			if (a==10){			
			   	for(a=1;a<=10;a++){
    					stage[b][a]=0;
				}	
				EffectCount[aa] = b;
				aa++;
				DeleteLine++;				
				for(y=b,z=y-1;y>0;y--,z--){
					for(x=0; x<=11 ;x++){
						stage[y][x]=stage[z][x];
					}
				}
			}
		}
	}
}

void Tetris_Effect(){
	static int n=1;                                                                                                                             
	static int image2[15];
	int starttime = 0 , starttime2 = 0 , starttime3 = 0 , starttime4 = 0;
	static int EffectCount0=0;
	static int EffectCount1=0;
	static int EffectCount2=0;
	static int EffectCount3=0;
	
	
        if(n){
		LoadDivGraph( "エフェクト.png" , 15 , 3, 5 , 40 , 40 , image2 ); // 画像の分割読み込み
		n--;
	}
	int EffectCoordinate[10]={380,400,420,440,460,480,500,520,540,560};
	int EffectCoordinate20=600;
	int EffectCoordinate19=580;
	int EffectCoordinate18=560;
	int EffectCoordinate17=540;
	int EffectCoordinate16=520;
	int EffectCoordinate15=500;
	int EffectCoordinate14=480;
	int EffectCoordinate13=460;
	int EffectCoordinate12=440;
	int EffectCoordinate11=420;
	int EffectCoordinate10=400;
	int EffectCoordinate9=380;
	int EffectCoordinate8=360;
	int EffectCoordinate7=340;
	int EffectCoordinate6=320;
	int EffectCoordinate5=300;
	int EffectCoordinate4=280;
	int EffectCoordinate3=260;
	int EffectCoordinate2=240;
	int EffectCoordinate1=220;
	
	
	
	
	if(EffectCount[0]!=0){
		if(EffectCount[0]==20){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate20, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate20, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate20, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate20, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate20, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate20, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate20, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate20, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate20, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate20, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==19){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate19, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate19, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate19, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate19, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate19, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate19, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate19, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate19, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate19, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate19, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==18){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate18, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate18, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate18, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate18, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate18, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate18, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate18, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate18, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate18, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate18, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
 			}
		}
		if(EffectCount[0]==17){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate17, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate17, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate17, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate17, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate17, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate17, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate17, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate17, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate17, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate17, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==16){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate16, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate16, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate16, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate16, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate16, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate16, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate16, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate16, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate16, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate16, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==15){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate15, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate15, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate15, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate15, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate15, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate15, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate15, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate15, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate15, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate15, image2[EffectCount0], TRUE);
				EffectCount0++;          
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==14){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate14, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate14, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate14, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate14, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate14, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate14, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate14, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate14, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate14, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate14, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==13){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate13, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate13, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate13, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate13, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate13, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate13, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate13, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate13, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate13, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate13, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==12){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate12, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate12, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate12, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate12, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate12, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate12, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate12, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate12, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate12, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate12, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==11){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate11, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate11, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate11, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate11, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate11, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate11, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate11, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate11, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate11, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate11, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==10){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate10, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate10, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate10, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate10, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate10, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate10, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate10, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate10, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate10, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate10, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==9){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate9, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate9, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate9, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate9, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate9, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate9, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate9, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate9, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate9, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate9, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==8){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate8, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate8, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate8, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate8, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate8, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate8, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate8, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate8, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate8, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate8, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==7){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate7, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate7, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate7, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate7, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate7, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate7, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate7, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate7, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate7, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate7, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==6){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate6, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate6, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate6, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate6, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate6, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate6, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate6, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate6, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate6, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate6, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==5){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate5, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate5, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate5, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate5, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate5, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate5, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate5, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate5, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate5, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate5, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==4){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate4, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate4, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate4, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate4, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate4, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate4, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate4, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate4, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate4, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate4, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==3){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate3, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate3, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate3, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate3, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate3, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate3, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate3, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate3, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate3, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate3, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==2){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate2, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate2, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate2, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate2, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate2, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate2, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate2, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate2, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate2, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate2, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		if(EffectCount[0]==1){
			if(GetNowCount() - starttime > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate1, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate1, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate1, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate1, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate1, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate1, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate1, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate1, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate1, image2[EffectCount0], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate1, image2[EffectCount0], TRUE);
				EffectCount0++;
				starttime = GetNowCount();
			}
		}
		 
	}
	
	if(EffectCount[1]!=0){
		if(EffectCount[1]==20){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate20, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate20, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate20, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate20, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate20, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate20, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate20, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate20, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate20, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate20, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==19){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate19, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate19, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate19, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate19, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate19, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate19, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate19, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate19, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate19, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate19, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==18){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate18, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate18, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate18, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate18, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate18, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate18, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate18, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate18, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate18, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate18, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==17){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate17, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate17, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate17, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate17, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate17, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate17, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate17, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate17, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate17, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate17, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==16){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate16, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate16, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate16, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate16, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate16, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate16, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate16, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate16, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate16, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate16, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==15){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate15, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate15, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate15, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate15, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate15, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate15, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate15, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate15, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate15, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate15, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==14){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate14, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate14, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate14, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate14, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate14, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate14, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate14, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate14, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate14, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate14, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==13){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate13, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate13, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate13, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate13, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate13, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate13, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate13, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate13, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate13, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate13, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==12){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate12, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate12, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate12, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate12, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate12, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate12, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate12, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate12, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate12, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate12, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==11){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate11, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate11, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate11, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate11, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate11, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate11, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate11, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate11, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate11, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate11, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==10){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate10, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate10, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate10, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate10, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate10, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate10, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate10, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate10, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate10, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate10, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==9){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate9, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate9, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate9, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate9, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate9, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate9, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate9, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate9, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate9, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate9, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==8){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate8, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate8, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate8, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate8, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate8, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate8, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate8, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate8, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate8, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate8, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==7){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate7, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate7, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate7, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate7, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate7, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate7, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate7, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate7, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate7, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate7, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==6){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate6, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate6, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate6, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate6, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate6, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate6, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate6, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate6, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate6, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate6, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==5){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate5, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate5, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate5, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate5, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate5, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate5, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate5, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate5, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate5, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate5, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==4){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate4, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate4, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate4, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate4, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate4, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate4, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate4, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate4, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate4, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate4, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==3){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate3, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate3, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate3, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate3, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate3, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate3, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate3, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate3, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate3, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate3, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==2){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate2, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate2, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate2, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate2, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate2, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate2, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate2, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate2, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate2, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate2, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		if(EffectCount[1]==1){
			if(GetNowCount() - starttime2 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate1, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate1, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate1, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate1, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate1, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate1, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate1, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate1, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate1, image2[EffectCount1], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate1, image2[EffectCount1], TRUE);
				EffectCount1++;
				starttime2 = GetNowCount();
			}
		}
		 
	}
	
	if(EffectCount[2]!=0){
		if(EffectCount[2]==20){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate20, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate20, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate20, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate20, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate20, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate20, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate20, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate20, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate20, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate20, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==19){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate19, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate19, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate19, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate19, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate19, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate19, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate19, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate19, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate19, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate19, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==18){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate18, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate18, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate18, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate18, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate18, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate18, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate18, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate18, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate18, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate18, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==17){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate17, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate17, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate17, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate17, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate17, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate17, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate17, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate17, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate17, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate17, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==16){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate16, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate16, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate16, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate16, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate16, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate16, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate16, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate16, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate16, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate16, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==15){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate15, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate15, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate15, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate15, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate15, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate15, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate15, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate15, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate15, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate15, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==14){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate14, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate14, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate14, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate14, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate14, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate14, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate14, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate14, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate14, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate14, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==13){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate13, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate13, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate13, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate13, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate13, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate13, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate13, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate13, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate13, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate13, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==12){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate12, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate12, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate12, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate12, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate12, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate12, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate12, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate12, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate12, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate12, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==11){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate11, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate11, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate11, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate11, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate11, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate11, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate11, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate11, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate11, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate11, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==10){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate10, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate10, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate10, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate10, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate10, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate10, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate10, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate10, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate10, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate10, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==9){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate9, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate9, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate9, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate9, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate9, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate9, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate9, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate9, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate9, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate9, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==8){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate8, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate8, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate8, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate8, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate8, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate8, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate8, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate8, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate8, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate8, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==7){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate7, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate7, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate7, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate7, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate7, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate7, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate7, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate7, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate7, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate7, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==6){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate6, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate6, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate6, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate6, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate6, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate6, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate6, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate6, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate6, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate6, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==5){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate5, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate5, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate5, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate5, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate5, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate5, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate5, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate5, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate5, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate5, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==4){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate4, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate4, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate4, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate4, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate4, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate4, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate4, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate4, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate4, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate4, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==3){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate3, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate3, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate3, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate3, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate3, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate3, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate3, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate3, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate3, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate3, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
			if(EffectCount[2]==2){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate2, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate2, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate2, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate2, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate2, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate2, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate2, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate2, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate2, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate2, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}                                    
		}
			if(EffectCount[2]==1){
			if(GetNowCount() - starttime3 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate1, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate1, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate1, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate1, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate1, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate1, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate1, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate1, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate1, image2[EffectCount2], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate1, image2[EffectCount2], TRUE);
				EffectCount2++;
				starttime3 = GetNowCount();
			}
		}
	}
	
	if(EffectCount[3]!=0){
		if(EffectCount[3]==20){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate20, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate20, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate20, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate20, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate20, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate20, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate20, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate20, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate20, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate20, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==19){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate19, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate19, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate19, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate19, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate19, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate19, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate19, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate19, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate19, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate19, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==18){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate18, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate18, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate18, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate18, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate18, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate18, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate18, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate18, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate18, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate18, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==17){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate17, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate17, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate17, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate17, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate17, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate17, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate17, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate17, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate17, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate17, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==16){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate16, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate16, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate16, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate16, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate16, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate16, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate16, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate16, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate16, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate16, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==15){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate15, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate15, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate15, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate15, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate15, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate15, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate15, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate15, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate15, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate15, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==14){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate14, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate14, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate14, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate14, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate14, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate14, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate14, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate14, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate14, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate14, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==13){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate13, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate13, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate13, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate13, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate13, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate13, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate13, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate13, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate13, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate13, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==12){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate12, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate12, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate12, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate12, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate12, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate12, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate12, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate12, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate12, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate12, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==11){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate11, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate11, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate11, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate11, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate11, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate11, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate11, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate11, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate11, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate11, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==10){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate10, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate10, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate10, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate10, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate10, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate10, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate10, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate10, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate10, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate10, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==9){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate9, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate9, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate9, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate9, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate9, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate9, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate9, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate9, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate9, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate9, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==8){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate8, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate8, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate8, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate8, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate8, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate8, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate8, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate8, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate8, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate8, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==7){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate7, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate7, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate7, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate7, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate7, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate7, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate7, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate7, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate7, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate7, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==6){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate6, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate6, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate6, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate6, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate6, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate6, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate6, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate6, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate6, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate6, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==5){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate5, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate5, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate5, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate5, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate5, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate5, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate5, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate5, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate5, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate5, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==4){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate4, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate4, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate4, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate4, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate4, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate4, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate4, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate4, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate4, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate4, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==3){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate3, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate3, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate3, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate3, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate3, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate3, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate3, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate3, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate3, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate3, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==2){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate2, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate2, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate2, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate2, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate2, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate2, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate2, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate2, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate2, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate2, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		if(EffectCount[3]==1){
			if(GetNowCount() - starttime4 > 1){
				DrawGraph( EffectCoordinate[0], EffectCoordinate1, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[1], EffectCoordinate1, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[2], EffectCoordinate1, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[3], EffectCoordinate1, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[4], EffectCoordinate1, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[5], EffectCoordinate1, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[6], EffectCoordinate1, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[7], EffectCoordinate1, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[8], EffectCoordinate1, image2[EffectCount3], TRUE);
				DrawGraph( EffectCoordinate[9], EffectCoordinate1, image2[EffectCount3], TRUE);
				EffectCount3++;
				starttime4 = GetNowCount();
			}
		}
		
		 
	}                                 
			
	if(EffectCount0 > 16 || EffectCount1 > 16 || EffectCount2 > 16 || EffectCount3 > 16){                                                          
		EffectCount[0]=0;
		EffectCount[1]=0;
		EffectCount[2]=0;
		EffectCount[3]=0;
		EffectCount0=0;
		EffectCount1=0;
		EffectCount2=0;
		EffectCount3=0;
	}
}																										
											
void Tetris_Gameover(){
	static int ikkai=0;
	int gameover_g,gameover_a,gameover_m,gameover_e,gameover_o,gameover_v,gameover_e2,gameover_r;//文字　GAMEOVER
	int continue_c,continue_o,continue_n,continue_t,continue_i,continue_n2,continue_u,continue_e;//文字　CONTINUE
	int quit_q,quit_u,quit_i,quit_t;//文字　QUIT
	int white;
	int Y[27]={0,0,0,0,0,0,0,0,-2,-4,-8,-4,-2,0,2,4,8,4,2,0,0,0,0,0,0,0,0};//文字Y座標変更用配列
	int A=7,B=0,C=0,D=0;//文字処理用変数
        int a=-30,b=-50,c=-70,d=-90,e=-110,f=-130,g=-150,h=-170;//gameover初期Y座標
	int i=0,j=0;//添え字
//文字画像を変数に格納-----------------------------------	
	
	if(stage[2][4]==2 || stage[2][5]==2 || stage[2][6]==2 || stage[2][7]==2 || stage[2][4]==11 || stage[2][5]==11 || stage[2][6]==11 || stage[2][7]==11 || stage[2][4]==12 || stage[2][5]==12 || stage[2][6]==12 || stage[2][7]==12 || stage[2][4]==13 || stage[2][5]==13 || stage[2][6]==13 || stage[2][7]==13 || stage[2][4]==14 || stage[2][5]==14 || stage[2][6]==14 || stage[2][7]==14 || stage[2][4]==15 || stage[2][5]==15 || stage[2][6]==15 || stage[2][7]==15 || stage[2][4]==16 || stage[2][5]==16 || stage[2][6]==16 || stage[2][7]==16){
//   	if(ikkai==0){
	gameover_g=LoadGraph("gameover/gameover_g.png");
	gameover_a=LoadGraph("gameover/gameover_a.png");
	gameover_m=LoadGraph("gameover/gameover_m.png");
	gameover_e=LoadGraph("gameover/gameover_e.png");
	gameover_o=LoadGraph("gameover/gameover_o.png");
	gameover_v=LoadGraph("gameover/gameover_v.png");
	gameover_e2=LoadGraph("gameover/gameover_e2.png");
	gameover_r=LoadGraph("gameover/gameover_r.png");
	
	continue_c=LoadGraph("gameover/continue_c.png");
	continue_o=LoadGraph("gameover/continue_o.png");
	continue_n=LoadGraph("gameover/continue_n.png");
	continue_t=LoadGraph("gameover/continue_t.png");
	continue_i=LoadGraph("gameover/continue_i.png");
	continue_n2=LoadGraph("gameover/continue_n2.png");
	continue_u=LoadGraph("gameover/continue_u.png");
	continue_e=LoadGraph("gameover/continue_e.png");
	
	quit_q=LoadGraph("gameover/quit_q.png");
	quit_u=LoadGraph("gameover/quit_u.png");
	quit_i=LoadGraph("gameover/quit_i.png");
	quit_t=LoadGraph("gameover/quit_t.png");

	white=LoadGraph("gameover/white.png");
	
//	ikkai++;
//	}

	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){

	SetDrawBlendMode(DX_BLENDMODE_ALPHA,128);
	DrawGraph(0,0,white,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	
//文字表示処理---------------------------------	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,i);
	DrawGraph(0,-50+a,gameover_g,TRUE);
	DrawGraph(0,-50+b,gameover_a,TRUE);
	DrawGraph(0,-50+c,gameover_m,TRUE);
	DrawGraph(0,-50+d,gameover_e,TRUE);
	DrawGraph(0,-50+e,gameover_o,TRUE);
	DrawGraph(0,-50+f,gameover_v,TRUE);
	DrawGraph(0,-50+g,gameover_e2,TRUE);
	DrawGraph(0,-50+h,gameover_r,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
        if(a<=0){
        a+=2;
        }
	if(b<=0){
        b+=2;
        }
	if(c<=0){
        c+=2;
        }
	if(d<=0){
        d+=2;
        }
	if(e<=0){
        e+=2;
        }
	if(f<=0){
        f+=2;
        }
	if(g<=0){
        g+=2;
        }
	if(h<=0){
        h+=2;
        }
	i+=2;
	
	if(h>=0){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,j);
       	if (CheckHitKey(KEY_INPUT_UP)==1 && C>0 && D>=10){
		C-=1;
		D=0;
	}
	if (CheckHitKey(KEY_INPUT_DOWN)==1 && C<1 && D>=10){
		C+=1;
		D=0;
	}

        if(C!=0){
	DrawGraph(0,-50,continue_c,TRUE);
	DrawGraph(0,-50,continue_o,TRUE);
	DrawGraph(0,-50,continue_n,TRUE);
	DrawGraph(0,-50,continue_t,TRUE);
	DrawGraph(0,-50,continue_i,TRUE);
	DrawGraph(0,-50,continue_n2,TRUE);
	DrawGraph(0,-50,continue_u,TRUE);
	DrawGraph(0,-50,continue_e,TRUE);
	}	
	if(C==0){
        DrawGraph(0,-50+Y[A],continue_c,TRUE);
	DrawGraph(0,-50+Y[A-1],continue_o,TRUE);
	DrawGraph(0,-50+Y[A-2],continue_n,TRUE);
	DrawGraph(0,-50+Y[A-3],continue_t,TRUE);
	DrawGraph(0,-50+Y[A-4],continue_i,TRUE);
	DrawGraph(0,-50+Y[A-5],continue_n2,TRUE);
	DrawGraph(0,-50+Y[A-6],continue_u,TRUE);
	DrawGraph(0,-50+Y[A-7],continue_e,TRUE);
		if(A<=27&&B==3){   
		  A++;
		  }
		if(A>=27){
		  A=7; 
		  }
	}	  
		     
	if(C!=1){	  
	DrawGraph(0,-50,quit_q,TRUE);
        DrawGraph(0,-50,quit_u,TRUE);
        DrawGraph(0,-50,quit_i,TRUE);
	DrawGraph(0,-50,quit_t,TRUE);
	}
	if(C==1){	  
	DrawGraph(0,-50+Y[A],quit_q,TRUE);
        DrawGraph(0,-50+Y[A-1],quit_u,TRUE);
        DrawGraph(0,-50+Y[A-2],quit_i,TRUE);
	DrawGraph(0,-50+Y[A-3],quit_t,TRUE);
		if(A<=23&&B==3){   
		  A++;
		 }
		if(A>=23){
		  A=7;
		}   
	}
		  D++;
	
		if(B==3){
		  B=0;
		}   
		  B++;
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	j+=3;
	}	  

//ESCAPEキーで終了-----------------------------	
	if (CheckHitKey(KEY_INPUT_RETURN)==1){
	        if(C==0){
			Tetris_Syokika();
			break;
		}	
		if(C==1){
			SceneMgr_ChangeScene(eScene_Menu);
			break;
		}
	
	}
	
	}
	
	}	
		
}


void Tetris_Hayasi(){
	static int ready,go;
	static int i,j,m=255,n=0;
	static double k=1.0;
	static int ikkai=0;
	
	if(ikkai==0){
		ready=LoadGraph("ready_go/ready.png");
		go=LoadGraph("ready_go/go.png");
		ikkai++;
	}
	
	if(j<=100){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,i);
	DrawGraph(0,100+j,ready,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		if(i<=255){
			i+=4;
		}
	    j+=2;
	}
	
	
	if(j!=0){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,i);
	DrawGraph(0,100+j,ready,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
		if(i>=0){
			i-=2;
		}
	}
	
	if(i<=0&&k<=1.8){
	
	DrawRotaGraph(535,400,k,0.0,go,TRUE);
	
		if(k<=1.8){
		k+=0.1;
		}
		if(n==6){
		k-=0.4;
		}
		n++;		
	}
	
	if(k>=1.8&&m>=0){
	 SetDrawBlendMode(DX_BLENDMODE_ALPHA,m);
         DrawRotaGraph(535,400,k,0.0,go,TRUE);
	 SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	 m-=5;
	}
	if(m<=0)
		readygo=1;
}

int Tetris_Koma(void)
{

static int i,j=0;

static int w[1]={0};

if(Rcount==0){
	if(start==0){
		random_koma(a);
		Sleep(1000);
		random_koma(b);
	}
	
	for(i=0;start==1&&i<7;i++){
		a[i-1]=a[i];		
	}
	if(start==0){
		start=1;
	}
	else{
			a[6]=b[j];
			j++;
	}

	if(j==7){
		random_koma(b);
		j=0;
	}

	Rcount=1;
}
	return 0;
}

//---------------------------------
void random_koma(int data[])
{

int random_koma[7]={1,2,3,4,5,6,7};
int a;
int b=7;
int c;
int i;

	srand(time(NULL));

for(i=0;i<7;i++){

	a=rand();

	a%=b;

	c=random_koma[a];

	random_koma[a]=random_koma[b-1];

	b--;

	data[i]=c;
}

}


//これもある程度追加
void Tetris_Syokika(){
	static int x,y;
	
	yzahyo=0;
	xzahyo=4;
	kakudo=0;
	s_count=0;
	renzoku=0;
	Rcount=0;
	Jcount=0;
	start=0;
	nextkoma=1;
	DeleteLine=0;
	sokudoCount=0;
	sokudo = 1000;
	sokudolevel=1;
	ScoreTime = GetNowCount();
	ScoreTime2=0;
	ScoreTime3=0;
	
	for(x=0; x<2 ; x++){
		time2[x]=0;
	}
	
	for(x=0 ; x<2 ; x++){
		Linetime[x]=0;
	}
	
	for(y=0;y<4;y++){
		for(x=0;x<4;x++){
			stock[y][x]=0;
		}
	}
	for(y=0;y<21;y++){
		for(x=0;x<10;x++){
		stage[y][x+1]=0;
		}
	}
	for(y=0;y<4;y++){
		for(x=0;x<4;x++){
			hairetu1[y][x]=0;
			hairetu2[y][x]=0;
			hairetu3[y][x]=0;
			hairetu4[y][x]=0;
			hairetu5[y][x]=0;
			hairetu6[y][x]=0;
		}
	}

	for(y=0;y<7;y++){
		a[y]=0;
		b[y]=0;
	}

}                                                                        

//新規追加
void Tetris_Score(){
	static int aCount=1;
	static int n=1;
	
	
	ScoreTime2 = ((GetNowCount() - ScoreTime));
	ScoreTime3 = ((GetNowCount() - ScoreTime));
	
		
	ScoreTime2 /= 10;
	time2[0] = (ScoreTime2%100);
	ScoreTime2 /= 100;
	
        ScoreTime3 /= 1000;
	time2[1] = (ScoreTime3);
	
	
	if(DeleteLine >= 40 && aCount==1){
		Linetime[0] = time2[0];
		Linetime[1] = time2[1];
		aCount=0;
	}
	
//	SetFontSize(20);	
	DrawFormatString(0,100,Cr7,"playtime    :    %02d",time2[1]);
	DrawFormatString(190,100,Cr7,": %02d",time2[0]);
	
	DrawFormatString(0,120,Cr3,"40DeleteLine:    %02d",Linetime[1]);
	DrawFormatString(190,120,Cr3,": %02d",Linetime[0]);
	DrawFormatString(0,60,Cr5,"DeleteLine  :    %d",DeleteLine);
	DrawFormatString(0,80,Cr6,"SpeedLevel  :    %d",sokudolevel);
  
}
