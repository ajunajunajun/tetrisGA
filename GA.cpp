//�w�b�_�t�@�C���Ɋ֐����ɍ�ҋL���A���L���͍쒹��

#include "DxLib.h"        
#include "Main.h"
#include "Tetris.h"
#include "GA.h"
#include "Keyboard.h"
#include "SceneMgr.h"

//�F
static int Cr = GetColor(255,127,0);

//��z��
static int GAkoma[7] = {1,2,3,4,5,6,7}; 

//�O���ϐ�
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
//���̋�
static int nextkoma=1;

//��񂾂��֐����s��
static int onetime=0;

//�Q�[���I�[�o�[�ɂȂ�����P
int gameover=1;


//��̏���
int junban=0;

//�G�t�F�N�g
static int EffectCount[4]={0,0,0,0};
static int DeleteLine=0;

//fps
extern int FPS;

//------------------------------------------------------------------------------
//��`�q���̒���
int GENOM_LENGTH = 4000;
//��`�q�W�c�̑傫��
int MAX_GENOM_LIST = 65;
//��`�q�I��
int SELECT_GENOM = 4;
//����J��Ԃ���
// 260

//[��`�q�W�c�̑傫��][��`�q���̒���]
int genome_list[65][4000];
//��`�q�I�����X�g
int SELECT_GENOMLIST[4];

//move���Ŏ��̂�
int nextfrag=0;
//�̑I��
int kotaiselect=0;
//���㐔
int generation=1;
//�̃i���o�[
int kotai=0;
//�]���̏����l
int hyouka=0;
//���X�g�I��
int selectlist[4000];
//�]�����X�g
int hyoukalist[66];
//�������i��`�q�j
int move=0;
//�]���I����������flag
int evaluation_finish=0;

//�I��肩�ǂ���
int finish=0;

	            
//�������X�g�쐬----------------------------------------------------------------
void GA_Initialize(){

	
	int i,j;
	int random_move;
        
	//0:���ړ�,1:���ړ�,2:�E�ړ�,3:����],4:�E��],5:�z�[���h
	for(i=0;i<MAX_GENOM_LIST;i++){
		for(j=0;j<GENOM_LENGTH;j++){
			random_move = GetRand(2);
			genome_list[i][j] = random_move;
		}
	}
}

//�]��--------------------------------------------------------------------------
void GA_Evaluation(){
	int j=0;
	int *p;
	int genten=0;
	
	
		
	//���ԂɑI��
	for(j=0;j<GENOM_LENGTH;j++){
		selectlist[j] = genome_list[kotaiselect][j];
	}
	p=&genten;
	
	//�̂̉��l�Z�o
	Hyouka1(stage,p);
	Hyouka2(stage,p);
	hyouka3();
	Hyouka4(stage,p);
	Hyouka5(stage,p);
	Hyouka6(stage,p);

	hyouka += genten;

	//�]�����X�g�̐擪�ɂ͏����l������(1�Â���Ă���)
	hyoukalist[kotaiselect] = hyouka;
	
	hyouka=0;
	kotaiselect++;
	kotai++;
	
	//�S�Ă̌̕]���I��������
	if(kotaiselect==66){
		kotai=0;
		evaluation_finish=1;
	}
}

//�f�b�g�X�y�[�X�̐��𐔂���֐�------------------------------------------------
void Hyouka1(int data[22][12],int *DATA)
{

int i,j,k;//�Y����

	for(i=1;i<11;i++){

		for(j=0;j<21;j++){

		if(data[j][i]==2 || data[j][i]==11 || data[j][i]==12 || data[j][i]==13 || data[j][i]==14 || data[j][i]==15 || data[j][i]==16){//2������������t���O�𗧂Ă�
			k=1;
		}                                     
		if(k==1 && data[j][i]==0){//�ŏ��Ɍ�������2�ȍ~��0�̐��𐔂���
		(*DATA)-=30000;
		}

		}
	k=0;//�t���O�̏�����
	}
}

//�ˏo�������፷������̐��𐔂���֐�----------------------------------------
void Hyouka2(int data[22][12],int *DATA)
{

int i,j;//�Y����
int sum=0;

	for(i=1;i<11;i++){
	
		for(j=0;j<22;j++){ 
			if(data[j][i]==2 || data[j][i]==11 || data[j][i]==12 || data[j][i]==13 || data[j][i]==14 || data[j][i]==15 || data[j][i]==16){
				sum+=21-j;//�񂲂Ƃ̍����̍��v
				break;
			}
		}
	}
	sum/=10;//��̍����̕���

	for(i=1;i<11;i++){
	
		for(j=0;j<22;j++){

			if(data[j][i]==2 || data[j][i]==11 || data[j][i]==12 || data[j][i]==13 || data[j][i]==14 || data[j][i]==15 || data[j][i]==16){

				if(sum+3<=21-j){//���ρ{3�ȏ�̍����Ȃ�-1�_
				(*DATA)-=10000;
				}
			   else if(sum-3>=21-j){//����-3�ȉ��̍����Ȃ�-1�_
				(*DATA)-=10000;
				}
				break;

			}
		}
	}
}
//���፷�̍��v�a----------------------------------------------------------------
void hyouka3()
{

	int sum[10]={0,0,0,0,0,0,0,0,0,0},//�ςݏグ��ꂽ����
	    def,//�e��̉E�ׂƂ̍��፷�̍��v�a
	     count,i,j;
                           
	//�e��̐ςݏグ��ꂽ�����𒲂ׂ�
	for(count=0,i=1;i<11;i++,count++){
	
		for(j=0;j<22;j++){

		if(stage[j][i]==2 || stage[j][i]==11 || stage[j][i]==12 || stage[j][i]==13 || stage[j][i]==14 || stage[j][i]==15 || stage[j][i]==16){
			sum[count]=21-j;//�񂲂Ƃ̍����̍��v
			break;
		}
		}
	}
	

	//�e��̉E�ׂƂ̍����̍��v�a�𒲂ׂ�
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
//9�������s�𐔂���֐�-------------------------------------------------------

void Hyouka4(int data[22][12],int *DATA)
{

int i,j;
int k;//���_����_��

	for(i=1;i<11;i++){
                
		for(j=0,k=0;j<21;j++,k+=10){

			if(data[j][i]==0){//�z��̔����ȉ������g��0�̎�
				(*DATA)-=k;//k�������_����
			}
		}

	}
}

//9�������s�𐔂���֐�-------------------------------------------------------
void Hyouka5(int data[22][12],int *DATA)
{

int i,j;//�Y����
int k;//�����Ă��鐔������ϐ�

	for(j=0;j<21;j++){

		for(i=1;i<11;i++){

			if(data[j][i]==2 || data[j][i]==11 || data[j][i]==12 || data[j][i]==13 || data[j][i]==14 || data[j][i]==15 || data[j][i]==16){
				k++;//�������Ă��邩������
			}
		}
			if(k==9){//9�����Ă�����
			(*DATA)+=200;//200�_���_
			}
		k=0;//k��������
	}
}
//���[�ɒu���������֐�----------------------------------------------------------
void Hyouka6(int data[22][12],int *DATA)
{

	int i,j;//�Y����
	int soezi[2]={1,10};//�Y����

	for(i=0;i<4;i++){

		for(j=1;j<21;j++){

			if(data[j][soezi[i]]==2 || data[j][soezi[i]]==11 || data[j][soezi[i]]==12 || data[j][soezi[i]]==13 || data[j][soezi[i]]==14 || data[j][soezi[i]]==15 || data[j][soezi[i]]==16){
				if(i==0 || i==1){
					(*DATA)+=20;//1��ڂ�10��ڂ̎�2�_���_
					}
			}
		}
	}
}

//�I��--------------------------------------------------------------------------
void GA_Select(){
	int i,j,k;
	int work;
	int work2[4000];

	//�]�����X�g���~���Ƀ\�[�g
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

//����?--------------------------------------------------------------------------
void GA_Crossover(){
	int i,j,m;
	int count;
	int cross;
	
	int random_gene;
	int randomgenelist[4000];
		
	//�G���[�g��"i",�e�I��"m"
	for(i=5,m=0;i<=MAX_GENOM_LIST;i+=5,m=(m+1)%5){
		for(count=0;count<4;count++){
			for(j=0;j<GENOM_LENGTH;j++){
				random_gene = GetRand(3);
				randomgenelist[j] = random_gene;
			}
			for(j=0;j<GENOM_LENGTH;j++){
				//�q���쐬
				if(j<generation*15)
					genome_list[i+count][j] = genome_list[m][j];
				else if(j>=generation*15)
					genome_list[i+count][j] = randomgenelist[j];                  
			}
		}
	}		
}

//�ˑR�ψ�----------------------------------------------------------------------
void GA_Mutation(){

	static int i,j=0;
		
	//��60~66�̈�`�q�Ƀz�[���h���������
	for(i=60;i<66;i++)
		genome_list[i][(generation*15+60)%4000] = 5;

}

//------------------------------------------------------------------------------
void GA_Update(){

	//�f�o�b�O�p�i�X�L�b�v�j
	if(Keyboard_Get(KEY_INPUT_UP)==1){
		hyouka=-100000;
		gameover=1;
	}

}	

void GA_Draw(){
	int i,j;
	static int Font01 = CreateFontToHandle("���C���I",25,7,DX_FONTTYPE_NORMAL);
	static int HandleB1=LoadGraph("B1.jpg",TRUE);
	static int HandleF=LoadGraph("framega1.png",TRUE);
	do{
		//�͂��߂���
		if(onetime==0){
			GA_Initialize();
			onetime=1;	
	        }
		//gameover�ɂȂ�����
	        if(gameover==1){
			GA_Evaluation();
			gameover=0;
			//���X�g���Ō�܂ŕ]���o���Ă����
			if(evaluation_finish==1){
				//�I��
				GA_Select();
				GA_Crossover();
				GA_Mutation();
				GA_Reset();
			}
			GA_Syokika();
		}
		//�]�����X�g�\��
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

	        //���X�g���Ō�܂ŕ]���o���Ă��Ȃ����                                   
		if(evaluation_finish==0){
			GA_Move();      	//elite�z��̒ʂ蓮������
			GA_Komaput();       //�����܂��Ă����Ɉړ�������u��
			Tetris_Kousin();        //��A�p�x��ύX����
			GA_Nextkoma();      //���̋�ɕύX����
			GA_Delete();        //�񑵂��������
			GA_Score();
			Tetris_Show();	        //�X�e�[�W�A���\������
			GA_Gameover();	//�Q�[���I�[�o�[����
	        }
		
		//�����
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
		
		
	//�`�ʃX�L�b�v�A����,�]�����X�g,�Ō�	
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
	
	//���ړ�
	if(selectlist[move]==0){
		yzahyo++;
	}
	//���ړ�
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
	//�E�ړ�                                          	
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
	//����]
	if(selectlist[move]==3){
		kakudo=(kakudo+3)%4;
		kaiten=1;
	}
	//�E��]
	if(selectlist[move]==4){
		kakudo=(kakudo+1)%4;
		kaiten=2;
	}
	//�z�[���h
	if(selectlist[move]==5){
		if(renzoku==0){
			kakudo=0;
			Tetris_Dainyu();
				/* �X�g�b�N����̎� */
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
                	/* �X�g�b�N�����̎� */
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
	//�S�[���ݒ�
	if(move==3999){
	}
	//���㖈�̈ړ������̒l��
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


	//������
	if( deletecount == 1){
	hyouka+=2500;
	deletecount = 0;
	}//������
	else if( deletecount == 2){
		hyouka+=7000;
		deletecount = 0;
	}//�O�����
	else if( deletecount == 3){
		hyouka+10000;
		deletecount = 0;
	}//�l�����
	else if( deletecount == 4){
		hyouka+=20000;
		deletecount = 0;
	}

}

void GA_Komaput(){
	//���W�w��p
	static int x,y;

	//�����ړ��悪���܂��Ă��玟�̋�
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
	//���W�w��p
	static int x,y;

	//�ړ����̋���Œ肷��
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
	static int Font01 = CreateFontToHandle("���C���I",25,7,DX_FONTTYPE_NORMAL);
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
