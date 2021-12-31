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
    
    template<class HiringCondition>
    void WorkPlace::hireEmployee(HiringCondition condition ,std::shared_ptr<Employee> employee,int id_of_manager)
    {
        if(condition(employee) == false)
        {
            throw EmployeeNotSelected();
        }
       
        std::shared_ptr<Manager> temp_manager(new Manager(id_of_manager,"a","a",1));
        std::shared_ptr<Manager> manager_in_workplace = *(managers.find(temp_manager));

        if(manager_in_workplace->getId() != id_of_manager)
        {
            throw ManagerIsNotHired();
        }

        manager_in_workplace->addEmployee(employee);

        // manager_in_workplace->employees.insert(employee);    // why are they accessible
        // manager_in_workplace->first_name = "ffsd";
        // (*manager_in_workplace).first_name = "ads";
    }
    
    void WorkPlace::hireManager(std::shared_ptr<Manager> manager)
    {
        std::shared_ptr<Manager> manager_in_workplace = *(managers.find(manager));
        if(manager_in_workplace->getId() == manager->getId())
        {
            throw ManagerAlreadyHired();
        }

        if(manager->getHired() == true)
        {
            throw CanNotHireManager();
        }
        
        managers.insert(manager);
        manager->setHired(true);   
    }

    void WorkPlace::fireEmployee(int employee_id, int manager_id)
    {
        std::shared_ptr<Manager> temp_manager(new Manager(manager_id,"a","a",1));
        std::shared_ptr<Manager> manager_in_workplace = *(managers.find(temp_manager));

        if(manager_in_workplace->getId() != manager_id)
        {
            throw ManagerIsNotHired();
        }

        manager_in_workplace->removeEmployee(employee_id);
    }

    void WorkPlace::fireManager(int manager_id)
    {    
        std::shared_ptr<Manager> tmp_manager(new Manager(manager_id,"a","a",1));
        std::shared_ptr<Manager> manager_in_set = *(managers.find(tmp_manager));

        if(manager_in_set->getId() != manager_id)
        {
            throw ManagerIsNotHired();
        }
        
        managers.erase(tmp_manager);
    }

    std::ostream& operator<<(std::ostream& stream, const WorkPlace& work_place)
    {
        stream << "Workplace name - " << work_place.getName() ;
        
        if(work_place.managers.size() == 0)
        {
            return stream;
        }

        stream << " Groups:" << std::endl;
        
        for(std::set<std::shared_ptr<Manager>, mtm::CompareCitizens>::iterator i = work_place.managers.begin(); i !=
        work_place.managers.end(); ++i)
        {
            stream << "Manager";
            (*i)->printLong(stream) << std::endl;
        } 
  
        return stream;
    }
}