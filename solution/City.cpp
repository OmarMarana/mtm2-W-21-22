#include "City.h"
#include "exceptions.h"
#include "Workplace.h"
#include "Faculty.h"
#include <iostream>

namespace mtm
{
    class FacultyHelperCondition: public Condition
    {
        bool operator()(Employee* employee) override
        {
            return employee->getId() > 0;
        }
    };

    class HiringConditionO {
        public:
            bool operator()(Employee *emp) {
                return true;
            }
    };


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
        throw EmployeeDoesNotExist();
        return employee_1;
    }

    bool City::doesExist(int employee_id)
    {
        for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == employee_id)
           {  
                return true;
           }
        }
        return false;  
    }

    Manager* City::doesManagerExist(std::set<Citizen* , CompareCitizens>& citizens, int manager_id)
    {
        Manager* manager_1 = nullptr;
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
        throw ManagerDoesNotExist();
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
        std::shared_ptr<Workplace> new_workplace(new Workplace(id,name,salary_of_employees,salary_of_managers));
        if(workplaces.find(new_workplace) != workplaces.end() )
        {
            throw WorkplaceAlreadyExists();
        }

        workplaces.insert(new_workplace);
    }


    void City::teachAtFaculty(int employee_id, int faculty_id)
    {
        
        Employee* employee = doesEmployeeExist(citizens, employee_id);

        FacultyHelperCondition c1 ;
        Faculty<Condition> faculty(faculty_id, Skill( 0, "c", 0),0, &c1 );
        if(faculties.find(faculty) == faculties.end())
        {
            throw FacultyDoesNotExist();
        }
        
        (*(faculties.find(faculty))).teach(employee);
        
    }
    

    void City::hireManagerAtWorkplace(int manager_id, int workplace_id)
    {
        Manager* manager = doesManagerExist(citizens, manager_id);
       
        std::shared_ptr<Workplace> work_place(new Workplace(workplace_id,"F",0,0));
        if(workplaces.find(work_place) == workplaces.end())
        {
            throw WorkplaceDoesNotExist();
        }


        (*(workplaces.find(work_place)))->hireManager(manager);
      
    }

    void City::fireEmployeeAtWorkplace(int employee_id, int manager_id, int workplace_id)
    {
        doesEmployeeExist(citizens, employee_id);
        doesManagerExist(citizens, manager_id);

        std::shared_ptr<Workplace> work_place(new Workplace(workplace_id,"F",0,0));
        if(workplaces.find(work_place) == workplaces.end())
        {
            throw WorkplaceDoesNotExist();
        }

        (*(workplaces.find(work_place)))->fireEmployee(employee_id, manager_id);

    }
    
    void City::fireManagerAtWorkplace(int manager_id, int workplace_id)
    {        
        Manager* manager = doesManagerExist(citizens, manager_id);

        std::shared_ptr<Workplace> work_place(new Workplace(workplace_id,"F",0,0));
        if(workplaces.find(work_place) == workplaces.end())
        {
            throw WorkplaceDoesNotExist();
        }

        (*(workplaces.find(work_place)))->fireManager(manager_id);
        
        manager->setSalary(-((*(workplaces.find(work_place)))->getManagersSalary()));
        manager->getEmployees().clear();
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
        for(std::set<std::shared_ptr<Workplace>, CompareWorkplaces>::iterator i = workplaces.begin(); i !=
        workplaces.end(); ++i)
        {
            if((*i)->isWorkingHere(employee_id1))
            {
                working_at_the_same_place = (*i)->isWorkingHere(employee_id2);
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

    }        
}

