#ifndef __WORKPLACE_H__
#define __WORKPLACE_H__
#include "Employee.h"
#include "Manager.h"
#include <vector>
#include <memory>

namespace mtm
{
                       
    ////typedef void*(*ConditionToCheck)(Condition*);
    class WorkPlace
    {
        private:
            int id;
            std::string name;
            int salary_of_employees;
            int salary_of_managers;
            std::set<std::shared_ptr<Manager>, CompareManager> managers;

        public:
        WorkPlace(int id,std::string name,int salary_of_employees,int salary_of_managers) : id(id),
        name(name), salary_of_employees(salary_of_employees), salary_of_managers(salary_of_managers) {}
        ~WorkPlace() = default;
        //write the other defaults for this class and other classes
        int getManagersSalary()const;
        int getWorkersSalary()const;
        std::string getName()const;
        int getId()const;
        
        template<class HiringCondition>
        void hireEmployee(HiringCondition condition ,std::shared_ptr<Employee> employee,int id_of_manager);
        void hireManager(std::shared_ptr<Manager> manager);
        void fireEmployee(int employee_id, int manager_id);
        void fireManager(int manager_id);
        bool isWorkingHere(int employee_id);
        friend std::ostream& operator<<(std::ostream& stream, const WorkPlace& work_place);
    };
     
    class CompareWorkplaces
    {
        public:
            bool operator()( WorkPlace workPlace1, WorkPlace workPlace2)
            {
                return workPlace1.getId() < workPlace2.getId(); 
            }
    };                    
  
}



#endif  //  __WORKPLACE_H__

