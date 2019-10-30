#include "Variables.h"

/*全局变量定义*/
//Matrix_typedef Matrix;//test

/*标准型变量*/
Matrix_typedef A;	//二维矩阵，𝑚 × 𝑛
Matrix_typedef c;	//列向量（𝑛维度）
Matrix_typedef b;	//列向量（𝑛维度）
Matrix_typedef x;	//列向量（未知数，不需要输入，𝑛维度）
size_t m;			//维度𝑚，不需要输入
size_t n;			//维度𝑛，不需要输入
/*标准型变量*/

/*大M法求解相关变量*/
double M;			//大M法的足够大的正数M
double x_a;			//人工变量
Matrix_typedef A_M;	//大M的矩阵A
Matrix_typedef c_M;	//大M的列向量c
/*大M法求解相关变量*/

/*求解原仿射尺度求解相关变量*/
size_t k;				//迭代次数
double Epsilon;			//一个近似为0的正数
double Alpha;			//一个近似为1的数
Matrix_typedef x_k;		//迭代用x列向量，也用于输入初始点
Matrix_typedef X_k;		//由x构成的对角阵
Matrix_typedef p_k;		//对偶估计向量
Matrix_typedef P_k;		//零空间投影矩阵
Matrix_typedef r_k;		//x_kd对应的约费用向量
Matrix_typedef d_yk;	//转移方向
Matrix_typedef d_xk;	//转移方向
double Alpha_k;			//步长
Matrix_typedef e;		//元素全为1的列向量，维度与当前问题的列向量x相同
//纯化函数相关变量
size_t j;			//迭代次数
Matrix_typedef p_j;	//纯化向量
Matrix_typedef I1;	//集合1
Matrix_typedef I2;	//集合2
Matrix_typedef X_p;	//p_j对应的对角阵
/*求解原仿射尺度求解相关变量*/

/*对中力计算相关变量*/
double Mu;				//一个大于零的标量μ
Matrix_typedef d_Muk;	//转移方向
/*对中力计算相关变量*/

/*最终解变量*/
Matrix_typedef cr;	//列向量（𝑛维度）
Matrix_typedef xr;	//列向量（未知数，不需要输入，𝑛维度）
/*最终解变量*/
/*全局变量定义*/
