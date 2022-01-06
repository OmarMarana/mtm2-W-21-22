#include <iostream>
#include "Employee.h"
#include "Manager.h"
#include "WorkPlace.h"
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
    
    Employee e1(10,"name","1", 2001);
    Employee e2(7,"name","2", 2002);
    Employee e3(11,"name","3", 2003);
    Employee e4(1,"name","4", 2004);


    Manager m1(100,"o","m", 2001);
    Manager m2(200,"w","e", 2001);

    
    Skill s1(4,"s1",0);
    Skill s2(3,"s2",0);
    Skill s3(2,"s3",0);


    e1.learnSkill(s1);
    e1.learnSkill(s2);
    e1.learnSkill(s3);



    HiringCondition c;
    WorkPlace wp1(10,"meta",100,200);

    wp1.hireManager(&m1);
    wp1.hireEmployee(c,&e1,100);
    wp1.hireEmployee(c,&e2,100);
    wp1.hireEmployee(c,&e3,100);
    wp1.hireEmployee(c,&e4,100);

    

    // Employee* eee1 = wp1.FindEmployee(1);

    WorkPlace wp2(20,"google",300,400);
    wp2.hireManager(&m2);
    wp2.hireEmployee(c,&e3,200);
    wp2.hireEmployee(c,&e4,200);

    wp2 = wp1;



    // wp1.fireEmployee(1,100);
    Employee* eee1 = wp1.FindEmployee(1);

    // if(eee1 == nullptr)
    // {
    //     std::cout << "null in wp1" << std::endl;
    // }

    // Employee* eee2  = wp2.FindEmployee(1);
    // if(eee2 != nullptr)
    // {
    //     std::cout << "exists in wp2" << std::endl;
    // }


    // wp1.hireEmployee(c,&e3,100);

    // Employee* eee1 = wp1.FindEmployee(3);

    // if(eee1 != nullptr)
    // {
    //     std::cout << "e3 found in wp1" << std::endl;
    // }


    // Employee* eee2 = wp2.FindEmployee(3);

    // if(eee2 != nullptr)
    // {
    //     std::cout << "e3 found in wp2" << std::endl;
    // }





    // e1.setSalary(100);
    // e2.setSalary(200);
    // e3.setSalary(300);
    // e4.setSalary(400);
    // Manager m1(1,"Big","Boss",2000);
    // cout << "printShort:" << endl;
    // m1.printShort(cout);
    // cout << endl<< "printLong:" << endl;
    // m1.printLong(cout);
    // m1.setSalary(500);
    // try {
    //     m1.removeEmployee(1);
    // }
    // catch (mtm::EmployeeIsNotHired&) {
    //     cout << endl<< "EmployeeIsNotHired" << endl;
    // }
    // m1.addEmployee(&e1);
    // try {
    //     m1.addEmployee(&e1);
    // }
    // catch (mtm::EmployeeAlreadyHired&) {
    //     cout << "EmployeeAlreadyHired" << endl << endl;
    // }
    // m1.removeEmployee(1);
    // m1.addEmployee(&e2);
    // m1.addEmployee(&e4);
    // m1.addEmployee(&e3);
    // Skill s1(1,"s1",10);
    // Skill s2(2,"s2",20);
    // Skill s3(3,"s3",30);
    // try {
    //     e2.forgetSkill(1);
    // }
    // catch (mtm::DidNotLearnSkill&) {
    //     cout << endl<< "DidNotLearnSkill" << endl;
    // }
    // e2.setScore(9);
    // e2.learnSkill(s1);
    // try {
    //     e2.learnSkill(s1);
    // }
    // catch (mtm::SkillAlreadyLearned&) {
    //     cout << "SkillAlreadyLearned" << endl << endl;
    // }
    
    
    

    // m1.printLong(cout);
    // m1.removeEmployee(2);
    // m1.removeEmployee(3);
    // m1.removeEmployee(4);
    // m1.printLong(cout);


    std::cout << "hello1" << std::endl;
    return 0;
}