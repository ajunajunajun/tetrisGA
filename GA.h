#pragma once

//---------------------------------------

void GA_Initialize();	//�����ݒ�

void GA_Evaluation();	//���l�Z�o
void Hyouka1(int data[22][12],int *DATA);
void Hyouka2(int data[22][12],int *DATA);
void hyouka3();
void Hyouka4(int data[22][12],int *DATA);//�f�b�g�X�y�[�X�̐��𐔂���֐�
void Hyouka5(int data[22][12],int *DATA);//9�������s�𐔂���֐�
void Hyouka6(int data[22][12],int *DATA);//���[�ɒu���������֐�



void GA_Select();	//�I��

void GA_Crossover();	//����

void GA_Mutation();	//�ˑR�ψ�

//----------------------------------------
void GA_Update();	//�X�V

void GA_Draw();		//�`��

void GA_Reset();	//����ύX�̂��߂̍Đݒ�

void GA_Move();         //���X�g�ɉ����ē�����

void GA_Delete();       //�s�����A������

void GA_Komaput();      //�����܂��Ă���u��

void GA_Put();          //�u��

void GA_Nextkoma();     //���̋�

void GA_Gameover();	//�Q�[���I�[�o�[

void GA_Score();        //�X�R�A�`�ʁA������

void GA_Syokika();	//������
