#pragma once

#include <Project.h>

/*单纯形求解函数声明*/
bool Project_solver_main();		//主函数

/*问题录入函数*/
static bool Question_Input();	//输入问题
static bool GetMatrix_A();		//获取标准型中的A
static bool GetMatrix_b();		//获取标准型中的b
static bool GetMatrix_c();		//获取标准型中的c
static void x_init();			//初始化自变量列向量x
/*问题录入函数*/

/*两阶段法求解函数*/
static bool TwoPhaseMethod_main();	//两阶段法主函数
static void x_2_init();				//原问题变量x与人工变量xa合并后的x_2初始化
static void c_2_init();				//初始化一阶段问题的c
static void A_2_init();				//初始化一阶段问题的A
/*两阶段法求解函数*/

/*修正单纯形求解*/
static bool Simplex_Solver_main(Matrix_typedef A_s_temp, Matrix_typedef c_s_temp, Matrix_typedef b_s_temp, Matrix_typedef x_s_temp);	//修正单纯形求解主函数
static bool Simplex_Solver_init(Matrix_typedef A_s_temp, Matrix_typedef c_s_temp, Matrix_typedef b_s_temp, Matrix_typedef x_s_temp);	//修正单纯形法初始化
static bool Simplex_Solver_OptimalityTest();																							//最优性检验
static bool Simplex_Solver_SeekOptimizationDirection();																					//求解改进方向
static bool Simplex_Solver_FindLambda();																								//求解步长
static bool Simplex_Solver_SetConfig();																									//更新设置
void EraseAllVariables();																												//清空变量内容
/*修正单纯形求解*/

//TEST
//bool Simplex_Solver_main(Matrix_typedef A_s_temp, Matrix_typedef c_s_temp, Matrix_typedef b_s_temp, Matrix_typedef x_s_temp);	//修正单纯形求解主函数