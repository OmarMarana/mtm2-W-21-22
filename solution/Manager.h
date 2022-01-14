#ifndef __MANAGER_H__
#define __MANAGER_H__
#include "Citizen.h"
#include "Employee.h"
#include <memory>
#include <vector>

#include <set>

namespace mtm
{   
	class Manager : public Citizen
	{
        private:
            int salary;
            bool hired;
            std::set<Employee*, mtm::CompareEmployee> employees; 

            std::vector<std::shared_ptr<Employee>> empls;

        public:
            
            Manager(int id,std::string first_name,std::string last_name,int year_of_birth,
            int salary = 0, bool hired = false):Citizen(id, first_name, last_name,year_of_birth), salary(salary), hired(hired) {}
            //returns the salary of the manager
            int getSalary()const;
            //add employee to the set employees of the manager
            void addEmployee(Employee* employee);
            //remove employee from the set employees of the manager
            void removeEmployee(int employee_id);
            //adds delta to the salary of the manager
            void setSalary(int delta);
            //checks if the manager get hired
            bool getHired() const;
            //update to hired if the manager is hired
            void setHired(bool hired);
            //print short of manager
            std::ostream& printShort(std::ostream& stream) const override;
            //print long of manager
            std::ostream& printLong(std::ostream& stream) const override;
            //clone of manager
            Citizen* clone() const override;
            //destructor of manager
            ~Manager() override = default;
            //checks if the employee is working for the manager 
            bool isEmployeeIn(int employee_id);
            //update employees salary After fire
            void updateEmployeesSalaryAfterFire(int delta);
            //deduce the salary of the employee after firing him
            void findEmployeeAndDeduceSalary(int employee_id,int delta);
            std::set<Employee*, mtm::CompareEmployee>& getEmployees();
            Employee* getEmployee(int employee_id);

    };
    class CompareManager 
    {
        public:
            bool operator()(Manager* manager1, Manager* manager2)
            {
                return manager1->getId() < manager2->getId(); 
            }
    };
}


#endif  //  __MANAGER_H__

