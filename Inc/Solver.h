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
static bool BigM_Method_main();	//��M��������
/*��M����⺯��*/

/*ԭ����߶����*/
static bool AffineScale_Method_main(Matrix_typedef A_AS, Matrix_typedef c_AS, Matrix_typedef b_AS, Matrix_typedef x_0);	//ԭ����߶ȷ�������
static bool AffineScale_Method_Init(Matrix_typedef x_0);																//��ʼ��
static bool AffineScale_Method_OptimalityTest(Matrix_typedef A_AS, Matrix_typedef c_AS, Matrix_typedef b_AS);			//�����Բ���
static void AffineScale_Method_xk2Xk();																					//x_kת��ΪX_k
static bool AffineScale_Method_p_k(Matrix_typedef A_AS, Matrix_typedef c_AS);											//����p_k
static bool AffineScale_Method_r_k(Matrix_typedef A_AS, Matrix_typedef c_AS);											//����r_k
static bool AffineScale_Method_r_k_check();																				//r_k��飬�Ƿ񶼴��ڵ�����
static bool AffineScale_Method_e_t_X_k_r_k_check();																		//���e_t��X_k��r_k�ĳ˻��Ƿ�С��Epsilon
static bool AffineScale_Method_d_yk();																					//����d_yk
static bool AffineScale_Method_d_yk_check();																			//���d_yk�Ƿ񶼴���0
static bool AffineScale_Method_Alpha_k();																				//���㲽��
static bool AffineScale_Method_SetConfig();																				//ˢ������
static bool AffineScale_Method_Purification();																			//��������
static bool Purification_Init();																						//����������ʼ��
/*ԭ����߶����*/

//TEST
//bool Simplex_Solver_main(Matrix_typedef A_s_temp, Matrix_typedef c_s_temp, Matrix_typedef b_s_temp, Matrix_typedef x_s_temp);	//�������������������