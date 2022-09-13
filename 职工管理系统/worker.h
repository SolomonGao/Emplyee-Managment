#pragma once
#include <iostream>
using namespace std;
#include <string>
#include "employee.h"

class Worker : public Employee
{
public:

	Worker(int ID, string name, int deptID);

	void showInfo();

	string getDeptName();

	~Worker();

};