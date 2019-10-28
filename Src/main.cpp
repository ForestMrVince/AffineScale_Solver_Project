#include <Project.h>

int main()
{
	/*size_t Determinant_n = 5, Determinant_m = 1;//穷举矩阵测试
	Matrix_Row FullyArrangedRow_temp(Determinant_n, 0);
	for (size_t i = 0; i < Determinant_n; i++)
	{
		Determinant_m = Determinant_m * (Determinant_n - i);
	}
	Matrix_typedef FullyArranged(Determinant_m, FullyArrangedRow_temp);
	FullyArranged_fun(&FullyArranged, Determinant_n);
	Project_ShowAMatrix(&FullyArranged);*/

	/*Project_GetAMatrix(&Matrix);//矩阵输入测试
	Project_ShowAMatrix(&Matrix);
	Matrix = Project_MatrixMultipliedByNumber(1.5,Matrix);
	Project_ShowAMatrix(&Matrix);
	Matrix = Project_MatrixTransposition(Matrix);
	Project_ShowAMatrix(&Matrix);
	Project_MatrixPlusMatrix(Matrix, Matrix, &Matrix);
	Project_ShowAMatrix(&Matrix);

	Matrix_Row Matrix_frontRow_temp(4, 1), Matrix_backRow_temp(2,1);//矩阵相乘测试
	Matrix_typedef Matrix_front(2, Matrix_frontRow_temp), Matrix_back(4, Matrix_backRow_temp);
	Project_MatrixMultiplication(Matrix_front, Matrix_back, &Matrix);
	Project_ShowAMatrix(&Matrix);*/

	/*Matrix_Row Row{3,4,2,1};//求逆序数测试
	std::cout << ReverseOrderNumber_fun(Row) << std::endl;*/
	
	/*Matrix_Row Row{ 1,1,1,1 };//行列式计算测试
	Matrix.push_back(Row);
	Row = { 0,2,0,0 };
	Matrix.push_back(Row);
	Row = { 0,0,2,0 };
	Matrix.push_back(Row);
	Row = { 0,0,0,2 };
	Matrix.push_back(Row);
	std::cout << Project_Determinant(Matrix) << std::endl;*/

	/*Matrix_Row Row{ 1,2,0,-1 };//求逆矩阵测试
	Matrix.push_back(Row);
	Row = { 2,0,-1,1 };
	Matrix.push_back(Row);
	Row = { 0,-1,1,2 };
	Matrix.push_back(Row);
	Row = { -1,1,2,2 };
	Matrix.push_back(Row);
	Project_ShowAMatrix(&Matrix);
	Project_MatrixInversion(Matrix, &Matrix);
	Project_ShowAMatrix(&Matrix);*/

	/*Matrix_Row Row1{ 1,1,1,0 };//求解器测试，例题3.1迭代测试.通过
	A_s.push_back(Row1);
	Row1 = { 2,1,0,1 };
	A_s.push_back(Row1);
	Project_ShowAMatrix(&A_s);

	Matrix_Row Row2(1,40);
	b_s.push_back(Row2);
	Row2[0] = 60;
	b_s.push_back(Row2);
	Project_ShowAMatrix(&b_s);

	Matrix_Row Row3(1,-3);
	c_s.push_back(Row3);
	Row3[0] = -2;
	c_s.push_back(Row3);
	Row3[0] = 0;
	c_s.push_back(Row3);
	Row3[0] = 0;
	c_s.push_back(Row3);
	Project_ShowAMatrix(&c_s);

	Matrix_Row Row(1,0);
	x_s.push_back(Row);
	Row[0] = 0;
	x_s.push_back(Row);
	Row[0] = 40;
	x_s.push_back(Row);
	Row[0] = 60;
	x_s.push_back(Row);
	Project_ShowAMatrix(&x_s);

	Simplex_Solver_main(A_s, c_s, b_s, x_s);

	Matrix_typedef c_s_x_s_Mult_Result;
	if (!Project_MatrixMultiplication(Project_MatrixTransposition(c_s), x_s, &c_s_x_s_Mult_Result))//检验
	{
		std::cout << "相乘失败！！！" << std::endl;
		return false;
	}
	std::cout << "最优解：" << std::endl;
	Project_ShowAMatrix(&c_s_x_s_Mult_Result);
	std::cout << "此时的x：" << std::endl;
	Project_ShowAMatrix(&x_s);
	std::cout << std::endl;*/

	/*Matrix_Row Row1{ 1,1,1,0,0 };//求解器测试，例题3.2迭代测试.通过
	A_s.push_back(Row1);
	Row1 = { 2,1,0,1,0 };
	A_s.push_back(Row1);
	Row1 = { 1,0,0,0,1 };
	A_s.push_back(Row1);
	Project_ShowAMatrix(&A_s);

	Matrix_Row Row2(1, 40);
	b_s.push_back(Row2);
	Row2[0] = 60;
	b_s.push_back(Row2);
	Row2[0] = 30;
	b_s.push_back(Row2);
	Project_ShowAMatrix(&b_s);

	Matrix_Row Row3(1, -3);
	c_s.push_back(Row3);
	Row3[0] = -2;
	c_s.push_back(Row3);
	Row3[0] = 0;
	c_s.push_back(Row3);
	Row3[0] = 0;
	c_s.push_back(Row3);
	Row3[0] = 0;
	c_s.push_back(Row3);
	Project_ShowAMatrix(&c_s);

	Matrix_Row Row(1, 0);
	x_s.push_back(Row);
	Row[0] = 0;
	x_s.push_back(Row);
	Row[0] = 40;
	x_s.push_back(Row);
	Row[0] = 60;
	x_s.push_back(Row);
	Row[0] = 30;
	x_s.push_back(Row);
	Project_ShowAMatrix(&x_s);

	Simplex_Solver_main(A_s, c_s, b_s, x_s);

	Matrix_typedef c_s_x_s_Mult_Result;
	if (!Project_MatrixMultiplication(Project_MatrixTransposition(c_s), x_s, &c_s_x_s_Mult_Result))//检验
	{
		std::cout << "相乘失败！！！" << std::endl;
		return false;
	}
	std::cout << "最优解：" << std::endl;
	Project_ShowAMatrix(&c_s_x_s_Mult_Result);
	std::cout << "此时的x：" << std::endl;
	Project_ShowAMatrix(&x_s);
	std::cout << std::endl;*/

	if (Project_solver_main())
	{
		std::cout << "求解成功！！！" << std::endl;

		Matrix_typedef c_s_x_s_Mult_Result;
		if (!Project_MatrixMultiplication(Project_MatrixTransposition(c_s), x_s, &c_s_x_s_Mult_Result))//检验
		{
			std::cout << "相乘失败！！！" << std::endl;
			return false;
		}
		std::cout << "最优解：" << std::endl;
		Project_ShowAMatrix(&c_s_x_s_Mult_Result);
		std::cout << "此时的x：" << std::endl;
		Project_ShowAMatrix(&x_s);
		std::cout << std::endl;
	}
	else
	{
		std::cout << "求解失败！！！" << std::endl;
	}

	system("pause");
}