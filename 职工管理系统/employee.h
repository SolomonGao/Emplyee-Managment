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
//三种职工抽象成一个职工类
//用多态的方式管理
//职工属性：编号，姓名，部门
//职工行为：岗位信息，获取岗位名称