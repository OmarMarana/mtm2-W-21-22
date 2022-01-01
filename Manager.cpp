#include "Manager.h"
#include "exceptions.h"
#include <iostream>

namespace mtm
{
    int Manager::getSalary()const
    {
        return salary;
    }
    void Manager::addEmployee(std::shared_ptr<Employee> employee)
    {
        std::shared_ptr<Employee> employee_in_set = *(employees.find(employee));  // check if find works as expected
        if(employee_in_set->getId() == employee->getId())
        {
            throw EmployeeAlreadyHired();
        }
        
        employees.insert(employee);
    }

    void Manager::removeEmployee(int employee_id)
    {
        //first_name,std::string last_name,int year_of_birth, int salary,int score
       
        std::shared_ptr<Employee> tmp_employee(new Employee(employee_id,"a","a",1));

        std::shared_ptr<Employee> employee_in_set = *(employees.find(tmp_employee));
        if(employee_in_set->getId() != employee_id)
        {
            throw EmployeeNotHired();
        }
        
        employees.erase(tmp_employee);

    }
    void Manager::setSalary(int salary_to_add)
    {   
        int new_salary = salary + salary_to_add;
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
        "id - " << getId() << "birth_year - " << getYearOfBirth() << 
        "Salary: " << salary <<  std::endl << "Employees:";       // check if there should be a space after Employees:
        
        for(std::set<std::shared_ptr<Employee>, mtm::CompareCitizens>::iterator i = employees.begin(); i != employees.end(); ++i)
        {
            (*i)->printShort(stream) << std::endl;
        } 
  
        return stream;
    }
    
    std::shared_ptr<Citizen> Manager::clone() const 
    {
        std::shared_ptr<Citizen> ptr(new Manager(*this));
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
        for(std::set<std::shared_ptr<Employee>, mtm::CompareCitizens>::iterator i = employees.begin(); i != employees.end(); ++i)
        {
           if((*i)->getId() == employee_id)
           {
               return true;
           }
        } 
        return false;
    }
}