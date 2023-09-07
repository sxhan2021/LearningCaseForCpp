#include <iostream>
#include <string>
#include "manager.h"
using namespace std;

Manager::Manager(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DepartId = dId;
}

void Manager::showInfo()
{
    cout << "职工编号：" << this->m_Id
        << "\t职工姓名：" << this->m_Name
        << "\t岗位：" << this->getDepartName()
        << "\t岗位职责：完成老板给的任务，并下发任务给员工" << endl; 
}

string Manager::getDepartName()
{
    return string("经理");
}
