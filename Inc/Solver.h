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
bool BigM_Method_main();		//大M法主函数
/*大M法求解函数*/

/*原仿射尺度求解*/

/*原仿射尺度求解*/

//TEST
//bool Simplex_Solver_main(Matrix_typedef A_s_temp, Matrix_typedef c_s_temp, Matrix_typedef b_s_temp, Matrix_typedef x_s_temp);	//修正单纯形求解主函数