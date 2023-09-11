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
    void Show_Menu();   //展示菜单
    void exitSystem();  //推出系统
    void Save();        //保存数据到文件
    void Add_Emp();     //增加人数
    int get_EmpNum();   //统计人数
    void init_Emp();    //初始化员工
    void Show_Emp();    //显示职工
    void Del_Emp();     //删除职工
    void delById(int id);
    int IsExist(int id);//职工是否存在
    void Mod_Emp();     //修改职工信息
    void Find_Emp();    //查找职工信息
    void Sort_Emp();    //按照职工编号排序
    void Clean_File();
    // 析构函数
    ~WorkerManager();
    
};


