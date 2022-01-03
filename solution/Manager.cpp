#include "Manager.h"
#include "exceptions.h"
#include <iostream>

namespace mtm
{

    // void Manager::updateEmployeeSalaryAfterFire(int employee_id, int salary_to_deduce)
    // {


    // }
    int Manager::getSalary()const
    {
        return salary;
    }
    void Manager::addEmployee(Employee* employee)
    {
        // if(*(employees.find(employee)) == nullptr)
        // {
        //     employees.insert(employee);
        //     return;
        // }

        if(employees.find(employee) == employees.end())
        {
            employees.insert(employee);
            return;
        }
        
        throw EmployeeAlreadyHired();
        
       /* Employee* employee_in_set = *(employees.find(employee));
        if(employee_in_set->getId() == employee->getId())
        {
            throw EmployeeAlreadyHired();
        }
        
        employees.insert(employee);*/
    }

    void Manager::removeEmployee(int employee_id)
    {
        //first_name,std::string last_name,int year_of_birth, int salary,int score
       
        

        Employee tmp_employee(employee_id,"a","a",1);

        if(employees.find(&tmp_employee) == employees.end())
        {
            throw EmployeeIsNotHired();
        }

        // Employee* employee_in_set = *(employees.find(&tmp_employee));
        // if(employee_in_set->getId() != employee_id)
        // {
        //     throw EmployeeIsNotHired();
        // }
        
        employees.erase(&tmp_employee);
    }
    
    void Manager::setSalary(int delta)
    {   
        int new_salary = salary + delta;
        if(new_salary <= 0)
        {
            this->salary = 0;
        }
        this->salary =new_salary;
    }
    std::ostream& Manager::printShort(std::ostream& stream) const 
    {
        return stream << getFirstName() << " " << getLastName() << std::endl 
        << "Salary: " << salary <<  std::endl;
        
    }
    std::ostream& Manager::printLong(std::ostream& stream) const 
    {
        stream << getFirstName() << " " << getLastName() << std::endl <<
        "id - " << getId() << " birth_year - " << getBirthYear() << std::endl <<
        "Salary: " << salary <<  std::endl << "Employees:"<<std::endl;       // check if there should be a space after Employees:
        
        for(std::set<Employee*, mtm::CompareCitizens>::iterator i = employees.begin(); i != employees.end(); ++i)
        {
            (*i)->printShort(stream) ;
        } 
        // stream << std::endl;
        return stream;
    }
    
    Citizen* Manager::clone() const 
    {
        Citizen* ptr(new Manager(*this));
        return ptr; 
    }

    bool Manager::getHired() const
    {
        return hired;
    }

    void Manager::setHired(bool hired)
    {
        this->hired = hired;
    }


    bool Manager::isEmployeeIn(int employee_id)
    {
        for(std::set<Employee*, mtm::CompareCitizens>::iterator i = employees.begin(); i != employees.end(); ++i)
        {
           if((*i)->getId() == employee_id)
           {
               return true;
           }
        } 
        return false;
    }

    void Manager::updateEmployeesSalaryAfterFire(int delta)
    {
        for(std::set<Employee*, mtm::CompareCitizens>::iterator i = employees.begin(); i != employees.end(); ++i)
        {
            (*i)->setSalary(delta);
        } 
    }

    void Manager::findEmployeeAndDeduceSalary(int employee_id,int delta)
    {  
        Employee tmp_employee(employee_id,"a","a",1);
        Employee* employee = *(employees.find(&tmp_employee));
        employee->setSalary(delta);
    }
}