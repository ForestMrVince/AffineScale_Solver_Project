#include "Solver.h"

/*��������⺯������*/
bool Project_solver_main()//������
{
	if (!Question_Input())
	{
		std::cout << "�����������Ч������" << std::endl;
		return false;
	}

	if (!BigM_Method_main())//�������׶η����
	{
		std::cout << "��M�����ʧ�ܣ�����" << std::endl;
		return false;
	}
	else
	{
		std::cout << "��M�����ɹ�������" << std::endl;
		return true;
	}
}


/*����¼�뺯��*/
static bool Question_Input()
{
	std::cout << "���������A��" << std::endl;
	if (!GetMatrix_A())
	{
		std::cout << "����ľ���A��Ч" << std::endl;
		return false;
	}

	std::cout << "���������b��" << std::endl;
	if (!GetMatrix_b())
	{
		std::cout << "����ľ���b��Ч" << std::endl;
		return false;
	}

	std::cout << "���������c��" << std::endl;
	if (!GetMatrix_c())
	{
		std::cout << "����ľ���c��Ч" << std::endl;
		return false;
	}

	x_init();//��ʼ���Ա���������x

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
	m = A.size();			//��ʼ������m
	n = A.begin()->size();	//��ʼ������n
	return true;
}

static bool GetMatrix_b()
{
	Matrix_typedef Matrix;
	std::cout << "Ϊ�����뷽�㣬������b��ת��" << std::endl;
	if (!Project_GetAMatrix(&Matrix))
	{
		return false;
	}
	Matrix = Project_MatrixTransposition(Matrix);//�������b��ת�ã�ת��һ�£����������b

	if (Matrix.size() != m)//�ж������b�������Ƿ��A���������
	{
		return false;
	}
	else
	{
		if (Matrix.begin()->size() != 1)//�ж������b�Ƿ�Ϊ������
		{
			return false;
		}
		else
		{
			b = Matrix;//¼��b
			return true;
		}
	}
}

static bool GetMatrix_c()
{
	Matrix_typedef Matrix;
	std::cout << "Ϊ�����뷽�㣬������c��ת��" << std::endl;
	if (!Project_GetAMatrix(&Matrix))
	{
		return false;
	}
	Matrix = Project_MatrixTransposition(Matrix);//�������c��ת�ã�ת��һ�£����������c

	if (Matrix.size() != n)//�ж������c�������Ƿ��A���������
	{
		return false;
	}
	else
	{
		if (Matrix.begin()->size() != 1)//�ж������c�Ƿ�Ϊ������
		{
			return false;
		}
		else
		{
			c = Matrix;//¼��c
			return true;
		}
	}
}

static void x_init()
{
	Matrix_Row x_T_RowTemp(n, 0);
	x.push_back(x_T_RowTemp);//��ʱxΪ����������x��ת��
	x = Project_MatrixTransposition(x);//��xת�û���
}
/*����¼�뺯��*/

/*��M�η���⺯��*/
//������
static bool BigM_Method_main()
{
	Matrix_Row x_0_row_temp(1, 1);
	Matrix_typedef x_0_temp(x.size()+1, x_0_row_temp);

	if (!BigM_Method_Init())
	{
		std::cout << "��M����ʼ�����󣡣�����" << std::endl;
		return false;
	}

	if (!AffineScale_Method_main(A_M, c_M, b, x_0_temp))
	{
		std::cout << "��M�����ʧ�ܣ�������" << std::endl;
		return false;
	}

	std::cout << "��M�����ɹ���������" << std::endl;
	return true;
}

//��ʼ��
static bool BigM_Method_Init()
{
	std::cout << "������M��" << std::endl;
	std::cin >> M;
	std::cout << "Mֵ��¼�룬�������������" << std::endl;

	Matrix_Row e_row_temp(1, 1);
	Matrix_typedef Matrix_e_temp(x.size(), e_row_temp);

	e = Matrix_e_temp;

	Matrix_Row Row_temp(1, M);
	c_M = c;
	c_M.push_back(Row_temp);

	Matrix_typedef Matrix_temp;

	if (!Project_MatrixMultiplication(A, e, &Matrix_temp))
	{
		std::cout << "��M����ʼ�� 1 ���󣡣�����" << std::endl;
		return false;
	}

	Matrix_temp = Project_MatrixMultipliedByNumber(-1, Matrix_temp);

	if (!Project_MatrixPlusMatrix(b, Matrix_temp, &Matrix_temp))
	{
		std::cout << "��M����ʼ�� 2 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMerging(A, Matrix_temp, &A_M))
	{
		std::cout << "��M����ʼ�� 3 ���󣡣�����" << std::endl;
		return false;
	}

	return true;
}
/*��M����⺯��*/

/*ԭ����߶����*/
//������
//static bool AffineScale_Method_main(Matrix_typedef A_AS, Matrix_typedef c_AS, Matrix_typedef b_AS, Matrix_typedef x_0)
bool AffineScale_Method_main(Matrix_typedef A_AS, Matrix_typedef c_AS, Matrix_typedef b_AS, Matrix_typedef x_0)//test
{
	std::cout << "ԭ����߶���⿪ʼ..." << std::endl;
	
	if (!AffineScale_Method_Init(x_0))
	{
		std::cout << "ԭ����߶ȷ���ʼ�����󣡣�����" << std::endl;
		return false;
	}

	while (!AffineScale_Method_OptimalityTest(A_AS, c_AS, b_AS))
	{
		#ifndef LogBarrier_Function
		if (!AffineScale_Method_d_yk())
		{
			std::cout << "ԭ����߶ȷ�d_yk������󣡣�����" << std::endl;
			return false;
		}

		if (AffineScale_Method_d_yk_check())
		{
			std::cout << "ԭ�������޽�ģ�������" << std::endl;
			return false;
		}

		if (!AffineScale_Method_Alpha_k())
		{
			std::cout << "����������󣡣�����" << std::endl;
			return false;
		}

		std::cout << "d_yk��" << std::endl;					//test
		Project_ShowAMatrix(&d_yk);							//test
		std::cout << "d_Muk��" << std::endl;					//test
		Project_ShowAMatrix(&d_Muk);						//test
		std::cout << "Alpha_k��" << Alpha_k << std::endl;	//test
		#endif

		#ifdef LogBarrier_Function
		if (!AffineScale_Method_d_yk())
		{
			std::cout << "ԭ����߶ȷ�d_yk������󣡣�����" << std::endl;
			return false;
		}

		if (!AffineScale_Method_P_k(A_AS))
		{
			std::cout << "ԭ����߶ȷ�P_k������󣡣�����" << std::endl;
			return false;
		}

		if (!AffineScale_Method_d_Muk())
		{
			std::cout << "ԭ����߶ȷ�d_Muk������󣡣�����" << std::endl;
			return false;
		}

		if (AffineScale_Method_d_Muk_check())
		{
			std::cout << "ԭ�������޽�ģ�������" << std::endl;
			return false;
		}

		if (!AffineScale_Method_Alpha_k())
		{
			std::cout << "����������󣡣�����" << std::endl;
			return false;
		}

		std::cout << "d_yk��" << std::endl;					//test
		Project_ShowAMatrix(&d_yk);							//test
		std::cout << "d_Muk��" << std::endl;					//test
		Project_ShowAMatrix(&d_Muk);						//test
		std::cout << "Alpha_k��" << Alpha_k << std::endl;	//test
		#endif

		if (!AffineScale_Method_SetConfig())
		{
			std::cout << "����ˢ�´��󣡣�����" << std::endl;
			return false;
		}
	}

	if (!AffineScale_Method_Purification(A_AS))
	{
		std::cout << "�������󣡣�����" << std::endl;
		return false;
	}

	std::cout << "ԭ����߶����ɹ���������" << std::endl;
	return true;
}

//��ʼ������
static bool AffineScale_Method_Init(Matrix_typedef x_0)
{
	k = 0;
	Epsilon = 0.00001;
	Alpha = 0.99;
	x_k = x_0;

	#ifdef LogBarrier_Function
	std::cout << "������̣�" << std::endl;
	std::cin >> Mu;
	std::cout << "��ֵ��¼�룬�������������" << std::endl;
	#endif

	I.clear();

	Matrix_Row I_row_temp(x_k.size(), 0);

	for (size_t i = 0; i < x_k.size(); i++)
	{
		I_row_temp[i] = 1;
		I.push_back(I_row_temp);
		I_row_temp[i] = 0;
	}

	Matrix_Row e_row_temp(1, 1);
	Matrix_typedef Matrix_temp(x_k.size(), e_row_temp);

	e = Matrix_temp;

	return true;
}

//��������
static bool AffineScale_Method_OptimalityTest(Matrix_typedef A_AS, Matrix_typedef c_AS, Matrix_typedef b_AS)
{
	AffineScale_Method_xk2Xk();

	if (!AffineScale_Method_p_k(A_AS, c_AS))
	{
		std::cout << "�������жϣ�p_k������󣡣�����" << std::endl;
		return false;
	}

	if (!AffineScale_Method_r_k(A_AS, c_AS))
	{
		std::cout << "�������жϣ�r_k������󣡣�����" << std::endl;
		return false;
	}

	if (AffineScale_Method_r_k_check() && AffineScale_Method_e_t_X_k_r_k_check())
	{
		std::cout << "ѭ���� k = " << k << "����ǰ�����ţ�������" << std::endl;

		xr = x_k;
		cr = c_AS;

		std::cout << "A_AS��" << std::endl;	//test
		Project_ShowAMatrix(&A_AS);			//test
		std::cout << "X_k��" << std::endl;	//test
		Project_ShowAMatrix(&X_k);			//test
		std::cout << "p_k��" << std::endl;	//test
		Project_ShowAMatrix(&p_k);			//test
		std::cout << "r_k��" << std::endl;	//test
		Project_ShowAMatrix(&r_k);			//test

		return true;
	}

	std::cout << "A_AS��" << std::endl;	//test
	Project_ShowAMatrix(&A_AS);			//test
	std::cout << "X_k��" << std::endl;	//test
	Project_ShowAMatrix(&X_k);			//test
	std::cout << "p_k��" << std::endl;	//test
	Project_ShowAMatrix(&p_k);			//test
	std::cout << "r_k��" << std::endl;	//test
	Project_ShowAMatrix(&r_k);			//test

	std::cout << "ѭ���� k = " << k << "����ǰ������ţ�������" << std::endl;
	std::cout << "����ѭ����������" << std::endl;
	return false;
}

static bool AffineScale_Method_SetConfig()
{
	Matrix_typedef Matrix_temp;

	#ifndef LogBarrier_Function
	if (!Project_MatrixMultiplication(X_k, d_yk, &Matrix_temp))
	{
		std::cout << "ˢ�����ã�1 ���󣡣�����" << std::endl;
		return false;
	}

	Matrix_temp = Project_MatrixMultipliedByNumber(Alpha_k, Matrix_temp);

	if (!Project_MatrixPlusMatrix(x_k, Matrix_temp, &x_k))
	{
		std::cout << "ˢ�����ã�2 ���󣡣�����" << std::endl;
		return false;
	}
	#endif

	#ifdef LogBarrier_Function

	Matrix_temp = Project_MatrixMultipliedByNumber(Alpha_k, d_Muk);

	if (!Project_MatrixPlusMatrix(x_k, Matrix_temp, &x_k))
	{
		std::cout << "ˢ�����ã�2 ���󣡣�����" << std::endl;
		return false;
	}
	#endif

	k++;
	return true;
}

//��������
static bool AffineScale_Method_Purification(Matrix_typedef A_p)
{
	std::cout << "��ʼ������������" << std::endl;

	if (!Purification_Init())
	{
		std::cout << "������ʼ�����󣡣�����" << std::endl;
	}

	do
	{
		std::cout << "p_j��" << std::endl;	//test
		Project_ShowAMatrix(&p_j);			//test
		
		j = j + 1;
		if (!u(p_j, A_p, &p_j))
		{
			std::cout << "ѭ���� j = " << j << " ��u������󣡣���" << std::endl;
			return false;
		}

		std::cout << "p_j+1��" << std::endl;	//test
		Project_ShowAMatrix(&p_j);			//test

		Purification_I1I2Calculate();//����I1&I2
	} while (!Purification_Check()/*I1&I2���ж�*/);

	return true;
}

static bool Purification_Init()
{
	Epsilon = 0.00001;
	j = 0;
	p_j = xr;

	return true;
}

static bool Purification_I1I2Calculate()
{
	Matrix_Row i(1,0);

	i[0] = 0;

	for (auto row_temp : p_j)
	{
		if (row_temp[0] < Epsilon)
		{
			I2.push_back(i);
		}
		else if (row_temp[0] > (1 - Epsilon))
		{
			I1.push_back(i);
		}

		i[0] = i[0] + 1;
	}

	return true;
}

static bool Purification_Check()
{
	if ((I1.size() + I2.size()) != p_j.size())
	{
		I1.clear();
		I2.clear();
		return false;
	}
	else
	{
		for (auto row_temp : I2)
		{
			for (auto temp : row_temp)
			{
				std::cout << temp << std::endl;
				(xr[temp])[0] = 0;
			}
		}

		I1.clear();
		I2.clear();

		std::cout << "�����ɹ�������" << std::endl;
		return true;
	}
}

static bool u(Matrix_typedef p_j0, Matrix_typedef A_p, Matrix_typedef* p_j1)
{
	Matrix_typedef Matrix_temp;

	p_j_2_X_p(p_j0);

	if (!Project_MatrixMultiplication(X_p, X_p, &Matrix_temp))
	{
		std::cout << "u���� 1 ���󣡣���" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(X_p, Matrix_temp, &Matrix_temp))
	{
		std::cout << "u���� 2 ���󣡣���" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(X_p, Matrix_temp, &Matrix_temp))
	{
		std::cout << "u���� 3 ���󣡣���" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(A_p, Matrix_temp, &Matrix_temp))
	{
		std::cout << "u���� 4 ���󣡣���" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, Project_MatrixTransposition(A_p), &Matrix_temp))
	{
		std::cout << "u���� 5 ���󣡣���" << std::endl;
		return false;
	}

	if (!Generalized_Inverse_matrix(Matrix_temp, &Matrix_temp))
	{
		std::cout << "u���� 6 ���󣡣���" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Project_MatrixTransposition(A_p), Matrix_temp, &Matrix_temp))
	{
		std::cout << "u���� 7 ���󣡣���" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(X_p, Matrix_temp, &Matrix_temp))
	{
		std::cout << "u���� 8 ���󣡣���" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(X_p, Matrix_temp, &Matrix_temp))
	{
		std::cout << "u���� 9 ���󣡣���" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, A_p, &Matrix_temp))
	{
		std::cout << "u���� 10 ���󣡣���" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, X_p, &Matrix_temp))
	{
		std::cout << "u���� 11 ���󣡣���" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, X_p, &Matrix_temp))
	{
		std::cout << "u���� 12 ���󣡣���" << std::endl;
		return false;
	}

	Matrix_Row p_j1_row_temp(1, 0);
	Matrix_typedef p_j1_temp(p_j0.size(), p_j1_row_temp);

	for (size_t i = 0; i < p_j1_temp.size(); i++)
	{
		(p_j1_temp[i])[0] = (Matrix_temp[i])[i];
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
		(X_p[i])[i] = (p_j0[i])[0];
	}
}

static bool Generalized_Inverse_matrix(Matrix_typedef matrix_temp, Matrix_typedef* matrix_result)
{
	Matrix_typedef Matrix_temp;

	if (!Project_MatrixMultiplication(matrix_temp, Project_MatrixTransposition(matrix_temp), &Matrix_temp))
	{
		std::cout << "������������ 1 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixInversion(Matrix_temp, &Matrix_temp))
	{
		std::cout << "������������ 2 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Project_MatrixTransposition(matrix_temp), Matrix_temp, &Matrix_temp))
	{
		std::cout << "������������ 3 ���󣡣�����" << std::endl;
		return false;
	}

	*matrix_result = Matrix_temp;

	return true;
}

//��������
static void AffineScale_Method_xk2Xk()
{
	Matrix_Row X_k_row_temp(x_k.size(), 0);
	Matrix_typedef Matrix_temp(x_k.size(), X_k_row_temp);

	X_k = Matrix_temp;
	for (size_t i = 0; i < x_k.size(); i++)
	{
		(X_k[i])[i] = (x_k[i])[0];
	}
}

static bool AffineScale_Method_p_k(Matrix_typedef A_AS, Matrix_typedef c_AS)
{
	Matrix_typedef Matrix_temp;

	if (!Project_MatrixMultiplication(X_k, X_k, &Matrix_temp))
	{
		std::cout << "�������жϣ�p_k 1 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(A_AS, Matrix_temp, &Matrix_temp))
	{
		std::cout << "�������жϣ�p_k 2 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, Project_MatrixTransposition(A_AS), &Matrix_temp))
	{
		std::cout << "�������жϣ�p_k 3 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixInversion(Matrix_temp, &Matrix_temp))
	{
		std::cout << "�������жϣ�p_k 4 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, A_AS, &Matrix_temp))
	{
		std::cout << "�������жϣ�p_k 5 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, X_k, &Matrix_temp))
	{
		std::cout << "�������жϣ�p_k 6 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, X_k, &Matrix_temp))
	{
		std::cout << "�������жϣ�p_k 7 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, c_AS, &p_k))
	{
		std::cout << "�������жϣ�p_k 8 ���󣡣�����" << std::endl;
		return false;
	}

	return true;
}

static bool AffineScale_Method_r_k(Matrix_typedef A_AS, Matrix_typedef c_AS)
{
	Matrix_typedef Matrix_temp;

	if (!Project_MatrixMultiplication(Project_MatrixTransposition(A_AS), p_k, &Matrix_temp))
	{
		std::cout << "�������жϣ�r_k 1 ���󣡣�����" << std::endl;
		return false;
	}

	Matrix_temp = Project_MatrixMultipliedByNumber(-1, Matrix_temp);

	if (!Project_MatrixPlusMatrix(c_AS, Matrix_temp, &r_k))
	{
		std::cout << "�������жϣ�r_k 2 ���󣡣�����" << std::endl;
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

	std::cout << "�������жϣ�r_k ȫ���ڵ����㣡������" << std::endl;
	return true;
}

static bool AffineScale_Method_e_t_X_k_r_k_check()
{
	Matrix_typedef Matrix_temp;

	if (!Project_MatrixMultiplication(Project_MatrixTransposition(e), X_k, &Matrix_temp))
	{
		std::cout << "�������жϣ�e_t��X_k��r_k�ĳ˻� 1 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, r_k, &Matrix_temp))
	{
		std::cout << "�������жϣ�e_t��X_k��r_k�ĳ˻� 2 ���󣡣�����" << std::endl;
		return false;
	}

	if (Matrix_temp.size() == 1)
	{
		if ((Matrix_temp.begin()->size()) == 1)
		{
			if ((Matrix_temp[0])[0] < Epsilon)
			{
				std::cout << "�������жϣ�e_t��X_k��r_k�ĳ˻�С��Epsilon��������" << std::endl;
				return true;
			}
		}
		else
		{
			std::cout << "�������жϣ�e_t��X_k��r_k�ĳ˻�ά�ȴ��󣡣�����" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "�������жϣ�e_t��X_k��r_k�ĳ˻�ά�ȴ��󣡣�����" << std::endl;
		return false;
	}

	std::cout << "�������жϣ�e_t��X_k��r_k�ĳ˻�����Epsilon��������" << std::endl;
	return false;
}

#ifndef LogBarrier_Function
static bool AffineScale_Method_d_yk()
{
	Matrix_typedef Matrix_temp;

	Matrix_temp = Project_MatrixMultipliedByNumber(-1, X_k);

	if (!Project_MatrixMultiplication(Matrix_temp, r_k, &d_yk))
	{
		std::cout << "�������жϣ�d_yk 1 ���󣡣�����" << std::endl;
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

	std::cout << "�������жϣ�d_yk ȫ�����㣡������" << std::endl;
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
			if ((!i) && (Alpha_k_now > 0))
			{
				Alpha_k_before = Alpha_k_now;
				i = true;
			}
			else
			{
				if ((Alpha_k_now < Alpha_k_before) && (Alpha_k_now > 0))
				{
					Alpha_k_before = Alpha_k_now;
				}
			}
		}
	}

	Alpha_k = Alpha_k_before;
	return true;
}
#endif

#ifdef LogBarrier_Function
static bool AffineScale_Method_d_yk()
{
	Matrix_typedef Matrix_temp;

	Matrix_temp = Project_MatrixMultipliedByNumber(-1, X_k);

	if (!Project_MatrixMultiplication(Matrix_temp, r_k, &d_yk))
	{
		std::cout << "�������жϣ�d_yk 1 ���󣡣�����" << std::endl;
		return false;
	}

	return true;
}

static bool AffineScale_Method_P_k(Matrix_typedef A_AS)
{
	Matrix_typedef Matrix_temp;

	if (!Project_MatrixMultiplication(X_k, X_k, &Matrix_temp))
	{
		std::cout << "�������жϣ�P_k 1 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(A_AS, Matrix_temp, &Matrix_temp))
	{
		std::cout << "�������жϣ�P_k 2 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, Project_MatrixTransposition(A_AS), &Matrix_temp))
	{
		std::cout << "�������жϣ�P_k 3 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixInversion(Matrix_temp, &Matrix_temp))
	{
		std::cout << "�������жϣ�P_k 4 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Project_MatrixTransposition(A_AS), Matrix_temp, &Matrix_temp))
	{
		std::cout << "�������жϣ�P_k 5 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(X_k, Matrix_temp, &Matrix_temp))
	{
		std::cout << "�������жϣ�P_k 6 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, A_AS, &Matrix_temp))
	{
		std::cout << "�������жϣ�P_k 7 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, X_k, &Matrix_temp))
	{
		std::cout << "�������жϣ�P_k 6 ���󣡣�����" << std::endl;
		return false;
	}

	Matrix_temp = Project_MatrixMultipliedByNumber(-1, Matrix_temp);

	if (!Project_MatrixPlusMatrix(I, Matrix_temp, &Matrix_temp))
	{
		std::cout << "�������жϣ�P_k 7 ���󣡣�����" << std::endl;
		return false;
	}

	P_k = Matrix_temp;

	return true;
}

static bool AffineScale_Method_d_Muk()
{
	if (!Project_MatrixMultiplication(X_k, d_yk, &d_xk))
	{
		std::cout << "�������жϣ�d_xk 1 ���󣡣�����" << std::endl;
		return false;
	}

	Matrix_typedef Matrix_temp;

	if (!Project_MatrixMultiplication(X_k, P_k, &Matrix_temp))
	{
		std::cout << "�������жϣ�d_Muk 1 ���󣡣�����" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(Matrix_temp, e, &Matrix_temp))
	{
		std::cout << "�������жϣ�d_Muk 2 ���󣡣�����" << std::endl;
		return false;
	}

	Matrix_temp = Project_MatrixMultipliedByNumber(Mu, Matrix_temp);

	if (!Project_MatrixPlusMatrix(d_xk, Matrix_temp, &Matrix_temp))
	{
		std::cout << "�������жϣ�d_Muk 2 ���󣡣�����" << std::endl;
		return false;
	}

	d_Muk = Matrix_temp;
	return true;
}

static bool AffineScale_Method_d_Muk_check()
{
	for (auto row_temp : d_Muk)
	{
		for (auto temp : row_temp)
		{
			if (temp <= 0)
			{
				return false;
			}
		}
	}

	std::cout << "�������жϣ�d_Muk ȫ�����㣡������" << std::endl;
	return true;
}

static bool AffineScale_Method_Alpha_k()
{
	Matrix_typedef Matrix_temp, X_I_temp;

	Matrix_temp = d_Muk;
	if (!Project_MatrixInversion(X_k, &X_I_temp))
	{
		std::cout << "Alpha_k���㣬1 ���󣡣���" << std::endl;
		return false;
	}

	if (!Project_MatrixMultiplication(X_I_temp, Matrix_temp, &Matrix_temp))
	{
		std::cout << "Alpha_k���㣬2 ���󣡣���" << std::endl;
		return false;
	}

	double Alpha_k_before = 0, Alpha_k_now = 0;
	bool i = false;

	for (auto row_temp : Matrix_temp)
	{
		for (auto temp : row_temp)
		{
			Alpha_k_now = Alpha / (0 - temp);
			if ((!i) && (Alpha_k_now > 0))
			{
				Alpha_k_before = Alpha_k_now;
				i = true;
			}
			else
			{
				if ((Alpha_k_now < Alpha_k_before) && (Alpha_k_now > 0))
				{
					Alpha_k_before = Alpha_k_now;
				}
			}
		}
	}

	Alpha_k = Alpha_k_before;
	return true;
}
#endif
/*ԭ����߶����*/