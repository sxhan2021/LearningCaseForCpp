#pragma once
#include <iostream>
#include <string>
using namespace std;

class Worker
{
public:
    int m_Id;           // 编号
    string m_Name;      // 姓名
    int m_DepartId;  // 部门编号

    virtual void showInfo() = 0;
    virtual string getDepartName() = 0;
};


