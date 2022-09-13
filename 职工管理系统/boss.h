#pragma once
#include <iostream>
using namespace std;
#include <string>
#include "employee.h"

class Boss : public Employee
{
public:

	Boss(int ID, string name, int deptID);

	void showInfo();

	string getDeptName();

	~Boss();

};
