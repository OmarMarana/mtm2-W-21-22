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

   City::City(const City& other)
   {
       this->name = other.name;
       this->faculties = other.faculties;
        
        for(std::set<std::shared_ptr<Workplace>, CompareWorkplaces>::iterator wp = other.workplaces.begin(); wp !=
        other.workplaces.end(); ++wp)
        {
            this->createWorkplace((*wp)->getId(),(*wp)->getName(),(*wp)->getWorkersSalary(),(*wp)->getManagersSalary());
            
            for(std::set<Manager*, CompareManager>::iterator mngr = (*wp)->getManagers().begin(); mngr !=
            (*wp)->getManagers().end(); ++mngr)
            {
                this->addManager((*mngr)->getId(),(*mngr)->getFirstName(),(*mngr)->getLastName(),(*mngr)->getBirthYear());
                this->hireManagerAtWorkplace((*mngr)->getId(),(*wp)->getId());

                for(std::set<Employee*, mtm::CompareEmployee>::iterator emp = (*mngr)->getEmployees().begin(); emp !=
                (*mngr)->getEmployees().end(); ++emp)
                {
                    HiringConditionO c1;
                    if(this->doesExist((*emp)->getId()))
                    {   
                        
                        this->hireEmployeeAtWorkplace(c1,(*emp)->getId(),(*mngr)->getId(),(*wp)->getId());
                    }
                    else
                    {
                        this->addEmployee((*emp)->getId(),(*emp)->getFirstName(),(*emp)->getLastName(),(*emp)->getBirthYear());
                        this->hireEmployeeAtWorkplace(c1,(*emp)->getId(),(*mngr)->getId(),(*wp)->getId());
                    }
                }
            }
        }
        for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = other.citizens.begin(); i !=
       other.citizens.end(); ++i)
        {
            if(this->doesExist((*i)->getId()) == false)
            {   
                Employee * tmp_emp1 = dynamic_cast<Employee*>(*i);
                if(tmp_emp1 == nullptr)
                {
                    this->addManager((*i)->getId(),(*i)->getFirstName(),(*i)->getLastName(),(*i)->getBirthYear());
                }
                else
                {
                    this->addEmployee((*i)->getId(),(*i)->getFirstName(),(*i)->getLastName(),(*i)->getBirthYear());
                    Employee * tmp_emp2 = doesEmployeeExist(this->citizens,(*i)->getId());
                    tmp_emp2->setScore(tmp_emp1->getScore());
                }
            }
        }

   }

   City& City::operator=(const City& other)
   {
       this->name = other.name;
       this->faculties = other.faculties;
       for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
       citizens.end(); ++i)
       {
           delete (*i);
       }
       workplaces.clear();

       for(std::set<std::shared_ptr<Workplace>, CompareWorkplaces>::iterator wp = other.workplaces.begin(); wp !=
        other.workplaces.end(); ++wp)
        {
            this->createWorkplace((*wp)->getId(),(*wp)->getName(),(*wp)->getWorkersSalary(),(*wp)->getManagersSalary());
            
            for(std::set<Manager*, CompareManager>::iterator mngr = (*wp)->getManagers().begin(); mngr !=
            (*wp)->getManagers().end(); ++mngr)
            {
                this->addManager((*mngr)->getId(),(*mngr)->getFirstName(),(*mngr)->getLastName(),(*mngr)->getBirthYear());
                this->hireManagerAtWorkplace((*mngr)->getId(),(*wp)->getId());

                for(std::set<Employee*, mtm::CompareEmployee>::iterator emp = (*mngr)->getEmployees().begin(); emp !=
                (*mngr)->getEmployees().end(); ++emp)
                {
                    HiringConditionO c1;
                    if(this->doesExist((*emp)->getId()))
                    {   
                        
                        this->hireEmployeeAtWorkplace(c1,(*emp)->getId(),(*mngr)->getId(),(*wp)->getId());
                    }
                    else
                    {
                        this->addEmployee((*emp)->getId(),(*emp)->getFirstName(),(*emp)->getLastName(),(*emp)->getBirthYear());
                        this->hireEmployeeAtWorkplace(c1,(*emp)->getId(),(*mngr)->getId(),(*wp)->getId());
                    }
                }
            }

        }
        for(std::set<Citizen*, mtm::CompareCitizens>::iterator i = other.citizens.begin(); i !=
       other.citizens.end(); ++i)
        {
            if(this->doesExist((*i)->getId()) == false)
            {   
                Employee * tmp_emp1 = dynamic_cast<Employee*>(*i);
                if(tmp_emp1 == nullptr)
                {
                    this->addManager((*i)->getId(),(*i)->getFirstName(),(*i)->getLastName(),(*i)->getBirthYear());
                }
                else
                {
                    this->addEmployee((*i)->getId(),(*i)->getFirstName(),(*i)->getLastName(),(*i)->getBirthYear());
                    Employee * tmp_emp2 = doesEmployeeExist(this->citizens,(*i)->getId());
                    tmp_emp2->setScore(tmp_emp1->getScore());
                }
            }
        }

        return *this;
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
       // bool found_employee = false;
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
        // if(found_employee == false)
        // {
            throw EmployeeDoesNotExist();
        //}
        return employee_1;
    }

    bool City::doesExist(int employee_id)
    {
        // Employee* employee_1 = nullptr;
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
        //bool found_manager = false;
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
        // if(found_manager == false)
        // {
            throw ManagerDoesNotExist();
        //}
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
        // Workplace new_workplace(id,name,salary_of_employees,salary_of_managers);
        std::shared_ptr<Workplace> new_workplace(new Workplace(id,name,salary_of_employees,salary_of_managers));
        // std::shared_ptr<Employee> new_employee(new Employee(id,first_name,last_name ,year_of_birth));
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
        
        (*(faculties.find(faculty))).teach(employee); // mr google says that elements in set are const, so employee can't be changed here
        
    }
    
    // static void  

    void City::hireManagerAtWorkplace(int manager_id, int workplace_id)
    {
        Manager* manager = doesManagerExist(citizens, manager_id);
       
        //Workplace work_place(workplace_id,"F",0,0);
        std::shared_ptr<Workplace> work_place(new Workplace(workplace_id,"F",0,0));
        if(workplaces.find(work_place) == workplaces.end())
        {
            throw WorkplaceDoesNotExist();
        }


        (*(workplaces.find(work_place)))->hireManager(manager);
    //   Workplace wp = (*(workplaces.find(work_place)));  //make sure that the managers set contains pointers to the same manager instances
    //   wp.hireManager(manager);

    //   workplaces.erase((*(workplaces.find(work_place))));
    //   workplaces.insert(wp);
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

        // Workplace work_place(workplace_id,"F",0,0);
        std::shared_ptr<Workplace> work_place(new Workplace(workplace_id,"F",0,0));
        if(workplaces.find(work_place) == workplaces.end())
        {
            throw WorkplaceDoesNotExist();
        }

        (*(workplaces.find(work_place)))->fireEmployee(employee_id, manager_id);

        // Workplace wp = (*(workplaces.find(work_place)));  //make sure that the managers set contains pointers to the same manager instances
        // wp.fireEmployee(employee_id, manager_id);
        // // employee_1->setSalary(-(wp.getWorkersSalary()));


        // workplaces.erase((*(workplaces.find(work_place))));
        // workplaces.insert(wp);

        
    }
    
    void City::fireManagerAtWorkplace(int manager_id, int workplace_id)
    {        
        Manager* manager = doesManagerExist(citizens, manager_id);

        // Workplace work_place(workplace_id,"F",0,0);
        std::shared_ptr<Workplace> work_place(new Workplace(workplace_id,"F",0,0));
        if(workplaces.find(work_place) == workplaces.end())
        {
            throw WorkplaceDoesNotExist();
        }


        (*(workplaces.find(work_place)))->fireManager(manager_id);
        // Workplace wp = (*(workplaces.find(work_place)));  //make sure that the managers set contains pointers to the same manager instances
        // wp.fireManager(manager_id);
        manager->setSalary(-((*(workplaces.find(work_place)))->getManagersSalary()));
        // manager_1->updateEmployeesSalaryAfterFire(-(wp.getWorkersSalary()));/////

        // workplaces.erase((*(workplaces.find(work_place))));
        // workplaces.insert(wp);    
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
            // Workplace wp = (*i);
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
    //    stream << std::endl;

    }        
}

