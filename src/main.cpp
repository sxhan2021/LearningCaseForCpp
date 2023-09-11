#include <iostream>
using namespace std;

#include "WorkerManager.h"
#include "Worker.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"

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
            wm.Show_Emp();
            break;
        case 3:                         // 删除离职职工
            wm.Del_Emp();
            break;
        case 4:                         // 修改职工信息
            wm.Mod_Emp();
            break;
        case 5:                         // 查找职工信息
            wm.Find_Emp();
            break;
        case 6:                         // 按照编号排序
            wm.Sort_Emp();
            break;
        case 7:                         // 清空所有文档
            wm.Clean_File();
            break;

        default:
            system("cls");
            break;
        }
    }
    return 0;
}
