#pragma once

#include <Project.h>

/*全局变量声明*/
//extern Matrix_typedef Matrix;

/*标准型变量*/
extern Matrix_typedef A;//二维矩阵，?? × ??
extern Matrix_typedef c;//列向量（??维度）
extern Matrix_typedef b;//列向量（??维度）
extern Matrix_typedef x;//列向量（未知数，不需要输入，??维度）
extern size_t m;//维度??，不需要输入
extern size_t n;//维度??，不需要输入

/*求解标准型拆分变量*/
//待求解问题的变量
extern Matrix_typedef A_s;//二维矩阵，??_s × ??_s
extern Matrix_typedef c_s;//列向量（??_s维度）
extern Matrix_typedef b_s;//列向量（??_s维度）
extern Matrix_typedef x_s;//列向量（初始点，不需要输入，??_s维度）
extern size_t m_s;//维度??_s，不需要输入
extern size_t n_s;//维度??_s，不需要输入
//A拆分成的
extern Matrix_typedef B;//基（?? × ??的方阵）
extern Matrix_typedef N;//非基（?? × (?? ? ??) 维的矩阵）
//c拆分成的
extern Matrix_typedef cB;//基c（长度为 ?? 的零列向量）
extern Matrix_typedef cN;//非基c（长度为 ?? ? ?? 的零列向量）
//x拆分成的
extern Matrix_typedef xB;//基变量（长度为 ?? 的零列向量）
extern Matrix_typedef xN;//非基变量（长度为 ?? ? ?? 的零列向量）

/*求解过程变量*/
/*变量下标集合*/
extern Matrix_typedef IB;//基变量的下标集合		※非常重要！！！！
extern Matrix_typedef IN;//非基变量的下标集合		※非常重要！！！！
/*迭代运算相关变量*/
extern Matrix_typedef r;//既约费用向量（所有的变量≥0，则结果最优。等价于rN≥0.）
extern Matrix_typedef rB;//基，既约费用向量（长度为 ?? 的零列向量）
extern Matrix_typedef rN;//非基，既约费用向量（长度为 ?? ? ?? 的列向量）
/*最优性判别变量*/
extern Matrix_typedef w_T;//单纯形乘子w的转置
extern size_t q;//当前所扫描到的非基变量的角标，或是入基变量角标
extern size_t jp;//当前所扫描到的基变量的角标，或是出基变量角标
extern double xq;//某一个非基变量（所有的xq≥0，则结果最优。等价于r≥0或rN≥0.）
extern double rq;//xq对应的，r或者说是rN的成员变量
extern double cq;//xq对应的，c或者说是cN的成员变量
extern Matrix_typedef Nq;//xq对应的，N中的列向量
extern Matrix_typedef Aq;//xq对应的，A中的列向量（与Nq相等，因为N是从A中拆分出来的）
/*改进变量*/
//改进方向
extern Matrix_typedef D;//dq构成的矩阵
extern Matrix_typedef dq;//Dq的xq对应的列，改进方向
//步长
extern double lambda;//迭代步长

/*两阶段法变量*/
extern Matrix_typedef xa;//人工变量，列向量（未知数，不需要输入，??维度），初始化为b！！！！，迭代完成后xa必须全为0，否则原问题不可行。
extern Matrix_typedef Aa;//两阶段法中，人工变量所对应的A的列的矩阵，实际为单位阵I维度为?? × ??
//extern Matrix_typedef x_2;//两阶段法的总变量列向量，是将xa拼在x后面，维度是??+??维度。初始化后，前面的x全为0，后面的xa=b
extern Matrix_typedef x_2;//两阶段法的自变量列向量，xa拼在原问题x的最后面，维度为 ?? + ?? = n_s, m = m_s
extern Matrix_typedef c_2;//两阶段法第一阶段的c，初始化为值全为1的列向量，维度为??，此时B=I，此时单位阵I维度为?? × ??
extern Matrix_typedef A_2;//两阶段法中，人工变量所对应的A的列的矩阵，实际为单位阵I维度为?? × ??，这个矩阵拼接到原问题A的后面形成的矩阵，维度为?? × (?? + ??)
extern Matrix_typedef b_2;//两阶段法中的列向量（??维度）