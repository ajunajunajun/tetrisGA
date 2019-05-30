//ヘッダファイルに関数毎に作者記入、無記入は作鳥井

#include "DxLib.h" 
#include "Main.h"
#include "Title.h"
#include "Tetris.h"
#include "GA.h"
#include "Keyboard.h"
#include "SceneMgr.h"

static Cr = GetColor(255,255,255);

	
void Title_Draw(){
	
	Title_Hayasi();
	
}

void Title_Hayasi(){
        int X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21;//ランダム座標変数
	int Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8,Y9,Y10,Y11,Y12,Y13,Y14,Y15,Y16,Y17,Y18,Y19,Y20,Y21;//ランダム座標変数
	int i1=0,i2=0,i3=0,j1=0,j2=0,j3=0,j4=0,j5=0,l1=0,l2=0,l3=0,l4=0,l5=0,l6=0,t1=0,t2=0,s1=0;//タイトルミノ移動用変数
	int I1,I2,I3,I4,J1,J2,J3,J4,L1,L2,L3,L4,T1,T2,T3,T4,O1,O2,O3,O4,Z1,Z2,Z3,Z4,S1,S2,S3,S4;//背景ミノ画像用変数
	int Imino,J1mino,J2mino,J3mino,J4mino,L1mino,L2mino,L3mino,L4mino,Tmino,Smino;//タイトルミノ画像用変数
	int back;//ぼかしフレーム画像用変数
	int start,count=0,COUNT=1;//スタート画像用変数
	double a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,i=0,j=0,k=0,l=0,m=0,n=0,o=0,p=0,q=0,r=0,s=0,t=0,u=0;//背景ミノ移動用変数
	
//背景ミノ画像を変数に格納-----------------------
	I1=LoadGraph("tetris_image/i1.png");
	I2=LoadGraph("tetris_image/i2.png");
	I3=LoadGraph("tetris_image/i3.png");
	I4=LoadGraph("tetris_image/i4.png");
	
	J1=LoadGraph("tetris_image/j1.png");
	J2=LoadGraph("tetris_image/j2.png");
	J3=LoadGraph("tetris_image/j3.png");
	J4=LoadGraph("tetris_image/j4.png");
	
	L1=LoadGraph("tetris_image/l1.png");
	L2=LoadGraph("tetris_image/l2.png");
	L3=LoadGraph("tetris_image/l3.png");
	L4=LoadGraph("tetris_image/l4.png");
	
	T1=LoadGraph("tetris_image/t1.png");
	T2=LoadGraph("tetris_image/t2.png");
	T3=LoadGraph("tetris_image/t3.png");
	T4=LoadGraph("tetris_image/t4.png");
	
	O1=LoadGraph("tetris_image/o1.png");
	O2=LoadGraph("tetris_image/o2.png");
	O3=LoadGraph("tetris_image/o3.png");
	O4=LoadGraph("tetris_image/o4.png");
	
	Z1=LoadGraph("tetris_image/z1.png");
	Z2=LoadGraph("tetris_image/z2.png");
	Z3=LoadGraph("tetris_image/z3.png");
	Z4=LoadGraph("tetris_image/z4.png");
	
	S1=LoadGraph("tetris_image/s1.png");
	S2=LoadGraph("tetris_image/s2.png");
	S3=LoadGraph("tetris_image/s3.png");
	S4=LoadGraph("tetris_image/s4.png");
	
//タイトルミノ画像を変数に格納----------------------------	
	Imino=LoadGraph("tetris_image/I_mino.png");
	
	J1mino=LoadGraph("tetris_image/J_mino1.png");
	J2mino=LoadGraph("tetris_image/J_mino2.png");
	J3mino=LoadGraph("tetris_image/J_mino3.png");
	J4mino=LoadGraph("tetris_image/J_mino4.png");
	
	L1mino=LoadGraph("tetris_image/L_mino1.png");
	L2mino=LoadGraph("tetris_image/L_mino2.png");
	L3mino=LoadGraph("tetris_image/L_mino3.png");
	L4mino=LoadGraph("tetris_image/L_mino4.png");
	
	Tmino=LoadGraph("tetris_image/T_mino.png");
		
	Smino=LoadGraph("tetris_image/S_mino.png");
	
//背景ぼかしフレーム画像を変数に格納---------------------
	back=LoadGraph("tetris_image/back.png");
	
//スタート画像を変数に格納-------------------------------	
	start=LoadGraph("tetris_image/start.png");
	
//ランダムなX座標を獲得----------------------------------	           
	X1=GetRand(874);
	X2=GetRand(874);
	X3=GetRand(874);
	X4=GetRand(874);
	X5=GetRand(874);
	X6=GetRand(874);
	X7=GetRand(874);
	X8=GetRand(874);
	X9=GetRand(874);
	X10=GetRand(874);
	X11=GetRand(874);
	X12=GetRand(874);
	X13=GetRand(874);
	X14=GetRand(874);
	X15=GetRand(874);
	X16=GetRand(874);
	X17=GetRand(874);
	X18=GetRand(874);
	X19=GetRand(874);
	X20=GetRand(874);
	X21=GetRand(874);
	
//ランダムなY座標獲得--------------------------	
	Y1=GetRand(786);
	Y2=GetRand(786);
	Y3=GetRand(786);
	Y4=GetRand(786);
	Y5=GetRand(786);
	Y6=GetRand(786);
	Y7=GetRand(786);
	Y8=GetRand(786);
	Y9=GetRand(786);
	Y10=GetRand(786);
	Y11=GetRand(786);
	Y12=GetRand(786);
	Y13=GetRand(786);
	Y14=GetRand(786);
	Y15=GetRand(786);
	Y16=GetRand(786);
	Y17=GetRand(786);
	Y18=GetRand(786);
	Y19=GetRand(786);
	Y20=GetRand(786);
	Y21=GetRand(786);
                 
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 ){
	
		Wait();		//待機
		Update();	//更新
		Draw();		//描画

        	Keyboard_Update();
//背景を流れるミノ-------------------------------

	//1
	if(a==Y1+786+100){
	X1=GetRand(874);
	Y1=GetRand(786);
	a=0;
	}
	DrawGraph(30+X1,-Y1+a-100,I1,TRUE);
	a++;

	if(b==Y2+786+100){
	X2=GetRand(874);
	Y2=GetRand(786);
	b=0;
	}
	DrawGraph(30+X2,-Y2+b-100,O1,TRUE);
	b++;
	
	if(c==Y3+786+100){
	X3=GetRand(874);
	Y3=GetRand(786);
	c=0;
	}	
	DrawGraph(30+X3,-Y3+c-100,T1,TRUE);
	c++;
	
	if(d==Y4+786+100){
	X4=GetRand(874);
	Y4=GetRand(786);
	d=0;
	}
	DrawGraph(30+X4,-Y4+d-100,L1,TRUE);
	d++;
	
	if(e==Y5+786+100){
	X5=GetRand(974);
	Y5=GetRand(786);
	e=0;
	}
	DrawGraph(30+X5,-Y5+e-100,J1,TRUE);
	e++;
	
	if(f==Y6+786+100){
	X6=GetRand(874);
	Y6=GetRand(786);
	f=0;
	}
	DrawGraph(30+X6,-Y6+f-100,Z1,TRUE);
	f++;
	
	if(g==Y7+786+100){
	X7=GetRand(874);
	Y7=GetRand(786);
	g=0;
	}
	DrawGraph(30+X7,-Y7+g-100,S1,TRUE);
	g++;
	
	//2
	if(h>=Y8+786+100){
	X8=GetRand(874);
	Y8=GetRand(786);
	h=0;
	}
	DrawGraph(30+X8,-Y8+h-100,I2,TRUE);
	h+=1.5;
	
	if(i>=Y9+786+100){
	X9=GetRand(874);
	Y9=GetRand(786);
	i=0;
	}
	DrawGraph(30+X9,-Y9+i-100,O2,TRUE);
	i+=1.5;
	
	if(j>=Y10+786+100){
	X10=GetRand(874);
	Y10=GetRand(786);
	j=0;
	}
	DrawGraph(30+X10,-Y10+j-100,T2,TRUE);
	j+=1.5;
	
	if(k>=Y11+786+100){
	X11=GetRand(874);
	Y11=GetRand(786);
	k=0;
	}
	DrawGraph(30+X11,-Y11+k-100,L2,TRUE);
	k+=1.5;
	
	if(l>=Y12+786+100){
	X12=GetRand(874);
	Y12=GetRand(786);
	l=0;
	}
	DrawGraph(30+X12,-Y12+l-100,J2,TRUE);
	l+=1.5;
	
	if(m>=Y13+786+100){
	X13=GetRand(874);
	Y13=GetRand(786);
	m=0;
	}
	DrawGraph(30+X13,-Y13+m-100,Z2,TRUE);
	m+=1.5;

	if(n>=Y14+786+100){
	X14=GetRand(874);
	Y14=GetRand(786);
	n=0;
	}
	DrawGraph(30+X14,-Y14+n-100,S2,TRUE);
	n+=1.5;

	//3
	if(n>=Y14+786+100){
	X14=GetRand(874);
	Y14=GetRand(786);
	n=0;
	}
	DrawGraph(30+X15,-Y15+o-100,I3,TRUE);
	o+=2;
	
	if(p>=Y16+786+100){
	X16=GetRand(874);
	Y16=GetRand(786);
	p=0;
	}
	DrawGraph(30+X16,-Y16+p-100,O3,TRUE);
	p+=2;
	
	if(q>=Y17+786+100){
	X17=GetRand(874);
	Y17=GetRand(786);
	q=0;
	}
	DrawGraph(30+X17,-Y17+q-100,T3,TRUE);
	q+=2;
	
	if(r>=Y18+786+100){
	X18=GetRand(874);
	Y18=GetRand(786);
	r=0;
	}
	DrawGraph(30+X18,-Y18+r-100,L3,TRUE);
	r+=2;
	
	if(s>=Y19+786+100){
	X19=GetRand(874);
	Y19=GetRand(786);
	s=0;
	}
	DrawGraph(30+X19,-Y19+s-100,J3,TRUE);
	s+=2;
	
	if(t>=Y20+786+100){
	X20=GetRand(874);
	Y20=GetRand(786);
	t=0;
	}
	DrawGraph(30+X20,-Y20+t-100,Z3,TRUE);
	t+=2;
	
	if(u>=Y21+786+100){
	X21=GetRand(874);
	Y21=GetRand(786);
	u=0;
	}
	DrawGraph(30+X21,-Y21+u-100,S3,TRUE);
        u+=2;
	
//タイトル表示----------------------------------------

        //1
	if(i1<=394){
	DrawGraph(425,-200+i1,Imino,TRUE);
        i1++;
	}
	if(i1>=394){
	DrawGraph(425,-200+i1,Imino,TRUE);
	}

	if(j1<=449){
	DrawGraph(717,-200+j1,J4mino,TRUE);
        j1++;
	}
	if(j1>=449){
	DrawGraph(717,-200+j1,J4mino,TRUE);
	}
	
	//2
	if(j2<=648){
	DrawGraph(262,-400+j2,J4mino,TRUE);
        j2++;
	}
	if(j2>=648){
	DrawGraph(262,-400+j2,J4mino,TRUE);
	}
	
	if(s1<=628){
	DrawGraph(517,-400+s1,Smino,TRUE);
        s1++;
	}   
	if(s1>=628){
	DrawGraph(517,-400+s1,Smino,TRUE);
	}
	
	if(l1<=625){
	DrawGraph(753,-400+l1,L4mino,TRUE);
        l1++;
	}
	if(l1>=625){
	DrawGraph(753,-400+l1,L4mino,TRUE);
	}	
	
	 //3
	if(l2<=796){
	DrawGraph(272,-600+l2,L1mino,TRUE);
        l2++;
	}
	if(l2>=796){
	DrawGraph(272,-600+l2,L1mino,TRUE);
	}
	
	if(l3<=765){
	DrawGraph(510,-600+l3,L2mino,TRUE);
        l3++;
	}
	if(l3>=765){
	DrawGraph(510,-600+l3,L2mino,TRUE);
	}
	
	if(l4<=734){
	DrawGraph(678,-600+l4,L3mino,TRUE);
        l4++;
	}
	if(l4>=734){
	DrawGraph(678,-600l+l4,L3mino,TRUE);
	}
	
	if(i2<=794){
	DrawGraph(121,-600+i2,Imino,TRUE);
        i2++;
	}
	if(i2>=794){
	DrawGraph(121,-600l+i2,Imino,TRUE);
	}
	
	if(i3<=794){
	DrawGraph(342,-600+i3,Imino,TRUE);
        i3++;
	}
	if(i3>=794){
	DrawGraph(342,-600l+i3,Imino,TRUE);
	}
	
	if(j3<=828){
	DrawGraph(605,-600+j3,J3mino,TRUE);
        j3++;
	}
	if(j3>=828){
	DrawGraph(605,-600l+j3,J3mino,TRUE);
	}
	
	//4
	if(t1<=935){
	DrawGraph(155,-800+t1,Tmino,TRUE);
        t1++;
	}
	if(t1>=935){
	DrawGraph(155,-800l+t1,Tmino,TRUE);
	}
	
	if(l5<=943){          
	DrawGraph(272,-800+l5,L1mino,TRUE);
        l5++;
	}
	if(l5>=943){
	DrawGraph(272,-800l+l5,L1mino,TRUE);
	}
	
	if(t2<=935){
	DrawGraph(376,-800+t2,Tmino,TRUE);
        t2++;
	}
	if(t2>=935){
	DrawGraph(376,-800l+t2,Tmino,TRUE);
	}
	
	if(l6<=942){
	DrawGraph(489,-800+l6,L1mino,TRUE);
        l6++;
	}
	if(l6>=942){
	DrawGraph(489,-800l+l6,L1mino,TRUE);
	}
	
	if(j4<=948){
	DrawGraph(619,-800+j4,J2mino,TRUE);
        j4++;
	}
	if(j4>=948){
	DrawGraph(619,-800l+j4,J2mino,TRUE);
	}
	
	if(j5<=945){
	DrawGraph(756,-800+j5,J1mino,TRUE);
        j5++;
	}
	if(j5>=945){
	DrawGraph(756,-800l+j5,J1mino,TRUE);
	}
	
//スタートの表示--------------------------------
	if(j4>=948){
	
	if(count<0){
	COUNT=1;
	}
	if(count>255){
	COUNT=0;	
	}
	                    
	if(COUNT==1){
	count+=3;
	}
	if(COUNT==0){
	count-=3;
	}
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,count);
	DrawGraph(0,-100,start,TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);	

	}
//背景のぼかしフレーム--------------------- 
 	DrawGraph(0,0,back,TRUE);	
	
//上キーで終了-----------------------------	
	if (CheckHitKey(KEY_INPUT_RETURN)==1){
		SceneMgr_ChangeScene(eScene_Menu);
		break;
	}
}
}        