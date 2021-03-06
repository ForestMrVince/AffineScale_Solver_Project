#pragma once

#include "Project.h"

/*单纯形求解函数声明*/
bool Project_solver_main();		//主函数

/*问题录入函数*/
static bool Question_Input();	//输入问题
static bool GetMatrix_A();		//获取标准型中的A
static bool GetMatrix_b();		//获取标准型中的b
static bool GetMatrix_c();		//获取标准型中的c
static void x_init();			//初始化自变量列向量x
/*问题录入函数*/

/*大M段法求解函数*/
static bool BigM_Method_main();	//大M法主函数
static bool BigM_Method_Init();	//大M法初始化
/*大M法求解函数*/

/*原仿射尺度求解*/
static bool AffineScale_Method_main(Matrix_typedef A_AS, Matrix_typedef c_AS, Matrix_typedef b_AS, Matrix_typedef x_0);	//原仿射尺度法主函数
static bool AffineScale_Method_Init(Matrix_typedef x_0);																//初始化
static bool AffineScale_Method_OptimalityTest(Matrix_typedef A_AS, Matrix_typedef c_AS, Matrix_typedef b_AS);			//最优性测试
static void AffineScale_Method_xk2Xk();																					//x_k转换为X_k
static bool AffineScale_Method_p_k(Matrix_typedef A_AS, Matrix_typedef c_AS);											//计算p_k
static bool AffineScale_Method_r_k(Matrix_typedef A_AS, Matrix_typedef c_AS);											//计算r_k
static bool AffineScale_Method_r_k_check();																				//r_k检查，是否都大于等于零
static bool AffineScale_Method_e_t_X_k_r_k_check();																		//检查e_t、X_k、r_k的乘积是否小于Epsilon
#ifndef LogBarrier_Function
static bool AffineScale_Method_d_yk();																					//计算d_yk
static bool AffineScale_Method_d_yk_check();																			//检查d_yk是否都大于0
static bool AffineScale_Method_Alpha_k();																				//计算步长
#endif
#ifdef LogBarrier_Function
static bool AffineScale_Method_d_yk();																					//计算d_yk
static bool AffineScale_Method_P_k(Matrix_typedef A_AS);																//计算P_k
static bool AffineScale_Method_d_Muk();																					//计算d_Muk
static bool AffineScale_Method_d_Muk_check();																			//检查d_yk是否都大于0
static bool AffineScale_Method_Alpha_k();																				//计算步长
#endif
static bool AffineScale_Method_SetConfig();																				//刷新设置
static bool AffineScale_Method_Purification(Matrix_typedef A_p);														//纯化函数
static bool Purification_Init();																						//纯化函数初始化
static bool Purification_I1I2Calculate();																				//I1和I2计算
static bool Purification_Check();																						//检查纯化是否完成
static bool u(Matrix_typedef p_j0, Matrix_typedef A_p, Matrix_typedef* p_j1);											//纯化函数中的u				※可能存在BUG
static void p_j_2_X_p(Matrix_typedef p_j0);																				//p_j到X_p的转换
static bool Generalized_Inverse_matrix(Matrix_typedef matrix_temp, Matrix_typedef* matrix_result);						//求广义逆矩阵				※可能存在BUG
/*原仿射尺度求解*/

//TEST
//bool Simplex_Solver_main(Matrix_typedef A_s_temp, Matrix_typedef c_s_temp, Matrix_typedef b_s_temp, Matrix_typedef x_s_temp);	//修正单纯形求解主函数