#pragma once

#include "Project.h"

/*��������⺯������*/
bool Project_solver_main();		//������

/*����¼�뺯��*/
static bool Question_Input();	//��������
static bool GetMatrix_A();		//��ȡ��׼���е�A
static bool GetMatrix_b();		//��ȡ��׼���е�b
static bool GetMatrix_c();		//��ȡ��׼���е�c
static void x_init();			//��ʼ���Ա���������x
/*����¼�뺯��*/

/*��M�η���⺯��*/
bool BigM_Method_main();		//��M��������
/*��M����⺯��*/

/*ԭ����߶����*/

/*ԭ����߶����*/

//TEST
//bool Simplex_Solver_main(Matrix_typedef A_s_temp, Matrix_typedef c_s_temp, Matrix_typedef b_s_temp, Matrix_typedef x_s_temp);	//�������������������