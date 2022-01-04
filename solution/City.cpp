#include "City.h"
#include "exceptions.h"
#include "WorkPlace.h"
#include "Faculty.h"
#include <iostream>

namespace mtm
{
    class FacultyCondition3: public Condition
    {
        bool operator()(Employee* employee) override
        {
            return employee->getId() > 0;
        }
    };

    City City::City(const City& city)
    {
        this->name = city.name;
        this->faculties = city.faculties; 
        this->workplaces = city.workplaces;
        
        for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = city.citizens.begin(); i !=
        city.citizens.end(); ++i)
        {
            Citizen* citizen = (*i)->clone(); 
            this->citizens.insert(citizen);
        }
    }

    City& City::operator=(const City& city)
    {
        this->name = city.name;
        this->faculties = city.faculties; 
        this->workplaces = city.workplaces;
        for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
            delete (*i);
        }
        for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = city.citizens.begin(); i !=
        city.citizens.end(); ++i)
        {
            Citizen* citizen = (*i)->clone(); 
            this->citizens.insert(citizen);
        }    
    }

    City::~City()
    {
        for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
            delete (*i);
        }
    }

    Employee* City::doesEmployeeExist(std::set<Citizen* , CompareCitizens>& citizens, int employee_id)
    {
        Employee* employee_1 = nullptr;
        bool found_employee = false;
        for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == employee_id)
           {  
               employee_1 = dynamic_cast<Employee*>(*i);
               if(employee_1 == nullptr)
               {
                   throw EmployeeDoesNotExist();
               }
               return employee_1;
           }
        }
        if(found_employee == false)
        {
            throw EmployeeDoesNotExist();
        }
        return employee_1;
    }

    Manager* City::doesManagerExist(std::set<Citizen* , CompareCitizens>& citizens, int manager_id)
    {
        Manager* manager_1 = nullptr;
        bool found_manager = false;
        for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == manager_id)
           {  
               manager_1 = dynamic_cast<Manager*>(*i);
               if(manager_1 == nullptr)
               {
                   throw ManagerDoesNotExist();
               }
               return manager_1;
           }
        }
        if(found_manager == false)
        {
            throw ManagerDoesNotExist();
        }
        return manager_1;
    }

    void City::addEmployee(int id,std::string first_name,std::string last_name,int year_of_birth)
    { 
        Employee* new_employee = new Employee(id, first_name, last_name, year_of_birth);
        
        for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == id)
           {   
               throw CitizenAlreadyExists();
           }
        } 
        citizens.insert(new_employee);
    }

    void City::addManager(int id,std::string first_name,std::string last_name,int year_of_birth)
    {
        Manager* new_manager = new Manager(id,first_name,last_name ,year_of_birth);

        for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == id)
           {  
               throw CitizenAlreadyExists();
           }
        } 
        
        citizens.insert(new_manager);
    }
    

    void City::addFaculty(int id,  Skill skill, int acquired_points, mtm::Condition* condition)
    {
        Faculty<Condition> faculty(id, skill, acquired_points, condition);
        
        if(faculties.find(faculty) != faculties.end())
        {
            throw FacultyAlreadyExists();
        }
          
        faculties.insert(faculty);
    }

    void City::createWorkplace(int id,std::string name,int salary_of_employees,int salary_of_managers)
    {
        WorkPlace new_workplace(id,name,salary_of_employees,salary_of_managers);

        if(workplaces.find(new_workplace) != workplaces.end() )
        {
            throw WorkplaceAlreadyExists();
        }

        workplaces.insert(new_workplace);
    }


    void City::teachAtFaculty(int employee_id, int faculty_id)
    {
        
        Employee* employee = doesEmployeeExist(citizens, employee_id);

        FacultyCondition3 c1 ;
        Faculty<Condition> faculty(faculty_id, Skill( 0, "c", 0),0, &c1 );
        if(faculties.find(faculty) == faculties.end())
        {
            throw FacultyDoesNotExist();
        }
        
        (*(faculties.find(faculty))).teach(*employee); // mr google says that elements in set are const, so employee can't be changed here
        
    }
    
    // static void  

    void City::hireManagerAtWorkplace(int manager_id, int workplace_id)
    {
        Manager* manager = doesManagerExist(citizens, manager_id);
       
        WorkPlace work_place(workplace_id,"F",0,0);
        if(workplaces.find(work_place) == workplaces.end())
        {
            throw WorkplaceDoesNotExist();
        }

      WorkPlace wp = (*(workplaces.find(work_place)));  //make sure that the managers set contains pointers to the same manager instances
      wp.hireManager(manager);

      workplaces.erase((*(workplaces.find(work_place))));
      workplaces.insert(wp);
      /*
      possible solutions:
      1.change set to vector and every time we used set.find we should use foreach.vecor
      and find the desired element. Additionally, in each ordered set we should use the algorithim vector.sort
      E.g at "https://en.cppreference.com/w/cpp/algorithm/sort".

      2.Each time we need to change an element in the set we should make a copy of the element and make the changes on the
      copy and insert it after removing the unupdated element  
      
      
      */
    }

    void City::fireEmployeeAtWorkplace(int employee_id, int manager_id, int workplace_id)
    {
        doesEmployeeExist(citizens, employee_id);
        doesManagerExist(citizens, manager_id);

        WorkPlace work_place(workplace_id,"F",0,0);
        if(workplaces.find(work_place) == workplaces.end())
        {
            throw WorkplaceDoesNotExist();
        }

        WorkPlace wp = (*(workplaces.find(work_place)));  //make sure that the managers set contains pointers to the same manager instances
        wp.fireEmployee(employee_id, manager_id);
        // employee_1->setSalary(-(wp.getWorkersSalary()));


        workplaces.erase((*(workplaces.find(work_place))));
        workplaces.insert(wp);

        
    }
    
    void City::fireManagerAtWorkplace(int manager_id, int workplace_id)
    {        
        Manager* manager = doesManagerExist(citizens, manager_id);

        WorkPlace work_place(workplace_id,"F",0,0);
        if(workplaces.find(work_place) == workplaces.end())
        {
            throw WorkplaceDoesNotExist();
        }

        WorkPlace wp = (*(workplaces.find(work_place)));  //make sure that the managers set contains pointers to the same manager instances
        wp.fireManager(manager_id);
        manager->setSalary(-(wp.getManagersSalary()));
        // manager_1->updateEmployeesSalaryAfterFire(-(wp.getWorkersSalary()));/////

        workplaces.erase((*(workplaces.find(work_place))));
        workplaces.insert(wp);    
    }

    int  City::getAllAboveSalary(std::ostream& stream, int salary)
    {
        int count = 0;
        Manager* manager;
        Employee* employee;
        for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
            employee = dynamic_cast<Employee*>(*i);
            if(employee != nullptr )
            {
                if(employee->getSalary() >= salary)
                {
                    count++;
                    employee->printShort(stream);
                }
            }
            else
            {
                manager = dynamic_cast<Manager*>(*i);
                if(manager->getSalary() >= salary)
                {
                    count++;
                    manager->printShort(stream);
                }
            }    
        }
        return count;
    }
    
    bool City::isWorkingInTheSameWorkplace(int employee_id1,int employee_id2)
    {
        doesEmployeeExist(citizens, employee_id1);
        doesEmployeeExist(citizens, employee_id2);

        bool working_at_the_same_place = false;
        for(std::set<WorkPlace, CompareWorkplaces>::iterator i = workplaces.begin(); i !=
        workplaces.end(); ++i)
        {
            WorkPlace wp = (*i);
            if(wp.isWorkingHere(employee_id1))
            {
                working_at_the_same_place = wp.isWorkingHere(employee_id2);
                if(working_at_the_same_place == true)
                {
                    break;
                }
            }
        }

        return working_at_the_same_place;  
    }

    void City::printAllEmployeesWithSkill(std::ostream& stream, int skill_id)
    {
       Employee* employee_1; 
       for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
       citizens.end(); ++i)
       {
           employee_1 = dynamic_cast<Employee*>(*i);
           if(employee_1 != nullptr)
           {
               if(employee_1->hasSkill(skill_id)==true)//?
                {
                    (*i)->printShort(stream);
                }
           }
       }
    //    stream << std::endl;

    }        
}

