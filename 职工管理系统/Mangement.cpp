#include "Management.h"



Management::Management()
{	
	//��ʼ����ʱ����ļ���ȡ����
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//�ļ������ڵ����
	if (!ifs.is_open())
	{
		/*cout << "�����������ļ�" << endl;*/
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����ڵ���Ϊ�յ����
	char ch;
	ifs >> ch; //��ȡһ���ַ���
	if (ifs.eof()) //Ȼ����eof�ж��Ƿ����ļ�β���� �����˵�����ļ�β��
	{
		/*cout << "�����ļ�Ϊ��" << endl;*/
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����ڲ��������ݵ����
	int num = this->getEmpNum();
	cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;
	//����һƬ�ռ�
	this->m_EmpArray = new Employee * [this->m_EmpNum];
	this->initEmp();
	//����
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
	cout << "===============��ӭʹ��ְ������ϵͳ===================" << endl;
	cout << "====================0.�˳��˵�========================" << endl;
	cout << "====================1.����ְ����Ϣ====================" << endl;
	cout << "====================2.��ʾְ����Ϣ====================" << endl;
	cout << "====================3.ɾ����ְԱ��====================" << endl;
	cout << "====================4.�޸�ְ����Ϣ====================" << endl;
	cout << "====================5.����ְ����Ϣ====================" << endl;
	cout << "====================6.���ձ������====================" << endl;
	cout << "====================7.��������ĵ�====================" << endl;
	cout << "======================================================" << endl;
	cout << endl;
}

void Management::add_emp()
{
	cout << "���������ְ������:" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0)
	{
		//�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;

		//�����¿ռ�
		Employee** newSpace = new Employee * [newSize];

		//��ԭ���ռ��µ����ݿ������¿ռ�
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
				cout << "�������" << i + 1 << "����ӵ�ְ����Ϣ��" << endl;
				cout << "��ţ�";
				cin >> addID;
				check = this->exist(addID);
				if (check == -1)
				{
					cout << "������";
					cin.ignore();
					getline(cin, addName);
					cout << "���ű�ţ�" << endl;
					cout << "1. ��ְͨ��" << endl;
					cout << "2. ����" << endl;
					cout << "3. �ϰ�" << endl;
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

					//�Ѵ����õ�ָ�뱣������
					newSpace[i + this->m_EmpNum] = employee;
					//�ͷ�ԭ�пռ� �ͷ�����Ҫ��[]
					delete[] this->m_EmpArray;
					//�����¿ռ�
					this->m_EmpArray = newSpace;
					//��������
					this->m_EmpNum = newSize;

					pass = true;
				}
				else
				{
					cout << "��ID�Ѿ����ڣ������ԡ�" << endl;
				}
			}
			
		}

		cout << "�ɹ����" << addNum << "����ְ��" << endl;

		this->m_FileEmpty = false;

		this->save();
	}
	else
	{
		cout << "��������" << endl;
	}
	//��ɺ����� �����ϼ�Ŀ¼
	system("pause");
	system("cls");
	}

void Management::Exit()
{
	cout << "��лʹ��" << endl;
	system("pause");
	exit(0);
}

void Management::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); 
	//д��
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

	//��ȡ����������������
	int ID;
	string name;
	int deptID;

	int emp_Num = 0;
	while (ifs >> ID && ifs >> name && ifs >> deptID) //��������� >>��ȡ���������ո���߻��оͻ�ֹͣ ���������ܹ�����һ������
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
		cout << "�ļ���¼�����ڻ�Ϊ�գ�" << endl;
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
		cout << "�ļ���¼�����ڻ�Ϊ�գ�" << endl;
	}

	else
	{
		int searchID;
		int index = -1;
		cout << "����Ҫɾ����Ա����ID���룺" << endl;
		cin >> searchID;

		index = exist(searchID);

		if (index != -1)
		{

			cout << "�ɹ�ɾ��ְ����" << this->m_EmpArray[index]->m_Name << endl;
			//�����е�ɾ�����ʾ�������ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
		}

		else
		{
			cout << "ְ����ӦID�����ڣ�" << endl;
		}
	}

	system("pause");
	system("cls");
}

void Management::editEmp()
{

	if (this->m_FileEmpty)
	{
		cout << "�ļ���¼�����ڻ�Ϊ�գ�" << endl;
	}

	else
	{
		int searchID;
		int ret = -1;
		cout << "����Ҫ�޸ĵ�Ա����ID���룺" << endl;
		cin >> searchID;
		ret = exist(searchID);
		if (ret != -1)
		{
			cout << "�ҵ�Ա��: ";
			this->m_EmpArray[ret]->showInfo();
			int edit = 0;
			cout << "������Ҫ�޸ĵ���Ϣ��" << endl;
			cout << "1.ID����" << endl;
			cout << "2.����" << endl;
			cout << "3.���ű��" << endl;
			cin >> edit;
			switch (edit)
			{
			case 1:
			{
				int id;
				int check = -1;
				check = this->exist(searchID);
				cout << "�������µ�ID���룺" << endl;
				cin >> id;
				check = exist(id);
				if (check == -1)
				{
					this->m_EmpArray[ret]->m_ID = id;
					cout << "�޸ĳɹ�" << endl;
				}
				else
				{
					cout << "��ID�Ѿ�����" << endl;
				}
				break;

			}
			case 2:
			{
				string name;
				cout << "�������µ�������" << endl;
				cin.ignore();
				cin >> name;
				this->m_EmpArray[ret]->m_Name = name;
				cout << "�޸ĳɹ�" << endl;
				break;
			}
			case 3:
			{
				string name = this->m_EmpArray[ret]->m_Name;
				int ID = this->m_EmpArray[ret]->m_ID;
				int deptID;
				cout << "�������µ�ID���룺" << endl;
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
				cout << "�޸ĳɹ�" << endl;
				this->save();
				break;
			}
			default:
				break;
			}
		}
		else
		{
			cout << "ְ����ӦID�����ڣ�" << endl;
		}
	}
	
	system("pause");
	system("cls");
}

void Management::searchEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "�ļ���¼�����ڻ�Ϊ�գ�" << endl;
	}

	else
	{	
		int choice = 0;
		cout << "ͨ��ID���һ���ͨ���������ң�" << endl;
		cout << "1.ID" << endl;
		cout << "2.����" << endl;
		cin >> choice;

		if (choice == 1)
		{
			int searchID;
			int index = -1;
			cout << "����Ҫ���ҵ�Ա����ID���룺" << endl;
			cin >> searchID;

			index = exist(searchID);

			if (index != -1)
			{
				cout << "�ҵ����ְ����" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
			{
				cout << "ְ����ӦID�����ڣ�" << endl;
			}
		}
		else if (choice == 2)
		{
			string name;
			bool flag = false;
			cout << "������Ҫ���ҵ�����" << endl;
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
				cout << "δ�ҵ�������" << name << "����ְ��" << endl;
			}
		}
		else
		{
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}

void Management::sortEmp()
{
	if (this->m_FileEmpty)
	{
		cout << "�ļ���¼�����ڻ�Ϊ�գ�" << endl;
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

		cout << "����ɹ�" << endl;
		this->save();
		this->showEmp();
	}
	
	system("pause");
	system("cls");
}

void Management::cleanFile()
{
	//��ģʽ ios::trunc ��������ļ���ɾ�������´���
	ofstream ofs(FILENAME, ios::trunc);
	ofs.close();

	//������ڶ�����Ҫ��ն�����ڲ�ά���������������
	//�ͷ�������Ҫ���ڲ�ά����ÿ�������ͷ�

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

	cout << "�ɹ�����ļ�" << endl;
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