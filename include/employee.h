#pragma once
#include <iostream>
#include <string>
#include "Worker.h"
using namespace std;

class Employee:public Worker
{
public:
    // 构造函数
    Employee(int id, string name, int dId);

    virtual void showInfo();
    virtual string getDepartName();
};

