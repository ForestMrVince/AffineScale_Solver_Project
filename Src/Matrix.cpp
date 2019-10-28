#include <Matrix.h>

bool Project_GetAMatrix(Matrix_typedef *Matrix)
{
	double temp_Element = 0;
	Matrix_Row temp_Row;
	size_t Row_size_Now = 0, Row_size_Before = 0;
	char temp_CharLoop_char = 0;
	bool NewRow_flag = true, NewRow_CharLoop_flag = true, NewRowLoop_flag = true;

	std::cout << "请输入你的矩阵：" << std::endl;

	while (NewRow_flag)
	{
		std::cout << "请输入新的一行（元素间以空格隔开，每一行以非数字字符结束）：" << std::endl;
		while (NewRowLoop_flag)
		{
			while (std::cin >> temp_Element)
			{
				temp_Row.push_back(temp_Element);
			}
			if (Row_size_Before == 0)
			{
				Row_size_Before = temp_Row.size();
				if (Row_size_Before == 0)
				{
					std::cout << "输入了空行！继续输入：" << std::endl;
				}
				else
				{
					NewRowLoop_flag = false;
				}
			}
			else
			{
				Row_size_Now = temp_Row.size();
				if (Row_size_Now == 0)
				{
					std::cout << "输入了空行！继续输入：" << std::endl;
				}
				if (Row_size_Now < Row_size_Before)
				{
					std::cout << "当前行元素不足！继续输入：" << std::endl;
				}
				if (Row_size_Now > Row_size_Before)
				{
					std::cout << "当前行元素过多！删除输入的所有矩阵元素！退出输入程序！" << std::endl;
					Matrix->clear();
					return false;
				}
				if (Row_size_Now == Row_size_Before)
				{
					NewRowLoop_flag = false;
				}
			}
			std::cin.clear();
			std::cin.ignore();
		}
		Matrix->push_back(temp_Row);
		temp_Row.clear();
		NewRowLoop_flag = true;

		while(NewRow_CharLoop_flag)
		{
			std::cout << "是否输入新的一行（Y/N）：" << std::endl;
			std::cin >> temp_CharLoop_char;
			switch (temp_CharLoop_char)
			{
				case 'Y':
					NewRow_flag = 1;
					NewRow_CharLoop_flag = false;
					break;

				case 'N':
					NewRow_flag = 0;
					NewRow_CharLoop_flag = false;
					break;

				default:
					std::cout << "输入了错误的操作符" << std::endl;
					break;
			}
			temp_CharLoop_char = 0;
			std::cin.clear();
			std::cin.ignore();
		}
		NewRow_CharLoop_flag = true;
	}

	return true;
}

bool Project_ShowAMatrix(Matrix_typedef *Matrix)
{
	if (Matrix->size() == 0)
	{
		std::cout << "矩阵为空" << std::endl;
		return false;
	}
	else
	{
		for (auto MatrixRow_temp : *Matrix)
		{
			for (auto MatrixElement_temp : MatrixRow_temp)
			{
				std::cout << MatrixElement_temp << ' ';
			}
			std::cout << std::endl;
		}
	}
	return true;
}

//求逆、求转置、矩阵相乘、数与矩阵相乘、矩阵相加

bool Project_MatrixInversion(Matrix_typedef Matrix, Matrix_typedef *MatrixReversed)//求逆，需要把return改为bool，形参添加一个矩阵变量的地址用于存储逆矩阵
{
	if (Matrix.size() == Matrix.begin()->size())
	{
		double Determinant = Project_Determinant(Matrix);
		//std::cout << Determinant << std::endl;//test
		if (Determinant == 0)
		{
			return false;
		}
		else
		{
			*MatrixReversed = Project_MatrixMultipliedByNumber(1 / Determinant, AdjugateMatrix_fun(Matrix));
			//std::cout << Determinant << std::endl;//test
			//Project_ShowAMatrix(&AdjugateMatrix_fun(Matrix));//test
		}
	}
	return true;
}

Matrix_typedef Project_MatrixTransposition(Matrix_typedef Matrix)//求转置
{
	size_t m_before = 0, n_before = 0;//m行n列

	m_before = Matrix.size();//行数提取
	n_before = Matrix.begin()->size();//列数提取

	Matrix_Row MatrixRow_Transp(m_before, 0);
	Matrix_typedef Matrix_Transp(n_before, MatrixRow_Transp);

	size_t i = 0;
	size_t j = 0;
	for (auto MatrixRow_temp : Matrix)
	{
		for (auto MatrixElement_temp : MatrixRow_temp)
		{
			(Matrix_Transp[j])[i] = MatrixElement_temp;
			j = j + 1;
		}
		i++;
		j = 0;
	}

	/*for (size_t i = 0; i < Matrix.size(); i++)
	{
		for (size_t j = 0; j < Matrix.begin()->size(); j++)
		{
			(Matrix_Transp[j])[i] = (Matrix[i])[j];
			j = j + 1;
		}
	}*/

	return Matrix_Transp;
}

bool Project_MatrixMultiplication(Matrix_typedef Matrix_front, Matrix_typedef Matrix_back, Matrix_typedef *MatrixMultiplicated)//矩阵相乘
{
	size_t m_front = Matrix_front.size(), n_front = Matrix_front.begin()->size(), m_back = Matrix_back.size(), n_back = Matrix_back.begin()->size();
	if (n_front == m_back)
	{
		Matrix_Row MatrixMultiplicatedRow_temp(n_back, 0);
		Matrix_typedef MatrixMultiplicated_temp(m_front, MatrixMultiplicatedRow_temp);
		size_t i0 = 0;//遍历Matrix_front的每一行的所有元素用；

		auto Matrix_front_p = Matrix_front.begin();
		for (size_t i = 0; i < m_front; i++)
		{
			for (size_t j = 0; j < n_back; j++)
			{
				for (auto Matrix_backRow_temp : Matrix_back)
				{
					(MatrixMultiplicated_temp[i])[j] = (MatrixMultiplicated_temp[i])[j] + (*Matrix_front_p)[i0] * Matrix_backRow_temp[j];
					i0++;
				}
				i0 = 0;
			}
			Matrix_front_p = Matrix_front_p + 1;
		}

		*MatrixMultiplicated = MatrixMultiplicated_temp;
		return true;
	}

	std::cout << "矩阵维度不满足要求，不能执行相乘操作！" << std::endl;
	return false;
}

Matrix_typedef Project_MatrixMultipliedByNumber(double Number, Matrix_typedef Matrix)//数与矩阵相乘
{
	auto MatrixRow_p = Matrix.begin();
	for (size_t i = 0; i < Matrix.size(); i++)
	{
		auto MatrixElement_p = MatrixRow_p->begin();
		for (size_t j = 0; j < MatrixRow_p->size(); j++)
		{
			*MatrixElement_p = (*MatrixElement_p) * Number;
			MatrixElement_p = MatrixElement_p + 1;
		}
		MatrixRow_p = MatrixRow_p + 1;
	}

	return Matrix;
}

bool Project_MatrixPlusMatrix(Matrix_typedef Matrix_front, Matrix_typedef Matrix_back, Matrix_typedef *MatrixAdded)//矩阵相加
{
	size_t m_front = Matrix_front.size(), n_front = Matrix_front.begin()->size(), m_back = Matrix_back.size(), n_back = Matrix_back.begin()->size();
	if ((m_front == m_back)&&(n_front == n_back))
	{
		Matrix_Row MatrixAddedRow_temp(n_front, 0);
		Matrix_typedef MatrixAdded_temp(m_front, MatrixAddedRow_temp);

		auto Matrix_front_p = Matrix_front.begin();
		auto Matrix_back_p = Matrix_back.begin();
		for (size_t i = 0; i < m_front; i++)
		{
			auto Matrix_frontElement_p = Matrix_front_p->begin();
			auto Matrix_backElement_p = Matrix_back_p->begin();
			for (size_t j = 0; j < n_front; j++)
			{
				(MatrixAdded_temp[i])[j] = *Matrix_frontElement_p + *Matrix_backElement_p;
				Matrix_frontElement_p = Matrix_frontElement_p + 1;
				Matrix_backElement_p = Matrix_backElement_p + 1;
			}
			Matrix_front_p = Matrix_front_p + 1;
			Matrix_back_p = Matrix_back_p + 1;
		}

		*MatrixAdded = MatrixAdded_temp;
		return true;
	}

	std::cout << "矩阵维度不相同，不能执行相加操作！" << std::endl;
	return false;
}

double Project_Determinant(Matrix_typedef Determinant)
{
	double result = 0;
	size_t Determinant_n = Determinant.size(), Determinant_m = 1;
	Matrix_Row FullyArrangedRow_temp(Determinant_n, 0);

	for (size_t i = 0; i < Determinant_n; i++)
	{
		Determinant_m = Determinant_m * (Determinant_n - i);
	}

	Matrix_typedef FullyArranged(Determinant_m, FullyArrangedRow_temp);
	
	//Project_ShowAMatrix(&FullyArranged);//test

	FullyArranged_fun(&FullyArranged, Determinant_n);

	//Project_ShowAMatrix(&FullyArranged);//test
	//std::cout << 3 << std::endl;//test
	//std::cout << 3 << std::endl;//test

	double DeterminantRowSum_temp = 1, j = 0;
	size_t i = 0;

	for (auto FullyArrangedRow_for : FullyArranged)
	{
		for (auto FullyArrangedElememt_for : FullyArrangedRow_for)
		{
			DeterminantRowSum_temp = DeterminantRowSum_temp * (((Determinant)[i])[FullyArrangedElememt_for-1]);
			i++;
		}

		j = ReverseOrderNumber_fun(FullyArrangedRow_for);
		//std::cout <<"DeterminantRowSum_temp = "<< DeterminantRowSum_temp << std::endl;//test
		//std::cout << "j = " << j << std::endl;//test
		result = result + DeterminantRowSum_temp * pow(-1, j);

		i = 0;
		DeterminantRowSum_temp = 1;
	}


	//std::cout << result << std::endl;//test
	return result;
}

static void FullyArranged_fun(Matrix_typedef *FullyArranged, size_t n)
{
	Matrix_Row FullyArrangedRowElement_temp; double Elemet_temp = 0;

	for (size_t i = 0; i < n; i++)
	{
		Elemet_temp = Elemet_temp + 1;
		FullyArrangedRowElement_temp.push_back(Elemet_temp);
	}

	std::vector<size_t> Line(n, 0);
	std::vector<size_t> factorial_vec;
	FullyArranged_fun_Exhaustive(FullyArranged, FullyArrangedRowElement_temp, 0, n, &Line, &factorial_vec);
}

static void FullyArranged_fun_Exhaustive(Matrix_typedef *FullyArranged, Matrix_Row FullyArrangedRowElement_temp, size_t start, size_t n, std::vector<size_t> *Line, std::vector<size_t> *factorial_vec)
{
	Matrix_Row FullyArrangedRowElement_temp_temp, FullyArrangedRow_temp; size_t factorial = 1;
	if (FullyArrangedRowElement_temp.size() != 0)
	{
		for (size_t i = 0; i < (FullyArrangedRowElement_temp.size() - 1); i++)
		{
			factorial = factorial * ((FullyArrangedRowElement_temp.size() - 1) - i);
		}
	}
	if (factorial_vec->size() != n)
	{
		factorial_vec->push_back(factorial);
	}

	for (size_t i = 0; i < n - start; i++)
	{
		FullyArrangedRowElement_temp_temp = FullyArrangedRowElement_temp;
		auto FullyArrangedRowElement_temp_temp_iterator = FullyArrangedRowElement_temp_temp.begin();
		FullyArrangedRowElement_temp_temp.erase(FullyArrangedRowElement_temp_temp_iterator + i);
		
		(*Line)[start] = i;

		for (size_t m = 0; m < factorial; m++)
		{
			size_t Line_base = 0;
			Line_base = 0;
			for (size_t j = 0; j < factorial_vec->size(); j++)
			{
				Line_base = Line_base + (((*factorial_vec)[j])*((*Line)[j]));
				//std::cout << "j= " << j << std::endl;//test
				//std::cout << "(*Line)[j]= " << (*Line)[j] << std::endl;//test
				//std::cout << "(*factorial_vec)[j]= " << (*factorial_vec)[j] << std::endl;//test
				//std::cout << "Line_base= " << Line_base << std::endl;//test
			}

			((*FullyArranged)[m + Line_base])[start] = FullyArrangedRowElement_temp[i];//需要注意每一层的那个数录入几次，比如列数为三的，第一层（start=0），每个数录入两次
			//Project_ShowAMatrix(FullyArranged);//test
			//std::cout << std::endl;//test
			//std::cout << "i= " << i << std::endl;//test
			//std::cout << "m= " << m << std::endl;//test
			//std::cout << "factorial= " <<factorial << std::endl;//test
			//std::cout << "start= " << start << std::endl;//test
			//std::cout << std::endl;//test
		}
		FullyArranged_fun_Exhaustive(FullyArranged, FullyArrangedRowElement_temp_temp, start + 1, n, Line, factorial_vec);//m的问题
	}
	if (start != n)
	{
		(*Line)[start] = 0;
	}
}

//double ReverseOrderNumber_fun(Matrix_Row FullyArranged_row)//test
static double ReverseOrderNumber_fun(Matrix_Row FullyArranged_row)
{
	double ReverseOrderNumber = 0;

	ReverseOrderNumber_fun_Exhaustive(&ReverseOrderNumber, FullyArranged_row);

	return ReverseOrderNumber;
}

static void ReverseOrderNumber_fun_Exhaustive(double *Number, Matrix_Row Row)
{
	double RowFirestElement_now = Row[0];
	Row.erase(Row.begin());
	for (auto Element_temp : Row)
	{
		if (RowFirestElement_now > Element_temp)
		{
			(*Number)++;
		}
	}
	if (Row.size() > 1)
	{
		ReverseOrderNumber_fun_Exhaustive(Number, Row);
	}
}

static Matrix_typedef AdjugateMatrix_fun(Matrix_typedef Matrix)
{
	Matrix_Row AdjugateMatrixRow;
	Matrix_typedef AdjugateMatrix, AlgebraicCofactor_M;

	for (size_t i = 0; i < Matrix.size(); i++)
	{
		for (size_t j = 0; j < Matrix.size(); j++)
		{
			AlgebraicCofactor_M = Matrix;
			auto AlgebraicCofactor_M_interator = AlgebraicCofactor_M.begin();
			for (size_t k = 0; k < AlgebraicCofactor_M.size(); k++)
			{
				AlgebraicCofactor_M_interator->erase(AlgebraicCofactor_M_interator->begin()+j);
				AlgebraicCofactor_M_interator = AlgebraicCofactor_M_interator + 1;
			}
			AlgebraicCofactor_M.erase(AlgebraicCofactor_M.begin() + i);

			AdjugateMatrixRow.push_back(pow(-1,i+j)*Project_Determinant(AlgebraicCofactor_M));
		}
		AdjugateMatrix.push_back(AdjugateMatrixRow);
		AdjugateMatrixRow.clear();
	}
	AdjugateMatrix = Project_MatrixTransposition(AdjugateMatrix);

	return AdjugateMatrix;
}

//矩阵辅助函数
bool Project_MatrixMerging(Matrix_typedef Matrix_front, Matrix_typedef Matrix_back, Matrix_typedef *Matrix_Merged)
{
	if (Matrix_front.size() != Matrix_back.size())
	{
		std::cout << "合并的矩阵行数不一致！！！" << std::endl;
		return false;
	}

	auto Matrix_front_iterator = Matrix_front.begin();
	for (auto Matrix_back_Row_temp : Matrix_back)
	{
		for (auto Matrix_back_Row_Element_temp : Matrix_back_Row_temp)
		{
			Matrix_front_iterator->push_back(Matrix_back_Row_Element_temp);
		}
		Matrix_front_iterator = Matrix_front_iterator + 1;
	}

	*Matrix_Merged = Matrix_front;
	return true;
}

//辅助函数
void Project_SelectionSort(Matrix_Row &arr)
{
	for (int i = 0; i < arr.size() - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < arr.size(); j++)
			if (arr[j] < arr[min])
				min = j;
		std::swap(arr[i], arr[min]);
	}
}