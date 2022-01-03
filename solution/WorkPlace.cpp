#include "WorkPlace.h"
#include "exceptions.h"
#include <iostream>

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
    
    void WorkPlace::hireManager(Manager* manager)
    {
        if((managers.find(manager)) != managers.end()) // managers is empty
        {
            throw ManagerAlreadyHired();
        }
        
        if(manager->getHired() == true)
        {
            throw CanNotHireManager();
        }

        managers.insert(manager);
        manager->setHired(true);
        manager->setSalary(this->salary_of_managers);
    }

    void WorkPlace::fireEmployee(int employee_id, int manager_id)
    {

        Manager temp_manager(manager_id,"a","a",1);
        if(managers.find(&temp_manager) == managers.end())
        {
            throw ManagerIsNotHired();
        }

        Manager* manager_in_workplace = *(managers.find(&temp_manager));
        if(manager_in_workplace->isEmployeeIn(employee_id) == true)
        {
            manager_in_workplace->findEmployeeAndDeduceSalary(employee_id, -(this->salary_of_employees));
        }
        manager_in_workplace->removeEmployee(employee_id);
        
        //write function that updates salary after fire
        //also make sure to update the salary of employees if their manager get fired

    }

    void WorkPlace::fireManager(int manager_id)
    {    
        Manager temp_manager(manager_id,"a","a",1);
        if(managers.find(&temp_manager) == managers.end())
        {
            throw ManagerIsNotHired();
        }
        ///update hired flag////////////////
        Manager* manager_in_workplace = *(managers.find(&temp_manager));
        manager_in_workplace->setHired(false);
        manager_in_workplace->updateEmployeesSalaryAfterFire(-(this->getWorkersSalary()));/////
        manager_in_workplace->setSalary(-(this->getManagersSalary()));/////

        managers.erase(&temp_manager);
    }

    std::ostream& operator<<(std::ostream& stream, const WorkPlace& work_place)
    {
        stream << "Workplace name - " << work_place.getName() ;
        
        if(work_place.managers.size() == 0)
        {
            return stream;
        }

        stream << " Groups:" << std::endl;
        
        for(std::set<Manager*, mtm::CompareCitizens>::iterator i = work_place.managers.begin(); i !=
        work_place.managers.end(); ++i)
        {
            stream << "Manager";
            (*i)->printLong(stream) << std::endl;
        } 
  
        return stream;
    }

    bool WorkPlace::isWorkingHere(int employee_id)
    {
        bool found = false;
        for(std::set<Manager*, CompareManager> ::iterator i = managers.begin(); i !=
        managers.end(); ++i)
        {
            found = (*i)->isEmployeeIn(employee_id);
        }
        return found;
    }


}