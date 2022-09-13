#include "Management.h"



Management::Management()
{	
	//初始化的时候打开文件读取数据
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//文件不存在的情况
	if (!ifs.is_open())
	{
		/*cout << "不存在数据文件" << endl;*/
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileEmpty = true;
		ifs.close();
		return;
	}

	//文件存在但是为空的情况
	char ch;
	ifs >> ch; //读取一个字符，
	if (ifs.eof()) //然后用eof判断是否是文件尾部。 如果是说明是文件尾部
	{
		/*cout << "数据文件为空" << endl;*/
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileEmpty = true;
		ifs.close();
		return;
	}

	//文件存在并且有数据的情况
	int num = this->getEmpNum();
	cout << "职工数量为：" << num << endl;
	this->m_EmpNum = num;
	//开辟一片空间
	this->m_EmpArray = new Employee * [this->m_EmpNum];
	this->initEmp();
	//测试
	/*for (int i = 0; i < m_EmpNum; i++)
	{
		cout << this->m_EmpArray[i]->m_ID
			<< this->m_EmpArray[i]->m_Name
			<< this->m_EmpArray[i]->m_deptID << endl;
	}*/

	this->m_FileEmpty = false;




}

void Management::showMenu()
{
	cout << "======================================================" << endl;
	cout << "===============欢迎使用职工管理系统===================" << endl;
	cout << "====================0.退出菜单========================" << endl;
	cout << "====================1.增加职工信息====================" << endl;
	cout << "====================2.显示职工信息====================" << endl;
	cout << "====================3.删除离职员工====================" << endl;
	cout << "====================4.修改职工信息====================" << endl;
	cout << "====================5.查找职工信息====================" << endl;
	cout << "====================6.按照编号排序====================" << endl;
	cout << "====================7.清空所有文档====================" << endl;
	cout << "======================================================" << endl;
	cout << endl;
}

void Management::add_emp()
{
	cout << "请输入添加职工数量:" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Employee** newSpace = new Employee * [newSize];

		//将原来空间下的数据拷贝到新空间
		if (this->m_EmpArray != 0)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		for (int i = 0; i < addNum; i++)
		{
			int addID;
			string addName;
			int addDeptID;

			int check = -1;

			bool pass = false;
			while (pass == false)
			{
				cout << "请输入第" << i + 1 << "个添加的职工信息：" << endl;
				cout << "编号：";
				cin >> addID;
				check = this->exist(addID);
				if (check == -1)
				{
					cout << "姓名：";
					cin.ignore();
					getline(cin, addName);
					cout << "部门编号：" << endl;
					cout << "1. 普通职工" << endl;
					cout << "2. 经理" << endl;
					cout << "3. 老板" << endl;
					cin >> addDeptID;

					Employee* employee = NULL;

					switch (addDeptID)
					{
					case 1:
						employee = new Worker(addID, addName, addDeptID);
						break;
					case 2:
						employee = new Manager(addID, addName, addDeptID);
						break;
					case 3:
						employee = new Boss(addID, addName, addDeptID);
						break;
					default:
						break;
					}

					//把创建好的指针保存起来
					newSpace[i + this->m_EmpNum] = employee;
					//释放原有空间 释放数组要加[]
					delete[] this->m_EmpArray;
					//更改新空间
					this->m_EmpArray = newSpace;
					//更改人数
					this->m_EmpNum = newSize;

					pass = true;
				}
				else
				{
					cout << "该ID已经存在，请重试。" << endl;
				}
			}
			
		}

		cout << "成功添加" << addNum << "名新职工" << endl;

		this->m_FileEmpty = false;

		this->save();
	}
	else
	{
		cout << "输入有误" << endl;
	}
	//完成后清屏 返回上级目录
	system("pause");
	system("cls");
	}

void Management::Exit()
{
	cout << "感谢使用" << endl;
	system("pause");
	exit(0);
}

void Management::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); 
	//写入
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_ID << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_deptID << " "
			<< endl;
	}

	ofs.close();
}

int Management::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//读取到这三个变量里面
	int ID;
	string name;
	int deptID;

	int emp_Num = 0;
	while (ifs >> ID && ifs >> name && ifs >> deptID) //右移运算符 >>读取数据遇到空格或者换行就会停止 所以这样能够读到一排数据
		emp_Num++;

	return emp_Num;
}

void Management::initEmp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int ID;
	string name;
	int deptID;

	int index = 0;
	while (ifs >> ID && ifs >> name && ifs >> deptID)
	{
		Employee* employee = NULL;

		if (deptID == 1)
		{
			employee = new Worker(ID, name, deptID);
		}

		else if (deptID == 2)
		{
			employee = new Manager(ID, name, deptID);
		}

		else
		{
			employee = new Boss(ID, name, deptID);
		}

		this->m_EmpArray[index] = employee;
		index++;
	}

	ifs.close();
}

void Management::showEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件记录不存在或为空！" << endl;
	}

	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

int Management::exist(int id)
{

	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{

		if (this->m_EmpArray[i]->m_ID == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void Management::delEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件记录不存在或为空！" << endl;
	}

	else
	{
		int searchID;
		int index = -1;
		cout << "输入要删除的员工的ID号码：" << endl;
		cin >> searchID;

		index = exist(searchID);

		if (index != -1)
		{

			cout << "成功删除职工：" << this->m_EmpArray[index]->m_Name << endl;
			//数组中的删除本质就是数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
		}

		else
		{
			cout << "职工对应ID不存在！" << endl;
		}
	}

	system("pause");
	system("cls");
}

void Management::editEmp()
{

	if (this->m_FileEmpty)
	{
		cout << "文件记录不存在或为空！" << endl;
	}

	else
	{
		int searchID;
		int ret = -1;
		cout << "输入要修改的员工的ID号码：" << endl;
		cin >> searchID;
		ret = exist(searchID);
		if (ret != -1)
		{
			cout << "找到员工: ";
			this->m_EmpArray[ret]->showInfo();
			int edit = 0;
			cout << "请输入要修改的信息：" << endl;
			cout << "1.ID号码" << endl;
			cout << "2.姓名" << endl;
			cout << "3.部门编号" << endl;
			cin >> edit;
			switch (edit)
			{
			case 1:
			{
				int id;
				int check = -1;
				check = this->exist(searchID);
				cout << "请输入新的ID号码：" << endl;
				cin >> id;
				check = exist(id);
				if (check == -1)
				{
					this->m_EmpArray[ret]->m_ID = id;
					cout << "修改成功" << endl;
				}
				else
				{
					cout << "此ID已经存在" << endl;
				}
				break;

			}
			case 2:
			{
				string name;
				cout << "请输入新的姓名：" << endl;
				cin.ignore();
				cin >> name;
				this->m_EmpArray[ret]->m_Name = name;
				cout << "修改成功" << endl;
				break;
			}
			case 3:
			{
				string name = this->m_EmpArray[ret]->m_Name;
				int ID = this->m_EmpArray[ret]->m_ID;
				int deptID;
				cout << "请输入新的ID号码：" << endl;
				cin >> deptID;
				delete this->m_EmpArray[ret];
				Employee* employee;
				if (deptID == 1)
				{
					employee = new Worker(ID, name, deptID);
				}

				else if (deptID == 2)
				{
					employee = new Manager(ID, name, deptID);
				}

				else
				{
					employee = new Boss(ID, name, deptID);
				}
				
				this->m_EmpArray[ret] = employee;
				cout << "修改成功" << endl;
				this->save();
				break;
			}
			default:
				break;
			}
		}
		else
		{
			cout << "职工对应ID不存在！" << endl;
		}
	}
	
	system("pause");
	system("cls");
}

void Management::searchEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件记录不存在或为空！" << endl;
	}

	else
	{	
		int choice = 0;
		cout << "通过ID查找还是通过姓名查找：" << endl;
		cout << "1.ID" << endl;
		cout << "2.姓名" << endl;
		cin >> choice;

		if (choice == 1)
		{
			int searchID;
			int index = -1;
			cout << "输入要查找的员工的ID号码：" << endl;
			cin >> searchID;

			index = exist(searchID);

			if (index != -1)
			{
				cout << "找到这个职工：" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
			{
				cout << "职工对应ID不存在！" << endl;
			}
		}
		else if (choice == 2)
		{
			string name;
			bool flag = false;
			cout << "请输入要查找的姓名" << endl;
			cin >> name;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}

			if (flag == false)
			{
				cout << "未找到叫做“" << name << "”的职工" << endl;
			}
		}
		else
		{
			cout << "输入有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

void Management::sortEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "文件记录不存在或为空！" << endl;
	}

	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int temp = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (this->m_EmpArray[temp]->m_ID > this->m_EmpArray[j]->m_ID)
				{
					temp = j;
				}
			}

			if (i != temp)
			{
				Employee* tempEmp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[temp];
				m_EmpArray[temp] = tempEmp;
			}
		}

		cout << "排序成功" << endl;
		this->save();
		this->showEmp();
	}
	
	system("pause");
	system("cls");
}

void Management::cleanFile()
{
	//打开模式 ios::trunc 如果存在文件则删除并重新创建
	ofstream ofs(FILENAME, ios::trunc);
	ofs.close();

	//如果存在对象则要清空对象和内部维护的整个数组清空
	//释放数组需要把内部维护的每个对象释放

	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			delete this->m_EmpArray[i];
		}
	}

	delete[] m_EmpArray;
	this->m_EmpNum = 0;
	m_EmpArray = NULL;
	this->m_FileEmpty = true;

	cout << "成功清空文件" << endl;
}


Management::~Management()
{
	if (m_EmpArray != NULL)
	{
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
			}
		}

		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;	
		this->m_EmpNum = 0;
		this->m_FileEmpty = true;
	}
}


//int partition(Employee** array, int left, int right)
//{
//	int temp;
//	temp = array[left]->m_ID;
//	while (left < right)
//	{
//		while (temp <= array[right]->m_ID && left < right)
//			right--;
//		array[left]->m_ID = array[right]->m_ID;
//		while (temp >= array[left]->m_ID && left < right)
//			left++;
//		array[right]->m_ID = array[left]->m_ID;
//	}
//	array[left]->m_ID = temp;
//	return left;
//}
//
//void quickSort(Employee** array, int left, int right)
//{
//	if (left < right)
//	{
//		int mid = 0;
//		mid = partition(array, left, right);
//		quickSort(array, left, mid - 1);
//		quickSort(array, mid - 1, right);
//	}
//
//}