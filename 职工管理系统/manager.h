#pragma once
#include <iostream>
using namespace std;
#include <string>
#include "employee.h"

class Manager : public Employee
{
public:

	Manager(int ID, string name, int deptID);

	void showInfo();

	string getDeptName();

	~Manager();

};