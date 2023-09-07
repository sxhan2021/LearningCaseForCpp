#pragma once
#include <iostream>
#include <string>
#include "Worker.h"

using namespace std;

class Manager:public Worker
{
public:
    // 构造函数
    Manager(int id, string name, int dId);

    virtual void showInfo();
    virtual string getDepartName();
};
