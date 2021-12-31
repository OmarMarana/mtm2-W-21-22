#include "City.h"
#include "exceptions.h"
#include "WorkPlace.h"
#include "Faculty.h"


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

      (*(workplaces.find(work_place))).hireManager(manager_1);
    }

    void City::fireEmployeeAtWorkPlace(int employee_id, int manager_id, int workplace_id)
    {

    }
    void City::fireManagerAtWorkPlace(int manager_id, int workplace_id)
    {

    }
    int  City::getAllAboveSalary(std::ostream& stream, int salary)
    {

    }
    bool City::isWorkingInTheSameWorkplace(int employee_id1,int employee_id2)
    {

    }
    void City::printAllEmployeesWithSkill(std::ostream& stream)
    {

    }
}