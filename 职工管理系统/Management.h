#pragma once //��ֹͷ�ļ��ظ�����
#include <iostream>
#include <string>
#include <fstream>
#include "employee.h"
#include "boss.h"
#include "worker.h"
#include "manager.h"
using namespace std;

class Management
{
public:
	Management();
		//�˵�չʾ
	void showMenu();
	void Exit();
	void add_emp();
	void save();
	int getEmpNum();
	void initEmp();
	void showEmp();

	int exist(int id);
	void delEmp();

	void editEmp();

	void searchEmp();

	void sortEmp();

	void cleanFile();

	int m_EmpNum;
	Employee** m_EmpArray;
	bool m_FileEmpty;

	~Management();

}; 
