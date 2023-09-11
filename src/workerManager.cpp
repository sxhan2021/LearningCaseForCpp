#include <iostream>
#include <string>
#include "WorkerManager.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"

using namespace std;

WorkerManager::WorkerManager()
{
    ifstream ifs(FILENAME, ios::in);
    // 文件不存在的情况
    if (!ifs.is_open())
    {
        // cout << "文件不存在" << endl;   // 测试输出
        this->m_EmpNum = 0;         // 初始化人数
        this->m_FileIsEmpty = true; // 初始化文件为空标志
        this->m_EmpArray = NULL;    // 初始化数组指针
        ifs.close();
        return;
    } 
    // 文件存在，并且没有记录
    char ch;
    ifs >> ch;  // 先读取
    if (ifs.eof())  // eof 文件为空的标志
    {
        // cout << "文件为空!" << endl;
        this->m_EmpNum = 0;         // 初始化人数
        this->m_FileIsEmpty = true; // 初始化文件为空标志
        this->m_EmpArray = NULL;    // 初始化数组指针
        ifs.close();
        return;
    } 
    //文件存在，并且记录数据
    int num = this->get_EmpNum();
    cout << "职工个数为：" << num << endl;  //测试代码
    this->m_EmpNum = num;           // 更新成员属性
    
    this->m_EmpArray = new Worker *[this->m_EmpNum]; //根据职工数创建数组
    
    this->init_Emp();   //初始化成员
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
        this->m_FileIsEmpty = false;    // 更新职工不为空的标志
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
    ofstream ofs(FILENAME, ios::out );      // | ios::app
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs << this->m_EmpArray[i]->m_Id << "\t"
            << this->m_EmpArray[i]->m_Name << "\t"
            << this->m_EmpArray[i]->m_DepartId << endl;
    }
    ofs.close();   
}
int WorkerManager::get_EmpNum()
{
    ifstream ifs(FILENAME, ios::in);
    int id, dId;
    string name;
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        num++;
    }
    ifs.close();
    return num;
}
void WorkerManager::init_Emp()
{
    ifstream ifs(FILENAME, ios::in);
    int id, dId;
    string name;
    int index = 0;
    while (ifs >> id && ifs >> name && ifs >> dId)
    {
        Worker *worker = NULL;
        if (dId == 1)
        {
            worker = new Employee(id, name, dId);
        }
        else if (dId == 2)
        {
            worker = new Manager(id, name, dId);
        }
        else
        {
            worker = new Boss(id, name, dId);
        }
        //存放在数组中
        this->m_EmpArray[index] = worker;
        index++; 
    }
    ifs.close();
}
void WorkerManager::Show_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "没有职员" << endl;
    }
    else
    {
        for (int i = 0; i < m_EmpNum; i++)
        {
            this->m_EmpArray[i]->showInfo();    // 利用多态调用程序接口
        } 
    }
}
void WorkerManager::Del_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else
    {
        cout << "输入要删除员工的编号：" << endl;
        int id;
        cin >> id;
        this->delById(id);
    }
}
void WorkerManager::delById(int id)
{
    int index = this->IsExist(id);
    if (index != -1)
    {
        for (int i = index; i < this->m_EmpNum - 1; i++)
        {
            this->m_EmpArray[i] = this->m_EmpArray[i+1];
        }
        this->m_EmpNum--;
        this->Save();
        cout << "删除成功" << endl;
    }
    else
    {
        cout << "删除失败或未找到此人！" << endl;
    }  
}
int WorkerManager::IsExist(int id)
{
    int index = -1;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if (this->m_EmpArray[i]->m_Id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}
void WorkerManager::Mod_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "文件不存在或记录为空！" << endl;
    }
    else
    {
        cout << "请输入要修改信息的职工编号:" << endl;
        int id;
        cin >> id;
        int index = this->IsExist(id);
        if (index != -1)
        {
            this->delById(id);     //先删除原来的数据
            int newId = 0;
            string newName = "";
            int dSelect = 0;

            cout << "查到：" << id << " 号员工，请输入新职工号：" << endl;
            cin >> newId;    
            cout << "请输入新姓名：" << endl;
            cin >> newName;  

            cout << "请输入岗位：" << endl;
            cout << "\t1.普通职工" << "\n"
                << "\t2.经理" << "\n"
                << "\t3.老板" << endl;
            cin >> dSelect;

            Worker *worker = NULL;
            switch (dSelect)
            {
            case 1:
                worker = new Employee(newId, newName, dSelect);
                break;
            case 2:
                worker = new Manager(newId, newName, dSelect);
                break;
            case 3:
                worker = new Boss(newId, newName, dSelect);
                break;
            default:
                break;
            }
            // this->m_EmpArray[index] = worker;   // 更改数据到数组中
            // 增加职工     (修改职工信息 -> 先删除员工，再增加员工)
            int newSize = this->m_EmpNum + 1;      // 计算新空间大小
            Worker ** newSpace = new Worker*[newSize];  // 开辟新空间
            // 将原空间下的内容存放到新空间下
            if (this->m_EmpArray != NULL)
            {
                for (int i = 0; i < this->m_EmpNum; i++)
                {
                    newSpace[i] = this->m_EmpArray[i];
                }
            }
            newSpace[this->m_EmpNum] = worker;

            delete[] this->m_EmpArray;     // 释放原有空间
            this->m_EmpArray = newSpace;    // 更改新空间的指向 
            this->m_EmpNum = newSize;       // 更新 新的个数
            this->m_FileIsEmpty = false;    // 更新职工不为空的标志
            cout << "修改成功!" << endl;
            this->Save();
        } 
        else
        {
            cout << "修改失败，查无此人" << endl;
        } 
    }
}
void WorkerManager::Find_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "记录为空或文件不存在！" << endl;
    }
    else
    {
        cout << "请选择查找方式：" << "\n"
            << "\t1.按照职工编号" << "\n"
            << "\t2.按照职工姓名" << endl;
        int select;
        cin >> select;
        if (select == 1)
        {
            cout << "请输入职工编号：" << endl;
            int newId;
            cin >> newId;
            int ret = IsExist(newId);
            if (ret != -1)
            {
                cout << "查找成功！该职工信息如下：" << endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else
            {
                cout << "查找失败，查无此人！" << endl;
            }   
        }
        else if (select == 2)
        {
            cout << "请输入职工姓名：" << endl;
            string newName;
            cin >> newName;
            bool flag = false;
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_Name == newName)
                {
                    cout << "查找成功，职工编号为: " 
                        << this->m_EmpArray[i]->m_Id
                        << "号的信息如下：" << endl; 
                    flag = true;
                    this->m_EmpArray[i]->showInfo();  
                }
            }
            if (flag == false)
            {
                cout << "查找失败，查无此人！" << endl;
            }     
        }
        else
        {
            cout << "输入选项有误！" << endl;
        }  
    } 
}
void WorkerManager::Sort_Emp()
{
    if (this->m_FileIsEmpty)
    {
        cout << "记录为空或文件不存在！" << endl;
    }
    else
    {
        cout << "请选择排序的顺序：\n" 
            << "\t1.升序\n" << "\t2.降序" << endl;
        int select;
        cin >> select;
        if (select == 1)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    if (this->m_EmpArray[i]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        Worker *tmp = this->m_EmpArray[j];
                        this->m_EmpArray[j] = this->m_EmpArray[i];
                        this->m_EmpArray[i] = tmp;
                    }  
                }
            }
        }
        else if (select == 2)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    if (this->m_EmpArray[i]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        Worker *tmp = this->m_EmpArray[j];
                        this->m_EmpArray[j] = this->m_EmpArray[i];
                        this->m_EmpArray[i] = tmp;
                    }  
                }
            }
        }
        else
        {
            cout << "输入有误！" << endl;
        }
        this->Save();
        cout << "排序成功,排序之后的结果为：" << endl;
        this->Show_Emp();
    }
}
void WorkerManager::Clean_File()
{
    cout << "确认清空？\n"
        << "  1.确认\n" << "  2.返回" << endl;
    int select = 0;
    cin >> select;
    if (select == 1)
    {
       ofstream ofs(FILENAME, ios::trunc);
       ofs.close();
       if (this->m_EmpArray != NULL)
       {
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
        this->m_EmpNum = 0;
        this->m_FileIsEmpty = true;
       }
       cout << "清空成功！" << endl;
    } 
}

WorkerManager::~WorkerManager()
{
    if (this->m_EmpArray != NULL)
    {
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
}
