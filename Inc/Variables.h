#pragma once

#include "Project.h"

/*ȫ�ֱ�������*/
//extern Matrix_typedef Matrix;

/*��׼�ͱ���*/
extern Matrix_typedef A;//��ά����m �� n
extern Matrix_typedef c;//��������nά�ȣ�
extern Matrix_typedef b;//��������mά�ȣ�
extern Matrix_typedef x;//��������δ֪��������Ҫ���룬??ά�ȣ�
extern size_t m;//ά��m������Ҫ����
extern size_t n;//ά��n������Ҫ����

/*����׼�Ͳ�ֱ���*/
//���������ı���
extern Matrix_typedef A_s;//��ά����m_s �� n_s
extern Matrix_typedef c_s;//��������n_sά�ȣ�
extern Matrix_typedef b_s;//��������m_sά�ȣ�
extern Matrix_typedef x_s;//����������ʼ�㣬����Ҫ���룬n_sά�ȣ�
extern size_t m_s;//ά��m_s������Ҫ����
extern size_t n_s;//ά��n_s������Ҫ����
//A��ֳɵ�
extern Matrix_typedef B;//����m �� m�ķ���
extern Matrix_typedef N;//�ǻ���m �� (n - m) ά�ľ���
//c��ֳɵ�
extern Matrix_typedef cB;//��c������Ϊ m ������������
extern Matrix_typedef cN;//�ǻ�c������Ϊ n - m ������������
//x��ֳɵ�
extern Matrix_typedef xB;//������������Ϊ m ������������
extern Matrix_typedef xN;//�ǻ�����������Ϊ n - m ������������

/*�����̱���*/
/*�����±꼯��*/
extern Matrix_typedef IB;//���������±꼯��		���ǳ���Ҫ��������
extern Matrix_typedef IN;//�ǻ��������±꼯��		���ǳ���Ҫ��������
/*����������ر���*/
extern Matrix_typedef r;//��Լ�������������еı�����0���������š��ȼ���rN��0.��
extern Matrix_typedef rB;//������Լ��������������Ϊ m ������������
extern Matrix_typedef rN;//�ǻ�����Լ��������������Ϊ n - m ����������
/*�������б����*/
extern Matrix_typedef w_T;//�����γ���w��ת��
extern size_t q;//��ǰ��ɨ�赽�ķǻ������ĽǱ꣬������������Ǳ�
extern size_t jp;//��ǰ��ɨ�赽�Ļ������ĽǱ꣬���ǳ��������Ǳ�
extern double xq;//ĳһ���ǻ����������е�xq��0���������š��ȼ���r��0��rN��0.��
extern double rq;//xq��Ӧ�ģ�r����˵��rN�ĳ�Ա����
extern double cq;//xq��Ӧ�ģ�c����˵��cN�ĳ�Ա����
extern Matrix_typedef Nq;//xq��Ӧ�ģ�N�е�������
extern Matrix_typedef Aq;//xq��Ӧ�ģ�A�е�����������Nq��ȣ���ΪN�Ǵ�A�в�ֳ����ģ�
/*�Ľ�����*/
//�Ľ�����
extern Matrix_typedef D;//dq���ɵľ���
extern Matrix_typedef dq;//Dq��xq��Ӧ���У��Ľ�����
//����
extern double lambda;//��������

/*���׶η�����*/
extern Matrix_typedef xa;//�˹���������������δ֪��������Ҫ���룬mά�ȣ�����ʼ��Ϊb����������������ɺ�xa����ȫΪ0������ԭ���ⲻ���С�
extern Matrix_typedef Aa;//���׶η��У��˹���������Ӧ��A���еľ���ʵ��Ϊ��λ��Iά��Ϊm �� m
//extern Matrix_typedef x_2;//���׶η����ܱ������������ǽ�xaƴ��x���棬ά����n+mά�ȡ���ʼ����ǰ���xȫΪ0�������xa=b
extern Matrix_typedef x_2;//���׶η����Ա�����������xaƴ��ԭ����x������棬ά��Ϊ n + m = n_s, m = m_s
extern Matrix_typedef c_2;//���׶η���һ�׶ε�c����ʼ��ΪֵȫΪ1����������ά��Ϊm����ʱB=I����ʱ��λ��Iά��Ϊm �� m
extern Matrix_typedef A_2;//���׶η��У��˹���������Ӧ��A���еľ���ʵ��Ϊ��λ��Iά��Ϊm �� m���������ƴ�ӵ�ԭ����A�ĺ����γɵľ���ά��Ϊm �� (n + m)
extern Matrix_typedef b_2;//���׶η��е���������mά�ȣ�
