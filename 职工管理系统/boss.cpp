#include "boss.h"


Boss::Boss(int ID, string name, int deptID)
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_deptID = deptID;
}

void Boss::showInfo()
{
	cout << "ְ����ţ�" << this->m_ID
		<< "\tְ��������" << this->m_Name
		<< "\tְ�����ţ�" << this->getDeptName()
		<< "\t��λְ�𣺷������������"
		<< endl;
}

string Boss::getDeptName()
{
	return string("�ϰ�");
}

Boss::~Boss()
{

}