#include "Solver.h"

/*单纯形求解函数声明*/
bool Project_solver_main()//主函数
{
	if (!Question_Input())
	{
		std::cout << "输入的问题无效！！！" << std::endl;
		return false;
	}

	if (!BigM_Method_main())//调用两阶段法求解
	{
		std::cout << "大M法求解失败！！！" << std::endl;
		return false;
	}
	else
	{
		std::cout << "大M法求解成功！！！" << std::endl;
		return true;
	}
}


/*问题录入函数*/
static bool Question_Input()
{
	std::cout << "请输入矩阵A：" << std::endl;
	if (!GetMatrix_A())
	{
		std::cout << "输入的矩阵A无效" << std::endl;
		return false;
	}

	std::cout << "请输入矩阵b：" << std::endl;
	if (!GetMatrix_b())
	{
		std::cout << "输入的矩阵b无效" << std::endl;
		return false;
	}

	std::cout << "请输入矩阵c：" << std::endl;
	if (!GetMatrix_c())
	{
		std::cout << "输入的矩阵c无效" << std::endl;
		return false;
	}

	x_init();//初始化自变量列向量x

	return true;
}

static bool GetMatrix_A()
{
	Matrix_typedef Matrix;
	if (!Project_GetAMatrix(&Matrix))
	{
		return false;
	}
	A = Matrix;
	m = A.size();			//初始化行数m
	n = A.begin()->size();	//初始化列数n
	return true;
}

static bool GetMatrix_b()
{
	Matrix_typedef Matrix;
	std::cout << "为了输入方便，请输入b的转置" << std::endl;
	if (!Project_GetAMatrix(&Matrix))
	{
		return false;
	}
	Matrix = Project_MatrixTransposition(Matrix);//将输入的b的转置，转置一下，变成真正的b

	if (Matrix.size() != m)//判断输入的b的行数是否和A的行数相等
	{
		return false;
	}
	else
	{
		if (Matrix.begin()->size() != 1)//判断输入的b是否为列向量
		{
			return false;
		}
		else
		{
			b = Matrix;//录入b
			return true;
		}
	}
}

static bool GetMatrix_c()
{
	Matrix_typedef Matrix;
	std::cout << "为了输入方便，请输入c的转置" << std::endl;
	if (!Project_GetAMatrix(&Matrix))
	{
		return false;
	}
	Matrix = Project_MatrixTransposition(Matrix);//将输入的c的转置，转置一下，变成真正的c

	if (Matrix.size() != n)//判断输入的c的行数是否和A的列数相等
	{
		return false;
	}
	else
	{
		if (Matrix.begin()->size() != 1)//判断输入的c是否为列向量
		{
			return false;
		}
		else
		{
			c = Matrix;//录入c
			return true;
		}
	}
}

static void x_init()
{
	Matrix_Row x_T_RowTemp(n, 0);
	x.push_back(x_T_RowTemp);//此时x为行向量，即x的转置
	x = Project_MatrixTransposition(x);//将x转置回来
}
/*问题录入函数*/

/*大M段法求解函数*/
//主函数
static bool BigM_Method_main()
{
	return true;
}
/*大M法求解函数*/

/*原仿射尺度求解*/
//主函数
static bool AffineScale_Method_main(Matrix_typedef A_AS, Matrix_typedef c_AS, Matrix_typedef b_AS, Matrix_typedef x_0)
{
	std::cout << "原仿射尺度求解开始..." << std::endl;
	
	if (!AffineScale_Method_Init(x_0))
	{
		std::cout << "原仿射尺度法初始化错误！！！！" << std::endl;
		return false;
	}

	while (!AffineScale_Method_OptimalityTest(A_AS, c_AS, b_AS))
	{
		if (!AffineScale_Method_d_yk())
		{
			std::cout << "原仿射尺度法d_yk计算错误！！！！" << std::endl;
			return false;
		}

		if (AffineScale_Method_d_yk_check())
		{
			std::cout << "原问题是无界的！！！！" << std::endl;
			return false;
		}

		if (!AffineScale_Method_Alpha_k())
		{
			std::cout << "步长计算错误！！！！" << std::endl;
			return false;
		}

		if (!AffineScale_Method_SetConfig())
		{
			std::cout << "设置刷新错误！！！！" << std::endl;
			return false;
		}
	}

	if (!AffineScale_Method_Purification(A_AS))
	{
		std::cout << "纯化错误！！！！" << std::endl;
		return false;
	}

	std::cout << "原仿射尺度求解成功！！！！" << std::endl;
	return true;
}

//初始化函数
static bool AffineScale_Method_Init(Matrix_typedef x_0)
{
	k = 0;
	Epsilon = 0.01;
	Alpha = 0.99;
	x_k = x_0;

	Matrix_Row X_k_row_temp(1, 1);
	Matrix_typedef Matrix_temp(x_k.size(), X_k_row_temp);

	e = Matrix_temp;

	return true;
}

//迭代运算
static bool AffineScale_Method_OptimalityTest(Matrix_typedef A_AS, Matrix_typedef c_AS, Matrix_typedef b_AS)
{
	AffineScale_Method_xk2Xk();

	if (!AffineScale_Method_p_k(A_AS, c_AS))
	{
		std::cout << "最优性判断，p_k计算错误！！！！" << std::endl;
		return false;
	}

	if (!AffineScale_Method_r_k(A_AS, c_AS))
	{
		std::cout << "最优性判断，r_k计算错误！！！！" << std::endl;
		return false;
	}

	if (AffineScale_Method_r_k_check() && AffineScale_Method_e_t_X_k_r_k_check())
	{
		std::cout << "循环至 k = " << k << "，当前解最优！！！！" << std::endl;

		xr = x_k;
		cr = c_AS;

		return true;
	}

	std::cout << "循环至 k = " << k << "，当前解非最优！！！！" << std::endl;
	std::cout << "继续循环！！！！" << std::endl;
	return false;
}

static bool AffineScale_Method_SetConfig()
{
	Matrix_typedef Matrix_temp;

	if (!Project_MatrixMultiplication(X_k, d_yk, &Matrix_temp))
	{
		std::cout << "刷新设置，1 错误！！！！" << std::endl;
		return false;
	}

	Matrix_temp = Project_MatrixMultipliedByNumber(Alpha_k, Matrix_temp);

	if (!Project_MatrixPlusMatrix(x_k, Matrix_temp, &x_k))
	{
		std::cout << "刷新设置，2 错误！！！！" << std::endl;
		return false;
	}

	return true;
}

//纯化函数
static bool AffineScale_Method_Purification(Matrix_typedef A_p)
{
	if (!Purification_Init())
	{
		std::cout << "纯化初始化错误！！！！" << std::endl;
	}

	do
	{
		j = j + 1;
		if (!u(p_j, A_p, &p_j))
		{
			std::cout << "循环至 j = " << j << " ，u计算错误！！！" << std::endl;
			return false;
		}
		//计算I1&I2
	} while (/*I1&I2的判断*/);
}

static bool Purification_Init()
{
	Epsilon = 0.01;
	j = 0;
	p_j = xr;

	//I1&I2

	return true;
}

static bool u(Matrix_typedef p_j0, Matrix_typedef A_p, Matrix_typedef* p_j1)
{
	Matrix_typedef Matrix_temp;

	p_j_2_X_p(p_j0);

	if (!Project_MatrixMultiplication(X_p, X_p, &Matrix_temp))
	{
		std::cout << "u计算 1 错误！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(X_p, Matrix_temp, &Matrix_temp))
	{
		std::cout << "u计算 2 错误！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(X_p, Matrix_temp, &Matrix_temp))
	{
		std::cout << "u计算 3 错误！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(A_p, Matrix_temp, &Matrix_temp))
	{
		std::cout << "u计算 4 错误！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, Project_MatrixTransposition(A_p), &Matrix_temp))
	{
		std::cout << "u计算 5 错误！！！" << std::endl;
		return false;
	}

	if (!Generalized_Inverse_matrix(Matrix_temp, &Matrix_temp))
	{
		std::cout << "u计算 6 错误！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Project_MatrixTransposition(A_p), Matrix_temp, &Matrix_temp))
	{
		std::cout << "u计算 7 错误！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(X_p, Matrix_temp, &Matrix_temp))
	{
		std::cout << "u计算 7 错误！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(X_p, Matrix_temp, &Matrix_temp))
	{
		std::cout << "u计算 8 错误！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, A_p, &Matrix_temp))
	{
		std::cout << "u计算 9 错误！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, X_p, &Matrix_temp))
	{
		std::cout << "u计算 9 错误！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, X_p, &Matrix_temp))
	{
		std::cout << "u计算 10 错误！！！" << std::endl;
		return false;
	}

	Matrix_Row p_j1_row_temp(1, 0);
	Matrix_typedef p_j1_temp(p_j0.size(), p_j1_row_temp);

	for (size_t i = 0; i < p_j1_temp.size(); i++)
	{
		(p_j1_temp[0])[i] = (Matrix_temp[i])[i];
	}

	*p_j1 = p_j1_temp;

	return true;
}

static void p_j_2_X_p(Matrix_typedef p_j0)
{
	Matrix_Row X_p_row_temp(p_j0.size(), 0);
	Matrix_typedef Matrix_temp(p_j0.size(), X_p_row_temp);

	X_p = Matrix_temp;
	for (size_t i = 0; i < p_j0.size(); i++)
	{
		(X_p[i])[i] = (p_j0[0])[i];
	}
}

static bool Generalized_Inverse_matrix(Matrix_typedef matrix_temp, Matrix_typedef* matrix_result)
{
	Matrix_typedef Matrix_temp;

	if (!Project_MatrixMultiplication(matrix_temp, Project_MatrixTransposition(matrix_temp), &Matrix_temp))
	{
		std::cout << "广义逆矩阵求解 1 错误！！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixInversion(Matrix_temp, &Matrix_temp))
	{
		std::cout << "广义逆矩阵求解 2 错误！！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Project_MatrixTransposition(matrix_temp), Matrix_temp, &Matrix_temp))
	{
		std::cout << "广义逆矩阵求解 3 错误！！！！" << std::endl;
		return false;
	}

	*matrix_result = Matrix_temp;

	return true;
}

//辅助函数
static void AffineScale_Method_xk2Xk()
{
	Matrix_Row X_k_row_temp(x_k.size(), 0);
	Matrix_typedef Matrix_temp(x_k.size(), X_k_row_temp);

	X_k = Matrix_temp;
	for (size_t i = 0; i < x_k.size(); i++)
	{
		(X_k[i])[i] = (x_k[0])[i];
	}
}

static bool AffineScale_Method_p_k(Matrix_typedef A_AS, Matrix_typedef c_AS)
{
	Matrix_typedef Matrix_temp;

	if (!Project_MatrixMultiplication(X_k, X_k, &Matrix_temp))
	{
		std::cout << "最优性判断，p_k 1 错误！！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(A_AS, Matrix_temp, &Matrix_temp))
	{
		std::cout << "最优性判断，p_k 2 错误！！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, Project_MatrixTransposition(A_AS), &Matrix_temp))
	{
		std::cout << "最优性判断，p_k 3 错误！！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixInversion(Matrix_temp, &Matrix_temp))
	{
		std::cout << "最优性判断，p_k 4 错误！！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, A_AS, &Matrix_temp))
	{
		std::cout << "最优性判断，p_k 5 错误！！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, X_k, &Matrix_temp))
	{
		std::cout << "最优性判断，p_k 6 错误！！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, X_k, &Matrix_temp))
	{
		std::cout << "最优性判断，p_k 7 错误！！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, c, &p_k))
	{
		std::cout << "最优性判断，p_k 8 错误！！！！" << std::endl;
		return false;
	}

	return true;
}

static bool AffineScale_Method_r_k(Matrix_typedef A_AS, Matrix_typedef c_AS)
{
	Matrix_typedef Matrix_temp;

	if (!Project_MatrixMultiplication(Project_MatrixTransposition(A_AS), p_k, &Matrix_temp))
	{
		std::cout << "最优性判断，r_k 1 错误！！！！" << std::endl;
		return false;
	}

	Matrix_temp = Project_MatrixMultipliedByNumber(-1, Matrix_temp);

	if (!Project_MatrixPlusMatrix(c_AS, Matrix_temp, &r_k))
	{
		std::cout << "最优性判断，r_k 2 错误！！！！" << std::endl;
		return false;
	}

	return true;
}

static bool AffineScale_Method_r_k_check()
{
	for (auto row_temp : r_k)
	{
		for (auto temp : row_temp)
		{
			if (temp < 0)
			{
				return false;
			}
		}
	}

	std::cout << "最优性判断，r_k 全大于等于零！！！！" << std::endl;
	return true;
}

static bool AffineScale_Method_e_t_X_k_r_k_check()
{
	Matrix_typedef Matrix_temp;

	if (!Project_MatrixMultiplication(Project_MatrixTransposition(e), X_k, &Matrix_temp))
	{
		std::cout << "最优性判断，e_t、X_k、r_k的乘积 1 错误！！！！" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, r_k, &Matrix_temp))
	{
		std::cout << "最优性判断，e_t、X_k、r_k的乘积 2 错误！！！！" << std::endl;
		return false;
	}

	if (Matrix_temp.size() == 1)
	{
		if ((Matrix_temp.begin()->size()) == 1)
		{
			if ((Matrix_temp[0])[0] < Epsilon)
			{
				std::cout << "最优性判断，e_t、X_k、r_k的乘积小于Epsilon！！！！" << std::endl;
				return true;
			}
		}
		else
		{
			std::cout << "最优性判断，e_t、X_k、r_k的乘积维度错误！！！！" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "最优性判断，e_t、X_k、r_k的乘积维度错误！！！！" << std::endl;
		return false;
	}

	std::cout << "最优性判断，e_t、X_k、r_k的乘积大于Epsilon！！！！" << std::endl;
	return false;
}

static bool AffineScale_Method_d_yk()
{
	Matrix_typedef Matrix_temp;

	Matrix_temp = Project_MatrixMultipliedByNumber(-1, X_k);

	if (!Project_MatrixMultiplication(Matrix_temp, r_k, &d_yk))
	{
		std::cout << "最优性判断，d_yk 1 错误！！！！" << std::endl;
		return false;
	}
	
	return true;
}

static bool AffineScale_Method_d_yk_check()
{
	for (auto row_temp : d_yk)
	{
		for (auto temp : row_temp)
		{
			if (temp <= 0)
			{
				return false;
			}
		}
	}

	std::cout << "最优性判断，d_yk 全大于零！！！！" << std::endl;
	return true;
}

static bool AffineScale_Method_Alpha_k()
{
	double Alpha_k_before = 0, Alpha_k_now = 0;
	bool i = false;

	for (auto row_temp : d_yk)
	{
		for (auto temp : row_temp)
		{
			Alpha_k_now = Alpha / (0 - temp);
			if (!i)
			{
				Alpha_k_before = Alpha_k_now;
				i = true;
			}
			else
			{
				if (Alpha_k_now > Alpha_k_before)
				{
					Alpha_k_before = Alpha_k_now;
				}
			}
		}
	}

	Alpha_k = Alpha_k_before;
	return true;
}
/*原仿射尺度求解*/