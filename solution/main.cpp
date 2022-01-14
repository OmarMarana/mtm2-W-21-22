#include <iostream>
#include "Employee.h"
#include "Manager.h"
#include "Workplace.h"
#include "City.h"
//#include "City.h"
#include <assert.h>
#include "exceptions.h"
#include "Citizen.h"
using namespace mtm;
using std::cout;
using std::endl;


class HiringCondition {
public:
    bool operator()(Employee *emp) {
        return true;
    }
};


int main()
{
    City c1("haifa");

    // // Skill s1(1,"Python",15);
    // // s1 = 1 + s1 + 1;
    
    // // std::cout << s1.getRequiredPoints() << "\n";


    // Employee e1(10,"name","1", 2001);
    // Employee e2(7,"name","2", 2002);
    // Employee e3(11,"name","3", 2003);
    // Employee e4(1,"name","4", 2004);


    // Manager m1(100,"o","m", 2001);
    // Manager m2(200,"w","e", 2001);
    // Manager m3(5,"1","2", 2001);
    // Manager m4(10,"w","e", 2001);
    // Manager m5(1,"w","e", 2001);
    
    // Skill s1(10,"s1",0);
    // Skill s2(3,"s2",0);
    // Skill s3(2,"s3",0);
    // Skill s4(1,"s4",0);
    // Skill s5(5,"s5",0);
    // Skill s6(4,"s6",0);
    

    // e1.learnSkill(s1);
    // e1.learnSkill(s2);
    // e1.learnSkill(s3);
    // e1.learnSkill(s4);
    // e1.learnSkill(s5);
    // e1.learnSkill(s6);


    HiringCondition c;
    Workplace wp1(10,"meta",100,200);

    c1.createWorkplace(1,"1",12,13);
    c1.addManager(1,"o","m",2001);
    c1.hireManagerAtWorkplace(1,1);
    c1.addEmployee(321312321,"mohammad","ghommaid",1998);
    c1.hireEmployeeAtWorkplace(c,321312321,1,1);
    c1.fireEmployeeAtWorkplace(321312321,1,1);
    c1.addEmployee(10,"x1","y1",1998);
    c1.addEmployee(2,"x2","y2",1998);
    c1.addEmployee(5,"x3","y3",1998);
    c1.addEmployee(4,"x4","y4",1998);
    c1.hireEmployeeAtWorkplace(c,10,1,1);
    c1.hireEmployeeAtWorkplace(c,2,1,1);
    c1.hireEmployeeAtWorkplace(c,5,1,1);
    c1.hireEmployeeAtWorkplace(c,4,1,1);

    c1.getAllAboveSalary(std::cout,2);

    // e1.printLong(std::cout);

    // m1.addEmployee(&e1);
    // m1.addEmployee(&e2);
    // m1.addEmployee(&e3);
    // m1.addEmployee(&e4);
    // m1.printLong(cout);

    

    // wp1.hireManager(&m1);
    // wp1.hireManager(&m2);
    // wp1.hireManager(&m3);
    // wp1.hireManager(&m4);
    // wp1.hireManager(&m5);
    // wp1.hireEmployee(c,&e1,100);
    // wp1.hireEmployee(c,&e2,100);
    // wp1.hireEmployee(c,&e3,100);
    // wp1.hireEmployee(c,&e4,100);


   
    // m1.printLong(cout);
    // m1.removeEmployee(2);
    // m1.removeEmployee(3);
    // m1.removeEmployee(4);
    // m1.printLong(cout);


    std::cout << "hello1" << std::endl;
    return 0;
}