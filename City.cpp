#include "City.h"
#include "exceptions.h"
#include "WorkPlace.h"
#include "Faculty.h"
#include <iostream>


namespace mtm
{
    void City::addEmployee(int id,std::string first_name,std::string last_name,int year_of_birth)
    { 
        std::shared_ptr<Employee> new_employee(new Employee(id,first_name,last_name ,year_of_birth));
        // std::shared_ptr<Employee> employee_in_set = *(citizens.find(new_employee));

        for(std::set<std::shared_ptr<Citizen>, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == id)
           {  
               throw EmployeeAlreadyExists();
           }
        } 

        citizens.insert(new_employee);
    }

    void City::addManager(int id,std::string first_name,std::string last_name,int year_of_birth)
    {
        std::shared_ptr<Manager> new_manager(new Manager(id,first_name,last_name ,year_of_birth));

        for(std::set<std::shared_ptr<Citizen>, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == id)
           {  
               throw ManagerAlreadyExists();
           }
        } 
        
        citizens.insert(new_manager);
    }
    

    void City::addFaculty(int id,  Skill skill, int acquired_points, mtm::Condition condition)
    {
        Faculty faculty(id, skill, acquired_points, condition);
        Faculty tmp_faculty = *(faculties.find(faculty)); 
        if( tmp_faculty.getId()  == id) 
        {
            throw FacultyAlreadyExists();
        }
        faculties.insert(faculty);
    }

    void City::createWorkplace(int id,std::string name,int salary_of_employees,int salary_of_managers)
    {
       WorkPlace new_workplace(id,name,salary_of_employees,salary_of_managers);
    //    WorkPlace tmp_workplace = (*workplaces.find(new_workplace)); 
        if( (*(workplaces.find(new_workplace))).getId()  == id) 
        {
            throw WorkplaceAlreadyExists();
        }
        workplaces.insert(new_workplace);
    }

    void City::teachAtFaculty(int employee_id, int faculty_id)
    {
        //need to check here if the id that was found belongs to a manager or an employee
        //in case it was a manager's id, an exception should be thrown
        bool found_employee = false;
        for(std::set<std::shared_ptr<Citizen>, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == employee_id)
           {  
               std::shared_ptr<Employee> employee_1 = std::dynamic_pointer_cast<Employee>(*i);
               if(employee_1.get() == nullptr)
               {
                   throw EmployeeDoesNotExist();
               }
               found_employee = true;
               break;
           }
        }

        if(found_employee == false)
        {
            throw EmployeeDoesNotExist();
        }
        mtm::Condition condition;
        Faculty faculty(faculty_id, Skill( 0, "c", 0),0, condition);

        Faculty tmp_faculty = *(faculties.find(faculty)); 
        if( tmp_faculty.getId()  != faculty_id) 
        {
            throw FacultyDoesNotExist();
        }
        
        std::shared_ptr<Employee> new_employee(new Employee(employee_id,"a","a" ,1));
        std::shared_ptr<Employee> employee = std::dynamic_pointer_cast<Employee>(*(citizens.find(new_employee)));
        
        (*(faculties.find(faculty))).teach(*employee); // mr google says that elements in set are const, so employee can't be changed here
        
    }
    
    // static void  

    template<class HiringCondition>
    void City::hireEmployeeAtWorkPlace(HiringCondition Condition,int employee_id, int manager_id, int workplace_id)
    {
        //may manager isnt in this workplace?
        std::shared_ptr<Employee> employee_1;
        bool found_employee = false;
        for(std::set<std::shared_ptr<Citizen>, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == employee_id)
           {  
               employee_1 = std::dynamic_pointer_cast<Employee>(*i);
               if(employee_1.get() == nullptr)
               {
                   throw EmployeeDoesNotExist();
               }
               found_employee = true;
               break;
           }
        }
        if(found_employee = false)
        {
            throw EmployeeDoesNotExist();
        }
//****************************************************
        bool found_manager = false;
        for(std::set<std::shared_ptr<Citizen>, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == manager_id)
           { 
               found_manager = true;
               break;
           }
        }
        if(found_manager = false)
        {
            throw ManagerDoesNotExist();
        }
//****************************************************
        WorkPlace work_place(workplace_id,"F",0,0);

        WorkPlace tmp_work_place = *(workplaces.find(work_place)); 
        if( tmp_work_place.getId() != workplace_id) 
        {
            throw WorkplaceDoesNotExist();
        }

    
        (*(workplaces.find(work_place))).hireEmployee(Condition ,employee_1 ,manager_id);
    }
    
    void City::hireManagerAtWorkPlace(int manager_id, int workplace_id)
    {
        std::shared_ptr<Manager> manager_1;
        bool found_manager = false;
        for(std::set<std::shared_ptr<Citizen>, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == manager_id)
           { 
               manager_1 = std::dynamic_pointer_cast<Manager>(*i);
               if(manager_1.get() == nullptr)
               {
                    throw ManagerDoesNotExist();
               }
               found_manager = true;
               break;
           }
        }
        if(found_manager = false)
        {
            throw ManagerDoesNotExist();
        }

        WorkPlace work_place(workplace_id,"F",0,0);

        WorkPlace tmp_work_place = *(workplaces.find(work_place)); 
        if( tmp_work_place.getId() != workplace_id) 
        {
            throw WorkplaceDoesNotExist();
        }

    //   (*(workplaces.find(work_place))).hireManager(manager_1);

      WorkPlace wp = (*(workplaces.find(work_place)));  //make sure that the managers set contains pointers to the same manager instances
      wp.hireManager(manager_1);

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

    void City::fireEmployeeAtWorkPlace(int employee_id, int manager_id, int workplace_id)
    {
        std::shared_ptr<Employee> employee_1;
        bool found_employee = false;
        for(std::set<std::shared_ptr<Citizen>, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == employee_id)
           {  
               employee_1 = std::dynamic_pointer_cast<Employee>(*i);
               if(employee_1.get() == nullptr)
               {
                   throw EmployeeDoesNotExist();
               }
               found_employee = true;
               break;
           }
        }
        if(found_employee = false)
        {
            throw EmployeeDoesNotExist();
        }
//****************************************************
        bool found_manager = false;
        for(std::set<std::shared_ptr<Citizen>, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == manager_id)
           { 
               found_manager = true;
               break;
           }
        }
        if(found_manager = false)
        {
            throw ManagerDoesNotExist();
        }

        WorkPlace work_place(workplace_id,"F",0,0);
        WorkPlace tmp_work_place = *(workplaces.find(work_place)); 
        if( tmp_work_place.getId() != workplace_id) 
        {
            throw WorkplaceDoesNotExist();
        }

        WorkPlace wp = (*(workplaces.find(work_place)));  //make sure that the managers set contains pointers to the same manager instances
        wp.fireEmployee(employee_id, manager_id);

        workplaces.erase((*(workplaces.find(work_place))));
        workplaces.insert(wp);

        
    }
    
    void City::fireManagerAtWorkPlace(int manager_id, int workplace_id)
    {
       std::shared_ptr<Manager> manager_1;
        bool found_manager = false;
        for(std::set<std::shared_ptr<Citizen>, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == manager_id)
           { 
               manager_1 = std::dynamic_pointer_cast<Manager>(*i);
               if(manager_1.get() == nullptr)
               {
                    throw ManagerDoesNotExist();
               }
               found_manager = true;
               break;
           }
        }
        if(found_manager = false)
        {
            throw ManagerDoesNotExist();
        }

        WorkPlace work_place(workplace_id,"F",0,0);
        WorkPlace tmp_work_place = *(workplaces.find(work_place)); 
        if( tmp_work_place.getId() != workplace_id) 
        {
            throw WorkplaceDoesNotExist();
        }

        WorkPlace wp = (*(workplaces.find(work_place)));  //make sure that the managers set contains pointers to the same manager instances
        wp.fireManager(manager_id);

        workplaces.erase((*(workplaces.find(work_place))));
        workplaces.insert(wp);    
    }

    int  City::getAllAboveSalary(std::ostream& stream, int salary)
    {
        int count = 0;
        std::shared_ptr<Manager> manager;
        std::shared_ptr<Employee> employee;
        for(std::set<std::shared_ptr<Citizen>, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
            employee = std::dynamic_pointer_cast<Employee>(*i);
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
                manager = std::dynamic_pointer_cast<Manager>(*i);
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
        std::shared_ptr<Employee> employee_1;
        bool found_employee = false;
        for(std::set<std::shared_ptr<Citizen>, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == employee_id1)
           {  
               employee_1 = std::dynamic_pointer_cast<Employee>(*i);
               if(employee_1.get() == nullptr)
               {
                   throw EmployeeDoesNotExist();
               }
               found_employee = true;
               break;
           }
        }
        if(found_employee = false)
        {
            throw EmployeeDoesNotExist();
        }


        std::shared_ptr<Employee> employee_2;
        found_employee = false;
        for(std::set<std::shared_ptr<Citizen>, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
           if((*i)->getId() == employee_id2)
           {  
               employee_2 = std::dynamic_pointer_cast<Employee>(*i);
               if(employee_2.get() == nullptr)
               {
                   throw EmployeeDoesNotExist();
               }
               found_employee = true;
               break;
           }
        }
        if(found_employee = false)
        {
            throw EmployeeDoesNotExist();
        }
    	
        bool working_at_the_same_place = false;
        // bool working_here = false;
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
       std::shared_ptr<Employee>employee_1; 
         for(std::set<std::shared_ptr<Citizen>, mtm::CompareCitizens>::iterator i = citizens.begin(); i !=
        citizens.end(); ++i)
        {
               employee_1 = std::dynamic_pointer_cast<Employee>(*i);
               if(employee_1.get() != nullptr)
               {
                    if(employee_1->hasSkill(skill_id)==true)//?
                    {
                        (*i)->printShort(stream) << std::endl;
                    }   
               }      
        }
    }       
}

