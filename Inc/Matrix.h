#pragma once

#include <Project.h>

//矩阵运算函数声明
bool Project_GetAMatrix(Matrix_typedef *Matrix);	//矩阵输入函数
bool Project_ShowAMatrix(Matrix_typedef *Matrix);	//显示一个矩阵
bool Project_MatrixInversion(Matrix_typedef Matrix, Matrix_typedef *MatrixReversed);//求逆
Matrix_typedef Project_MatrixTransposition(Matrix_typedef Matrix);//求转置
bool Project_MatrixMultiplication(Matrix_typedef Matrix_front, Matrix_typedef Matrix_back, Matrix_typedef *MatrixMultiplicated);//矩阵相乘
Matrix_typedef Project_MatrixMultipliedByNumber(double Number, Matrix_typedef Matrix);//数与矩阵相乘
bool Project_MatrixPlusMatrix(Matrix_typedef Matrix_front, Matrix_typedef Matrix_back, Matrix_typedef *MatrixAdded);//矩阵相加
static Matrix_typedef AdjugateMatrix_fun(Matrix_typedef Matrix);//计算伴随矩阵;

//行列式运算
double Project_Determinant(Matrix_typedef Determinant);//行列式
static void FullyArranged_fun(Matrix_typedef *FullyArranged, size_t n);//求行列式列序数排列组合矩阵
static void FullyArranged_fun_Exhaustive(Matrix_typedef *FullyArranged, Matrix_Row FullyArrangedRowElement_temp, size_t start, size_t n, std::vector<size_t> *Line, std::vector<size_t> *factorial_vec);//求行列式列序数排列组合矩阵函数的穷举递归函数
static double ReverseOrderNumber_fun(Matrix_Row FullyArranged_row);//求逆序数
static void ReverseOrderNumber_fun_Exhaustive(double *Number, Matrix_Row Row);//求逆序数函数的穷举递归函数

//矩阵辅助函数
bool Project_MatrixMerging(Matrix_typedef Matrix_front, Matrix_typedef Matrix_back, Matrix_typedef *Matrix_Merged);//前后合并两个矩阵，※未测试BUG

//辅助函数
void Project_SelectionSort(Matrix_Row &arr);//从小到大排序

//test
//void FullyArranged_fun(Matrix_typedef *FullyArranged, size_t n);
//double ReverseOrderNumber_fun(Matrix_Row FullyArranged_row);//求逆序数