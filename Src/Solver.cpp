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
		std::cout << "两阶段法求解失败！！！" << std::endl;
		return false;
	}
	else
	{
		std::cout << "两阶段法求解成功！！！" << std::endl;
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
bool BigM_Method_main()
{
	return true;
}
/*大M法求解函数*/

/*原仿射尺度求解*/

/*原仿射尺度求解*/