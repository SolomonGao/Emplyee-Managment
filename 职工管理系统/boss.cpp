#include "boss.h"


Boss::Boss(int ID, string name, int deptID)
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_deptID = deptID;
}

void Boss::showInfo()
{
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t职工部门：" << this->getDeptName()
		<< "\t岗位职责：发布任务给经理"
		<< endl;
}

string Boss::getDeptName()
{
	return string("老板");
}

Boss::~Boss()
{

}