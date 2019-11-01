#pragma once

#include "Project.h"

/*全局变量声明*/
//extern Matrix_typedef Matrix;

/*标准型变量*/
extern Matrix_typedef A;	//二维矩阵，m × n
extern Matrix_typedef c;	//列向量（n维度）
extern Matrix_typedef b;	//列向量（m维度）
extern Matrix_typedef x;	//列向量（未知数，不需要输入，n维度）
extern size_t m;			//维度m，不需要输入
extern size_t n;			//维度n，不需要输入
/*标准型变量*/

/*大M法求解相关变量*/
extern double M;			//大M法的足够大的正数M，尽量的大。					※值由用户输入。
extern double x_a;			//人工变量
extern Matrix_typedef A_M;	//大M的矩阵A
extern Matrix_typedef c_M;	//大M的列向量c
/*大M法求解相关变量*/

/*求解原仿射尺度求解相关变量*/
extern size_t k;				//迭代次数
extern double Epsilon;			//一个近似为0的正数
extern double Alpha;			//一个近似为1的数
extern Matrix_typedef x_k;		//迭代用x列向量，也用于输入初始点
extern Matrix_typedef X_k;		//由x构成的对角阵
extern Matrix_typedef p_k;		//对偶估计向量
extern Matrix_typedef P_k;		//零空间投影矩阵
extern Matrix_typedef r_k;		//x_kd对应的约费用向量
extern Matrix_typedef d_yk;		//转移方向
extern Matrix_typedef d_xk;		//转移方向
extern double Alpha_k;			//步长
extern Matrix_typedef e;		//元素全为1的列向量，维度与当前问题的列向量x相同
extern Matrix_typedef I;		//单位阵
//纯化函数相关变量
extern size_t j;			//迭代次数
extern Matrix_typedef p_j;	//纯化向量
extern Matrix_typedef I1;	//集合1
extern Matrix_typedef I2;	//集合2
extern Matrix_typedef X_p;	//p_j对应的对角阵
/*求解原仿射尺度求解相关变量*/

/*对中力计算相关变量*/
extern double Mu;				//一个大于零的标量μ，尽量的小。				※值由用户输入。
extern Matrix_typedef d_Muk;	//转移方向
/*对中力计算相关变量*/

/*最终解变量*/
extern Matrix_typedef cr;	//列向量（𝑛维度）
extern Matrix_typedef xr;	//列向量（未知数，不需要输入，𝑛维度）
/*最终解变量*/
/*全局变量声明*/
