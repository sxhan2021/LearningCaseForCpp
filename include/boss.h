#pragma once
#include <iostream>
#include <string>
#include "Worker.h"

using namespace std;

class Boss:public Worker
{
public:
    // 构造函数
    Boss(int id, string name, int dId);

    virtual void showInfo();
    virtual string getDepartName();
};
