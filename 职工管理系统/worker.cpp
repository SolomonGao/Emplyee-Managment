#include "worker.h"


Worker::Worker(int ID, string name, int deptID)
{
	this->m_ID = ID;
	this->m_Name = name;
	this->m_deptID = deptID;
}

void Worker::showInfo()
{
	cout << "ְ����ţ�" << this->m_ID
		<< "\tְ��������" << this->m_Name
		<< "\tְ�����ţ�" << this->getDeptName()
		<< "\t��λְ����ɾ�����������" 
		<< endl;
}

string Worker::getDeptName()
{
	return string("Ա��");
}

Worker::~Worker()
{

}