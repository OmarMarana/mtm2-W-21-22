#ifndef __MANAGER_H__
#define __MANAGER_H__
#include "Citizen.h"
#include "Employee.h"
#include <memory>
#include <set>
namespace mtm
{   
    

	class Manager : public Citizen
	{
        int salary;
        std::set<std::shared_ptr<Employee>, mtm::CompareCitizens> employees; 

        Manager(int id,std::string first_name,std::string last_name,int year_of_birth,
        int salary):Citizen(id, first_name, last_name,year_of_birth),salary(salary){}
        int getSalary();
        void addEmployee(Employee* employee);
        void removeEmployee(Employee* employee); 
        void setSalary(int salary_to_add);
        std::ostream& printShort(std::ostream& stream) const override;
        std::ostream& printLong(std::ostream& stream) const override;
        std::shared_ptr<Citizen> clone() const override;
        ~Manager() override;
    };
}


#endif  //  __MANAGER_H__

