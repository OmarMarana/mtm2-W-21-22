#ifndef __WORKPLACE_H__
#define __WORKPLACE_H__
#include "Employee.h"
#include "Manager.h"
#include <vector>
#include <memory>
#include "exceptions.h"

namespace mtm
{
                       
    class Workplace
    {
        private:
            int id;
            std::string name;
            int salary_of_employees;
            int salary_of_managers;
            std::set<Manager*, CompareManager> managers;

            std::vector<std::shared_ptr<Manager>> mngrs;
            std::vector<std::shared_ptr<Employee>> empls;

        public:
        Workplace(int id,std::string name,int salary_of_employees,int salary_of_managers) : id(id),
        name(name), salary_of_employees(salary_of_employees), salary_of_managers(salary_of_managers) {}
        Workplace(const Workplace& other);
        Workplace& operator=(const Workplace& other);
        //work place destructor
        ~Workplace() = default;
        //return the salary of the manager
        int getManagersSalary()const;
        //return the salary of the employee
        int getWorkersSalary()const;
        //return the name of the manager
        std::string getName()const;
        //return the id of the manager
        int getId()const;
        
        template<class HiringCondition>
        //ad the employee to the Workplace if he satisfies the condition 
        void hireEmployee(HiringCondition condition ,Employee* employee,int id_of_manager);
        //ad the manager to the Workplace
        void hireManager(Manager* manager) ;
        //remove the employee from the Workplace
        void fireEmployee(int employee_id, int manager_id);
        //remove the manager from the Workplace
        void fireManager(int manager_id);
        //check if the manager work in the Workplace
        bool isWorkingHere(int employee_id);
        //print format for Workplace
        friend std::ostream& operator<<(std::ostream& stream, const Workplace& work_place);
        Employee* FindEmployee(int employee_id);
        std::set<Manager*, CompareManager>& getManagers();

    };
     
    class CompareWorkplaces
    {
        public:
            bool operator()( std::shared_ptr<Workplace> workPlace1, std::shared_ptr<Workplace> workPlace2)
            {
                return workPlace1->getId() < workPlace2->getId(); 
            }
    };

    template<class HiringCondition>
    void Workplace::hireEmployee(HiringCondition condition ,Employee* employee,int id_of_manager)
    {
        if(condition(employee) == false)
        {
            throw EmployeeNotSelected();
        }

        Manager temp_manager(id_of_manager,"a","a",1);
        if(managers.find(&temp_manager) == managers.end())
        {
            throw ManagerIsNotHired();
        }

        Manager* manager_in_workplace =*(managers.find(&temp_manager)); 
        manager_in_workplace->addEmployee(employee);
        employee->setSalary(this->salary_of_employees);   
    }
}



#endif  //  __WORKPLACE_H__

