#ifndef __WORKPLACE_H__
#define __WORKPLACE_H__
#include "Employee.h"

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

        public:
        Citizen(int id,std::string name,int salary_of_employees,int salary_of_managers);
        int getManagersSalary();
        int getWorkersSalary();
        std::string getName();
        int getId();
        
        template<class HiringCondition>
        void hireEmployee(HiringCondition condition ,Employee* employee,int id_of_manager);
        void hireManager(Manager* manager);
        void fireEmployee(int employee_id, int manager_id);
        void fireManager(int manager_id);
        friend std::ostream& operator<<(std::ostream& stream, const WorkPlace& work_place);
    };
  
}



#endif  //  __WORKPLACE_H__

