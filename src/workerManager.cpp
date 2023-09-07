#include <iostream>
#include <string>
#include "WorkerManager.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"

using namespace std;

WorkerManager::WorkerManager()
{
    this->m_EmpNum = 0;         // 初始化人数
    this->m_EmpArray = NULL;    // 初始化数组指针
}

void WorkerManager::Show_Menu()
{
    cout << "***** 欢迎使用职工管理系统！*****" << endl;
    cout << "*****   0.退出管理系统  *****" << endl; 
    cout << "*****   1.增加职工信息  *****" << endl; 
    cout << "*****   2.显示职工信息  *****" << endl; 
    cout << "*****   3.删除离职职工  *****" << endl; 
    cout << "*****   4.修改职工信息  *****" << endl; 
    cout << "*****   5.查找职工信息  *****" << endl; 
    cout << "*****   6.按照编号排序  *****" << endl; 
    cout << "*****   7.清空所有文档  *****" << endl;  
}
void WorkerManager::exitSystem()
{
    cout << "欢迎下次使用～" << endl;
    // cin.get();
    // cin.clear();
    exit(0);
}
void WorkerManager::Add_Emp()
{
    cout << "请输入增加职工的数量：" << endl;
    int addNum;
    cin >> addNum;
    if (addNum > 0)
    {
        int newSize = this->m_EmpNum + addNum;      // 计算新空间大小
        Worker ** newSpace = new Worker*[newSize];  // 开辟新空间
        // 将原空间下的内容存放到新空间下
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
        }
        // 输入新数据
        for (int i = 0; i < addNum; i++)
        {
            int id, dSelect;
            string name;
            cout << "请输入第" << i+1 << "个新职工编号：" << endl;
            cin >> id;              // 可以判断下id是否为int，如果输入错误，会陷入死循环
            cout << "请输入第" << i+1 << "个新职工姓名：" << endl; 
            cin >> name;            // 可以判断下name是否为string，如果输入错误，会陷入死循环
            cout << "请选择该职工的岗位：" << endl;
            cout << "1.普通职工" << "\n2.经理" << "\n3.老板" << endl;
            cin >> dSelect;         // 同理

            Worker *worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(id, name, 1);
                break;
            case 2:
                worker = new Manager(id, name, 2);
                break;
            case 3:
                worker = new Boss(id, name, 3);
                break;
            default:
                break;
            }
            newSpace[this->m_EmpNum + i] = worker;
        }
        delete[] this->m_EmpArray;     // 释放原有空间
        this->m_EmpArray = newSpace;    // 更改新空间的指向 
        this->m_EmpNum = newSize;       // 更新 新的个数
        cout << "成功添加" << addNum << "名新职工！" << endl;
        this->Save();   // 保存数据
    }
    else
    {
        cout << "输入有误" << endl;
    } 
    
}
void WorkerManager::Save()
{
    ofstream ofs(FILENAME, ios::out | ios::app);
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << "\t"
            << this->m_EmpArray[i]->m_Name << "\t"
            << this->m_EmpArray[i]->m_DepartId << endl;
    }
    ofs.close();   
}

WorkerManager::~WorkerManager()
{

}
