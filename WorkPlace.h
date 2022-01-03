#ifndef __WORKPLACE_H__
#define __WORKPLACE_H__
#include "Employee.h"
#include "Manager.h"
#include <vector>
#include <memory>
#include "exceptions.h"

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
        if(condition(employee.get()) == false)
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
        employee->setSalary(this->salary_of_employees);
        // manager_in_workplace->employees.insert(employee);    // why are they accessible
        // manager_in_workplace->first_name = "ffsd";
        // (*manager_in_workplace).first_name = "ads";
    }
    
    void WorkPlace::hireManager(std::shared_ptr<Manager> manager)
    {
        if((managers.find(manager)) == managers.end()) // managers is empty
        {
            managers.insert(manager);
            manager->setHired(true);
            manager->setSalary(this->salary_of_managers);
            return;
        }

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
        manager->setSalary(this->salary_of_managers);
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
        //write function that updates salary after fire
        //also make sure to update the salary of employees if their manager get fired

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

    bool WorkPlace::isWorkingHere(int employee_id)
    {
        bool found = false;
        for(std::set<std::shared_ptr<Manager>, CompareManager> ::iterator i = managers.begin(); i !=
        managers.end(); ++i)
        {
            found = (*i)->isEmployeeIn(employee_id);
        }
        return found;
    }

  
}



#endif  //  __WORKPLACE_H__

