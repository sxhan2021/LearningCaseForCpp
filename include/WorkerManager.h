#pragma once
#include <iostream>
#include <fstream>
#include "Worker.h"
#define FILENAME "empFile.txt"
using namespace std;

class WorkerManager
{
public:
    int m_EmpNum;   // 记录文件中的人数个数
    Worker ** m_EmpArray;   // 员工数组的指针 <这是一个指向 指针 的 指针数组，每个指针 指向 一个Worker类型的对象>

    bool m_FileIsEmpty;
    
    // 构造函数
    WorkerManager();
    // 展示菜单
    void Show_Menu();
    void exitSystem();
    void Save();
    void Add_Emp();

    // 析构函数
    ~WorkerManager();
    
};

