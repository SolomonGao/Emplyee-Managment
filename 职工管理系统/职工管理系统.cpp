// 职工管理系统.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <fstream>
#include "Management.h"
#include "employee.h"
#include "worker.h"
#include "boss.h"
#include "manager.h"
using namespace std;

int main()
{
    //测试
    //Employee * em1 = NULL;
    //em1 = new Worker(1, "高兴", 1);

    //em1->showInfo();
    //delete em1;
    //em1 = NULL;

    //em1 = new Boss(2, "高兴", 2);
    //em1->showInfo();

     
    int choice = 0;
    Management m_M;
    while (true)
    {
        m_M.showMenu();

        cout << "请输入您的选项: " << endl;
        cin >> choice;

        switch (choice)
        {
        case 0: //退出
            m_M.Exit();
            break;
        case 1: //添加职工
            m_M.add_emp();
            break;
        case 2: //显示职工
            m_M.showEmp(); 
            break;
        case 3: //删除职工
            m_M.delEmp();
            break;
        case 4: //修改职工
            m_M.editEmp();
            break;
        case 5: //查找职工
            m_M.searchEmp();
            break;
        case 6: //排序
            m_M.sortEmp();
            break;
        case 7: //清空
            m_M.cleanFile();
            break;
        default:
            system("cls"); //清屏操作
            break;
        }

    }


    system("pause");

    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
