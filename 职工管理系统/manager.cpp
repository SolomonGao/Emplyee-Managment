#include "manager.h"


Manager::Manager(int ID, string name, int deptID)
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_deptID = deptID;
}

void Manager::showInfo()
{
	cout << "ְ����ţ�" << this->m_ID
		<< "\tְ��������" << this->m_Name
		<< "\tְ�����ţ�" << this->getDeptName()
		<< "\t��λְ������ϰ彻�������񲢷��������Ա��"
		<< endl;
}

string Manager::getDeptName()
{
	return string("����");
}

Manager::~Manager()
{

}