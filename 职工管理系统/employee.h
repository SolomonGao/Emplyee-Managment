#pragma once
#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#define FILENAME "empFILE.txt"

class Employee
{
public:

	virtual void showInfo() = 0;

	virtual string getDeptName() = 0;

	int m_ID;
	string m_Name;
	int m_deptID;


};
//����ְ�������һ��ְ����
//�ö�̬�ķ�ʽ����
//ְ�����ԣ���ţ�����������
//ְ����Ϊ����λ��Ϣ����ȡ��λ����