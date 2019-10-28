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
		std::cout << "���׶η����ʧ�ܣ�����" << std::endl;
		return false;
	}
	else
	{
		std::cout << "���׶η����ɹ�������" << std::endl;
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
bool BigM_Method_main()
{
	return true;
}
/*��M����⺯��*/

/*ԭ����߶����*/

/*ԭ����߶����*/