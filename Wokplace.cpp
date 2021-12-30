#include "WorkPlace.h"
#include "exceptions.h"

namespace mtm
{
    int WorkPlace::getManagersSalary() const
    {
        return salary_of_managers;
    }
    int WorkPlace::getWorkersSalary()const
    {
        return salary_of_employees;
    }
    std::string WorkPlace::getName()const
    {
        return name;
    }
    int WorkPlace::getId()const
    {
        return id;
    }
    
    template<class HiringCondition>
    void WorkPlace::hireEmployee(HiringCondition condition ,std::shared_ptr<Employee> employee,int id_of_manager)
    {
        if(condition(employee) == false)
        {
            throw EmployeeNotSelected();
        }
        //Manager(int id,std::string first_name,std::string last_name,int year_of_birth, int salary)
       
        std::shared_ptr<Manager> temp_manager(new Manager(id_of_manager,"a","a",1,1));
        std::shared_ptr<Manager> manager_in_workplace = *(managers.find(temp_manager));

        if(manager_in_workplace->getId() != id_of_manager)
        {
            throw ManagerIsNotHired();
        }
        /*
        here!
        here!
        */


    }
    void hireManager(std::shared_ptr<Manager> manager);
    void fireEmployee(int employee_id, int manager_id);
    void fireManager(int manager_id);
    std::ostream& operator<<(std::ostream& stream, const WorkPlace& work_place);


}