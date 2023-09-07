#include <iostream>
using namespace std;

#include "WorkerManager.h"
#include "Worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"

void test01()
{
    Worker *worker;
    worker = new Employee(1, "张三", 1);
    worker->showInfo();
    cout << worker->getDepartName() << endl;

    worker = new Boss(2, "李四", 2);
    worker->showInfo();
    cout << worker->getDepartName() << endl;

    worker = new Manager(3, "王五", 3);
    worker->showInfo();
    cout << worker->getDepartName() << endl;
}


int main()
{
    WorkerManager wm;
    int choice;
    while (true)
    {
        wm.Show_Menu();
        cout << "请输入您的选择: " << endl;
        cin >> choice; 
        switch (choice)
        {
        case 0:                         // 退出管理系统
            wm.exitSystem();
            break;
        case 1:
            wm.Add_Emp();      // 增加职员信息
            break;
        case 2:                         // 显示职工信息
            // wm.showClerk(filePath);
            break;
        case 3:                         // 删除离职职工
            cout << "输入要删除的职工编号" << endl;
            int num;
            cin >> num;
            // wm.deleteClerk(num);
            break;
        case 4:                         // 修改职工信息

            break;
        case 5:                         // 查找职工信息

            break;
        case 6:                         // 按照编号排序

            break;
        case 7:                         // 清空所有文档

            break;

        default:
            system("cls");
            break;
        }
    }
    
    // test01();
    return 0;
}
