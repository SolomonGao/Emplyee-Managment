#include "worker.h"


Worker::Worker(int ID, string name, int deptID)
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_deptID = deptID;
}

void Worker::showInfo()
{
	cout << "职工编号：" << this->m_ID
		<< "\t职工姓名：" << this->m_Name
		<< "\t职工部门：" << this->getDeptName()
		<< "\t岗位职责：完成经理交给的任务" 
		<< endl;
}

string Worker::getDeptName()
{
	return string("员工");
}

Worker::~Worker()
{

}