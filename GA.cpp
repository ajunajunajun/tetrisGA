//ヘッダファイルに関数毎に作者記入、無記入は作鳥井

#include "DxLib.h"        
#include "Main.h"
#include "Tetris.h"
#include "GA.h"
#include "Keyboard.h"
#include "SceneMgr.h"

//色
static int Cr = GetColor(255,127,0);

//駒配列
static int GAkoma[7] = {1,2,3,4,5,6,7}; 

//外部変数
extern int xzahyo,yzahyo;
extern int Nowselect;
extern int kakudo;
extern int renzoku;
extern int s_count;
extern int ycount;
extern int kaiten;
extern int stage[22][12];
extern int nowkoma[4][4];
extern int stock[4][4];    
//次の駒
static int nextkoma=1;

//一回だけ関数を行う
static int onetime=0;

//ゲームオーバーになったら１
int gameover=1;


//駒の順番
int junban=0;

//エフェクト
static int EffectCount[4]={0,0,0,0};
static int DeleteLine=0;

//fps
extern int FPS;

//------------------------------------------------------------------------------
//遺伝子情報の長さ
int GENOM_LENGTH = 4000;
//遺伝子集団の大きさ
int MAX_GENOM_LIST = 65;
//遺伝子選択数
int SELECT_GENOM = 4;
//世代繰り返し数
// 260

//[遺伝子集団の大きさ][遺伝子情報の長さ]
int genome_list[65][4000];
//遺伝子選択リスト
int SELECT_GENOMLIST[4];

//move数で次個体へ
int nextfrag=0;
//個体選択
int kotaiselect=0;
//世代数
int generation=1;
//個体ナンバー
int kotai=0;
//評価の初期値
int hyouka=0;
//リスト選択
int selectlist[4000];
//評価リスト
int hyoukalist[66];
//動き数（遺伝子）
int move=0;
//評価終了したかのflag
int evaluation_finish=0;

//終わりかどうが
int finish=0;

	            
//初期リスト作成----------------------------------------------------------------
void GA_Initialize(){

	
	int i,j;
	int random_move;
        
	//0:下移動,1:左移動,2:右移動,3:左回転,4:右回転,5:ホールド
	for(i=0;i<MAX_GENOM_LIST;i++){
		for(j=0;j<GENOM_LENGTH;j++){
			random_move = GetRand(2);
			genome_list[i][j] = random_move;
		}
	}
}

//評価--------------------------------------------------------------------------
void GA_Evaluation(){
	int j=0;
	int *p;
	int genten=0;
	
	
		
	//順番に選択
	for(j=0;j<GENOM_LENGTH;j++){
		selectlist[j] = genome_list[kotaiselect][j];
	}
	p=&genten;
	
	//個体の価値算出
	Hyouka1(stage,p);
	Hyouka2(stage,p);
	hyouka3();
	Hyouka4(stage,p);
	Hyouka5(stage,p);
	Hyouka6(stage,p);

	hyouka += genten;

	//評価リストの先頭には初期値が入る(1づつずれている)
	hyoukalist[kotaiselect] = hyouka;
	
	hyouka=0;
	kotaiselect++;
	kotai++;
	
	//全ての個体評価終了したら
	if(kotaiselect==66){
		kotai=0;
		evaluation_finish=1;
	}
}

//デットスペースの数を数える関数------------------------------------------------
void Hyouka1(int data[22][12],int *DATA)
{

int i,j,k;//添え字

	for(i=1;i<11;i++){

		for(j=0;j<21;j++){

		if(data[j][i]==2 || data[j][i]==11 || data[j][i]==12 || data[j][i]==13 || data[j][i]==14 || data[j][i]==15 || data[j][i]==16){//2が見つかったらフラグを立てる
			k=1;
		}                                     
		if(k==1 && data[j][i]==0){//最初に見つかった2以降の0の数を数える
		(*DATA)-=30000;
		}

		}
	k=0;//フラグの初期化
	}
}

//突出した高低差を持つ列の数を数える関数----------------------------------------
void Hyouka2(int data[22][12],int *DATA)
{

int i,j;//添え字
int sum=0;

	for(i=1;i<11;i++){
	
		for(j=0;j<22;j++){ 
			if(data[j][i]==2 || data[j][i]==11 || data[j][i]==12 || data[j][i]==13 || data[j][i]==14 || data[j][i]==15 || data[j][i]==16){
				sum+=21-j;//列ごとの高さの合計
				break;
			}
		}
	}
	sum/=10;//列の高さの平均

	for(i=1;i<11;i++){
	
		for(j=0;j<22;j++){

			if(data[j][i]==2 || data[j][i]==11 || data[j][i]==12 || data[j][i]==13 || data[j][i]==14 || data[j][i]==15 || data[j][i]==16){

				if(sum+3<=21-j){//平均＋3以上の高さなら-1点
				(*DATA)-=10000;
				}
			   else if(sum-3>=21-j){//平均-3以下の高さなら-1点
				(*DATA)-=10000;
				}
				break;

			}
		}
	}
}
//高低差の合計和----------------------------------------------------------------
void hyouka3()
{

	int sum[10]={0,0,0,0,0,0,0,0,0,0},//積み上げられた高さ
	    def,//各列の右隣との高低差の合計和
	     count,i,j;
                           
	//各列の積み上げられた高さを調べる
	for(count=0,i=1;i<11;i++,count++){
	
		for(j=0;j<22;j++){

		if(stage[j][i]==2 || stage[j][i]==11 || stage[j][i]==12 || stage[j][i]==13 || stage[j][i]==14 || stage[j][i]==15 || stage[j][i]==16){
			sum[count]=21-j;//列ごとの高さの合計
			break;
		}
		}
	}
	

	//各列の右隣との高さの合計和を調べる
	for( count = 0 ; count < 9 ; count++){
		if( sum[count] > sum[count+1]){
			def = sum[count] - sum[count+1];
		}

		else{
			def = sum[count+1] - sum[count];
		}
		
		if(def==1){
		hyouka -= def*10;
		}
		if(def==2){
		hyouka -= def*15;
		}
		if(def==3){
		hyouka -= def*30;
		}
		if(def==4){
		hyouka -= def*50;
		}
		if(def>=5){
		hyouka -= def*100;
		}
	}	
}
//9個揃えた行を数える関数-------------------------------------------------------

void Hyouka4(int data[22][12],int *DATA)
{

int i,j;
int k;//減点する点数

	for(i=1;i<11;i++){
                
		for(j=0,k=0;j<21;j++,k+=10){

			if(data[j][i]==0){//配列の半分以下かつ中身が0の時
				(*DATA)-=k;//kだけ減点する
			}
		}

	}
}

//9個揃えた行を数える関数-------------------------------------------------------
void Hyouka5(int data[22][12],int *DATA)
{

int i,j;//添え字
int k;//揃っている数を入れる変数

	for(j=0;j<21;j++){

		for(i=1;i<11;i++){

			if(data[j][i]==2 || data[j][i]==11 || data[j][i]==12 || data[j][i]==13 || data[j][i]==14 || data[j][i]==15 || data[j][i]==16){
				k++;//何個揃っているか数える
			}
		}
			if(k==9){//9個揃っていたら
			(*DATA)+=200;//200点加点
			}
		k=0;//kを初期化
	}
}
//両端に置かせたい関数----------------------------------------------------------
void Hyouka6(int data[22][12],int *DATA)
{

	int i,j;//添え字
	int soezi[2]={1,10};//添え字

	for(i=0;i<4;i++){

		for(j=1;j<21;j++){

			if(data[j][soezi[i]]==2 || data[j][soezi[i]]==11 || data[j][soezi[i]]==12 || data[j][soezi[i]]==13 || data[j][soezi[i]]==14 || data[j][soezi[i]]==15 || data[j][soezi[i]]==16){
				if(i==0 || i==1){
					(*DATA)+=20;//1列目と10列目の時2点加点
					}
			}
		}
	}
}

//選択--------------------------------------------------------------------------
void GA_Select(){
	int i,j,k;
	int work;
	int work2[4000];

	//評価リストを降順にソート
	for(j=MAX_GENOM_LIST;j>0;j--){
		for(i=1;i<j;i++){
			if(hyoukalist[i]<hyoukalist[i+1]){
				work = hyoukalist[i];
				hyoukalist[i] = hyoukalist[i+1];
				hyoukalist[i+1] = work;
				
				for(k=0;k<GENOM_LENGTH;k++){	
					work2[k] = genome_list[i-1][k];
					genome_list[i-1][k] = genome_list[i][k];
					genome_list[i][k] = work2[k];
				}
				 
			}
		}
	}
	
}

//交叉?--------------------------------------------------------------------------
void GA_Crossover(){
	int i,j,m;
	int count;
	int cross;
	
	int random_gene;
	int randomgenelist[4000];
		
	//エリート数"i",親選択"m"
	for(i=5,m=0;i<=MAX_GENOM_LIST;i+=5,m=(m+1)%5){
		for(count=0;count<4;count++){
			for(j=0;j<GENOM_LENGTH;j++){
				random_gene = GetRand(3);
				randomgenelist[j] = random_gene;
			}
			for(j=0;j<GENOM_LENGTH;j++){
				//子供作成
				if(j<generation*15)
					genome_list[i+count][j] = genome_list[m][j];
				else if(j>=generation*15)
					genome_list[i+count][j] = randomgenelist[j];                  
			}
		}
	}		
}

//突然変異----------------------------------------------------------------------
void GA_Mutation(){

	static int i,j=0;
		
	//個体60~66の遺伝子にホールドを一つ加える
	for(i=60;i<66;i++)
		genome_list[i][(generation*15+60)%4000] = 5;

}

//------------------------------------------------------------------------------
void GA_Update(){

	//デバッグ用（スキップ）
	if(Keyboard_Get(KEY_INPUT_UP)==1){
		hyouka=-100000;
		gameover=1;
	}

}	

void GA_Draw(){
	int i,j;
	static int Font01 = CreateFontToHandle("メイリオ",25,7,DX_FONTTYPE_NORMAL);
	static int HandleB1=LoadGraph("B1.jpg",TRUE);
	static int HandleF=LoadGraph("framega1.png",TRUE);
	do{
		//はじめだけ
		if(onetime==0){
			GA_Initialize();
			onetime=1;	
	        }
		//gameoverになったら
	        if(gameover==1){
			GA_Evaluation();
			gameover=0;
			//リストが最後まで評価出来ていれば
			if(evaluation_finish==1){
				//選択
				GA_Select();
				GA_Crossover();
				GA_Mutation();
				GA_Reset();
			}
			GA_Syokika();
		}
		//評価リスト表示
		DrawGraph(0,0,HandleB1,TRUE);		
		DrawGraph(245,154,HandleF,TRUE);
		DrawFormatStringToHandle(0,30,Cr,Font01,"move:%d",move);
		DrawFormatStringToHandle(0,60,Cr,Font01,"kotai:%d",kotai);
		DrawFormatStringToHandle(0,90,Cr,Font01,"generation:%d",generation);
		for(i=0,j=0;i<66;i++){
			if(i==23)
				j=1;	
			if(i==45)
				j=2;	
			if(i!=0)
				DrawFormatStringToHandle(610+j*140,20+i*30-j*660,Cr,Font01,"%02d:%d",i,hyoukalist[i]);
		}

	        //リストが最後まで評価出来ていなければ                                   
		if(evaluation_finish==0){
			GA_Move();      	//elite配列の通り動かせる
			GA_Komaput();       //下埋まってた時に移動したら置く
			Tetris_Kousin();        //駒、角度を変更する
			GA_Nextkoma();      //次の駒に変更する
			GA_Delete();        //列揃ったら消す
			GA_Score();
			Tetris_Show();	        //ステージ、駒を表示する
			GA_Gameover();	//ゲームオーバー判定
	        }
		
		//おわり
		if(generation<=10)
			break;		 
		if(generation==260)
			break;
		if(generation>200)
			break;
		if(generation==261){                           
			WaitKey();
			break;
		}
		
		
	//描写スキップ、世代,評価リスト,最後	
	}while( generation%50!=0 || hyoukalist[20]!=0);
               
}         

void GA_Reset(){
	int i;

	kotaiselect=0;
	kotai=0;
	generation++;
	evaluation_finish=0;
	gameover=1;
	hyouka=-100000;		
		
			
	for(i=0;i<66;i++)
		hyoukalist[i] = 0;
	
}
void GA_Move(){
	static int x,y;
	static int i,j;
	static int stocknow;
	static int stocknowsub;
	static int stock_sub[4][4]={0,0,0,0,
	 		     0,0,0,0,
			     0,0,0,0,
			     0,0,0,0};			     
	
	//下移動
	if(selectlist[move]==0){
		yzahyo++;
	}
	//左移動
	if(selectlist[move]==1){
		xzahyo--;
		
		for(y=0;y<=3;y++){
			for(x=0;x<=3;x++){
				if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
					if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
					xzahyo++;
					}
				}	
			}
		}		

	}
	//右移動                                          	
	if(selectlist[move]==2){
		xzahyo++;

		for(y=0;y<=3;y++){
			for(x=0;x<=3;x++){
				if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
					if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
								xzahyo--;
					}
				}	
			}
		}		
	}
	//左回転
	if(selectlist[move]==3){
		kakudo=(kakudo+3)%4;
		kaiten=1;
	}
	//右回転
	if(selectlist[move]==4){
		kakudo=(kakudo+1)%4;
		kaiten=2;
	}
	//ホールド
	if(selectlist[move]==5){
		if(renzoku==0){
			kakudo=0;
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
	move++;
	//ゴール設定
	if(move==3999){
	}
	//世代毎の移動増分の値↓
	if(move== generation *15+100)
		nextfrag=1;
		
		
		
}

void GA_Delete(){

	int a,b,x,y,z,deletecount,aa=0;

	for(b=1,deletecount=0 ; b<=22; b++){
		for(a=1; a<=11 && (stage[b][a]==2 || stage[b][a]==11 || stage[b][a]==12 || stage[b][a]==13 || stage[b][a]==14 || stage[b][a]==15 || stage[b][a]==16); a++){
				if(a==10){			
			   	for(a=1;a<=10;a++){
    					stage[b][a]=0;
				}

				deletecount++;
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


	//一列消し
	if( deletecount == 1){
	hyouka+=2500;
	deletecount = 0;
	}//二列消し
	else if( deletecount == 2){
		hyouka+=7000;
		deletecount = 0;
	}//三列消し
	else if( deletecount == 3){
		hyouka+10000;
		deletecount = 0;
	}//四列消し
	else if( deletecount == 4){
		hyouka+=20000;
		deletecount = 0;
	}

}

void GA_Komaput(){
	//座標指定用
	static int x,y;

	//もし移動先が埋まってたら次の駒
	for(y=0;y<=3;y++){
		for(x=0;x<=3;x++){
			if(nowkoma[y][x]==1 || nowkoma[y][x]==5 || nowkoma[y][x]==6 || nowkoma[y][x]==7 || nowkoma[y][x]==8 || nowkoma[y][x]==9 || nowkoma[y][x]==10){
				if(stage[yzahyo+y][xzahyo+x]==2 || stage[yzahyo+y][xzahyo+x]==3 || stage[yzahyo+y][xzahyo+x]==11 || stage[yzahyo+y][xzahyo+x]==12 || stage[yzahyo+y][xzahyo+x]==13 || stage[yzahyo+y][xzahyo+x]==14 || stage[yzahyo+y][xzahyo+x]==15 || stage[yzahyo+y][xzahyo+x]==16){
						yzahyo--;
					GA_Put();
					nextkoma=1;
					renzoku=0;
				}
			}	
		}
	}		
	GA_Nextkoma();
}


void GA_Put(){
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


void GA_Nextkoma(){
	if(nextkoma==1){
		Nowselect=GAkoma[junban];
		junban = (junban+1)%7;
		yzahyo=0;
		xzahyo=4;
		kakudo=0;
		nextkoma=0;
	}
}

void GA_Gameover(){
	
	if(stage[2][4]==2 || stage[2][5]==2 || stage[2][6]==2 || stage[2][7]==2 || stage[2][4]==11 || stage[2][5]==11 || stage[2][6]==11 || stage[2][7]==11 || stage[2][4]==12 || stage[2][5]==12 || stage[2][6]==12 || stage[2][7]==12 || stage[2][4]==13 || stage[2][5]==13 || stage[2][6]==13 || stage[2][7]==13 || stage[2][4]==14 || stage[2][5]==14 || stage[2][6]==14 || stage[2][7]==14 || stage[2][4]==15 || stage[2][5]==15 || stage[2][6]==15 || stage[2][7]==15 || stage[2][4]==16 || stage[2][5]==16 || stage[2][6]==16 || stage[2][7]==16){
		gameover=1;	
		DeleteLine=0;	
	}	
	if(nextfrag==1){
		DeleteLine=0;	
		gameover=1;
	}
		
}

void GA_Score(){	
	static int Font01 = CreateFontToHandle("メイリオ",25,7,DX_FONTTYPE_NORMAL);
	DrawFormatStringToHandle(0,125,Cr,Font01,"DeleteLine  :    %d",DeleteLine);
}

                           
void GA_Syokika(){
	static int x,y;

	nextfrag=0;
	move=0;
	yzahyo=0;
	xzahyo=4;
	kakudo=0;
	junban=0;
	s_count=0;
	renzoku=0;
	nextkoma=1;
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
}
