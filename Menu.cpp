//ÉwÉbÉ_ÉtÉ@ÉCÉãÇ…ä÷êîñàÇ…çÏé“ãLì¸ÅAñ≥ãLì¸ÇÕçÏíπà‰

#include "DxLib.h"
#include "Main.h"
#include "Tetris.h"
#include "GA.h"
#include "Keyboard.h"
#include "SceneMgr.h"

static Cr = GetColor(0,0,0);

extern int FPS;
	
void Menu_Draw(){
	int X1,X2,X3,X4,X5,X6,X7,X8,X9,X10,X11,X12,X13,X14,X15,X16,X17,X18,X19,X20,X21;//ÉâÉìÉ_ÉÄç¿ïWïœêî
	int Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8,Y9,Y10,Y11,Y12,Y13,Y14,Y15,Y16,Y17,Y18,Y19,Y20,Y21;//ÉâÉìÉ_ÉÄç¿ïWïœêî             
	int I1,I2,I3,I4,J1,J2,J3,J4,L1,L2,L3,L4,T1,T2,T3,T4,O1,O2,O3,O4,Z1,Z2,Z3,Z4,S1,S2,S3,S4;//îwåiÉ~ÉmâÊëúópïœêî
	int back;//Ç⁄Ç©ÇµÉtÉåÅ[ÉÄâÊëúópïœêî
	int start,count=0,COUNT=1;//ÉXÉ^Å[ÉgâÊëúópïœêî
	double a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,i=0,j=0,k=0,l=0,m=0,n=0,o=0,p=0,q=0,r=0,s=0,t=0,u=0;//îwåiÉ~Émà⁄ìÆópïœêî
	int tetris2_t,tetris2_e,tetris2_t2,tetris2_r,tetris2_i,tetris2_s,tetris2_g,tetris2_a;//ï∂éöÅ@TETRIS GA
	int tetris_t,tetris_e,tetris_t2,tetris_r,tetris_i,tetris_s;//ï∂éöÅ@TETRIS
	int option_o,option_p,option_t,option_i,option_o2,option_n;//ï∂éöÅ@OPTION
	int back_b,back_a,back_c,back_k;//ï∂éöÅ@BACK
	int Y[27]={0,0,0,0,0,0,0,0,-2,-4,-8,-4,-2,0,2,4,8,4,2,0,0,0,0,0,0,0,0};//ï∂éöYç¿ïWïœçXópîzóÒ
	int A=7,B=0,C=0,D=0;//ï∂éöèàóùópïœêî
	

//îwåiÉ~ÉmâÊëúÇïœêîÇ…äiî[-----------------------
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
	
//îwåiÇ⁄Ç©ÇµÉtÉåÅ[ÉÄâÊëúÇïœêîÇ…äiî[---------------------
	back=LoadGraph("tetris_image/back.png");
	
//ÉXÉ^Å[ÉgâÊëúÇïœêîÇ…äiî[-------------------------------	
	start=LoadGraph("tetris_image/start.png");

//ï∂éöâÊëúÇïœêîÇ…äiî[-----------------------------------	
	tetris2_t=LoadGraph("char/tetris2_t.png");
	tetris2_e=LoadGraph("char/tetris2_e.png");
	tetris2_t2=LoadGraph("char/tetris2_t2.png");
	tetris2_r=LoadGraph("char/tetris2_r.png");
	tetris2_i=LoadGraph("char/tetris2_i.png");
	tetris2_s=LoadGraph("char/tetris2_s.png");
	tetris2_g=LoadGraph("char/tetris2_g.png");
	tetris2_a=LoadGraph("char/tetris2_a.png");	
	
	tetris_t=LoadGraph("char/tetris_t.png");
	tetris_e=LoadGraph("char/tetris_e.png");
	tetris_t2=LoadGraph("char/tetris_t2.png");
	tetris_r=LoadGraph("char/tetris_r.png");
	tetris_i=LoadGraph("char/tetris_i.png");
	tetris_s=LoadGraph("char/tetris_s.png");
	
	option_o=LoadGraph("char/option_o.png");
	option_p=LoadGraph("char/option_p.png");
	option_t=LoadGraph("char/option_t.png");
	option_i=LoadGraph("char/option_i.png");
	option_o2=LoadGraph("char/option_o2.png");
	option_n=LoadGraph("char/option_n.png");
	
	back_b=LoadGraph("char/back_b.png");
	back_a=LoadGraph("char/back_a.png");
	back_c=LoadGraph("char/back_c.png");
	back_k=LoadGraph("char/back_k.png");
	
//ÉâÉìÉ_ÉÄÇ»Xç¿ïWÇälìæ----------------------------------	           
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
	
//ÉâÉìÉ_ÉÄÇ»Yç¿ïWälìæ--------------------------	
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
        	Wait();		//ë“ã@
		Update();	//çXêV
		Draw();		//ï`âÊ

		Keyboard_Update();
//îwåiÇó¨ÇÍÇÈÉ~Ém-------------------------------

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
	
//ï∂éöï\é¶èàóù---------------------------------
       	if (CheckHitKey(KEY_INPUT_UP)==1 && C>0 && D>=10){
		C-=1;
		D=0;
	}
	if (CheckHitKey(KEY_INPUT_DOWN)==1 && C<3 && D>=10){
		C+=1;
		D=0;
	}

        if(C!=0){
	DrawGraph(100,-20,tetris2_t,TRUE);
	DrawGraph(100,-20,tetris2_e,TRUE);
	DrawGraph(100,-20,tetris2_t2,TRUE);
	DrawGraph(57,-20,tetris2_r,TRUE);
	DrawGraph(57,-20,tetris2_i,TRUE);
	DrawGraph(57,-20,tetris2_s,TRUE);
	DrawGraph(57,-20,tetris2_g,TRUE);
	DrawGraph(57,-20,tetris2_a,TRUE);
	}	
	if(C==0){
        DrawGraph(100,-20+Y[A],tetris2_t,TRUE);
	DrawGraph(100,-20+Y[A-1],tetris2_e,TRUE);
	DrawGraph(100,-20+Y[A-2],tetris2_t2,TRUE);
	DrawGraph(57,-20+Y[A-3],tetris2_r,TRUE);
	DrawGraph(57,-20+Y[A-4],tetris2_i,TRUE);
	DrawGraph(57,-20+Y[A-5],tetris2_s,TRUE);
	DrawGraph(57,-20+Y[A-6],tetris2_g,TRUE);
	DrawGraph(57,-20+Y[A-7],tetris2_a,TRUE);
		if(A<=27&&B==3){   
		  A++;
		  }
		if(A>=27){
		  A=7; 
		  }
	}	  
		     
	if(C!=1){	  
	DrawGraph(100,-20,tetris_t,TRUE);
        DrawGraph(100,-20,tetris_e,TRUE);
        DrawGraph(100,-20,tetris_t2,TRUE);
	DrawGraph(100,-20,tetris_r,TRUE);
	DrawGraph(100,-20,tetris_i,TRUE);
	DrawGraph(100,-20,tetris_s,TRUE);
	}
	if(C==1){	  
	DrawGraph(100,-20+Y[A],tetris_t,TRUE);
        DrawGraph(100,-20+Y[A-1],tetris_e,TRUE);
        DrawGraph(100,-20+Y[A-2],tetris_t2,TRUE);
	DrawGraph(100,-20+Y[A-3],tetris_r,TRUE);
	DrawGraph(100,-20+Y[A-4],tetris_i,TRUE);
	DrawGraph(100,-20+Y[A-5],tetris_s,TRUE);
		if(A<=25&&B==3){   
		  A++;
		 }
		if(A>=25){
		  A=7;
		}   
	}
	
	if(C!=2){
	DrawGraph(100,-20,option_o,TRUE);
	DrawGraph(100,-20,option_p,TRUE);
	DrawGraph(100,-20,option_t,TRUE);
	DrawGraph(100,-20,option_i,TRUE);
	DrawGraph(100,-20,option_o2,TRUE);
	DrawGraph(100,-20,option_n,TRUE);
	}
	if(C==2){
	DrawGraph(100,-20+Y[A],option_o,TRUE);
	DrawGraph(100,-20+Y[A-1],option_p,TRUE);
	DrawGraph(100,-20+Y[A-2],option_t,TRUE);
	DrawGraph(100,-20+Y[A-3],option_i,TRUE);
	DrawGraph(100,-20+Y[A-4],option_o2,TRUE);
	DrawGraph(100,-20+Y[A-5],option_n,TRUE);
		if(A<=25&&B==3){   
		  A++;
		 }
		if(A>=25){
		  A=7;
		}  
	}
	
	if(C!=3){
	DrawGraph(100,-20,back_b,TRUE);
	DrawGraph(100,-20,back_a,TRUE);
	DrawGraph(100,-20,back_c,TRUE);
	DrawGraph(100,-20,back_k,TRUE);
	}
	if(C==3){
	DrawGraph(100,-20+Y[A],back_b,TRUE);
	DrawGraph(100,-20+Y[A-1],back_a,TRUE);
	DrawGraph(100,-20+Y[A-2],back_c,TRUE);
	DrawGraph(100,-20+Y[A-3],back_k,TRUE);
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
		  
//îwåiÇÃDrawGraph(0,0,tetris2_s,TRUE);Ç⁄Ç©ÇµÉtÉåÅ[ÉÄ--------------------- 
 	DrawGraph(0,0,back,TRUE);
		
	if(Keyboard_Get(KEY_INPUT_RETURN)==1&&C==0){
		Tetris_Syokika();
		SceneMgr_ChangeScene(eScene_GA);
		//GAéûÇÃfpsílê›íË
		FPS = 830;
		break;
	}
	if(Keyboard_Get(KEY_INPUT_RETURN)==1&&C==1){
		Tetris_Syokika();
		GA_Syokika();
		SceneMgr_ChangeScene(eScene_Tetris);
		break;
	}
	if(Keyboard_Get(KEY_INPUT_RETURN)==1&&C==2){
		SceneMgr_ChangeScene(eScene_Option);
		Keyboard_Update();
		break;
	}
	if(Keyboard_Get(KEY_INPUT_RETURN)==1&&C==3){
		SceneMgr_ChangeScene(eScene_Title);
		break;
	}
}

}