#include "Solver.h"

/*单纯形求解函数声明*/
bool Project_solver_main()//主函数
{
	if (!Question_Input())
	{
		std::cout << "输入的问题无效！！！" << std::endl;
		return false;
	}

	if (!TwoPhaseMethod_main())//调用两阶段法求解
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

/*两阶段法求解函数*/
static bool TwoPhaseMethod_main()//两阶段法主函数
{
	b_2 = b;//b_2的初始化
	x_2_init();
	c_2_init();
	A_2_init();

	if (!Simplex_Solver_main(A_2, c_2, b_2, x_2))//开始求解第一阶段
	{
		std::cout << "第一阶段求解失败！！！" << std::endl;
		return false;
	}

	Matrix_typedef c_s_x_s_Mult_Result;
	if (!Project_MatrixMultiplication(Project_MatrixTransposition(c_s), x_s, &c_s_x_s_Mult_Result))//检验
	{
		std::cout << "第一阶段检验相乘失败！！！" << std::endl;
		return false;
	}
	if ((c_s_x_s_Mult_Result[0])[0] != 0)
	{
		std::cout << "第一阶段检验证明：原问题不可行！！！" << std::endl;
		return false;
	}
	std::cout << "第一阶段求解成功！！！" << std::endl;

	for (size_t i_x = 0; i_x < x.size(); i_x++)//消除人工变量
	{
		(x[i_x])[0] = (x_s[i_x])[0];
	}

	void EraseAllVariables();//清空变量内容
	if (!Simplex_Solver_main(A, c, b, x))//开始求解第二阶段
	{
		std::cout << "第二阶段求解失败！！！" << std::endl;
		return false;
	}

	return true;
}

//两阶段法初始化
static void x_2_init()
{
	xa = b_2;
	x_2 = x;

	auto xa_T = Project_MatrixTransposition(xa);
	auto x_2_T = Project_MatrixTransposition(x_2);

	if (!Project_MatrixMerging(x_2_T, xa_T, &x_2_T))//合并两个矩阵
	{
		std::cout << "矩阵合并失败！！！" << std::endl;
		return;
	}

	x_2 = Project_MatrixTransposition(x_2_T);
}

static void c_2_init()
{
	Matrix_Row ca_RowTemp(xa.size(), 1);
	Matrix_typedef ca;
	ca.push_back(ca_RowTemp);

	Matrix_Row c_2_RowTemp(x.size(), 0);
	c_2.push_back(c_2_RowTemp);

	if (!Project_MatrixMerging(c_2, ca, &c_2))//合并两个矩阵
	{
		std::cout << "c_2 矩阵合并失败！！！" << std::endl;
		return;
	}
	c_2 = Project_MatrixTransposition(c_2);
}

static void A_2_init()
{
	Matrix_Row Aa_RowTemp(xa.size(), 0);

	for (size_t i=0; i < xa.size(); i++)
	{
		Aa_RowTemp[i] = 1;
		Aa.push_back(Aa_RowTemp);
		Aa_RowTemp[i] = 0;
	}

	if (Aa.size() != xa.size())//test
	{
		std::cout << "Aa行数错误" << std::endl;//test
	}
	else//test
	{
		if (Aa.begin()->size() != xa.size())//test
		{
			std::cout << "Aa列数错误" << std::endl;//test
		}
	}
	
	A_2 = A;//首先把A的成员都引入进来，因为A_2是把Aa拼接在A后面

	if (!Project_MatrixMerging(A_2, Aa, &A_2))//合并两个矩阵
	{
		return;
	}
}
/*两阶段法求解函数*/

/*修正单纯形求解(带Bland规则)*/
//bool Simplex_Solver_main(Matrix_typedef A_s_temp, Matrix_typedef c_s_temp, Matrix_typedef b_s_temp, Matrix_typedef x_s_temp)//修正单纯形求解主函数
static bool Simplex_Solver_main(Matrix_typedef A_s_temp, Matrix_typedef c_s_temp, Matrix_typedef b_s_temp, Matrix_typedef x_s_temp)//修正单纯形求解主函数
{
	if (!Simplex_Solver_init(A_s_temp, c_s_temp, b_s_temp, x_s_temp))//初始化单纯形变量
	{
		std::cout << "初始化错误！！！" << std::endl;
		return false;
	}

	while (!Simplex_Solver_OptimalityTest())			//进行最优性检验
	{
		if (!Simplex_Solver_SeekOptimizationDirection())		//求解改进方向
		{
			return false;
		}

		if (!Simplex_Solver_FindLambda())					//求解步长
		{
			return false;
		}

		if (!Simplex_Solver_SetConfig())					//求解步长
		{
			return false;
		}
	}

	return true;
}

//修正单纯形法初始化
static bool Simplex_Solver_init(Matrix_typedef A_s_temp, Matrix_typedef c_s_temp, Matrix_typedef b_s_temp, Matrix_typedef x_s_temp)
{
	A_s = A_s_temp; c_s = c_s_temp; b_s = b_s_temp; x_s = x_s_temp;
	m_s = A_s_temp.size(); n_s = c_s.size();
	Matrix_typedef N_T, B_T;
	Matrix_Row Row_temp;
	IN.push_back(Row_temp);//向IN里添加一个行
	IB.push_back(Row_temp);//向IB里添加一个行

	IN.begin()->clear();
	N_T.clear();
	cN.clear();
	xN.clear();
	IB.begin()->clear();
	B_T.clear();
	cB.clear();
	xB.clear();
	size_t i = 0;
	for (auto x_s_Row_temp : x_s)
	{
		for (auto x_s_RowElement_temp : x_s_Row_temp)
		{
			if (x_s_RowElement_temp == 0)	//初始化非基
			{
				IN.begin()->push_back(i);										//初始化非基脚标集
				N_T.push_back((Project_MatrixTransposition(A_s))[i]);		//初始化A列的非基矩阵，的转置
				cN.push_back(c_s[i]);
				xN.push_back(x_s[i]);
			}
			else							//初始化基
			{
				IB.begin()->push_back(i);										//初始化基脚标集
				B_T.push_back((Project_MatrixTransposition(A_s))[i]);		//初始化A列的基矩阵，的转置
				cB.push_back(c_s[i]);
				xB.push_back(x_s[i]);
			}
		}
		i++;
	}
	//如果B不是方阵——修复
	while (B_T.size() != B_T.begin()->size())
	{
		B_T.push_back(*(N_T.end() - 1));
		N_T.erase(N_T.end() - 1);
		
		IB.begin()->push_back(*(IN.begin()->end() - 1));
		IN.begin()->erase(IN.begin()->end() - 1);

		cB.push_back(*(cN.end() - 1));
		cN.erase(cN.end() - 1);

		xB.push_back(*(xN.end() - 1));
		xN.erase(xN.end() - 1);
	}
	//修复↑
	B = Project_MatrixTransposition(B_T);
	N = Project_MatrixTransposition(N_T);
	

	Matrix_Row r_row_temp(n_s,0);
	Matrix_typedef r_temp;
	r_temp.push_back(r_row_temp);
	r_temp = Project_MatrixTransposition(r_temp);
	r = r_temp;//r是个列向量

	if ((IB[0]).size() != m_s)//test
	{
		std::cout << "IB 初始化错误！！！" << std::endl;
		return false;
	}

	return true;
}

//最优性检验
static bool Simplex_Solver_OptimalityTest()
{
	Matrix_typedef B_Inv, cB_T;
	cB_T = Project_MatrixTransposition(cB);
	if (!Project_MatrixInversion(B, &B_Inv))
	{
		std::cout << "B的逆矩阵不存在！！！" << std::endl;
	}
	if (!Project_MatrixMultiplication(cB_T, B_Inv, &w_T))//更新w_t
	{
		std::cout << "求单纯形乘子的计算出错！！！" << std::endl;
	}

	Matrix_typedef Matrix_temp, Aq_T, A_s_T = Project_MatrixTransposition(A_s);//Matrix_temp为w_T与Aq的乘积
	Aq_T.push_back((*A_s_T.begin()));//初始化Aq_T
	size_t i = 0;

	for (auto temp : IN[0])
	{
		q = temp;

		Aq_T[0] = A_s_T[q];//取出A_s的第q列
		Aq = Project_MatrixTransposition(Aq_T);

		if (!Project_MatrixMultiplication(w_T, Aq, &Matrix_temp))
		{
			std::cout << "最优性检测矩阵乘法错误！！！" << std::endl;
			return false;
		}
		cq = (c_s[q])[0];
		rq = cq - (Matrix_temp[0])[0];
		(r[q])[0] = rq;

		if ((rq) < 0)
		{
			i++;//如果i==0则全部rq≥0，则此时达到最优
		}
	}

	if (i == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//求解改进方向
static bool Simplex_Solver_SeekOptimizationDirection()
{
	//找出q
	Matrix_Row IN_temp = IN[0];
	Project_SelectionSort(IN_temp);//为实现bland规则(1)，从小到大排序

	for (auto temp : IN_temp)
	{
		q = temp;
		if ((r[q])[0] < 0)//实现bland规则(1)，break时的q始终是最小的，因为前面对IN进行了从小到大的排序，此时q是入基变量角标
		{
			break;
		}
	}

	//计算改进方向
	Matrix_typedef B_Inv, B_Inv_Sub0, d, dq_T;//B_Inv_Sub0为-B_Inv
	Matrix_typedef Aq_T, A_s_T = Project_MatrixTransposition(A_s);
	Aq_T.push_back((*A_s_T.begin()));//初始化Aq_T

	if (!Project_MatrixInversion(B, &B_Inv))
	{
		std::cout << "B的逆矩阵不存在！！！" << std::endl;
	}

	B_Inv_Sub0 = Project_MatrixMultipliedByNumber(-1, B_Inv);

	Aq_T[0] = A_s_T[q];//取出A_s的第q列
	Aq = Project_MatrixTransposition(Aq_T);
	if (!Project_MatrixMultiplication(B_Inv_Sub0, Aq, &d))
	{
		std::cout << "求解改进方向矩阵乘法错误！！！" << std::endl;
		return false;
	}//算出了d

	Matrix_Row dq_T_Row_temp(n_s, 0);
	dq_T.push_back(dq_T_Row_temp);

	for (auto j = 0; j < d.size(); j++)
	{
		(dq_T[0])[((IB[0])[j])] = (d[j])[0];
	}
	(dq_T[0])[q] = 1;
	dq = Project_MatrixTransposition(dq_T);//没有使用拼接，为了保证每个矩阵中每一行的行号，与自变量的行号对应。

	//dq = d;//Project_MatrixMerging
	//dq_T = Project_MatrixTransposition(dq);//求dq的转置，为拼接做准备
	//Matrix_Row eq_Row_temp(n_s - m_s, 0);
	//Matrix_typedef eq(1, eq_Row_temp);
	//if (!Project_MatrixMerging(dq_T, eq, &dq_T))
	//{
	//	std::cout << "求解改进方向，方向向量合并错误！！！" << std::endl;
	//	return false;
	//}
	//dq = Project_MatrixTransposition(dq_T);
	//(dq[q])[0] = 1;//计算出最终的dq																※可能引发BUG，所以被上文代码块替换

	size_t i = 0;
	for (auto d_Row_temp : d)
	{
		for (auto d_Row_Element_temp : d_Row_temp)
		{
			if (d_Row_Element_temp <= 0)
			{
				i++;
			}
		}
	}

	if (i == 0)
	{
		std::cout << "求解改进方向，解无界！！！" << std::endl;
		return false;
	}

	return true;
}

//求解步长
static bool Simplex_Solver_FindLambda()
{
	Matrix_Row IB_temp = IB[0];
	double lambda_Now = 0; size_t jp_Now = 0; lambda = 0;
	Project_SelectionSort(IB_temp);//为实现bland规则(2)，从小到大排序

	for (auto temp : IB_temp)
	{
		jp_Now = temp;
		if ((dq[jp_Now])[0] < 0)//实现bland规则(2)，break时的jp始终是最小的，因为前面对IB进行了从小到大的排序，此时jp是出基变量角标
		{
			lambda_Now = -((x_s[jp_Now])[0]) / ((dq[jp_Now])[0]);
			if (lambda == 0)
			{
				lambda = lambda_Now;
				jp = jp_Now;
			}
			else
			{
				if (lambda_Now < lambda)
				{
					lambda = lambda_Now;
					jp = jp_Now;
				}
			}
		}
	}

	return true;
}

//更新设置
static bool Simplex_Solver_SetConfig()
{
	//更新x_s
	Matrix_typedef lambda_dq = Project_MatrixMultipliedByNumber(lambda, dq);
	Project_MatrixPlusMatrix(lambda_dq, x_s, &x_s);

	//更新
	//计算出/入基变量角标再IB/IN中的位置
	size_t i = 0, j = 0;
	for (auto IB_temp : IB[0])
	{
		if (IB_temp == jp)
		{
			break;
		}
		else
		{
			i++;
		}
	}
	for (auto IN_temp : IN[0])
	{
		if (IN_temp == q)
		{
			break;
		}
		else
		{
			j++;
		}
	}

	//IN与IB互换元素
	double IN_IB_temp = 0;
	IN_IB_temp = (IN[0])[j];
	(IN[0])[j] = (IB[0])[i];
	(IB[0])[i] = IN_IB_temp;

	//N和B互换元素
	Matrix_typedef N_T, B_T;
	Matrix_Row N_B_Row_temp;
	N_T = Project_MatrixTransposition(N);
	B_T = Project_MatrixTransposition(B);
	N_B_Row_temp = N_T[j];
	N_T[j] = B_T[i];
	B_T[i] = N_B_Row_temp;
	N = Project_MatrixTransposition(N_T);
	B = Project_MatrixTransposition(B_T);

	//cN和cB互换元素
	Matrix_Row cN_cB_Row_temp;
	cN_cB_Row_temp = cN[j];
	cN[j] = cB[i];
	cB[i] = cN_cB_Row_temp;

	//xN和xB互换元素
	Matrix_Row xN_xB_Row_temp;
	xN_xB_Row_temp = xN[j];
	xN[j] = xB[i];
	xB[i] = xN_xB_Row_temp;

	return true;
}

//清空变量
void EraseAllVariables()
{
	//清空变量
	A_s.clear();
	c_s.clear();
	b_s.clear();
	x_s.clear();
	B.clear();
	N.clear();
	cB.clear();
	cN.clear();
	xB.clear();
	xN.clear();
	IB.clear();
	IN.clear();
	r.clear();
	rB.clear();
	rN.clear();
	w_T.clear();
	Nq.clear();
	Aq.clear();
	D.clear();
	dq.clear();
}